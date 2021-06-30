#ifndef Tokenizer_h
#define Tokenizer_h
#include "Arduino.h"
#include "stackdef.h"

class Tokenizer {
  public:
    int index = 0;
    int count = 0;

    stackdef message;
    char* msg;

    Tokenizer(char msg[]);
    void addToStack(String &str);
    void advance(String &str, char c );
    void getTokens();
    char peek();
    void skipWhitespace();
};

#endif
