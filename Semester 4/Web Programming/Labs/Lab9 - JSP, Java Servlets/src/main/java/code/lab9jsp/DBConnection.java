package code.lab9jsp;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DBConnection {
    protected static Connection connectToDB() throws ClassNotFoundException, SQLException {
        String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        String DB_URL = "jdbc:mysql://localhost:3306/puzzledb";
        String DbUser = "root";
        String DbPassword = "";

        Class.forName(JDBC_DRIVER);
        return DriverManager.getConnection(DB_URL, DbUser, DbPassword);
    }
}
