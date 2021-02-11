package controller;

import java.sql.Timestamp;

import db.Rilevazioni_Table;
import db.model.Rilevazione;
import model.Dam;
import model.DataPoint;
import model.Mode;
import serial.CommChannel;
import java.sql.Date;

public class DamServiceController {

	private Mode mode;
	private Dam dam;
	private String state;
	private CommChannel channel;
	private Rilevazioni_Table rilevazioni;
	private final static int DELTA_L = 4;
	
	public DamServiceController(final Rilevazioni_Table rilevazioni, final CommChannel channel) {
		this.dam = new Dam();
		this.mode = Mode.AUTOMATIC;
		this.channel = channel;
		this.rilevazioni = rilevazioni;
		this.state ="NORMAL";
	}
	
	public void processData(final DataPoint data) {
		Rilevazione rilevazione = new Rilevazione();
		rilevazione.setWaterLevel(data.getValue());
		rilevazione.setState(data.getState());
		if(this.state!=data.getState()) {
			if(data.getState()=="PRE_ALARM") {
				this.channel.sendMsg("STOPF");
			}else if(data.getState()=="ALARM") {
				this.channel.sendMsg("STARTF");
			}
		}
		this.state = data.getState();
		//System.out.println("Water Level: " + rilevazione.getWaterLevel() + " - State : " + rilevazione.getState());
		if(rilevazione.getState().equals("ALARM") && this.mode==Mode.AUTOMATIC) {
			openDam(rilevazione);
			this.channel.sendMsg(String.valueOf(this.dam.getDamOpeningLevel()));
		}
		rilevazione.setModality(String.valueOf(this.mode));
		rilevazione.setTimeStamp(new Timestamp(System.currentTimeMillis()));
		rilevazione.setOpening(this.dam.getDamOpeningLevel());
		if(data.getState()!="NORMAL") {
			this.rilevazioni.persist(rilevazione);
		}
	}
	
	public Rilevazione getLastData() {
		return this.rilevazioni.getLastData(); 
	}
	
	public String getSystemState() {
		return this.state;
	}
	
	private void openDam(Rilevazione rilevazione) {
		Float level = rilevazione.getWaterLevel();
		if(level < 460) {
			rilevazione.setState("PRE_ALARM");
			dam.setDamOpeningLevel(0);
		}else if(level >=460 && level <460+DELTA_L) {
			dam.setDamOpeningLevel(20);
		}else if(level >=460+DELTA_L && level <460+2*DELTA_L) {
			dam.setDamOpeningLevel(40);
		}else if(level >=460+2*DELTA_L && level <460+3*DELTA_L) {
			dam.setDamOpeningLevel(60);
		}else if(level >=460+3*DELTA_L && level <460+4*DELTA_L) {
			dam.setDamOpeningLevel(80);
		}else if(level >=460+4*DELTA_L) {
			dam.setDamOpeningLevel(100);
		}
	}
	
	public Mode getMode() {
		return this.mode;
	}

	public void setMode(Mode mode) {
		this.mode = mode;
	}
}
