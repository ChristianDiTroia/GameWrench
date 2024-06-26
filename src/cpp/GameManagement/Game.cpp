#include "GameManagement/Game.hpp"

#include <algorithm>

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
    window.setView(sf::View(
        sf::Vector2f(resolutionX / 2.0f, resolutionY / 2.0f),
        sf::Vector2f(resolutionX, resolutionY)
    ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators
////////////////////////////////////////////////////////////////////////////////////////////////////

/// Displays a graphical frame to the game window.
/// Should be called repeatedly in a main game loop.
void gw::Game::outputFrame() {
    // Poll window events //
    sf::Event evnt;
    while (window.pollEvent(evnt)) {
        switch (evnt.type) {
            case (sf::Event::Closed):
                window.close();
                running = false;
                break;
            case (sf::Event::LostFocus):
                window.waitEvent(evnt);
                if (evnt.type == sf::Event::GainedFocus) {
                    break;
                }
        }
    }
    // Run the game //
    if (running) {
        deltaTime = clock.restart().asSeconds(); // time between last 2 outputted frames
        totalTime += deltaTime; // record actual time game is running
        deltaTime = std::min(deltaTime, 1.0f / 20.0f); // artificially keep deltaTime >= 20fps

        // Clear previous frame
        window.clear();
        // Update state of all sprites in the current room
        updateGameState();
        // Draw all sprites in the current room
        drawAll();
        // Display frame on screen
        window.display();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members
////////////////////////////////////////////////////////////////////////////////////////////////////

void gw::Game::updateSprites(const std::vector<gw::AnimatedSprite*>& sprites) {
    for (AnimatedSprite* sprite : sprites) { sprite->update(deltaTime); }
}

void gw::Game::updateGameState() {
    updateSprites(map.curRoom->getAnimatedSprites());
    updateSprites(map.getGlobalAnimatedSprites());
    for (Collider* collider : map.curRoom->colliders) { collider->resolveAllCollisions(); }
}

void gw::Game::draw(const std::vector<Sprite*>& sprites) {
    for (Sprite* sprite : sprites) { window.draw(*sprite); }
}

void gw::Game::draw(const std::vector<AnimatedSprite*>& sprites) {
    for (AnimatedSprite* sprite : sprites) { window.draw(*sprite); }
}

void gw::Game::drawAll() {
    draw(map.curRoom->getSprites());
    draw(map.curRoom->getAnimatedSprites());
    draw(map.getGlobalAnimatedSprites());
    draw(map.getGlobalSprites());
}