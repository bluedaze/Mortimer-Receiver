/*
  Dispatcher.h - Library for dispatching messages the radio.
  Created by Sean Pedigo, June 25, 2021.
  Released into the public domain.
*/

#include <NRFLite.h>
#include "Arduino.h"
#ifndef debugUtils_H
#define debugUtils_H
      unsigned long count;
      unsigned long lastCheck = 1000;
      extern NRFLite _radio;
      #ifdef DEBUG
          #define printDebugInfo() \
          { \
            if (millis() > lastCheck){ \
              Serial.println(_radio.hasData()); \
              lastCheck = millis() + 1500; \
            } \
          }
          #define serial_debugger(x) \
          { \
            Serial.begin(x); \
            while(!Serial) {   } \
            Serial.println("Initializing..."); \
          }
          #define checkRadioConnection() \
          { \
            bool hasConnection = false; \
            while(hasConnection == false) { \
              count++; \
              Serial.println(); \
              Serial.print("Loop Number: "); \
              Serial.println(count); \
              Serial.println("Checking radio connection..."); \
              if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) { \
                hasConnection = false; \
                Serial.println("Cannot communicate with radio"); \
              } \
              else { \
                hasConnection = true; \
                Serial.println("ConnectionStatus: True"); \
                Serial.println(); \
              } \
            }  \
          }
          #define DEBUG_PRINTLN(x) Serial.println(x);
          #define DEBUG_PRINT(x) Serial.print(x);
      #else
          #define checkRadioConnection() \
            { \
              bool hasConnection = false; \
              while(hasConnection == false) { \
                if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) { \
                  hasConnection = false; \
                } else { \
                  hasConnection = true; \
                } \
              } \
            } 
          #define printDebugInfo();
          #define serial_debugger(x);
          #define DEBUG_PRINTLN(x);
          #define DEBUG_PRINT(x);
    
#endif
#endif
