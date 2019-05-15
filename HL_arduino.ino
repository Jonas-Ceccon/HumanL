#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(40, 6, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  // put your setup code here, to run once:

}

void loop() {
  
  
  String recv = Serial.readString();
  
  while(recv != "START"){
    Serial.write("no START marker recieved");
    String recv = Serial.readString();
  }

  delay(100);
  Serial.println("START");
  while (!Serial.available()){
    ;
  }
  
  int lengt = Serial.read();
  delay(100);
  
  Serial.write(lengt);

  while (!Serial.available()){
    ;
  }
  if(Serial.readString()=="ERROR"){
    return;
  }
  
  
}
