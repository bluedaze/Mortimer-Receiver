#include "Tokenizer.h"
#include "DebugUtils.h"
    
    Tokenizer::Tokenizer(char msg[]) {
        this -> msg = msg;
        getTokens();
    }

    void Tokenizer::addToStack(String &str) {
        message.tokens[index] = str;
        index++;
        count++;
        str = "";
    }

    void Tokenizer::advance(String &str, char c ) {
        str+= c;
        count++;
    }

    void Tokenizer::getTokens() {
        String str = "";
        char c = msg[count];
        while (count < strlen(msg) +1) {
            if (isspace(c)) {
                skipWhitespace();
                addToStack(str);
                c = msg[count];
            } else if (c == '\0') {
                addToStack(str);
            } else {
                advance(str, c);
                c = msg[count];
            }
        }
    }

    char Tokenizer::peek() {
        char peekValue = msg[count+1];
        return peekValue;
    }

    void Tokenizer::skipWhitespace() {
        while (isspace(peek())) {
            count++;
        }
    }
