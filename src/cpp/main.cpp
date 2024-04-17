#include <iostream>
#include <cstdlib>

#include "GameWrench.hpp"

using namespace gw;

class Released
{
public:

	Released(sf::Keyboard::Key key) : key(key), isPressed(false), wasPressed(false) {}

	bool operator () () {
		bool released = false;

		if (sf::Keyboard::isKeyPressed(key)) isPressed = true;
		else isPressed = false;

		if (wasPressed && !isPressed) released = true;

		if (isPressed) wasPressed = true;
		else wasPressed = false;

		return released;
	}

private:
	sf::Keyboard::Key key;
	bool isPressed;
	bool wasPressed;
};

Released bRelease(sf::Keyboard::B);

// Define 1 in-game meter
gw::helpers::PixelConverter meter(16);

static void handleCollision (gw::Sprite& sprite, gw::Sprite& collidedWith, 
	gw::Vector2f collision) {
	if (sprite.getPosition().x < collidedWith.getPosition().x) { collision.x *= -1; }
	if (sprite.getPosition().y < collidedWith.getPosition().y) { collision.y *= -1; }
	else {
		// If equal positioning, send sprite toward middle of the screen //
		gw::Vector2f centerScreen(1920 / 2, 1080 / 2);
		if (sprite.getPosition() > centerScreen) { collision = collision * -1; }
	}
	//Entity& player = dynamic_cast<Entity&>(sprite);
	//if (collision.y > 0) { player.addVelocity(0, -player.getVelocity().y); }
	sprite.movePosition(collision);
	/*std::cout << collision.x << "     " << collision.y << std::endl;*/
};

void static playerActions(gw::AnimatedSprite& self) {
	Entity& player = dynamic_cast<Entity&>(self);
	typedef sf::Keyboard kb;

	player.animate("idle", 0.07);

	bool D = false; bool A = false;
	if (kb::isKeyPressed(kb::D)) {
		player.animate("run", 0.06);
		if (player.isMirroredX()) { player.mirrorX(); }
		D = true;
	}
	if (kb::isKeyPressed(kb::A)) {
		player.animate("run", 0.05);
		if (!player.isMirroredX()) { player.mirrorX(); }
		A = true;
	}

	float speedx = meter.toPixels(10);
	Vector2f velocity(0, player.getVelocity().y);
	velocity.x = D * speedx + A * -speedx;
	player.setVelocity(velocity);

	float speedy = meter.toPixels(-20);
	if (kb::isKeyPressed(kb::Space)) {
		player.animate("jump", 0.1);
		player.setVelocity(player.getVelocity().x, speedy);
	}
	if (player.getPosition().y < meter.toPixels(19.5)) { player.animate("jump", 0.1); }

	// simulate gravity
	if (player.getVelocity().y < meter.toPixels(10)) { player.addVelocity(0, meter.toPixels(1)); }
}

int main() {
	
	// Create map and game objects
	GameMap map;
	Game game(map, 640, 360, "GameWrench First Game!!!");

	// Set background
	Sprite background("./sprites/pixel_adventure_sprites/background/Yellow.png", 64, 64);
	meter.scaleSprite(background, 40, 22.5);
	background.setPosition(meter.toPixels(20), meter.toPixels(11.25));
	map.addGlobalSprite(background);

	// create the floor
	TileStructure floor("./sprites/pixel_adventure_sprites/terrain/Terrain_(16x16).png", 16, 16);
	floor.setSubsprite(0, 6, 3, 3);
	meter.scaleSprite(floor, 2, 2);
	floor.asRow(20);
	floor.setPosition(meter.toPixels(1), meter.toPixels(21.5));
	map.addGlobalSprite(floor);

	// create player character
	Entity ninjaFrog("./sprites/pixel_adventure_sprites/Main characters/Ninja Frog/ninjaFrogSpriteSheet_32x32.png", 32, 32);
	ninjaFrog.addAnimation("idle", gw::helpers::rowAnimation(2, 0, 9))
		.addAnimation("run", gw::helpers::rowAnimation(3, 0, 10))
		.addAnimation("jump", gw::helpers::rowAnimation(0, 0, 0));
	ninjaFrog.setPosition(meter.toPixels(20), meter.toPixels(19.5));
	ninjaFrog.defineBehavior(playerActions);
	map.addGlobalSprite(ninjaFrog);

	// collision detection with the floor
	BoxCollider floorCollision(handleCollision);
	floorCollision.applyCollision(ninjaFrog)
		.canCollideWith(floor);
	game.addCollider(floorCollision);

	while (game.isPlaying()) { game.outputFrame(); }
}