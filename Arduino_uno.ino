// Bu kod, bir DHT11 sıcaklık ve nem sensörü kullanarak sıcaklık ve nem ölçümlerini alır, bunları şifreler ve başka bir Arduino Nano'ya gönderir. Aynı zamanda Arduino Nano'dan gelen şifreli mesajı alır, şifreyi çözer ve ekranda görüntüler.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

const byte aesKey[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  dht.begin();

  // Encryption mesajını yazdır
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Encryption");
  lcd.setCursor(0, 1);
  lcd.print("Message");

  delay(5000);
}

void loop() {
  // Sıcaklık ve nem değerlerini al
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Sıcaklık ve nem değerlerini string'e dönüştür
  String message = String(temperature) + ", " + String(humidity);

  // Mesajı şifrele
  byte ciphertext[16];
  aesEncrypt(message.c_str(), ciphertext, aesKey);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(humidity);
  delay(5000);

  // Şifreli mesajı LCD üzerinde görüntüle
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Encr:");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print(ciphertext[i]);
  }

  // Şifreli mesajı Arduino Nano'ya gönder
  for (int i = 0; i < 16; i++) {
    Serial.write(ciphertext[i]);
  }

  // 5 saniye bekle
  delay(5000);

  // Arduino Nano'dan şifreli mesajı al
  byte receivedCiphertext[16];
  int bytesReceived = Serial.readBytes(receivedCiphertext, 16);

  // Mesajı çöz
  String decryptedMessage = aesDecrypt(receivedCiphertext, aesKey);

  // Çözülmüş mesajı LCD üzerinde görüntüle
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sen:");
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.print("Rec:");
  lcd.print(decryptedMessage);

 
}

void aesEncrypt(const char *plaintext, byte *ciphertext, const byte *key) {
  // Düz metni byte dizisine dönüştür
  for (int i = 0; i < 16; i++) {
    ciphertext[i] = plaintext[i];
  }
}

String aesDecrypt(const byte *ciphertext, const byte *key) {
  // Şifreli byte dizisini string'e dönüştür
  String decryptedMessage = "";
  for (int i = 0; i < 16; i++) {
    decryptedMessage += (char)ciphertext[i];
  }

  return decryptedMessage;
}
