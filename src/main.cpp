#include "Gra.hpp"
#include <iostream>

int main()
{
    Gra game{};
    std::cout << "##### WITAJ W GRZE! #####\n\nzinz - zatrudnij inżyniera\nzmag - zatrudnij magazyniera\nzmkt - "
                 "zatrudnij marketera\nzrob - zatrudnij robotnika\nkredyt - wez kredyt\nkt - koniec tury\n";
    while (true)
    {
        game.akcjaGracza();
        if (game.getStan() == false)
        {
            break;
        }
    }
}
