package model;

import java.util.Collections;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public enum State {
	NORMAL("NORMAL"), 
	PRE_ALARM("PRE_ALARM"), 
	ALARM("ALARM"); 

    private String name;

    private static final Map<String,State> ENUM_MAP;

    State (String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    static {
        Map<String,State> map = new ConcurrentHashMap<String, State>();
        for (State instance : State.values()) {
            map.put(instance.getName().toLowerCase(),instance);
        }
        ENUM_MAP = Collections.unmodifiableMap(map);
    }

    public static State get (String name) {
        return ENUM_MAP.get(name.toLowerCase());
    }
}