package model;


public class DamSystem {
	private Mode mode;
	private State state;
	private Dam dam;
	private boolean stateChanged;

	public DamSystem() {
		super();
		this.mode = Mode.AUTOMATIC;
		this.state = State.NORMAL;
		this.dam = new Dam();
	}

	public String getMode() {
		return mode.getName();
	}

	public void setMode(Mode mode) {
		this.mode = mode;
	}

	public String getState() {
		return state.getName();
	}

	public void setState(State state) {
		this.state = state;
	}

	public boolean isStateChanged() {
		return this.stateChanged;
	}

	public void setNewDetection(DataPoint detection) {
		//this.setMode(Mode.get(detection.getModality()));
		State oldState = State.get(this.getState());
		this.setState(State.get(detection.getState()));
		this.stateChanged = !(this.state == oldState);

		if (this.state == State.ALARM && this.mode == Mode.AUTOMATIC) {
			this.dam.openDam(detection.getWaterLevel());
		}else if(this.state == State.NORMAL || this.state == State.PRE_ALARM) {
			this.dam.closeDam();
		}
	}

	public void openDam(int damOpeningLevel) {
		if (this.mode == Mode.MANUAL) {
			this.dam.setDamOpeningLevel(damOpeningLevel);
		}
	}
	
	public boolean isDamOpen() {
		return this.dam.isDamOpen(); 
	}
	
	public int getDamOpeningLevel() {
		return this.dam.getDamOpeningLevel(); 
	}
	
	public void setMode(String mode) {
		this.mode = Mode.get(mode); 
	}
}
