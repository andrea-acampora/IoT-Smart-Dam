package db.model;

import java.sql.Timestamp;


import model.Mode;
import model.State;

public class Rilevazione {

    private int id;
    private State state;
    private Mode modality;
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
        this.state = State.get(state);
    }

    public void setModality(String modality) {
        this.modality = Mode.get(modality);
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
        return state.getName();
    }

    public String getModality() {
        return modality.getName();
    }

    public Timestamp getTimeStamp() {
        return timeStamp;
    }
    
    public int getOpening() {
    	return this.opening;
    }

}
