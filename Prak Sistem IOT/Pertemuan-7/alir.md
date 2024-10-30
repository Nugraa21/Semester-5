```
#define THINGER_SERIAL_DEBUG
#include <ThingerESP32.h>
#include "arduino_secrets.h"
#define LED1 12
#define LED2 13
#define Sensor 32
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
    // untuk debugging
    Serial.begin(115200);
    // set LED1 dan LED2 sebagai output
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    // SSID dan password Access Point
    thing.add_wifi(SSID, SSID_PASSWORD);

    // resource input on/off untuk LED1
    thing["led1"] << digitalPin(LED1);

    // resource input on/off untuk LED2
    thing["led2"] << digitalPin(LED2);
}

void loop() {
    thing.handle();
}

```
```
flowchart TD
    A[Mulai] --> B[Inisialisasi Serial]
    B --> C[Inisialisasi Pin LED1 dan LED2]
    C --> D[Koneksi WiFi]
    D --> E[Tambahkan Resource untuk LED1]
    E --> F[Tambahkan Resource untuk LED2]
    F --> G[Loop Program]
    G --> H[thing.handle()]
    H --> G

```