#include <SFML/Graphics.hpp>
#include "gra.h"
int main()
{
        //glowna petla
    gra game;
    while (game.running())
    {
        game.update();
        game.render();
    }


    return 0;
}