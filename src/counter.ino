//network config
#include "config.h"
AdafruitIO_Feed *input = io.feed("state");

//analog acc reqs
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
//for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
//for hardware & software SPI
#define LIS3DH_CS 10
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif
//variables for three axis
int counter; int state;
int ax; int ay; int az;
int bx; int by; int bz;
int nAn;


void setup() {
  // start the serial connection
  #ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif

  Serial.begin(115200);
  while (!Serial);

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
      //connect to net
  Serial.println("Connecting to Adafruit IO");
  io.connect();
  Serial.println();
    // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println(io.statusText());
  //setting range for sensor, reccomend 2G at first
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");
}

void loop(){
  io.run();

  nAn = 200;
  while (counter <= 10){
  // grab the one state of the acc
    lis.read();
    ax = lis.x; ay = lis.y; az = lis.z;
  //get new number to be compared against
    delay(250);
    lis.read();
    bx = lis.x; by = lis.y; bz = lis.z;
   //check to see if movement has stopped
    if (Movement(ax, bx) && Movement(ay,by) && Movement(az, bz)){
      counter = 0;
      //Serial.println("Counter: ");
      Serial.println("Counter reset");
      SaveState(0);
      }
    else{
      counter++;
      //std::string count = "Counter: " + counter;
      Serial.println("Counter: " + counter);
      //Serial.println(io);
      }
     delay(700);
    }
  Serial.println("The Laundry is Done!!!");
  SaveState(1);
}


void SaveState(int state){
  input->save(state);

}

bool Movement(int r1, int r2){
  return (abs(r2 -r1) <= nAn);
}
