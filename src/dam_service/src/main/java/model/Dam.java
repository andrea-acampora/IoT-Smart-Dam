package model;

public class Dam {

	private final static int DELTA_L = 4;
	private int damOpeningLevel;

	public Dam() {
		this.damOpeningLevel = 0;
	}

	public int getDamOpeningLevel() {
		return damOpeningLevel;
	}

	public void setDamOpeningLevel(int damOpeningLevel) {
		this.damOpeningLevel = damOpeningLevel;
	}

	public void openDam(float level) {
		if (level >= 460 && level < 460 + DELTA_L) {
			this.setDamOpeningLevel(20);
		} else if (level >= 460 + DELTA_L && level < 460 + 2 * DELTA_L) {
			this.setDamOpeningLevel(40);
		} else if (level >= 460 + 2 * DELTA_L && level < 460 + 3 * DELTA_L) {
			this.setDamOpeningLevel(60);
		} else if (level >= 460 + 3 * DELTA_L && level < 460 + 4 * DELTA_L) {
			this.setDamOpeningLevel(80);
		} else if (level >= 460 + 4 * DELTA_L) {
			this.setDamOpeningLevel(100);
		}
	}
	
	public void closeDam() {
		this.setDamOpeningLevel(0);
	}
	
	public boolean isDamOpen() {
		return this.damOpeningLevel > 0; 
	}

}
