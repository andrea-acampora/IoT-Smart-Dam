package model;

public class DataPoint {
	private float waterLevel;
	private String state;
	
	public DataPoint(float waterLevel, String state) {
		this.waterLevel = waterLevel;
		this.state = state;
	}
	
	public float getWaterLevel() {
		return waterLevel;
	}
	
	public String getState() {
		return state;
	}
}
