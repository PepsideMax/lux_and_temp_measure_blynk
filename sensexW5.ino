#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <SPI.h>

// sensor 1
#include <Adafruit_BMP280.h>
Adafruit_BMP280 BMP280;

// sensor 2
#include <math.h>
int BH1750address = 0x23; 
byte buff[2];

// OLED display
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char auth[] = "TVieXUefxACvwWjBMpiZw5doaP8Ns9gV";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "kluis";
char pass[] = "485454085";
int led[]= {13,12,14,22};

BlynkTimer timer;
float bmpTemp;
uint16_t val=0;
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V69, bmpTemp);
  Blynk.virtualWrite(V70, val);
}

void setup() {
    Wire.begin();

    Serial.begin(9600);

    Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);

    //BMP280 Sensor:
    if ( BMP280.begin()) {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
        while (1) delay(10);
    }

    //SSD1306 OLED:
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    timer.setInterval(1000L, myTimerEvent);
}
void loop() {
    Blynk.run();
    delay(3000);
    //BMP280:
    bmpTemp = BMP280.readTemperature();

    //BH1750:
        int i;
    BH1750_Init(BH1750address);
    delay(200);
    
    if(2==BH1750_Read(BH1750address))
    {
        val=((buff[0]<<8)|buff[1])/1.2;
    }
//    lux = BH.readLightLevel();

    //Serial monitor print:
    Serial.print("temp = ");
    Serial.print(bmpTemp);
    Serial.println(" °C");
    Serial.print("Light = ");
    Serial.print(val);
    Serial.println(" lux");
    Serial.println();

    //OLED print:
    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(0, 16);
    display.setTextColor(WHITE);
    display.println("Temp:");
    display.setCursor(0, 24);
    display.setTextColor(BLACK, WHITE);
    display.print((char)247); // ' ° ' symbol
    display.print("C: ");
    display.print(bmpTemp, 1);

    display.setCursor(0, 32);
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    display.setTextColor(BLACK, WHITE);
    display.print("Light = ");
    display.print(val);
    display.print(" lux");

    display.display();

    timer.run(); // Initiates BlynkTimer
}
void BH1750_Init(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();
}
void BH1750_Init(int address)
{
    Wire.beginTransmission(address);
    Wire.write(0x10);//1lx reolution 120ms
    Wire.endTransmission();
}
