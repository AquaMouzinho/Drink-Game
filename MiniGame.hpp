#ifndef MINIGAME_HPP
#define MINIGAME_HPP

#include "ASCII_Engine/SpriteBuffer.hpp"

class MiniGame
{
public:
    MiniGame(){}

    static void run();
private:
    static SpriteBuffer screen;
};

#endif