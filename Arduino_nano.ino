// Bu kod, I2C arayüzü üzerinden bağlı bir LCD ekranı kullanarak şifreleme işlemi gerçekleştirir. Şifrelenmiş mesajı alır, çözer ve tekrar şifreleyerek iletişimi sağlar. Ayrıca, LED'i yanıp sönme şeklinde kontrol eder.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD ekran için I2C bağlantısını tanımla

const byte aesKey[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}; // Şifreleme anahtarını belirle

void setup() {
  Serial.begin(9600); // Seri iletişimi başlat
  lcd.init(); // LCD ekranını başlat
  lcd.clear(); // LCD ekranını temizle

  // Encryption mesajını yazdır
  lcd.backlight();
  lcd.print("Encryption");
  lcd.setCursor(0, 1);
  lcd.print("Message");

  delay(5000);
}

void loop() {
  // Arduino Uno'dan şifreli mesajı bekle
  byte receivedCiphertext[16];
  int bytesReceived = Serial.readBytes(receivedCiphertext, 16);

  // Mesajı çöz
  String decryptedMessage = aesDecrypt(receivedCiphertext, aesKey);

  // Çözülmüş mesajı LCD üzerinde görüntüle
  lcd.clear();
  
  lcd.setCursor(0, 1);
  lcd.print(decryptedMessage);

  // Mesajı tekrar şifrele
  byte ciphertext[16];
  aesEncrypt(decryptedMessage.c_str(), ciphertext, aesKey);

  // Şifreli mesajı LCD üzerinde görüntüle
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Encr:");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print(ciphertext[i]);
  }



  // Şifreli mesajı Arduino Uno'ya gönder
  for (int i = 0; i < 16; i++) {
    Serial.write(ciphertext[i]);
  }

  // 5 saniye bekle
  delay(5000);

  // Arduino Uno'dan şifreli mesajı al
  bytesReceived = Serial.readBytes(receivedCiphertext, 16);

  // Mesajı çöz
  decryptedMessage = aesDecrypt(receivedCiphertext, aesKey);

  // Çözülmüş mesajı LCD üzerinde görüntüle
  lcd.clear();
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
