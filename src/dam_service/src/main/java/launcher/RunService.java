package launcher;

import io.vertx.core.AbstractVerticle;

import io.vertx.core.Vertx;
import model.DamSystem;
import serial.CommChannel;
import serial.SerialCommChannel;
import vertx.DataService;

import controller.DamServiceController;
import db.Rilevazioni_Table;

/*
 * Data Service as a vertx event-loop 
 */
public class RunService extends AbstractVerticle {

	private final static int PORT = 8080;
	
	public static void main(String[] args) throws Exception {
        CommChannel channel = new SerialCommChannel("/dev/ttyACM2",9600);
		Rilevazioni_Table rilevazioni = new Rilevazioni_Table();
		DamSystem damSystem = new DamSystem(); 
		DamServiceController controller = new DamServiceController(rilevazioni,channel, damSystem);
		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(PORT, controller);
		vertx.deployVerticle(service);
	}
}