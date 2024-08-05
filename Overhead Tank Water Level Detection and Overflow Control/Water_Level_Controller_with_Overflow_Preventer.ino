 
#include <FastLED.h>
#define NUM_LEDS 7
#define LED_PIN 5
CRGB leds[NUM_LEDS];

const int dataPin = 12;   /* Q7 */
const int clockPin = 13;  /* CP */
const int latchPin = 14;  /* PL */

const int numBits = 8;   /* Set to 8 * number of shift registers */
int a[8];
int BinaryToDecimal(int a[]);

int check;

int relayPin = 4;
int buzzer = 16;

void setup() {
  Serial.begin(115200);

  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(60);

  pinMode(relayPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Step 1: Sample
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);

  // Step 2: Shift
  int j=0;
  Serial.print("Bits: ");
  for (int i = 0; i < numBits; i++) {
    int bit = digitalRead(dataPin);
    if (bit == HIGH) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
    a[j]=bit;
    j++;
    
    digitalWrite(clockPin, HIGH); // Shift out the next bit
    digitalWrite(clockPin, LOW);
  }
  BinaryToDecimal(a);

  Serial.println();

  if((check == 64)||(check == 65)||(check == 67)||(check == 71)||(check == 79)||(check == 95)||(check == 127)){
    leds[6] = CRGB::Blue;
    FastLED.show();
    delay(200);
    leds[6] = CRGB::Black;
    FastLED.show();
    delay(200);
  }

 
}
int BinaryToDecimal(int a[])
{
  int sum=0;
  int mul=128;
  for(int i=0;i<8;i++)
  {
    if(a[i]==1)
    {
      sum+=mul;
    }
    mul/=2;
  }
  Serial.println();
  Serial.print("DEC: ");
  Serial.print(sum);
  check = sum;
  switch(sum)
  {
    case 1:
    case 65:
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Black;
      leds[2] = CRGB::Black;
      leds[3] = CRGB::Black;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
      FastLED.show();
    break;
    case 3:
    case 67:
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Black;
      leds[3] = CRGB::Black;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
      FastLED.show();
    break;
    case 7:
    case 71:
      leds[0] = CRGB::Yellow;
      leds[1] = CRGB::Yellow;
      leds[2] = CRGB::Yellow;
      leds[3] = CRGB::Black;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
      FastLED.show();
    break;
    case 15:
    case 79:
      leds[0] = CRGB::Yellow;
      leds[1] = CRGB::Yellow;
      leds[2] = CRGB::Yellow;
      leds[3] = CRGB::Yellow;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
      FastLED.show();
      digitalWrite(relayPin, LOW);
      digitalWrite(buzzer, LOW);
   break;
    case 31:
    case 95:
      leds[0] = CRGB::Green;
      leds[1] = CRGB::Green;
      leds[2] = CRGB::Green;
      leds[3] = CRGB::Green;
      leds[4] = CRGB::Green;
      leds[5] = CRGB::Black;
      FastLED.show();
    break;
    case 63:
    case 127:
      leds[0] = CRGB::Green;
      leds[1] = CRGB::Green;
      leds[2] = CRGB::Green;
      leds[3] = CRGB::Green;
      leds[4] = CRGB::Green;
      leds[5] = CRGB::Green;
      FastLED.show();
      digitalWrite(relayPin, HIGH);
      digitalWrite(buzzer, HIGH);
    break;
    default:
      leds[0] = CRGB::Black;
      leds[1] = CRGB::Black;
      leds[2] = CRGB::Black;
      leds[3] = CRGB::Black;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
      FastLED.show();
    break;
  }
  return 0;
}