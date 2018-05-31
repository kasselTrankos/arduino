#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

// Color definitions
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

/*
  Teensy3.x and Arduino's
  You are using 4 wire SPI here, so:
  MOSI:  11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
  MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
  SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
  the rest of pin below:
*/
#define __CS 10
#define __DC 9
/*
  Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
  Arduino's 8 bit: any
  DUE: check arduino site
  If you do not use reset, tie it to +3V3
*/


TFT_ILI9163C display = TFT_ILI9163C(__CS, 8, __DC);

#include <DHT.h>

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Comenzamos el sensor DHT
  dht.begin();
  // put your setup code here, to run once:
  display.begin();


  uint16_t time = millis();
  display.begin();
  display.setRotation(1); display.fillScreen(BLACK); 
  display.setTextColor(YELLOW, BLACK); 
  display.setTextSize(2); 
  display.setCursor(0, 5); display.print("Number"); 

  
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahrenheit
  float f = dht.readTemperature(true);

  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  // Calcular el índice de calor en Fahrenheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
  //display.clearScreen();
  /*display.fillScreen(BLUE);
  display.setCursor(30, 20);

  display.setTextColor(RED);
  display.setTextSize(2);
  display.println(String(hic) + " C");
  display.drawCircle(72, 33, 17, 0xE32);

  delay(4000);
  */
  display.setCursor(10, 50);  display.print(String(hic));
  delay(500);
}
