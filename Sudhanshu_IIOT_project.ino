#include <OneWire.h>
#include <DallasTemperature.h>
#include <Modbus.h>
#include <ModbusSerial.h>
const int ACT_HREG = 2;
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
const int SENSOR_HREG = 1;
ModbusSerial mb;
long ts;
/*
   The setup function. We only start the sensors here
*/
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  mb.config(&Serial, 9600, SERIAL_8N1);
  mb.setSlaveId(1);
  mb.addHreg(SENSOR_HREG);

  // Start up the library
  sensors.begin();
  sensors.setResolution(12);
  
  ts = millis();
}

/*
   Main function, get and show the temperature
*/
void loop(void)
{
    mb.task();
  int numberOfDevices = sensors.getDeviceCount();
  if (numberOfDevices > 0) {
    sensors.requestTemperatures();
    for (int i = 0; i < numberOfDevices; i++) {
      DeviceAddress tempDeviceAddress;
      sensors.getAddress(tempDeviceAddress, i);
      for (uint8_t i = 0; i < 8; i++) {
        if (tempDeviceAddress[i] < 16);
        
      }
      
      float t = sensors.getTempCByIndex(0);
      Serial.println(t);
      if (millis() > ts + 2000) {
        ts = millis();
//        Setting raw value (0-1024)
       mb.Hreg(SENSOR_HREG, t);

     }
    }
  }

  }
