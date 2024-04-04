#include <iostream>

#include "GameWrench.hpp"

int main() {
	// Create player sprite from skeleton character
	std::string spritePath = "./sprites/skeleton_spritesheet.png";
	gw::Entity player(spritePath, 128, 128);
	player.setPosition(900, 500);
	player.setScale(2.5f, 2.5f);

	// Create animations for the player
	player.addAnimation("die", gw::helpers::rowAnimation(0, 0, 3))
		.addAnimation("hurt", gw::helpers::rowAnimation(0, 3, 5))
		.addAnimation("attack", gw::helpers::rowAnimation(0, 10, 14))
		.addAnimation("jump_start", gw::helpers::rowAnimation(4, 0, 5))
		.addAnimation("jump_mid", gw::helpers::rowAnimation(4, 5, 5))
		.addAnimation("jump_end", gw::helpers::rowAnimation(4, 6, 9))
		.addAnimation("jump_full", gw::helpers::rowAnimation(4, 0, 9))
		.addAnimation("run", gw::helpers::rowAnimation(2, 7, 13))
		.addAnimation("idle", gw::helpers::rowAnimation(2, 0, 6))
		.addAnimation("all", gw::helpers::multiRowAnimation(0, 0, {14, 13 ,13, 7, 9}));

	// Make new still skeleton from already existing skeleton sprite
	gw::Entity stillSkeleton(player);
	stillSkeleton.animate("all", 0.1); // Play all forever

	// Create an effect
	std::string sfxPath = "./sprites/fireball_spritesheet.png";
	gw::Effect explode(sfxPath, gw::Vector2u(128, 128));
	explode.setAnimation(gw::helpers::rowAnimation(5, 0, 12));
	explode.setPosition(600, 600);
	// Duplicate the effect
	gw::Effect explode2(explode);
	// Start first effect, not second
	explode.playEffect(1, 0.04, 300, 0);

	// Create backgrounds
	gw::Sprite background1("./sprites/blue_city.png", 2302, 1395);
	background1.setPosition(960, 540);
	gw::Sprite background2("./sprites/misty_city.png", 2302, 1395);
	background2.setPosition(960, 540);

	// Create TileStructure 
	gw::TileStructure structure("./sprites/pixel_adventure_sprites/Terrain/Terrain_(16x16).png", 16, 16);
	structure.setSubsprite(9, 18, 2, 2);
	structure.setScale(3, 3);
	structure.asRow(5);
	structure.setPosition(300, 300);
	gw::TileStructure structure2(structure);
	structure2.asRectangle(8, 8, true);
	structure2.positionRelativeTo(structure, gw::TileStructure::xCenter, gw::TileStructure::bottom);

	// Create game map
	gw::GameMap map("Origin");
	map.addRoomRight("Origin - right");

	//// Add sprites to map
	// Global Sprites
	map.addGlobalSprite(player)
		.addGlobalSprite(explode2);
	// Origin room
	map.curRoom->addSprite(background1)
		//.addSprite(stillSkeleton)
		.addSprite(structure)
		.addSprite(structure2);
	// Origin - right room
	map.curRoom->right->addSprite(background2)
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !inAir) {
			player.animate("jump_start", 0.05, false);
			player.addVelocity(0, -800);
			inAir = true;
			explode2.setPosition(player.getPosition().x, player.getPosition().y + 128);
			explode2.playEffect(1, .02);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			player.animate("attack", 0.09, false);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
			explode.playEffect(10, 0.07);
		}

		// Jump physics
		if (inAir) { 
			player.addVelocity(0, 10);
			player.animate("jump_mid", 0.05);
		}
		if (player.getVelocity().y >= 800 && inAir) {
			gw::Vector2f vel = player.getVelocity();
			player.setVelocity(vel.x, 0);
			player.animate("jump_end", 0.05, false);
			inAir = false;
		}

		// effect logic
		if (explode.getPosition().x >= 1920) { explode.setVelocity(-300, 0); }
		else if (explode.getPosition().x <= 0) { explode.setVelocity(300, 0); }
		if (!explode.isPlaying()) { explode.playEffect(1, 0.04); }
		if (abs(player.getPosition().x - explode.getPosition().x) <= 20 && map.curRoom != map.head) player.animate("hurt", 0.1, false);

		// Allow player to move between rooms
		if (player.getPosition().x >= 1920 && !executed) {
			map.curRoom = map.curRoom->right; executed = true;
			player.setPosition(100, player.getPosition().y);
			explode.hide();
		}
		else if (player.getPosition().x <= 0 && executed) {
			map.curRoom = map.curRoom->left; executed = false;
			player.setPosition(1920, player.getPosition().y);
			explode.hide();
		}

		// Display frames to the screen
		game.outputFrame();
	}
	
}