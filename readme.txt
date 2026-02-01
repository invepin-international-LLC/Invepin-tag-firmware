====================================================
Invepin ESP32-S3 BLE Micro-Pin Firmware
====================================================

Project Name:
Invepin Smart Micro-Pin – BLE Advertising Firmware

Description:
This firmware turns an ESP32-S3 into an Invepin smart micro-pin.
The device continuously broadcasts a Bluetooth Low Energy (BLE)
manufacturer advertisement containing a unique Invepin ID, battery
level, and tag metadata. It is designed for real-time inventory
tracking, loss prevention, and geofencing within the Invepin ecosystem.

The firmware uses broadcast-only BLE advertising (no pairing required),
making it ideal for low-power, scalable deployment in retail,
logistics, and enterprise environments.

----------------------------------------------------
Core Features
----------------------------------------------------
- BLE manufacturer advertising (no connection required)
- Unique 16-byte Invepin tag identifier
- Real-time battery level telemetry
- Configurable advertising interval
- High transmission power for retail-scale coverage
- Lightweight NimBLE stack for efficiency

----------------------------------------------------
Hardware Requirements
----------------------------------------------------
- ESP32-S3 development board or module
- Battery connected to ADC-capable GPIO
- GPIO 4 used for battery voltage reading (configurable)

----------------------------------------------------
Software Requirements
----------------------------------------------------
- Arduino IDE or PlatformIO
- ESP32 board support package
- NimBLE-Arduino library

----------------------------------------------------
Configuration
----------------------------------------------------
Key configuration values are defined at the top of the source file:

- INVEPIN_ID
  Unique identifier for this micro-pin (16 characters recommended)

- COMPANY_ID
  BLE Manufacturer ID (0x4956 = "IV" for Invepin)

- ADVERTISING_INTERVAL
  BLE advertising interval in milliseconds

----------------------------------------------------
BLE Manufacturer Data Packet Format
----------------------------------------------------
The firmware broadcasts the following manufacturer data payload:

Byte(s)   Description
-------   ---------------------------------------
0–1       Manufacturer ID (Invepin)
2–17      Invepin Tag ID (16 bytes)
18        Battery Level (0–100%)
19        Tag Type (0x01 = BLE Micro-Pin)
20        Firmware Version (0x01 = v1.0)
21        Reserved / Flags

This packet is designed for ingestion by Invepin Colony
(edge scanners) and Hive (cloud analytics).

----------------------------------------------------
Runtime Behavior
----------------------------------------------------
- On boot, the device initializes BLE and begins advertising.
- The BLE payload is broadcast every 500 milliseconds.
- Every 60 seconds, the battery level is re-read.
- Advertising is briefly restarted to update the payload.
- No user interaction or BLE pairing is required.

----------------------------------------------------
Battery Measurement
----------------------------------------------------
- Battery voltage is read using the ESP32 ADC on GPIO 4.
- Raw ADC values are mapped to a 0–100% range.
- For production deployments, ADC calibration is recommended.

----------------------------------------------------
Use Cases
----------------------------------------------------
- Smart inventory tagging
- Loss prevention and shrinkage detection
- Real-time item presence tracking
- Battery health monitoring
- Edge-to-cloud IoT telemetry

----------------------------------------------------
Notes
----------------------------------------------------
- Preferences (NVS) is included for future expansion
  (e.g., persistent ID storage, calibration data).
- GPS, tamper detection, and geofence flags can be added
  as additional manufacturer data bytes.
- Power optimization can be applied for coin-cell deployments.

----------------------------------------------------
License
----------------------------------------------------
© Invepin International
All rights reserved.

Pinpoint Precision. Infinite Protection.
====================================================
