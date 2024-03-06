#include <iostream>
#include "GameWrench.h"
#include <SFML/Graphics.hpp>

static std::vector<gw::Vector2f> animationRange(int row, int col, int range) {
	std::vector<gw::Vector2f> animation;
	for (int i = col; i < col + range; i++) {
		animation.emplace_back(i, row);
	}
	return animation;
}

int main() {
	// Create player sprite from skeleton character
	std::string spritePath = "./sprites/skeleton_spritesheet.png";
	gw::Entity player(spritePath, 128, 128);
	player.setPosition(900, 500);
	player.setScale(2.5f, 2.5f);

	// Create animations for the player
	player.addAnimation("die", animationRange(0, 0, 3))
		.addAnimation("attack", animationRange(0, 10, 5))
		.addAnimation("jump_start", animationRange(4, 0, 6))
		.addAnimation("jump_end", animationRange(4, 6, 4))
		.addAnimation("run", animationRange(2, 7, 7))
		.addAnimation("idle", animationRange(2, 0, 7));

	// Make new still skeleton from already existing skeleton sprite
	gw::Entity stillSkeleton(player);
	stillSkeleton.animate("attack", 0.09); // Play attack forever

	// Create an effect
	std::string sfxPath = "./sprites/fireball_spritesheet.png";
	gw::Effect explode(sfxPath, gw::Vector2u(128, 128));
	explode.setAnimation(animationRange(5, 0, 13));
	explode.playEffect(5, 0.06);
	explode.setPosition(600, 600);

	// Create backgrounds
	gw::Sprite background1("./sprites/blue_city.png", 2302, 1395);
	background1.setPosition(960, 540);
	gw::Sprite background2("./sprites/misty_city.png", 2302, 1395);
	background2.setPosition(960, 540);

	// Create game map
	gw::GameMap map("Origin");
	map.addRoomRight("Origin - right");

	//// Add sprites to map
	// Origin room
	map.curRoom->addSprite(player)
		.addSprite(background1)
		.addSprite(stillSkeleton);
	// Origin - right room
	map.curRoom->right->addSprite(background2)
		.addSprite(player)
		.addSprite(explode);

	gw::Game game(map, 1920, 1080, "First Game");

	bool executed = false;
	bool inAir = false;
	// Main game loop
	while (game.isPlaying()) {
		// Default animation to idle
		player.animate("idle", 0.1);

		// Movement animations and positioning
		gw::Vector2f speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { 
			speed.x -= 512.0f;
			player.animate("run", 0.07);
			if (!player.isMirroredX()) { player.mirrorX(); }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
			speed.x += 512.0f; 
			player.animate("run", 0.07);
			if (player.isMirroredX()) { player.mirrorX(); }
		}
		player.setVelocity(speed.x, player.getVelocity().y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player.animate("jump_start", 0.07, false);
			player.addVelocity(0, -50);
			inAir = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			player.animate("attack", 0.09, false);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
			explode.playEffect(1, 0.07);
		}

		// Jump physics
		if (inAir) { 
			player.addVelocity(0, +10);
		}
		if (player.getPosition().y >= 501 && inAir) {
			gw::Vector2f vel = player.getVelocity();
			player.setVelocity(vel.x, 0);
			gw::Vector2f pos = player.getPosition();
			player.setPosition(pos.x, 500);
			player.animate("jump_end", 0.07, false);
			inAir = false;
		}

		// Display frames to the screen
		game.outputFrame();
		
		// Change rooms after 8 seconds
		if (game.gameTime() > 8 && !executed) { map.curRoom = map.curRoom->right; executed = true; }
	}

}