#define DEBUG
#include <SPI.h>
#include <NRFLite.h>
#include "RadioPacket.h"
#include "DebugUtils.h"
const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t PIN_RADIO_CE = 11;
const static uint8_t PIN_RADIO_CSN = 12;
NRFLite _radio;
RadioPacket _radioData;

void setup()
{
    serial_debugger(115200);
    checkRadioConnection();
}

void loop() {
    printDebugInfo();
    uint32_t packetSize = _radio.hasData();
    if (packetSize == sizeof(RadioPacket)) {
        _radio.readData(&_radioData);

        String msg = String(_radioData.Message);

        Serial.print("Received '");
        Serial.print(msg);
        Serial.print("' from radio ");
        Serial.println(_radioData.FromRadioId);
    }
}
