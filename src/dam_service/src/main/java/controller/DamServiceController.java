package controller;

import model.Dam;
import model.DataPoint;
import model.Mode;
import model.WaterLevel;
import serial.CommChannel;

public class DamServiceController {

	private WaterLevel waterLevel;
	private Mode mode;
	private Dam dam;
	private CommChannel channel;
	private final static int DELTA_L = 4;
	
	public DamServiceController(final WaterLevel waterLevel, final Dam dam, final CommChannel channel) {
		this.waterLevel = waterLevel;
		this.dam = dam;
		this.mode = Mode.AUTOMATIC;
		this.channel = channel;
	}
	
	public void processData(final DataPoint data) {
		float waterLevel = data.getValue();
		String state = data.getState();
		System.out.println("Water Level: " + waterLevel + " - State : " + state);
		this.addData(waterLevel, state);
		if(state=="ALARM" && this.mode==Mode.AUTOMATIC) {
			openDam();
			this.channel.sendMsg(String.valueOf(this.dam.getDamOpeningLevel()));
		}
		//PUSH TO DB
	}
	
	private void openDam() {
		System.out.println("OPENING DAM....");
		float level = this.waterLevel.getWaterLevel();
		if(level < 460) {
			this.waterLevel.setState("NORMAL");
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

	private void addData(float waterLevel, String state) {
		this.waterLevel.setWaterLevel(waterLevel);
		this.waterLevel.setState(state);
	}
	
}
