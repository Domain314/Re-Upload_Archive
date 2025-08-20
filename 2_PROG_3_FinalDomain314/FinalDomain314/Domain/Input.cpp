#include "Input.hpp"

char Input::getInput() {
    unsigned char ch1 = _getch();

    switch ((int)ch1)
    {
        // 10 = Enter
        case KEY_ENTER:
            return '.';
            break;
        case KEY_ESC:
            return getInput2();
            break;
        default:
            break;
    }
    return ch1;
}

char Input::getInput2() {
    unsigned char ch1 = _getch();

    if (ch1 == KEY_ARROW_CHAR1)
    {
        // Some Arrow key was pressed, determine which?
        unsigned char ch2 = _getch();

        switch (ch2)
        {
            case KEY_ARROW_UP:
                return 'w'; break;
            case KEY_ARROW_DOWN:
                return 's'; break;
            case KEY_ARROW_LEFT:
                return 'a'; break;
            case KEY_ARROW_RIGHT:
                return 'd'; break;
        }
    }
    else
    {
        return ',';
    }
    return ch1;
}

// get Input instantly, without pressing Enter
// src: https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
unsigned char Input::_getch(void)
{
    unsigned char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    //printf("%c\n", buf);
    return buf;
}

char Input::_getChar() {
    char c;
    std::cin >> c;
    return c;
}