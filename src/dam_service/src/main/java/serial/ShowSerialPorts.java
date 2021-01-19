package serial;

import jssc.*;

public class ShowSerialPorts {
	
    public static void main(String[] args) {
    	String[] portNames = SerialPortList.getPortNames();
		for (int i = 0; i < portNames.length; i++){
		    System.out.println(portNames[i]);
		}
    	//System.out.println(SerialPortList.getPortNames()[0]);
	}
}
