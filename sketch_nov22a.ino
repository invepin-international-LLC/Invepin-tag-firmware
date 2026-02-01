#include <NimBLEDevice.h>
#include <Preferences.h>

Preferences preferences;
NimBLEAdvertising *pAdvertising;

// Configuration
const char* INVEPIN_ID = "INV-ESP32-0001-ABCD"; // Unique 16-char ID
const uint16_t COMPANY_ID = 0x4956; // Invepin manufacturer ID
const int ADVERTISING_INTERVAL = 500; // milliseconds

// Function declarations
uint8_t getBatteryLevel();
void updateAdvertisement();

void setup() {
  Serial.begin(115200);
  Serial.println("Invepin ESP32-S3 Starting...");
  
  // Initialize BLE
  NimBLEDevice::init("Invepin");
  NimBLEDevice::setPower(ESP_PWR_LVL_P9); // Max power
  
  // Create advertising
  pAdvertising = NimBLEDevice::getAdvertising();
  
  // Build manufacturer data packet
  std::string manufacturerData;
  manufacturerData += (char)(COMPANY_ID & 0xFF);
  manufacturerData += (char)(COMPANY_ID >> 8);
  manufacturerData += INVEPIN_ID; // 16 bytes
  manufacturerData += (char)getBatteryLevel(); // 1 byte
  manufacturerData += (char)0x01; // Tag type: BLE
  manufacturerData += (char)0x01; // Firmware v1.0
  manufacturerData += (char)0x00;
  
  pAdvertising->setManufacturerData(manufacturerData);
  // Remove the problematic setAdvertisementType() call
  pAdvertising->setMinInterval(ADVERTISING_INTERVAL);
  pAdvertising->setMaxInterval(ADVERTISING_INTERVAL);
  
  // Start advertising
  pAdvertising->start();
  Serial.println("Invepin broadcasting!");
}

void loop() {
  // Update battery level every 60 seconds
  delay(60000);
  updateAdvertisement();
}

uint8_t getBatteryLevel() {
  // Read battery voltage (ESP32-S3 ADC)
  int rawValue = analogRead(39); // GPIO4 for battery
  int percentage = map(rawValue, 0, 4095, 0, 100);
  return constrain(percentage, 0, 100);
}

void updateAdvertisement() {
  pAdvertising->stop();
  // Rebuild packet with new battery level
  std::string manufacturerData;
  manufacturerData += (char)(COMPANY_ID & 0xFF);
  manufacturerData += (char)(COMPANY_ID >> 8);
  manufacturerData += INVEPIN_ID;
  manufacturerData += (char)getBatteryLevel();
  manufacturerData += (char)0x01;
  manufacturerData += (char)0x01;
  manufacturerData += (char)0x00;
  pAdvertising->setManufacturerData(manufacturerData);
  pAdvertising->start();
}
