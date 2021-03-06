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
int io; int state;
int ax; int ay; int az;
int bx; int by; int bz;
int nAn; int fox; int rabbit; int duck; int dinner;


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
  io = 0;
  while (io < 10){
  // grab the one state of the acc
    lis.read();
    state = 0;
    //input ->save(state);
    ax = lis.x; ay = lis.y; az = lis.z;

  //get new number to be compared against
    delay(250);
    lis.read();
    bx = lis.x; by = lis.y; bz = lis.z;

    //FOX FOX FOX FOX FOX FOX FOX FOX FOX FOX FOX FOX
    if(abs(bx - ax) <= nAn){
      fox = 0; //not moving
      }
    else{
      fox = 1; //still moving
    }
    //DUCK DUCK DUCK DUCK DUCK DUCK DUCK DUCK DUCK DUCK
    if(abs(bx - ax) <= nAn){
      fox = 0; //not moving
      }
    else{
      fox = 1; //still moving
    }
    //RABBIT RABBIT RABBIT RABBIT RABBIT RABBIT RABBIT
    if(abs(bx - ax) <= nAn){
      fox = 0; //not moving
      }
    else{
      fox = 1; //still moving
    }
    dinner = fox + rabbit + duck;
   //DINNER DINNER DINNER DINNER DINNER DINNER DINNER DINNER DINNER DINNER
    if (dinner > 0){
      io =0;
//      Serial.println("Counter: ");
      Serial.println(io);
      }
    else{
      io++;
//      Serial.println("Counter: ");
      Serial.println(io);
      }
     io = abs(io);
     delay(500);
    }

  if(io >= 10){
    Serial.println("The Laundry is Done!!!");
    SaveState(1);
    return;
  }
  delay(1000);
  SaveState(0);
}

void SaveState(int state){
  input->save(state);

}

Boolean Movement(int r1, int r2){
  return (abs(r2 -r1) <= nAn);
}
