package db.model;

import java.sql.Timestamp;

public class Rilevazione {

    private int id;
    private String state;
    private String modality;
    private Timestamp timeStamp;
    private int opening;
    
    private float waterLevel; 

    public float getWaterLevel() {
        return waterLevel;
    }

    public void setWaterLevel(float waterLevel) {
        this.waterLevel = waterLevel;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setState(String state) {
        this.state = state;
    }

    public void setModality(String modality) {
        this.modality = modality;
    }

    public void setTimeStamp(Timestamp timeStamp) {
        this.timeStamp = timeStamp;
    }

    public void setOpening(int value) {
    	this.opening = value;
    }
    public int getId() {
        return id;
    }

    public String getState() {
        return state;
    }

    public String getModality() {
        return modality;
    }

    public Timestamp getTimeStamp() {
        return timeStamp;
    }
    
    public int getOpening() {
    	return this.opening;
    }

}
