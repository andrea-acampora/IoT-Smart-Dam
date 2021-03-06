package db;

import java.sql.Connection;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import db.connection.DBConnection;
import db.model.Rilevazione;

public class Rilevazioni_Table {

	private DBConnection dataSource;
	private String tableName;

	public Rilevazioni_Table() {
		dataSource = new DBConnection();
		tableName = "rilevazione";
	}

	public void persist(Rilevazione rilevazione) {
		Connection connection = this.dataSource.getMySQLConnection();

		if (findByPrimaryKey(rilevazione.getId()) != null) {
			new Exception("Rilevazione exists");
			System.out.println("Errore" + "Rilevazione exists");
		}

		PreparedStatement statement = null;
		String insert = "insert into " + tableName + " (state, waterLevel) values (?,?)";
		try {
			statement = connection.prepareStatement(insert);
			statement.setString(1, rilevazione.getState());
			statement.setFloat(2, rilevazione.getWaterLevel());
			statement.executeUpdate();
		}

		catch (SQLException e) {
			new Exception(e.getMessage());
			System.out.println("Errore" + e.getMessage());
		} finally {
			try {
				if (statement != null)
					statement.close();
				if (connection != null)
					connection.close();
			} catch (SQLException e) {
				new Exception(e.getMessage());
				System.out.println("Errore" + e.getMessage());
			}
		}
	}

	public Rilevazione getLastData() {
		Rilevazione rilevazione = null;

		Connection connection = this.dataSource.getMySQLConnection();
		PreparedStatement statement = null;
		String query = "select id,waterLevel,state,DATE_FORMAT(timeStamp,'%Y-%m-%d %H:%i:%s') as timestamp from rilevazione ORDER BY timeStamp DESC LIMIT 1";
		try {
			statement = connection.prepareStatement(query);
			ResultSet result = statement.executeQuery();
			if (result.next()) {
				rilevazione = new Rilevazione();
				rilevazione.setId(result.getInt("id"));
				rilevazione.setState(result.getString("state"));
				rilevazione.setTimeStamp(result.getTimestamp("timestamp"));
				rilevazione.setWaterLevel(result.getFloat("waterLevel"));
			}
		} catch (SQLException e) {
			new Exception(e.getMessage());
			System.out.println("Errore" + e.getMessage());
		} finally {
			try {
				if (statement != null)
					statement.close();
				if (connection != null)
					connection.close();
			} catch (SQLException e) {
				new Exception(e.getMessage());
				System.out.println("Errore" + e.getMessage());
			}
		}
		return rilevazione;
	}

	public Rilevazione findByPrimaryKey(int idRilevazione) {
		Rilevazione rilevazione = null;

		Connection connection = this.dataSource.getMySQLConnection();
		PreparedStatement statement = null;
		String query = "select * from " + tableName + " where id=?";
		try {
			statement = connection.prepareStatement(query);
			statement.setInt(1, idRilevazione);
			ResultSet result = statement.executeQuery();
			if (result.next()) {
				rilevazione = new Rilevazione();
				rilevazione.setId(result.getInt("id"));
				rilevazione.setState(result.getString("state"));
				rilevazione.setTimeStamp(result.getTimestamp("timeStamp"));
				rilevazione.setWaterLevel(result.getFloat("waterLevel"));

			}
		} catch (SQLException e) {
			new Exception(e.getMessage());
			System.out.println("Errore" + e.getMessage());
		} finally {
			try {
				if (statement != null)
					statement.close();
				if (connection != null)
					connection.close();
			} catch (SQLException e) {
				new Exception(e.getMessage());
				System.out.println("Errore" + e.getMessage());
			}
		}
		return rilevazione;
	}
}
