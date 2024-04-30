#include "./demos.hpp"

#include "GameWrench.hpp"
#include <SFML/Audio.hpp>

using namespace gw;

namespace demo4setup
{
    bool onBottom = true;
    bool spacePressed = false;

    helpers::PixelConverter meter(16);

    static void playerActions(AnimatedSprite& self) {
        Entity& player = dynamic_cast<Entity&>(self);
        typedef sf::Keyboard kb;

        player.animate("run", 0.07, false);

        bool inAir = player.getVelocity().y != 0;
        if (kb::isKeyPressed(kb::Space) && !spacePressed) {
            spacePressed = true;
            if (!inAir) {
                if (onBottom) { player.setVelocity(meter.toPixels(0, -40)); }
                else { player.setVelocity(meter.toPixels(0, 40)); }
            } else { // in air jump, flip gravity
                float gravity = meter.toPixels(100);
                if (onBottom) { gravity *= -1; }
                player.mirrorY();
                player.applyGravity(0, gravity);
            }
        }
        else {
            spacePressed = false;
        }
    }

    static void playerCollision(Sprite& sprite, Sprite& collidedWith, Vector2f collision) {
        Entity& player = dynamic_cast<Entity&>(sprite);
        player.setVelocity(0, 0);
        if (sprite.getPosition().y > collidedWith.getPosition().y) { 
            onBottom = false; 
        }
        else {
            onBottom = true;
        }

    }

} // namespace demo4setup

void demos::runDemo4() {
    using namespace demo4setup;

    GameMap map("cave");
    Game game(map, 640, 360, "Cave Runner");

    Entity knight("./sprites/dungeon_crawler_sprites/dungeon_spritesheet(32x32).png", 16, 32);
    knight.addAnimation("run", helpers::rowAnimation(3, 10, 15));
    meter.scaleSprite(knight, 2, 4);
    knight.setPosition(meter.toPixels(10, 11.5));
    knight.defineBehavior(playerActions);
    knight.applyGravity(meter.toPixels(0, 100));
    map.curRoom->addSprite(knight);

    TileStructure bottom("./sprites/pixel_adventure_sprites/terrain/Terrain_(16x16).png", 16, 16);
    bottom.setSubsprite(0, 0, 3, 3);
    meter.scaleSprite(bottom, 2, 2);
    bottom.asRow(20);
    bottom.setPosition(meter.toPixels(1, 21.5));
    map.curRoom->addSprite(bottom);

    TileStructure top(bottom);
    top.setPosition(meter.toPixels(1, 1));
    map.curRoom->addSprite(top);

    BoxCollider terrainCollider(playerCollision, true);
    terrainCollider.applyCollision(knight)
        .canCollideWith(top)
        .canCollideWith(bottom);
    map.curRoom->addCollider(terrainCollider);

    while (game.isPlaying()) {
        game.outputFrame();
    }
}