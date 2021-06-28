#define DEBUG
#include <SPI.h>
#include <NRFLite.h>
#include "RadioPacket.h"
#include "DebugUtils.h"
const static uint8_t RADIO_ID = 0;
const static uint8_t PIN_RADIO_CE = 12;
const static uint8_t PIN_RADIO_CSN = 11;
NRFLite _radio;
RadioPacket _radioData;
String messages[10];
void setup()
{
    serial_debugger(115200);
    checkRadioConnection();
}

void loop() {
    printDebugInfo();
    uint32_t packetSize = _radio.hasData();
    while(_radio.hasData()){
        RadioPacket packet;
        _radio.readData(&packet);
        messages[packet.packetNumber] = packet.Message;
        DEBUG_PRINTLN("Packet Number: " + String(packet.packetNumber));
        DEBUG_PRINT("Message: ");
        DEBUG_PRINTLN(messages[packet.packetNumber]);
    }
}
