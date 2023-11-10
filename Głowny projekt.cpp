#include <iostream>
#include "gra.h"

int main()
{
    Game gra();
        //glowna petla
    while (window.isOpen())
    {
        
        while (gra.running())
        {
            gra.update();
            gra.render();
        }

        window.clear();
       
        window.display();
    }

    return 0;
}