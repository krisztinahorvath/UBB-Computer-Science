package code.lab9jsp;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class ActionsOnDatabase {
    private Connection connection;
    private int score;
    private final int rows = 3;
    private final int columns = 3;
    private final int[][] puzzle = new int[rows][columns];

    private boolean solved = false;

    ActionsOnDatabase(){
        try{
            connection = DBConnection.connectToDB();
        } catch (SQLException | ClassNotFoundException exception){
            exception.printStackTrace();
        }
    }


    public String getScore(String username){
        // to update the score if necessary
        String puzzle = getPuzzle(username);

        // get score from database
        StringBuilder res = new StringBuilder();
        try{
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM score WHERE username = ?");
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();
            if(resultSet.next()){
                score = resultSet.getInt("value");
            }
            else{
                System.out.println("no rows in score");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        if(solved)
            res.append("<p id='scoreId'>You finished the puzzle in ").append(score).append(" moves!</p>");
        else
            res.append("<p id='scoreId'>Score: ").append(score).append("</p>");

        return res.toString();
    }

    public String getPuzzle(String username){
        // get puzzle from database
        StringBuilder res = new StringBuilder();

        try{
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM puzzle where ID >= 0 AND ID < ? AND username = ?");
            preparedStatement.setInt(1, rows * columns);
            preparedStatement.setString(2, username);
            ResultSet resultSet = preparedStatement.executeQuery();
            int[] where = new int [rows * columns];
            while(resultSet.next()){
                // pos 0..8 in the grid we have the id of the photo 0..8
                where[resultSet.getInt("position")] = resultSet.getInt("id");
            }

            int count = 0;

            for(int i = 0; i < rows; i++)
                for(int j = 0; j < columns; j++){
                    puzzle[i][j] = where[count];
                    count++;
                }

            solved = true;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    // id of the photo = position => solved puzzle
                    if (puzzle[i][j] != (i * columns + j)) {
                        solved = false;
                    }
                    res.append("<img id='").append(puzzle[i][j]).append("' class='puzzle_piece' src='images/").append(puzzle[i][j]).append(".jpg'/>");
                }
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return res.toString();
    }

    public void swap(int id1, int id2, String username) throws SQLException {
        // id = nr of the photo in [0, 8]

            try{
                PreparedStatement queryPos1 = connection
                        .prepareStatement("SELECT position FROM puzzle where id = ?");
                queryPos1.setInt(1, id1);

                ResultSet resultSet1 = queryPos1.executeQuery();
                resultSet1.next();
                int pos1 = Integer.parseInt(resultSet1.getString(1));


                PreparedStatement queryPos2 = connection
                        .prepareStatement("SELECT position FROM puzzle where id = ?");
                queryPos2.setInt(1, id2);

                ResultSet resultSet2 = queryPos2.executeQuery();
                resultSet2.next();
                int pos2 = Integer.parseInt(resultSet2.getString(1));


                PreparedStatement statement = connection
                        .prepareStatement("UPDATE puzzle SET position = ? WHERE id = ? and username = ?");

                statement.setInt(1, pos1);
                statement.setInt(2, id2);
                statement.setString(3, username);

                statement.executeUpdate();

                PreparedStatement statement1 = connection
                        .prepareStatement("UPDATE puzzle SET position = ? WHERE id = ? and username = ?");

                statement1.setInt(1, pos2);
                statement1.setInt(2, id1);
                statement1.setString(3, username);

                statement1.executeUpdate();

                PreparedStatement preparedStatement3 = connection
                        .prepareStatement("UPDATE score SET value = score.value + 1 where username = ?");
                preparedStatement3.setString(1, username);
                preparedStatement3.execute();
            } catch (SQLException e){
                throw new RuntimeException(e);
            }

    }

    private List<Integer> shufflePuzzle(){
        // random photos
        List<Integer> randomPuzzle = IntStream.rangeClosed(0, rows * columns - 1).boxed().collect(Collectors.toList());
      //  List<Integer> randomPuzzle = new ArrayList<>(Arrays.asList(1, 0, 2, 3, 4, 5, 6, 7, 8));
        // shuffle
        Collections.shuffle(randomPuzzle);
        return randomPuzzle;
    }

    public void resetPuzzle(String username){
        List<Integer> randomPuzzle = shufflePuzzle();

        try{
            // clear the tables in the database

            PreparedStatement preparedStatement1 = connection.prepareStatement("DELETE FROM puzzle WHERE username = ?");
            preparedStatement1.setString(1, username);
            preparedStatement1.execute();

            PreparedStatement preparedStatement2 = connection.prepareStatement("DELETE FROM score WHERE username = ?");
            preparedStatement2.setString(1, username);
            preparedStatement2.execute();

            PreparedStatement preparedStatement3 = connection.prepareStatement("INSERT INTO score VALUES (0, ?)");
            preparedStatement3.setString(1, username);
            preparedStatement3.execute();

        } catch(SQLException e){
            e.printStackTrace();
        }

        try{
            // add puzzle pieces
            for(int i = 0; i < rows * columns; i++){
                PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO puzzle (ID, position, username) VALUES (?, ?, ?)");
                preparedStatement.setInt(1, i);
                preparedStatement.setInt(2, randomPuzzle.get(i));
                preparedStatement.setString(3, username);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
