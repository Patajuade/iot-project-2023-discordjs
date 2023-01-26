#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <SoftwareSerial.h> //for esp
#include <ArduinoJson.h>    //for esp

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6
// how many pixels in the matrix
#define NUMPIXELS 64
#define off 0, 0, 0

// Tilt's pin
const int tiltPin = 7;

// how many pixels, which pin to use to send signals.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// nodeMCU
SoftwareSerial statusNode(5, 3);
SoftwareSerial resultNode(12, 13);

int delayVal = 5000; // Delay in milliseconds between changing displayed number
int randNum;         // Variable to store the random number

// Define pixel arrays used to display numbers
int numDefault[] = {0, 1, 2, 5, 6, 7, 8, 10, 13, 15, 16, 18, 21, 23, 24, 25, 26, 29, 31, 32, 34, 37, 39, 40, 42, 45, 47, 48, 50, 53, 55, 56, 57, 58, 61, 62, 63};
int num1[] = {0, 1, 2, 7, 8, 13, 15, 16, 18, 23, 24, 29, 31, 32, 34, 39, 40, 45, 47, 48, 50, 55, 56, 61, 62, 63};
int num2[] = {0, 1, 2, 5, 6, 7, 10, 13, 15, 16, 18, 21, 24, 25, 26, 29, 31, 32, 34, 39, 40, 45, 47, 48, 50, 55, 56, 57, 58, 61, 62, 63};
int num3[] = {0, 1, 2, 5, 6, 7, 8, 13, 15, 16, 18, 23, 24, 25, 26, 29, 31, 32, 34, 39, 40, 45, 47, 48, 50, 55, 56, 57, 58, 61, 62, 63};
int num4[] = {0, 1, 2, 7, 8, 13, 15, 16, 18, 23, 24, 25, 26, 29, 31, 32, 34, 37, 39, 40, 42, 45, 47, 48, 50, 53, 55, 56, 58, 61, 62, 63};
int num5[] = {0, 1, 2, 5, 6, 7, 8, 13, 15, 16, 18, 23, 24, 25, 26, 29, 31, 32, 34, 37, 42, 45, 47, 48, 50, 53, 56, 57, 58, 61, 62, 63};
int num6[] = {0, 1, 2, 5, 6, 7, 8, 10, 13, 15, 16, 18, 21, 23, 24, 25, 26, 29, 31, 32, 34, 37, 42, 45, 47, 48, 50, 53, 56, 57, 58, 61, 62, 63};
int num7[] = {0, 1, 2, 7, 8, 13, 15, 16, 18, 23, 24, 29, 31, 32, 34, 39, 40, 45, 47, 48, 50, 55, 56, 58, 57, 61, 62, 63};
int num8[] = {0, 1, 2, 5, 6, 7, 8, 10, 13, 15, 16, 18, 21, 23, 24, 25, 26, 29, 31, 32, 34, 37, 39, 40, 42, 45, 47, 48, 50, 53, 55, 56, 57, 58, 61, 62, 63};
int num9[] = {0, 1, 2, 5, 6, 7, 8, 13, 15, 16, 18, 23, 24, 25, 26, 29, 31, 32, 34, 37, 39, 40, 42, 45, 47, 48, 50, 53, 55, 56, 57, 58, 61, 62, 63};
int num10[] = {2, 5, 6, 7, 8, 10, 13, 18, 21, 23, 24, 26, 29, 34, 37, 39, 40, 42, 45, 50, 53, 55, 56, 57, 58, 61};
int num11[] = {2, 7, 8, 13, 18, 23, 24, 29, 34, 39, 40, 45, 50, 55, 56, 61};
int num12[] = {2, 5, 6, 7, 10, 13, 18, 21, 24, 25, 26, 29, 34, 39, 40, 45, 50, 55, 56, 57, 58, 61};
int num13[] = {2, 5, 6, 7, 8, 13, 18, 23, 24, 25, 26, 29, 34, 39, 40, 45, 50, 55, 56, 57, 58, 61};
int num14[] = {2, 7, 8, 13, 18, 23, 24, 25, 26, 29, 34, 37, 39, 40, 42, 45, 50, 53, 55, 56, 58, 61};
int num15[] = {2, 5, 6, 7, 8, 13, 18, 23, 24, 25, 26, 29, 34, 37, 42, 45, 50, 53, 56, 57, 58, 61};
int num16[] = {2, 5, 6, 7, 8, 10, 13, 18, 21, 23, 24, 25, 26, 29, 34, 37, 42, 45, 50, 53, 56, 57, 58, 61};
int num17[] = {2, 7, 8, 13, 18, 23, 24, 29, 34, 39, 40, 45, 50, 55, 56, 58, 57, 61};
int num18[] = {2, 5, 6, 7, 8, 10, 13, 18, 21, 23, 24, 25, 26, 29, 34, 37, 39, 40, 42, 45, 50, 53, 55, 56, 57, 58, 61};
int num19[] = {2, 5, 6, 7, 8, 13, 18, 23, 24, 25, 26, 29, 34, 37, 39, 40, 42, 45, 50, 53, 55, 56, 57, 58, 61};
int num20[] = {0, 1, 2, 5, 6, 7, 8, 10, 15, 16, 21, 23, 24, 26, 29, 30, 31, 34, 37, 39, 40, 42, 45, 50, 53, 55, 56, 57, 58, 61, 62, 63};

