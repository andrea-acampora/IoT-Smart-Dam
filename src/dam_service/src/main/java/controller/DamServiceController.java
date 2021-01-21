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
	private CommChannel channel;
	private Rilevazioni_Table rilevazioni;
	private final static int DELTA_L = 4;
	
	public DamServiceController(final Rilevazioni_Table rilevazioni, final CommChannel channel) {
		this.dam = new Dam();
		this.mode = Mode.AUTOMATIC;
		this.channel = channel;
		this.rilevazioni = rilevazioni;
	}
	
	public void processData(final DataPoint data) {
		Rilevazione rilevazione = new Rilevazione();
		rilevazione.setWaterLevel(data.getValue());
		rilevazione.setState(data.getState());
		System.out.println("Water Level: " + rilevazione.getWaterLevel() + " - State : " + rilevazione.getState());
		if(rilevazione.getState()=="ALARM" && this.mode==Mode.AUTOMATIC) {
			openDam(rilevazione);
			this.channel.sendMsg(String.valueOf(this.dam.getDamOpeningLevel()));
		}
		rilevazione.setModality(String.valueOf(this.mode));
		rilevazione.setTimeStamp(new Timestamp(System.currentTimeMillis()));
		this.rilevazioni.persist(rilevazione);
	}
	
	private void openDam(Rilevazione rilevazione) {
		System.out.println("OPENING DAM....");
		float level = rilevazione.getWaterLevel();
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
}
