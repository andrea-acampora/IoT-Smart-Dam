package model;

public class DataPoint {
	private float value;
	private String state;
	
	public DataPoint(float value, String state) {
		this.value = value;
		this.state = state;
	}
	
	public float getValue() {
		return value;
	}
	
	public String getState() {
		return state;
	}
}