// Define sizes of arrays used above
int pixelCountDefault = 38;
int pixelCount = 64;
bool showMatrix;

void setup()
{
  // NodeMCU setup
  Serial.begin(115200);
  statusNode.begin(115200);
  resultNode.begin(115200);
  delay(1000);
  //Serial.println("Program started");

  // Matrix setup
  pixels.begin();          // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(tiltPin, INPUT); // INITIALIZE tilts pin
  pixels.show();
}
bool isNumberSend = false;
void sendNumberToNodeMCU(int num)
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject &data = jsonBuffer.createObject();

  // Serial.print("Result : ");
  // Serial.println(num);

  // Assign collected data to JSON Object
  data["status"] = num;//0 = wait; -1 = get;

  // Send data to NodeMCU
  data.printTo(statusNode);
  jsonBuffer.clear();
  isNumberSend = true;
}

int getResult(){
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(resultNode);
  
  if (data == JsonObject::invalid()) {
    jsonBuffer.clear();
  }

  int result = data["result"];
  Serial.print("getResult");
  Serial.println(result);
  return result;
}
void loop()
{
  // loop listening to the tilt's state
  int tiltSensorValue = digitalRead(tiltPin);
  delay(100);

  sendNumberToNodeMCU(0);
  while (tiltSensorValue == LOW && showMatrix == false)
  {
    showMatrix = true;
    sendNumberToNodeMCU(-1);
    getResult();
  }
  if(showMatrix == true){
    switch (5)
    {
    case 1:
      draw(num1, sizeof num1 / sizeof num1[0]);
      break;
    case 2:
      draw(num2, sizeof num2 / sizeof num2[0]);
      break;
    case 3:
      draw(num3, sizeof num3 / sizeof num3[0]);
      break;
    case 4:
      draw(num4, sizeof num4 / sizeof num4[0]);
      break;
    case 5:
      draw(num5, sizeof num5 / sizeof num5[0]);
      break;
    case 6:
      draw(num6, sizeof num6 / sizeof num6[0]);
      break;
    case 7:
      draw(num7, sizeof num7 / sizeof num7[0]);
      break;
    case 8:
      draw(num8, sizeof num8 / sizeof num8[0]);
      break;
    case 9:
      draw(num9, sizeof num9 / sizeof num9[0]);
      break;
    case 10:
      draw(num10, sizeof num10 / sizeof num10[0]);
      break;
    case 11:
      draw(num11, sizeof num11 / sizeof num11[0]);
      break;
    case 12:
      draw(num12, sizeof num12 / sizeof num12[0]);
      break;
    case 13:
      draw(num13, sizeof num13 / sizeof num13[0]);
      break;
    case 14:
      draw(num14, sizeof num14 / sizeof num14[0]);
      break;
    case 15:
      draw(num15, sizeof num15 / sizeof num15[0]);
      break;
    case 16:
      draw(num16, sizeof num16 / sizeof num16[0]);
      break;
    case 17:
      draw(num17, sizeof num17 / sizeof num17[0]);
      break;
    case 18:
      draw(num18, sizeof num18 / sizeof num18[0]);
      break;
    case 19:
      draw(num19, sizeof num19 / sizeof num19[0]);
      break;
    case 20:
      draw(num20, sizeof num20 / sizeof num20[0]);
      break;
    }
  }

  else
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(off));
      pixels.show();
    }
  }
  showMatrix = false;
}

void draw(int tab[], int num)
{

  for (int i = 0; i < num; i++)
  {
    pixels.setPixelColor(tab[i], random(0,255), random(0,200), random(0,200));
    pixels.show();
  }
  delay(delayVal);
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(off));
    pixels.show();
  }
}

void wipe()
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}
