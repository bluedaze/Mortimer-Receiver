//#define DEBUG // Comment out to get rid of debug print statements.
#include "Parser.h"
#include "DebugUtils.h"
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

    Parser::Parser(stackdef &msg, int tokens) {
        this-> msg = msg;
        this-> tokens = tokens;
        parseTokens();
    }


    void Parser::startEngine(char a) {
        DEBUG_PRINTLN("Starting engine...");
        analogWrite(E1, a);
        analogWrite(E2, a);
        digitalWrite(M1, HIGH);
        digitalWrite(M2, HIGH);
    }

    void Parser::turnRight (char a, char b) {
        DEBUG_PRINTLN("Turning right...");
        analogWrite (E1, a);
        digitalWrite(M1, HIGH);
        analogWrite (E2, b);
        digitalWrite(M2, LOW);
    }

    void Parser::turnLeft (char a, char b) {
        DEBUG_PRINTLN("Turning left...");
        analogWrite (E1, a);
        digitalWrite(M1, LOW);
        analogWrite (E2, b);
        digitalWrite(M2, HIGH);
    }

    void Parser::Parser::stopEngine(void) {
        DEBUG_PRINTLN("Stopping engine...");
        digitalWrite(E1, LOW);
        digitalWrite(E2, LOW);
    }

    void Parser::uwbFuncs() {
        if (msg.tokens[index] == "start") {
            startUWB();
            index++;
        }
        else if (msg.tokens[index] == "stop") {
            stopUWB();
            index++;
        }
    }

    void Parser::startUWB() {
        DEBUG_PRINTLN("Starting Ultra Wide Band...");
    }

    void Parser::stopUWB() {
        DEBUG_PRINTLN("Stopping Ultra Wide Band...");
    }
    
    void Parser::reverse (char a, char b) {
      DEBUG_PRINTLN("Reversing engine...");
      analogWrite (E1, a);
      digitalWrite(M1, LOW);
      analogWrite (E2, b);
      digitalWrite(M2, LOW);
    }

    void Parser::engineFuncs() {
        if (msg.tokens[index] == "start") {
            startEngine(255);
            index++;
        } else if (msg.tokens[index] == "stop") {
            stopEngine();
            index++;
        } else if (msg.tokens[index] == "right"){
            turnRight(250, 250);
            index++;
        } else if(msg.tokens[index] == "reverse"){
            reverse(250, 250);
            index++;
        } else if(msg.tokens[index] == "left"){
            turnLeft(250, 250);
            index++;
        }
    }

    void Parser::parseTokens() {
        while (index < tokens) {
//            DEBUG_PRINT(msg.tokens[index])
            if (msg.tokens[index] == "engine") {
                index++;
                engineFuncs();
            } else if (msg.tokens[index] == "uwb") {
                index++;
                uwbFuncs();
            } else if (msg.tokens[index] == ";") {
                index++;
            } else {
//              DEBUG_PRINTLN("Broken");
//                Serial.println("Invalid input. "
//                "Commands are written in a noun verb structure."
//                "ie noun: 'engine' verb: 'start'");
                index++;
                break;
            }
        }
    }
