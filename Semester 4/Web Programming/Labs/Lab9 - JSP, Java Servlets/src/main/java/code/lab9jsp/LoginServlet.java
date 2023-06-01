package code.lab9jsp;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.*;

@WebServlet(name = "LoginServlet", urlPatterns = "/login")
public class LoginServlet extends HttpServlet {
    private boolean validUser(String username, String password, Connection connection) throws SQLException {
        Statement stmt = connection.createStatement();
        String sql = "SELECT * FROM users where username = ? and password = ?";

        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        preparedStatement.setString(1, username);
        preparedStatement.setString(2, password);

        ResultSet resultSet = preparedStatement.executeQuery();

        if(!resultSet.next()) {
            return false;
        }

        preparedStatement.close();
        resultSet.close();
        stmt.close();
        connection.close();

        return true;
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        RequestDispatcher rd = null;

        try {
            Connection connection = DBConnection.connectToDB();
            if(validUser(username, password, connection)){
                HttpSession session = request.getSession();
                session.setAttribute("logged", "true");
                session.setAttribute("username", username);
                //response.sendRedirect("puzzle.jsp");
                rd = request.getRequestDispatcher("puzzle.jsp");
                rd.forward(request, response);
            }
            else
                response.sendRedirect("loginFailed.jsp");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
