#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(40, 6, NEO_GRB + NEO_KHZ800); //declaration of the variable that will contain the function called when we wnt to change a pixel's color


void setup() {
  Serial.begin(9600); //if you want to change this, do not forget to change it on Python
  // put your setup code here, to run once:

}

void loop() {
  while(!Serial){ //do nothing until a serial port is connected (i'll put the code that runs an already existent map for the pixel matrix before this line)
    ;
  }
  waitinput(); //wait for serial input
  while(Serial.readString() != "START"){//if the serial input isn't the SRART marker from the pthon program, then do nothing
    delay(100); //wait for python to be in a 'recieving mood'
    Serial.write("no START marker recieved"); //send the error code to python
    waitinput(); //wait for another serial input
  }

  delay(100); //wait for python to set itself back in order to recieve data
  Serial.println("START"); //tell python that the START marker was recieved
  waitinput(); //wait for python's input
  
  int lengt = Serial.read(); //this variable sent by python is the total ammount of data that will be sent through serial port (/!\ including the two markers, START and END /!\)
  delay(100);//wait for python
  
  Serial.write(lengt); //tell python which value was recieved
  waitinput();//wait for python to compare it with his own value
  if(Serial.readString()=="ERROR"){ //if Python and Arduino doesn't have the same value, Python will return an error, and the program will restart
    return;
  }
  
  
}

void waitinput(){ //definition of the function that waits for serial inputs..
  while (!Serial.available()){ //..yup, that's just what I said
    ;
  }
}
