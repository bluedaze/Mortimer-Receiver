//#define  DEBUG // Comment out to get rid of debug print statements.
#include <SPI.h>
#include <NRFLite.h>
#include "RadioPacket.h"
#include "DebugUtils.h"
#include "Parser.h"
#include "Tokenizer.h"
unsigned long count;
unsigned long lastCheck = 1000;
const static uint8_t RADIO_ID = 0;
const static uint8_t PIN_RADIO_CE = 11;
const static uint8_t PIN_RADIO_CSN = 12;
NRFLite _radio;
RadioPacket _radioData;
String messages[10];
void setup() {
    serial_debugger(115200);
    checkRadioConnection();
}

void parseTokens(String str) {
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    Tokenizer tokens(char_array);
    Parser parser(tokens.message, tokens.index);
}

void loop() {
    // I am temporarily using a string.
    // In the future this should be replaced with a fixed size array.
    String str = "";
    printDebugInfo();
    uint32_t packetSize = _radio.hasData();
    while(_radio.hasData()){
        RadioPacket packet;
        _radio.readData(&packet);
        messages[packet.packetNumber] = packet.Message;
        DEBUG_PRINTLN("Packet Number: " + String(packet.packetNumber));
        DEBUG_PRINT("Packet: ");
        DEBUG_PRINTLN(packet.Message);
        str+= packet.Message;
    }
    if(str.length() > 0){
      parseTokens(str);     
    }
    Serial.flush();
}
