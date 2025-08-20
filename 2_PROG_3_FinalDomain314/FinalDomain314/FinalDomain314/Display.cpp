#include <chrono>
#include "Display.hpp"

Display::Display(std::vector<Team*> teams) {
    this->maxX = teams.at(0)->getPlayers().size() > teams.at(1)->getPlayers().size() ? teams.at(0)->getPlayers().size() : teams.at(1)->getPlayers().size();
    maxX = maxX < 5 ? 5 : maxX;
    createLines(maxX);

    //display with 2 different colours for both teams.
    display1.push_back({"| "});
    display2.push_back({"| \033[1m\033[33m"});
    for (int j = 0; j < maxX; ++j) {
        display1.at(0).push_back("    ");
        display2.at(0).push_back("    ");
    }
    display1.at(0).push_back(" |");
    display2.at(0).push_back("\033[0m |");
    display1.push_back({"| "});
    display2.push_back({"| \033[35m"});
    for (int j = 0; j < maxX; ++j) {
        display1.at(1).push_back("    ");
        display2.at(1).push_back("    ");
    }
    display1.at(1).push_back(" |");
    display2.at(1).push_back("\033[0m |");

    // display without colour
//    for (int i = 0; i < 2; ++i) {
//        display1.push_back({"| "});
//        display2.push_back({"| "});
//        for (int j = 0; j < maxX; ++j) {
//            display1.at(i).push_back("    ");
//            display2.at(i).push_back("    ");
//        }
//        display1.at(i).push_back(" |");
//        display2.at(i).push_back(" |");
//    }
}

Display::~Display() {
    std::vector<std::vector<std::string>>().swap(display1);
    std::vector<std::vector<std::string>>().swap(display2);
    std::vector<std::string>().swap(console);
}

void Display::createLines(int screenX) {
    emptyLine += "| ";
    fullLine += "----";
    for (int i = 0; i < screenX; ++i) {
        fullLine += "----";
        emptyLine += "    ";
    }
    fullLine += "\n";
    emptyLine += " |\n";
}

// set strings for each character. display1 = health; display2 = name.
// set spaces before and after name, for marking arrows ">pw<".
void Display::setCharacters(std::vector<Team*> teams) {
    int groupMember = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < maxX+2; ++j) {
            if (j >= teams.at(i)->getPlayers().size()) { break; }
            display1.at(i).at(j+1) = teams.at(i)->getPlayer(groupMember)->getHealthAsString();
            display2.at(i).at(j+1) = " " + teams.at(i)->getPlayer(groupMember)->getNameAsString() + " ";
            teams.at(i)->getPlayer(groupMember)->setIndex(j);
            groupMember++;
        }
        groupMember = 0;
    }
}

// print all strings and characters and measure time in microseconds. display result
void Display::printDisplays() {
    auto start = std::chrono::high_resolution_clock::now();

    clearScreen();
    std::cout << fullLine;
    std::cout << emptyLine;
    printDisplay();
    std::cout << emptyLine;
    std::cout << fullLine;
    std::cout << thisTurn;
    for (auto & i : console) {
        std::cout << i << "\n";
    }
    std::cout << fullLine;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << std::endl;
}

void Display::printWall() {
    std::cout << "\n";
}

// print each display
void Display::printDisplay() {
    for (int i = 0; i < maxX+2; ++i) {
        std::cout << display1.at(0).at(i);
    }
    printWall();
    for (int i = 0; i < maxX+2; ++i) {
        std::cout << display2.at(0).at(i);
    }
    printWall();
    std::cout << emptyLine;
    for (int i = 0; i < maxX+2; ++i) {
        std::cout << display1.at(1).at(i);
    }
    printWall();
    for (int i = 0; i < maxX+2; ++i) {
        std::cout << display2.at(1).at(i);
    }
    printWall();
}

// place arrows, left and right of player name. place on all, if group spell
void Display::markPlayer(int teamNum, int playerIndex, bool isGroupSpell){
    if (isGroupSpell) {
        for (int i = 0; i < display2.at(teamNum).size()-1; ++i) {
            if (display2.at(teamNum).at(i).at(1) == ' ') { continue; }
            display2.at(teamNum).at(i).at(0) = '>';
            display2.at(teamNum).at(i).at(3) = '<';
        }
    } else {
        display2.at(teamNum).at(playerIndex+1).at(0) = '>';
        display2.at(teamNum).at(playerIndex+1).at(3) = '<';
    }
}

// function rollercoaster
void Display::unMarkPlayer(int teamNum, int playerIndex, bool isGroupSpell) {
    if (isGroupSpell) {
        unMarkAll();
    } else {
        display2.at(teamNum).at(playerIndex+1).at(0) = ' ';
        display2.at(teamNum).at(playerIndex+1).at(3) = ' ';
    }
}

void Display::unMarkAll() {
    for (int i = 0; i < display2.at(0).size()-2; ++i) {
        unMarkPlayer(0, i, false);
    }
    for (int i = 0; i < display2.at(1).size()-2; ++i) {
        unMarkPlayer(1, i, false);
    }
}
// end of function rollercoaster

void Display::markConsoleLine(int index){
    console.at(index).at(0) = '>';
}

void Display::unMarkConsoleLine(int index) {
    console.at(index).at(0) = ' ';
}

void Display::addMessage(std::string mes) {
    console.push_back(mes);
}

void Display::resetAllMessages() {
    console.clear();
}

// set first line of console
void Display::playersTurnMessage(std::string entity, std::string name, int teamNum) {
    resetAllMessages();
    std::string colour = teamNum == 0 ? BOLDYELLOW : MAGENTA;
    this->thisTurn = colour + entity + name + "'s turn.\n" + RESET;
}

// overload for non-NPC characters with MP
void Display::playersTurnMessage(std::string entity, std::string name, int mana, int teamNum) {
    resetAllMessages();
    std::string colour = teamNum == 0 ? BOLDYELLOW : MAGENTA;
    this->thisTurn = colour + entity + name + "'s turn. " + std::to_string(mana) + "MP\n" + RESET;
}

// simulate thinking. silly humans.
void Display::animateDecision(std::string name) {
    int time = 100000;
    console.push_back(" ");
    for (int i = 0; i < 2; ++i) {
        console.at(console.size()-1) = name + " choose -";
        printDisplays();
        usleep(time);
        console.at(console.size()-1) = name + " choose \\";
        printDisplays();
        usleep(time);
        console.at(console.size()-1) = name + " choose |";
        printDisplays();
        usleep(time);
        console.at(console.size()-1) = name + " choose /";
        printDisplays();
        usleep(time);
    }
    console.pop_back();
}

