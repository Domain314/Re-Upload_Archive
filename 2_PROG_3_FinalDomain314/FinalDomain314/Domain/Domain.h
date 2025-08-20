#ifndef DOMAIN_H
#define DOMAIN_H
#pragma once


#include <string>

#define randomNum(max) (std::rand()%max)
#define clearScreen() (std::cout << "\033c")

namespace Domain
{
    typedef struct Vector2 {
        int x;
        int y;

        Vector2(int x = 0, int y = 0) {
            this->x = x;
            this->y = y;
        };

        void setAllSides(int x, int y) {
            this->x = x;
            this->y = y;
        }

    }Vector2;

    typedef struct Vector3 {
        int x;
        int y;
        int z;

        Vector3(int x = 0, int y = 0, int z = 0) {
            this->x = x;
            this->y = y;
            this->z = z;
        };

        void setAllSides(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

    }Vector3;

}


#endif // DOMAIN_H