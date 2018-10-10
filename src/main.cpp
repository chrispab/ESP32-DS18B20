#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
// #define ONE_WIRE_BUS 2
// #define DHTPIN GPIO_NUM_25                    // LHS_P_8 what digital pin we're connected to
#define ONE_WIRE_BUS GPIO_NUM_25

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
}

void loop(void)
{
  static float lastTemp;
  float filterTemp;
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temp...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.print("DONE..");

  Serial.print("Temperature is: ");
  float temp = sensors.getTempCByIndex(0);
  Serial.print(temp); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(" ; ");
  filterTemp = temp + (lastTemp - temp)/2;
  Serial.println(filterTemp);
  lastTemp = temp;

  delay(5000);
}
