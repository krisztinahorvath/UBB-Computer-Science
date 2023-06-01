package code.lab9jsp;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Stream;

@WebServlet(name="PuzzleServlet", urlPatterns = "/puzzle")
public class PuzzleServlet extends HttpServlet {
    HttpSession currentSession;
    String username;

    public void writePuzzle(PrintWriter printWriter, String puzzleHtml, String scoreHtml){
        printWriter.println("<html>");
        printWriter.println("<head>");
        printWriter.println("<title>Puzzle</title>");
        printWriter.println("<link rel='stylesheet' type='text/css' href='style.css'>");
        printWriter.println("<script src=\"https://code.jquery.com/jquery-3.6.0.min.js\"></script>");
        printWriter.println("<script src=\"https://code.jquery.com/ui/1.12.1/jquery-ui.min.js\" integrity=\"sha256-VazP97ZCwtekAsvgPBSUwPFKdrwD3unUfSGVYrahUqU=\" crossorigin=\"anonymous\"></script>");
        printWriter.println("<script src=\"puzzle.js\" defer></script> ");
        printWriter.println("</head>");
        printWriter.println("<body>");
        printWriter.println("<div id='score'>");
        printWriter.println(scoreHtml);
        printWriter.println("</div>");
        printWriter.println("<div id='puzzle'>");
        printWriter.println(puzzleHtml);
        printWriter.println("</div>");
        printWriter.println("<div id='status'>");
        printWriter.println("</div>");
        printWriter.println("</body>");
        printWriter.println("</html>");
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        currentSession = request.getSession();
        username = (String) currentSession.getAttribute("username");

        response.setContentType("text/html");
        ActionsOnDatabase db = new ActionsOnDatabase();
        writePuzzle(response.getWriter(), db.getPuzzle(username), db.getScore(username));
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        currentSession = request.getSession();

        response.setContentType("text/html");
        ActionsOnDatabase db = new ActionsOnDatabase();
        db.resetPuzzle(username);
        writePuzzle(response.getWriter(), db.getPuzzle(username), db.getScore(username));
    }

    public void doPut(HttpServletRequest request, HttpServletResponse response) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(request.getInputStream()));

        String data = bufferedReader.readLine();

        Map<String, String> params = new HashMap<>();

        Stream.of(data.split("&", 2)).forEach((par) -> {
            String[] arr = par.split("=", 2);
            params.put(arr[0], arr[1]);
        });
        int id1 = Integer.parseInt(params.get("id1"));
        int id2 = Integer.parseInt(params.get("id2"));

        ActionsOnDatabase db = new ActionsOnDatabase();
        try {
            db.swap(id1, id2, username);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        String scoreHtml = db.getScore(username);
        response.setContentType("text/html");
        response.getWriter().write(scoreHtml);
    }
}
