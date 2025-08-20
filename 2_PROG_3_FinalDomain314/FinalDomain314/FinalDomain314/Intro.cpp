#include "Intro.hpp"

Intro::Intro() {
    this->sword1.emplace_back(R"(                                                            |\           )");
    this->sword1.emplace_back(R"(                                                            <<\          )");
    this->sword1.emplace_back(R"(                                                             / \       //)");
    this->sword1.emplace_back(R"( _-----------------------------------------------------------{o}______/| )");
    this->sword1.emplace_back(R"(<       -==============================================:::{+}///////////])");
    this->sword1.emplace_back(R"( ------------------------------------------------------------{o}~~~~~~\| )");
    this->sword1.emplace_back(R"(                                              \ /       \\)");
    this->sword1.emplace_back(R"(                                             <</          )");

    this->sword2.emplace_back(R"(            /> )");
    this->sword2.emplace_back(R"(           /<  )");
    this->sword2.emplace_back(R"( |/~~~~~~~{o}----------------------------------------------------------~)");
    this->sword2.emplace_back(R"(           \<                                                          )");
    this->sword2.emplace_back(R"(            \<                                                         )");
    this->sword2.emplace_back(R"(             \>                                                        )");


    this->endDisplay.emplace_back(R"(                                                            |\)");
    this->endDisplay.emplace_back(R"(                                                            <<\)");
    this->endDisplay.emplace_back(R"(                                                             / \       //)");
    this->endDisplay.emplace_back(R"( _-----------------------------------------------------------{o}______/|)");
    this->endDisplay.emplace_back(R"(<       -==============================================:::{+}///////////])");
    this->endDisplay.emplace_back(R"( ------------------------------------------------------------{o}~~~~~~\|)");
    this->endDisplay.emplace_back(R"(           />                                                \ /       \\)");
    this->endDisplay.emplace_back(R"(          /<                                                <</)");
    this->endDisplay.emplace_back(R"(|/~~~~~~~{o}----------------------------------------------------------~)");
    this->endDisplay.emplace_back(R"(          \<)");
    this->endDisplay.emplace_back(R"(           \<)");
    this->endDisplay.emplace_back(R"(            \>)");

    this->animatedLines.push_back({
        R"(           />              F                                 \ /       \\)",
        R"(           />              Fi                                \ /       \\)",
        R"(           />              Fin                               \ /       \\)",
        R"(           />              Fina                              \ /       \\)",
        R"(           />              Final                             \ /       \\)",
        R"(           />              Final                             \ /       \\)",
        R"(           />              Final                             \ /       \\)",
        R"(           />              Final                             \ /       \\)",
        R"(           />              Final                             \ /       \\)",
        R"(           />              Final                             \ /       \\)",
        R"(           />              Final                             \ /       \\)",
        R"(           />              Final                             \ /       \\)"
    });
    this->animatedLines.push_back({
        R"(          /<                                                <</)",
        R"(          /<                                                <</)",
        R"(          /<                                                <</)",
        R"(          /<                  D                             <</)",
        R"(          /<                  Do                            <</)",
        R"(          /<                  Dom                           <</)",
        R"(          /<                  Doma                          <</)",
        R"(          /<                  Domai                         <</)",
        R"(          /<                  Domain                        <</)",
        R"(          /<                  Domain3                       <</)",
        R"(          /<                  Domain31                      <</)",
        R"(          /<                  Domain314                     <</)",
    });

    this->start = "              >Start<\n";

    for (int i = 0; i < 30; ++i) {
        this->emptySpace.push_back(' ');
    }
}

void Intro::playIntro() {
    usleep(TIME_LONG);
    moveSword1();
}

void Intro::moveSword1() {
    int pixelCounter = 0;
    for (int i = 0; i < 70; ++i) {
        clearScreen();
        for (int j = 0; j < sword1.size(); ++j) {
            for (int e = 50-i; e >= 0; --e) {
                std::cout << " ";
                pixelCounter++;
            }
            if (j >= 6) {
                std::cout << "               ";
            }
            std::cout << sword1.at(j).substr(0, sword1.at(j).size()-pixelCounter) << "\n";
            pixelCounter = 0;
        }
        std::cout << "\n\n\n\n";
        usleep(linearInterpolation((float)i/70));
    }
    moveSword2();
}

void Intro::moveSword2() {
    for (int i = 0; i < 70; ++i) {
        clearScreen();
        for (int j = 0; j < sword1.size(); ++j) {
            if (j >= 6 && i > 55) {
                std::cout << sword2.at(j-6).substr(70-i, sword2.at(j-6).size());
                for (int k = 0; k < 70-i; ++k) {
                    std::cout << ' ';
                }

            } else if (j >= 6) {
                std::cout << "               ";
            }
            std::cout << sword1.at(j) << "\n";

        }
        for (int j = 2; j < sword2.size(); ++j) {
            std::cout << sword2.at(j).substr(70-i, sword2.at(j).size()) << "\n";
        }
        usleep(linearInterpolation((float)i/70));
    }
    moveLetters();
}

void Intro::moveLetters() {
    usleep(TIME_LONG);
    for (int i = 0; i < 12; ++i) {
        clearScreen();
        for (int j = 0; j < endDisplay.size(); ++j) {
            if (j == 6 || j == 7) {
                std::cout << getAnimatedLine(j-6, i) << "\n";
            } else {
                std::cout << endDisplay.at(j) << "\n";
            }

        }
        usleep(TIME_LONG*0.75);
    }
    endIntro();
}

void Intro::endIntro() {
    usleep(TIME_LONG);
    clearScreen();
    for (int i = 0; i < endDisplay.size(); ++i) {
        if (i == 6 || i == 7) {
            std::cout << getAnimatedLine(i-6, animatedLines.at(0).size()-1) << "\n";
        } else {
            std::cout << endDisplay.at(i);
            if (i == (endDisplay.size()-1)) {
                std::cout << start;
            }
            std::cout << std::endl;
        }
    }
}

std::string Intro::getAnimatedLine(int index, int progress) {
    return animatedLines.at(index).at(progress);
}


// custom LERP
int Intro::linearInterpolation(float t) {
    return TIME_START + (easeIn(t)*(TIME_END - TIME_START));
}

// nice tutorial: https://www.febucci.com/2018/08/easing-functions/
float Intro::easeIn(float t) {
    return t*t;
}
