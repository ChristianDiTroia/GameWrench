#include <iostream>
#include "GameWrench.h"
#include <SFML/Graphics.hpp>

static std::vector<gw::Vector2u> animationRange(int row, int col, int range) {
	std::vector<gw::Vector2u> animation;
	for (int i = col; i < col + range; i++) {
		animation.emplace_back(i, row);
	}
	return animation;
}

int main() {

	sf::RenderWindow window(sf::VideoMode(2560, 1440), "GameWrench", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(165);
	sf::Clock time;
	float timer = 0;
	float printTimer = 0;
	float deltaTime = 0;

	// Create player sprite from skeleton character
	std::string spritePath = "./sprites/skeleton_spritesheet.png";
	gw::Entity player(spritePath, gw::Vector2u(128, 128));
	player.setPosition(900, 500);
	player.setScale(2.5f, 2.5f);

	// Create animations for the player
	player.addAnimation("die", animationRange(0, 0, 3));
	player.addAnimation("attack", animationRange(0, 10, 5));
	player.addAnimation("jump", animationRange(4, 0, 10));
	player.addAnimation("run", animationRange(2, 7, 7));
	player.addAnimation("idle", animationRange(2, 0, 7));

	// Create an effect
	std::string sfxPath = "./sprites/fireball_spritesheet.png";
	gw::Effect explode(sfxPath, gw::Vector2u(128, 128));
	explode.setAnimation(animationRange(5, 0, 13));
	explode.playEffect(5, 0.06);
	explode.setPosition(600, 600);

	// Main game loop
	while (window.isOpen()) {
		deltaTime = time.restart().asSeconds();
		printTimer += deltaTime;
		timer += deltaTime;

		// Window events loop
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) { window.close(); }
			switch (evnt.type) {
			case sf::Event::LostFocus:
				while (evnt.type != sf::Event::GainedFocus) {
					window.waitEvent(evnt);
				}
				break;
			}
		};

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
		player.setVelocity(speed.x, speed.y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player.animate("jump", 0.07, false);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			player.animate("attack", 0.09, false);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
			explode.playEffect(1, 0.07);
		}

		// Debug info to console
		if (printTimer >= 0.5) {
			std::cout << speed.x << " " << speed.y << std::endl;
			std::cout << player.getCurrentAnimation() << std::endl;
			printTimer = 0;
		}

		// Update AnimatedSprites
		player.update(deltaTime);
		explode.update(deltaTime);

		// Draw sprites
		window.clear(sf::Color::White);
		window.draw(player);
		window.draw(explode);

		// Output frame to window
		window.display();
		
	}

}