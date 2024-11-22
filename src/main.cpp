#include "Gra.hpp"

int main()
{
    Gra game{};
    while (true)
    {
        game.akcja_gracza();
        if(game.get_stan()==false)
        {
            break;
        }
    }
    
}
