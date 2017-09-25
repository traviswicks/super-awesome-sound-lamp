#include <FastLED.h>

#define NUM_LEDS 20
#define LED_PIN 6
#define MIC_PIN A0

#define MIC_MIN 615.0
#define MIC_MAX 620.0

CRGB leds[NUM_LEDS];

int mic_min = MIC_MAX, mic_max = MIC_MIN;

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB(0, 120, 0);
  }

  FastLED.show();
  delay(1000);
}

void loop() {

  int num_to_show;

  float sound_level;

  sound_level = analogRead(MIC_PIN);

  if ( sound_level < mic_min ) {
    mic_min = sound_level;
  } else if ( sound_level > mic_max ) {
    mic_max = sound_level;
  }

  num_to_show = map(sound_level, MIC_MIN, MIC_MAX, 0, NUM_LEDS);
  if (num_to_show > NUM_LEDS ) {
    num_to_show = NUM_LEDS;
  }
  setColor(CRGB(0, 0, 120), num_to_show);
  FastLED.show();


  Serial.print(sound_level);
  Serial.print(" ");
//  Serial.print(num_to_show);
//  Serial.print(" ");
  Serial.print(mic_min);
  Serial.print(" ");
  Serial.print(mic_max);
  Serial.println();

  delay(10);
}

void setColor(CRGB color, int num_leds) {
  int i;
  for(i = 0; i < num_leds; i++) {
    leds[i] = color;
  }
  for(int j = i; j < NUM_LEDS; j++) {
    leds[j] = CRGB(0, 0, 0);
  }
}



