package controller;

import java.sql.Timestamp;

import db.Rilevazioni_Table;
import db.model.Rilevazione;
import model.DamSystem;
import model.DataPoint;
import model.Mode;
import model.State;
import serial.CommChannel;

public class DamServiceController {

	private CommChannel channel;
	private Rilevazioni_Table rilevazioni;
	private DamSystem damSystem;

	public DamServiceController(final Rilevazioni_Table rilevazioni, final CommChannel channel, DamSystem damSystem) {
		this.channel = channel;
		this.rilevazioni = rilevazioni;
		this.damSystem = damSystem;
	}

	public void processData(final DataPoint data) {
		this.comunicateNewDetection(data); 
		Rilevazione rilevazione = new Rilevazione();
		rilevazione.setWaterLevel(data.getWaterLevel());
		rilevazione.setState(data.getState());
		rilevazione.setTimeStamp(new Timestamp(System.currentTimeMillis()));

		if (this.checkIfStateChanged()) {
			if (damSystem.getState() == State.PRE_ALARM.getName() || damSystem.getState() == State.NORMAL.getName()) {
				this.channel.sendMsg("P=0F");
				this.channel.sendMsg("STOPF");
			} else if (damSystem.getState() == State.ALARM.getName()) {
				this.channel.sendMsg("STARTF");
			}
		}

		if (this.checkIfDamIsOpen() && this.damSystem.getMode()==Mode.AUTOMATIC.getName()) {
			this.channel.sendMsg("P="+String.valueOf(this.damSystem.getDamOpeningLevel())+"F");
		}

		if (damSystem.getState() != State.NORMAL.getName()) {
			this.rilevazioni.persist(rilevazione);
		}
	}

	public Rilevazione getLastData() {
		return this.rilevazioni.getLastData();
	}

	public boolean checkIfDamIsOpen() {
		return damSystem.isDamOpen();
	}

	public void comunicateNewDetection(DataPoint detection) {
		this.damSystem.setNewDetection(detection);
	}

	public boolean checkIfStateChanged() {
		return this.damSystem.isStateChanged();
	}

	public String getSystemState() {
		return this.damSystem.getState(); 
	}

	public String getMode() {
		return this.damSystem.getMode(); 
	}

	public void setMode(Mode mode) {
		this.damSystem.setMode(mode);
		this.channel.sendMsg("M="+mode.getName()+"F");
	}
	
	public void setDamOpeningLevel(String value) {
		this.damSystem.setDamOpeningLevel(Integer.valueOf(value));
	}
	
	public int getDamOpeningLevel() {
		return this.damSystem.getDamOpeningLevel();
	}
}
