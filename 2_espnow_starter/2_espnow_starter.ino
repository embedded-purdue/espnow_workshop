/*
 * =========================================================================
 * ESP-NOW Wireless Chatroom — STUDENT STARTER FILE
 * =========================================================================
 * Complete the 5 TODOs below to build a two-way wireless text communicator!
 *
 * WIRING (ESP32-WROOM-32E  --->  1602 I2C LCD):
 * - GND  --->  GND
 * - VIN  --->  VCC (5V)
 * - D21  --->  SDA
 * - D22  --->  SCL
 * =========================================================================
 */

#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to 0x3F if needed

// -------------------------------------------------------------------------
// TODO 1: Replace the zeros below with the OTHER team's MAC address!
// Example: {0x5c, 0x01, 0x3b, 0x9c, 0x78, 0xc0}
// -------------------------------------------------------------------------
uint8_t receiverAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 


// -------------------------------------------------------------------------
// TODO 2: Define the data "envelope" (struct)
// Inside the curly braces, declare a character array named 'textMsg'
// with a size of 32 bytes:  char textMsg[32];
// -------------------------------------------------------------------------
typedef struct struct_message {
  // YOUR CODE HERE

} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;


// --- CALLBACK: Runs automatically after we send a message ---
void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


// --- CALLBACK: Runs automatically when a message arrives over the air ---
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
  // Unpack the raw wireless bytes into our 'myData' struct
  memcpy(&myData, incomingData, sizeof(myData));
  
  Serial.print("Received message: ");
  Serial.println(myData.textMsg);

  String msg = String(myData.textMsg);

  // -----------------------------------------------------------------------
  // TODO 5: Print 'msg' onto the 16x2 LCD screen!
  // Hints:
  // 1. Clear the old message with: lcd.clear();
  // 2. Set the cursor to column 0, row 0: lcd.setCursor(0, 0);
  // 3. Print the message: lcd.print(msg);
  // (Bonus challenge: If msg.length() > 16, split it onto row 1!)
  // -----------------------------------------------------------------------
  // YOUR CODE HERE

}


// --- SETUP: Runs once at startup ---
void setup() {
  Serial.begin(115200);

  // -----------------------------------------------------------------------
  // TODO 3: Wake up the LCD screen and print a startup message
  // Hints:
  // 1. Call lcd.init(); and lcd.backlight();
  // 2. Move the cursor to (0, 0) and print "Ready..."
  // -----------------------------------------------------------------------
  // YOUR CODE HERE


  // Initialize Wi-Fi in Station mode and start ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register our Send and Receive callbacks
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  
  // Register the other team's ESP32 as a peer
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}


// --- MAIN LOOP: Repeats forever ---
void loop() {
  if (Serial.available()) {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim(); 

    if (inputString.length() > 0 && inputString.length() < 32) {
      // Pack the typed String into our struct's character array
      inputString.toCharArray(myData.textMsg, 32);
      
      // -------------------------------------------------------------------
      // TODO 4: Send 'myData' wirelessly via ESP-NOW!
      // Hint: Use esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));
      // Save its return value in an 'esp_err_t result' variable and print
      // whether it equaled ESP_OK!
      // -------------------------------------------------------------------
      // YOUR CODE HERE
      
    } else if (inputString.length() >= 32) {
      Serial.println("Message too long! Max 31 characters.");
    }
  }
}