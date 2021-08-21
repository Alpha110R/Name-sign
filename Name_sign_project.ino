#include <HCSR04.h>
#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    30
#define BRIGHTNESS  200
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
UltraSonicDistanceSensor distanceSensor(3, 2);  // Initialize sensor that uses digital pins 13 and 12.

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int moneRandomLight =2;



void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    
}


void loop () {
    double distance = distanceSensor.measureDistanceCm();
    int analogValue = analogRead(A0);

    
    Serial.print("distance: ");
    Serial.println(distance);

  Serial.print("Analog reading = ");
  Serial.println(analogValue); 

  if(distance < 20){
    randomLight();
  }

  if (analogValue < 100) {
    Serial.println(" - Dark");
    FastLED.setBrightness(20);
    
  } else if (analogValue < 300) {
    Serial.println(" - Dim");
    FastLED.setBrightness(80);
    
  } else{
    Serial.println(" - Light");
    FastLED.setBrightness(255);
  }
  FillLEDsFromPaletteColors(0);
  FastLED.show();

  delay(300);
    
}


void FillLEDsFromPaletteColors(int colorIndex)
{
    uint8_t brightness = 200;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    }
}

void randomLight(){
  if(moneRandomLight ==8){
    moneRandomLight=2;
  }
  switch(moneRandomLight){
    case 2:
          fill_solid( currentPalette, 16, CRGB(255,0,0));
          break;
    case 3:
          fill_solid( currentPalette, 16, CRGB(0, 255, 0));
          break;
    case 4:
          fill_solid( currentPalette, 16, CRGB(255, 165, 0));
          break;
    case 5:
          fill_solid( currentPalette, 16, CRGB(106, 90, 205));
          break;
    case 6:
          fill_solid( currentPalette, 16, CRGB(255, 0, 255));
          break;
    case 7:
          fill_solid( currentPalette, 16, CRGB(0, 0, 255));
          break;
  }
  moneRandomLight +=1;
}
