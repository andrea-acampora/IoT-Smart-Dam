package launcher;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import model.Dam;
import model.WaterLevel;
import serial.CommChannel;
import serial.SerialCommChannel;
import vertx.DataService;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

import controller.DamServiceController;

/*
 * Data Service as a vertx event-loop 
 */
public class RunService extends AbstractVerticle {

	private final static int PORT = 8080;
	
	public static void main(String[] args) throws Exception {
        CommChannel channel = new SerialCommChannel("/dev/ttyACM0",9600);
		WaterLevel waterLevel = new WaterLevel();
		Dam dam = new Dam();
		DamServiceController controller = new DamServiceController(waterLevel, dam, channel);
		Vertx vertx = Vertx.vertx();
		DataService service = new DataService(PORT, controller);
		vertx.deployVerticle(service);
	}
}