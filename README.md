# Secure-Arduino-Communication-using-AES
This project implements a secure communication system between two Arduino boards using AES (128-bit) encryption. It demonstrates how sensitive IoT data can be protected during transmission.

👤 Author
Yasin Ali

📌 Overview
-Reads temperature and humidity using a DHT11 sensor
-Encrypts the data using AES algorithm
-Sends encrypted data from Arduino Uno → Arduino Nano
-Decrypts the received data on the receiver side
-Displays both encrypted and decrypted messages on LCD (I2C)

⚙️ Hardware Components
-Arduino Uno (Transmitter)
-Arduino Nano (Receiver)
-DHT11 Temperature & Humidity Sensor
-2x 16x2 LCD Display (I2C)
-Jumper wires

🔌 Connections
-Arduino Uno
-DHT11 → Data: D2, VCC: 3.3V, GND: GND
-LCD (I2C) → SDA: A4, SCL: A5
-Arduino Nano
-LCD (I2C) → SDA: A4, SCL: A5

Communication
Uno TX → Nano RX
Uno RX → Nano TX

🔑 Encryption Details
Algorithm: AES (Advanced Encryption Standard)
Key Size: 128-bit (16 bytes)
Data is converted to string, then encrypted into a 16-byte ciphertext
Same key is used for decryption on receiver side

🔄 Workflow
Sensor reads temperature & humidity
Data is formatted into a message
Message is encrypted using AES
Encrypted bytes are sent via Serial
Receiver reads encrypted data
Data is decrypted using same AES key
Results displayed on LCD

📟 Output
LCD shows:
Encrypted data (ciphertext)
Decrypted original message

🎯 Purpose
Demonstrate secure IoT communication
Show practical use of encryption/decryption in embedded systems
Provide a simple foundation for secure data transmission projects

🚀 Future Improvements
Use real AES library instead of simplified implementation
Add wireless communication (NRF24L01 / WiFi / LoRa)
Improve error handling & data integrity checks
Optimize memory usage for embedded systems
