#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define  PIN 6
#define PIXELS 40
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800); // definition of our matrix, if you are using another type of board, please edit this part

void setup() {
  pixels.begin();
  Serial.begin(9600);
}


void loop(){
    if (Serial.available()){ //if we recieve something
      while(true){ //Python will take some breaks between each sent data, so we while true with a break in order to avoid loop exit before we get everything
        while(!Serial.available()){//wait until we recieve something
          ;
        }
        String first = Serial.readString(); //this should be the position of a pixel, BUT...
        if(first == "END"){//...if we recieve the END marker...
          myFile = SD.open("map.txt", FILE_READ);
          ReadFile(); //...display the pixels position and colors now stored in the .txt file...
          break; // ...and get out of the loop
        }
        while(!Serial.available()){ //Wait For Serial Input
          ;
        }
        String R = Serial.readString(); //we should recieve the first color as a string
        while(!Serial.available()){ //WFSI
          ;
        }
        String G = Serial.readString(); //and now the second color
        while(!Serial.available()){ //WFSI
          ;
        }
        String B = Serial.readString(); // and then the third
        myFile = SD.open("map.txt", FILE_WRITE); // remember that the file should be already existent in order to be written on
        WriteFile(first, R, G, B); // we write the data into the SD CARD
        myFile.close();
        
        /*Serial.print("Received Values: ");
        Serial.println(first);
        int n = first.toInt();
        Serial.println(R);
        int r = R.toInt();
        Serial.println(G);
        int g = G.toInt();
        Serial.println(B);
        int b = B.toInt();
        if ((n >= 0) && (n <= PIXELS))
        {
            pixels.setPixelColor(n, r, g, b);
            pixels.show();
        }*/// debug function
      }
    ReadFile(); //in case we don't recieve anything, read the existent file
    }
  }
/*int select_pixel(int pos){
  pixels.setPixelColor(pos, pixels.Color(30, 30, 30));
  pixels.show();
  return pos;
}*/// debug function

void WriteFile(String n, String R, String G, String B){ //function that writes a file in the SD card
  myFile.print(n); 
  myFile.print("-");
  myFile.print(R);
  myFile.print("-");
  myFile.print(G);
  myFile.print("-");
  myFile.print(B);
  myFile.print("-"); //it prints every recieved number formatted in a single line in order to be easily read by the ReadFile function
}
void ReadFile(){ //function that reads a written file in the SD card
  while(myFile.available()){ // While there is some unread data in the .txt file
    
    String nread = myFile.readStringUntil("\n");
    String Rread = myFile.readStringUntil("\n");
    String Gread = myFile.readStringUntil("\n");
    String Bread = myFile.readStringUntil("\n"); // we read the four first data
    
    String nedit = nread.replace("-","");
    String Redit = Rread.replace("-","");
    String Gedit = Gread.replace("-","");
    String Bedit = Bread.replace("-",""); // we remove the formatting, for they can be convertible into int
    
    int nint = nedit.toInt();
    int Rint = Redit.toInt();
    int Gint = Gedit.toInt();
    int Bint = Bedit.toInt(); //we convert them into int
    pixels.setPixelColor(nint, Rint,Gint,Bint); //we select our pixel
    pixels.show()// we lit it up
  }
}
   
