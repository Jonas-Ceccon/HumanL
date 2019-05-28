#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define  PIN 6
#define PIXELS 40
int line_p = 0;
int column_p = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(40, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  Serial.begin(9600);
}

void loop()
{
    if (Serial.available())
    {
        String a = Serial.readString();
        while(!Serial.available()){
          ;
        }
        String R = Serial.readString();
        while(!Serial.available()){
          ;
        }
        String G = Serial.readString();
        while(!Serial.available()){
          ;
        }
        String B = Serial.readString();
        
        Serial.print("Received Values: ");
        Serial.println(a);
        int n = a.toInt();
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
            delay(1000);
        }
    }
}

int select_pixel(int pos){
  pixels.setPixelColor(pos, pixels.Color(30, 30, 30));
  pixels.show();
  return pos;
}
