package vertx;

import io.vertx.core.AbstractVerticle;

import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.Json;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import model.DataPoint;
import model.Mode;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

import controller.DamServiceController;
import db.model.Rilevazione;

/*
 * Data Service as a vertx event-loop 
 */
public class DataService extends AbstractVerticle {

	private int port;
	private DamServiceController controller;

	public DataService(final int port, final DamServiceController controller) {
		this.port = port;
		this.controller = controller;
	}

	@Override
	public void start() {
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.post("/api/data").handler(this::handleAddNewData);
		router.post("/api/mode").handler(this::handleChangeMode);
		router.post("/api/openingDam").handler(this::handleDamOpening);
		router.get("/api/data").handler(this::handleGetData);
		vertx.createHttpServer().requestHandler(router).listen(port);

		log("Service ready.");
	}

	private void handleAddNewData(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
			float value = res.getFloat("value");
			String state = res.getString("state");
			this.controller.processData(new DataPoint(value, state));
			response.setStatusCode(200).end();
		}
	}

	private void handleChangeMode(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
			if(res.getString("mode").equals("manual")) {
				this.controller.setMode(Mode.MANUAL);
			}else if(res.getString("mode").equals("automatic")) {
				this.controller.setMode(Mode.AUTOMATIC);
			}
			response.setStatusCode(200).end();
		}
	}
	
	private void handleDamOpening(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
				this.controller.setDamOpeningLevel(res.getString("opening"));
			}
			response.setStatusCode(200).end();
		}
	
	private void handleGetData(RoutingContext routingContext) {
		Rilevazione rilevazione = this.controller.getLastData();
		JsonObject data = new JsonObject();
		data.put("state", this.controller.getSystemState());

		if(this.controller.getSystemState().equals("PRE_ALARM")) {
			data.put("value", rilevazione.getWaterLevel());
			data.put("timeStamp", String.valueOf(rilevazione.getTimeStamp()));
		}else  if(this.controller.getSystemState().equals("ALARM")) {
			if(this.controller.getMode()==Mode.MANUAL.getName()) {
				data.put("modality", "MANUAL");
			}
			data.put("value", rilevazione.getWaterLevel());
			data.put("timeStamp", String.valueOf(rilevazione.getTimeStamp()));
			data.put("opening", String.valueOf(this.controller.getDamOpeningLevel()));
			}
		routingContext.response().putHeader("content-type", "application/json")
								.putHeader("Access-Control-Allow-Origin","*")
								.putHeader("Access-Control-Allow-Methods", "POST,GET,PUT,DELETE")
								.end(data.encodePrettily());

	}

	private void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] " + msg);
	}

	public DamServiceController getDamServiceController() {
		return controller;
	}
}