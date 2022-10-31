#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Smoothed.h>
//yumuşatma kütüphanesi

Smoothed <float> ortDeger;

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
float vectorprevious;
float vector;
float totalvector;
int adim = 0;



void setup() {
  Serial.begin(115200);
  ortDeger.begin(SMOOTHED_AVERAGE,3);
  // while (!Serial);
  Serial.println("MPU6050 OLED demo");

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.display();
  //delay(500);  // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
}

void loop() {

 sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  display.clearDisplay();
  display.setCursor(0, 0);

  Serial.print("Accelerometer ");
  Serial.print("X: ");
  Serial.print(a.acceleration.x, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Y: ");
  Serial.print(a.acceleration.y, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Z: ");
  Serial.print(a.acceleration.z, 1);
  Serial.println(" m/s^2");

  display.println("Accelerometer - m/s^2");
  display.print(a.acceleration.x, 1);
  display.print(", ");
  display.print(a.acceleration.y, 1);
  display.print(", ");
  display.print(a.acceleration.z, 1);
  display.println("");

  vector = sqrt((a.acceleration.x * a.acceleration.x) + (a.acceleration.y * a.acceleration.y) + (a.acceleration.z * a.acceleration.z));
ortDeger.add(vector);
float sortDeger=ortDeger.get();

  totalvector = abs(sortDeger - vectorprevious);
  if (totalvector >= 5 ) {
    adim++;
  }
  vectorprevious = vector;
  display.println("Vektor:");
  display.print(vector);
  display.print("ADIM:");
  display.println(adim);

  display.display();
  delay(100);
}