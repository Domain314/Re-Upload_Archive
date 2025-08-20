#ifndef INC_3_FINALDOMAIN314_INTRO_HPP
#define INC_3_FINALDOMAIN314_INTRO_HPP

#include "../Domain/Domain.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>

#define TIME_START 30000
#define TIME_END 5000
#define TIME_LONG 500000

class Intro {
public:
    Intro();
    void playIntro();
    void moveSword1();
    void moveSword2();
    void moveLetters();
    void endIntro();

    std::string getAnimatedLine(int index, int progress);

    int linearInterpolation(float t);
    float easeIn(float t);

private:
    std::vector<std::string> sword1;
//    std::vector<std::vector<char>> sword1;
    std::vector<std::string> sword2;
    std::vector<std::string> endDisplay;
    std::vector<std::vector<std::string>> animatedLines;
    std::string start;

    std::vector<char> emptySpace;
};


#endif //INC_3_FINALDOMAIN314_INTRO_HPP
