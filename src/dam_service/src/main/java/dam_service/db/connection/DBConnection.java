package db.connection;
import java.sql.*;

public class DBConnection {
    
    public Connection getMySQLConnection()  {
        
       String driver = "com.mysql.jdbc.Driver";
       String dbUri = "jdbc:mysql://localhost:3306/SmartDam?characterEncoding=latin1";
       String userName = "root";
       String password = "";
        
       Connection connection = null;
        try {
            System.out.println("DataSource.getConnection() driver = "+driver);
            Class.forName(driver);
            System.out.println("DataSource.getConnection() dbUri = "+dbUri);
            connection = DriverManager.getConnection(dbUri, userName, password);
        }
        catch (ClassNotFoundException e) {
            new Exception(e.getMessage());
            System.out.println("Errore 1"+ e.getMessage());
        }
        catch(SQLException e) {
            new Exception(e.getMessage());
            System.out.println("Errore 2"+ e.getMessage());
        }
        return connection;
    }
}
