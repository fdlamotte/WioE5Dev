#include <Arduino.h>
#include "HardwareSerial.h"

#include <LittleFS_Config.h>

using namespace Adafruit_LittleFS_Namespace;

HardwareSerial mySerial {PB7, PB6};
unsigned long last_millis {0};
bool state {true};
static constexpr unsigned long blink_duration {1000};

Adafruit_LittleFS fs;

void setup(void)
{
    bool fs_ok = false;
    uint32_t boot_cpt = 0;

    mySerial.begin(115200);
    delay(100);
    pinMode(PB5, OUTPUT);
    mySerial.println(F("Booted!"));

    if (!(fs_ok = fs.begin(&_InternalFSConfig))) {
        Serial.println("Format flash");
        fs.format();
        if (!(fs_ok = fs.begin(&_InternalFSConfig))){
            Serial.println("Couldn't init flash");
        }
    }

    if (fs_ok) {
        int ret;
        File file = fs.open("/counter");
        if (file) {
            uint32_t val;
            if (ret = file.read(&val, sizeof(val)))
                boot_cpt = val;
            file.close();
     
        }
        boot_cpt ++;
        Serial.printf("Boot counter : %d\r\n", boot_cpt);
        file = fs.open("counter", FILE_O_WRITE);
        if (file) {
            file.seek(0);
            file.truncate();
            file.write((uint8_t*)&boot_cpt, sizeof(boot_cpt));
            file.close();
        }
    }


    last_millis = millis();
}

void loop(void)
{

    if (millis() - last_millis > blink_duration){
        state = !state;
        digitalWrite(PB5, state);
        last_millis += blink_duration;

        mySerial.print(F("Loop B)"));
        mySerial.println(millis());
    }

    while (mySerial.available() > 0){
        mySerial.print(mySerial.read());
    }

    
}