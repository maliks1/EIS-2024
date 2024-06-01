#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define LED_PIN_RED 7
#define LED_PIN_GREEN 8
#define SENSOR_PIN A0

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Konfigurasi pin sensor dan LED
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  
  // Memulai komunikasi serial
  Serial.begin(9600);
  Serial.println("MQ3 Sensor Heating Up!");

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Blink LED merah saat pemanasan sensor
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN_RED, HIGH);
    delay(500);
    digitalWrite(LED_PIN_RED, LOW);
    delay(500);
  }
}

void loop() {
  // Membaca nilai dari sensor gas
  int gasValue = analogRead(SENSOR_PIN);
  
  // Menampilkan nilai sensor di Serial Monitor
  Serial.print("Sensor Value: ");
  Serial.println(gasValue);

  // Menampilkan nilai sensor di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("sensor_gas:");
  lcd.setCursor(0, 1);
  lcd.print(gasValue);
  
  // Mengatur status LED berdasarkan nilai sensor
  setLED(gasValue);
  
  // Delay untuk stabilisasi pembacaan sensor
  delay(1000);
}

// Fungsi untuk mengatur status LED
void setLED(int value) {
  // Tentukan nilai batas atas dan bawah
  const int upperThreshold = 1001;
  const int lowerThreshold = 500;

  if (value > upperThreshold) {
    // Nilai sensor di atas batas atas (berbahaya)
    digitalWrite(LED_PIN_RED, HIGH);
    digitalWrite(LED_PIN_GREEN, LOW);
  } else if (value < lowerThreshold) {
    // Nilai sensor di bawah batas bawah (normal)
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_GREEN, HIGH);
  } else {
    // Nilai sensor di antara batas bawah dan atas (waspada)
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_GREEN, LOW);
  }
}
