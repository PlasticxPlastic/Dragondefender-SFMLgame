#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Game.h"

using namespace sf;
int main()
{
    sf::err().rdbuf(NULL);
    srand(NULL);
    sf::Music music;
    music.openFromFile("Sounds/x11.ogg");
    music.setVolume(5);
    music.play();
    music.setLoop(true);
    Game game;
    game.run();
    return 0;
}