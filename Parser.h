#ifndef Parser_h
#define Parser_h
#include "Arduino.h"
#include "stackdef.h"

class Parser {
  public:
    int tokens;
    stackdef msg;
    int index = 0;

    Parser(stackdef &msg, int tokens);
    void startEngine(char a);
    void turnRight (char a, char b) ;
    void turnLeft (char a, char b);
    void stopEngine(void);
    void uwbFuncs();
    void startUWB();
    void stopUWB();
    void reverse (char a, char b);
    void engineFuncs();
    void parseTokens();
};
#endif
