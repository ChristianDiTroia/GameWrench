#include "Game.h"

using namespace gw;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

gw::Game::Game(GameMap& map, Vector2u resolution, std::string name) :
    Game(map, resolution.x, resolution.y, name)
{}

gw::Game::Game(GameMap& map, int resolutionX, int resolutionY, std::string name) :
    map(map),
    window(sf::VideoMode(resolutionX, resolutionY), name, sf::Style::Default),
    deltaTime(0),
    totalTime(0),
    running(true)
{
    window.setVerticalSyncEnabled(true); // framerate == monitor's refresh rate
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators
////////////////////////////////////////////////////////////////////////////////////////////////////

/// Displays a graphical frame to the game window.
/// Should be called repeatedly in a main game loop.
bool gw::Game::outputFrame() {
    if (running) {
        deltaTime = clock.restart().asSeconds();    // record time since last frame outputted
        totalTime += deltaTime;

        // Poll window events
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
                running = false;
            }
        }

        // Clear previous frame
        window.clear();
        // Draw Sprites
        for (gw::Sprite* sprite : map.curRoom->spriteList()) { window.draw(*sprite); }
        // Update and draw AnimatedSprites
        for (gw::AnimatedSprite* sprite : map.curRoom->animatedSpriteList()) {
            sprite->update(deltaTime);
            window.draw(*sprite);
        }
        // Display frame on screen
        window.display();
    }
    return running;
}