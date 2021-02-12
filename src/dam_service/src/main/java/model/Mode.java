package model;

import java.util.Collections;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public enum Mode {
	AUTOMATIC("automatic"), 
	MANUAL("manual");

	private String name;

	private static final Map<String, Mode> ENUM_MAP;

	Mode (String name) {
    this.name = name;
}

	public String getName() {
		return this.name;
	}

	static {
		Map<String, Mode> map = new ConcurrentHashMap<String, Mode>();
		for (Mode instance : Mode.values()) {
			map.put(instance.getName().toLowerCase(), instance);
		}
		ENUM_MAP = Collections.unmodifiableMap(map);
	}

	public static Mode get(String name) {
		return ENUM_MAP.get(name.toLowerCase());
	}
}