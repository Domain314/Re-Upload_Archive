#ifndef INC_3_FINALDOMAIN314_INPUT_HPP
#define INC_3_FINALDOMAIN314_INPUT_HPP


#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

// other key codes
//const int KEY_ARROW_CHAR1 = 224;
//const int KEY_ARROW_UP = 72;
//const int KEY_ARROW_DOWN = 80;
//const int KEY_ARROW_LEFT = 75;
//const int KEY_ARROW_RIGHT = 77;

// my key codes (Manjaro Linux)
const char KEY_ARROW_CHAR1 = '[';
const int KEY_ARROW_UP = 65;
const int KEY_ARROW_DOWN = 66;
const int KEY_ARROW_LEFT = 68;
const int KEY_ARROW_RIGHT = 67;
const int KEY_ENTER = 10;
const int KEY_ESC = 27;

class Input {
public:
    char getInput();
    char getInput2();
    unsigned char _getch(void);
    char _getChar();
};


#endif //INC_3_FINALDOMAIN314_INPUT_HPP
