#include "demos/demos.hpp"

#include "GameWrench.hpp"
#include <iostream>

using namespace gw;

namespace demo2setup
{	

////////////////////////////////////////////////////////////////////////////////////////////////////
// Global data
////////////////////////////////////////////////////////////////////////////////////////////////////
 
	// Game status - change this from anywhere to determine if the player has lost
	bool gameOver = false;

	// Define player globally as it is involved in most operations
	Entity ninjaFrog("./sprites/pixel_adventure_sprites/Main characters/Ninja Frog/ninjaFrogSpriteSheet_32x32.png", 32, 32);

	// Define 1 in-game meter for pixel unit conversions
	helpers::PixelConverter meter(16);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Game behavior functions (actions and collision)
////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define the player's controls
	static void playerActions(AnimatedSprite& self) {
		Entity& player = dynamic_cast<Entity&>(self);
		typedef sf::Keyboard kb;

		player.animate("idle", 0.06);

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

		float speedx = meter.toPixels(16);
		Vector2f velocity(0, player.getVelocity().y);
		velocity.x = D * speedx + A * -speedx;
		player.setVelocity(velocity);

		bool inAir = player.getVelocity().y != 0;
		float speedy = meter.toPixels(-40);
		if (kb::isKeyPressed(kb::Space) && !inAir) {
			player.animate("jump", 1);
			player.setVelocity(player.getVelocity().x, speedy);
		}
		if (inAir) {
			if (player.getVelocity().y > 0) {
				player.animate("fall", 1);
			}
			else {
				player.animate("jump", 1);
			}
		}

		if (player.getVelocity().y == 0) { player.addVelocity(0, 1); } // prevent y-vel == 0 inAir
	}

	// Define what happens when player collides with terrain
	static void playerCollision(Sprite& sprite, Sprite& collidedWith, Vector2f collision) {
		Entity& player = dynamic_cast<Entity&>(sprite);
		if ((collision.y > collision.x) /*&& collision.x <= 1*/) { // collision on Y
			// stop vertical momentum on y-axis collisions
			player.setVelocity(player.getVelocity().x, 0);
			if (player.getPosition().y > collidedWith.getPosition().y) player.addVelocity(0, 1); // bumped head - send back down
		}
		else if (collision.x > collision.y) { // collision on X
			// wall cling ability
			if (player.getVelocity().y >= 0) { player.setSubsprite(0, 3); } // don't cling if jumping
			player.setVelocity(player.getVelocity().x, 0); // stop falling when clinging
		}
	};
	
	// Define rockHead behavior
	static void rockHeadActions(AnimatedSprite& self) {
		Entity& rockHead = dynamic_cast<Entity&>(self);

		rockHead.animate("blink", 0.5, false);
		float dist = abs(ninjaFrog.getPosition().x - rockHead.getPosition().x);
		if (dist <= meter.toPixels(1) && rockHead.getVelocity().y == 0) {
			rockHead.setVelocity(0, meter.toPixels(15));
		}
		else if (rockHead.getPosition().y <= meter.toPixels(1.1)) {
			rockHead.setVelocity(0, 0); 
		}

	}

	// Define what happens when rockHead collides with terrain
	static void rockHeadCollision(Sprite& sprite, Sprite& collidedWith, Vector2f collision) {
		Entity& rockHead = dynamic_cast<Entity&>(sprite);
		if (collision.y > collision.x) { // collision on Y
			rockHead.setVelocity(rockHead.getVelocity().x, 0); // stop momentum on y-axis collisions
			if (rockHead.getPosition().y < collidedWith.getPosition().y) rockHead.setVelocity(meter.toPixels(0, -5)); // hit ground - send back up
		}
	};

	// Define enemy behavior
	static void enemyActions(AnimatedSprite& self) {
		Entity& enemy = dynamic_cast<Entity&>(self);

		// Make an enemy that follows the player when close by
		float velocity = 0;
		Vector2f dist = ninjaFrog.getPosition() - enemy.getPosition();
		if (abs(dist.x) <= meter.toPixels(10) && abs(dist.x) > 1 && abs(dist.y) < meter.toPixels(8)) {
			if (dist.x > 0) { // player towards the right
				velocity = meter.toPixels(4);
				if (enemy.isMirroredX()) { enemy.mirrorX(); }
			} else if (dist.x < 0) { // player towards the left
				velocity = meter.toPixels(-4);
				if (!enemy.isMirroredX()) { enemy.mirrorX(); }
			}
			enemy.animate("run", 0.1); // player in sight, chase player
		}
		else { // too close or too far from player, idle
			enemy.animate("idle", 0.1);
		}

		enemy.setVelocity(velocity, enemy.getVelocity().y);
	}

	// Define what happens when the player collides with an enemy
	static void enemyCollision(Sprite& sprite, Sprite& collidedWith, Vector2f collision) { gameOver = true;	}
	
	// Define what happens when the player collides with an item
	static void itemCollision(Sprite& sprite, Sprite& collidedWith, Vector2f collision) {

	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Level design
////////////////////////////////////////////////////////////////////////////////////////////////////

	// Room 1 terrain
	static SpriteCollection* buildRoom1() {
		TileStructure& floor = *(new TileStructure("./sprites/pixel_adventure_sprites/terrain/Terrain_(16x16).png", 16, 16));
		floor.setSubsprite(0, 6, 3, 3);
		meter.scaleSprite(floor, 2, 2);
		floor.asRow(20);
		floor.setPosition(meter.toPixels(1, 21.5));

		TileStructure& platform1 = *(new TileStructure(floor));
		platform1.setSubsprite(8, 0, 3, 3);
		platform1.movePosition(meter.toPixels(6, -6));
		platform1.asRow(4);

		TileStructure& platform2 = *(new TileStructure(platform1));
		platform2.movePosition(meter.toPixels(20, 0));

		TileStructure& platform3 = *(new TileStructure(platform2));
		platform3.setSubsprite(9, 13, 2, 2);
		meter.scaleSprite(platform3, 2, 2);
		platform3.movePosition(meter.toPixels(-12, -6));
		platform3.asRow(6);

		TileStructure& platform4 = *(new TileStructure(platform3));
		platform4.setSubsprite(5, 13, 2, 2);
		meter.scaleSprite(platform4, 1, 1);
		platform4.movePosition(meter.toPixels(-12.5, -6));

		TileStructure& platform5 = *(new TileStructure(platform4));
		platform5.movePosition(meter.toPixels(30, 0));

		TileStructure& beam = *(new TileStructure(platform3));
		beam.setSubsprite(8, 15, 1, 3);
		beam.asRectangle(2, 4, false);
		beam.positionRelativeTo(platform3, TileStructure::xCenter, TileStructure::bottom);

		TileStructure& wall1 = *(new TileStructure(platform3));
		wall1.setSubsprite(4, 17, 3, 3);
		wall1.asColumn(20);
		wall1.positionRelativeTo(floor, TileStructure::left, TileStructure::top);
		wall1.movePosition(meter.toPixels(2, 0));

		TileStructure& wall2 = *(new TileStructure(wall1));
		wall1.positionRelativeTo(floor, TileStructure::right, TileStructure::top);
		wall1.movePosition(meter.toPixels(-2, 0));

		SpriteCollection* room1 = new SpriteCollection;
		room1->addSprite(platform1)
			.addSprite(platform2)
			.addSprite(platform3)
			.addSprite(platform4)
			.addSprite(platform5)
			.addSprite(beam)
			.addSprite(wall1)
			.addSprite(wall2)
			.addSprite(floor);

		return room1;
	}

	// Room 1 rock head enemies
	static SpriteCollection* room1RockHeads() {
		Entity& rockHead = *(new Entity("./sprites/pixel_adventure_sprites/Traps/Rock Head/Blink (42x42).png", 42, 42));
		rockHead.addAnimation("blink", helpers::rowAnimation(0, 0, 3));
		rockHead.setPosition(meter.toPixels(20, 1.1));

		SpriteCollection* room1Rockheads = new SpriteCollection;
		room1Rockheads->addSprite(rockHead);

		return room1Rockheads;
	}

	// Room 1 character enemies
	static SpriteCollection* room1Enemies() {
		Entity& enemy1 = *(new Entity("./sprites/pixel_adventure_sprites/Main Characters/Mask dude/maskdude_spritesheet(32x32).png", 32, 32));
		enemy1.addAnimation("idle", helpers::rowAnimation(2, 0, 10))
			.addAnimation("run", helpers::rowAnimation(3, 0, 11));
		meter.scaleSprite(enemy1, 2, 2);
		enemy1.setPosition(meter.toPixels(30, 13.5));
		enemy1.applyGravity(meter.toPixels(0, 100));

		SpriteCollection* room1enemies = new SpriteCollection;

		room1enemies->addSprite(enemy1);

		return room1enemies;
	}

	// Room 1 collectables
	static SpriteCollection* room1Items() {
		Effect& orange1 = *(new Effect("./sprites/pixel_adventure_sprites/Items/Fruits/Orange.png", 32, 32));
		orange1.setAnimation(helpers::rowAnimation(0, 0, 16));
		orange1.playEffect(0.1);
		orange1.setPosition(meter.toPixels(20, 8));
		
		SpriteCollection* room1Items = new SpriteCollection;
		room1Items->addSprite(orange1);

		return room1Items;
	}

	// Room 2 terrain
	static SpriteCollection* buildRoom2() {
		TileStructure& roof = *(new TileStructure("./sprites/pixel_adventure_sprites/terrain/Terrain_(16x16).png", 16, 16));
		roof.setSubsprite(0, 0, 3, 3);
		meter.scaleSprite(roof, 2, 2);
		roof.asRow(20);
		roof.setPosition(meter.toPixels(1, 1));

		TileStructure& platform1 = *(new TileStructure(roof));
		platform1.setSubsprite(5, 13, 2, 2);
		meter.scaleSprite(platform1, 1, 1);
		platform1.setPosition(meter.toPixels(12.25, 20));
		platform1.asRectangle(16, 3, true);

		TileStructure& platform2 = *(new TileStructure(platform1));
		platform2.setSubsprite(1, 13, 2, 2);
		platform2.asRectangle(3, 6, true);
		platform2.positionRelativeTo(platform1, TileStructure::xCenter, TileStructure::top);

		TileStructure& platform3 = *(new TileStructure(platform2));
		platform3.asRectangle(3, 3, true);
		platform3.positionRelativeTo(platform2, TileStructure::left, TileStructure::bottom);
		platform3.movePosition(meter.toPixels(0, -3.05));

		TileStructure& platform4 = *(new TileStructure(platform3));
		platform4.positionRelativeTo(platform2, TileStructure::right, TileStructure::bottom);
		platform4.movePosition(meter.toPixels(0, -3.05));

		TileStructure& platform5 = *(new TileStructure(platform4));
		platform5.asRectangle(2, 2, false);
		platform5.positionRelativeTo(platform4, TileStructure::right, TileStructure::bottom);
		platform5.movePosition(meter.toPixels(0, -2));

		TileStructure& platform6 = *(new TileStructure(platform5));
		platform5.positionRelativeTo(platform3, TileStructure::left, TileStructure::bottom);
		platform5.movePosition(meter.toPixels(0, -2));

		TileStructure& wall1 = *(new TileStructure(platform5));
		wall1.setSubsprite(4, 17, 3, 3);
		meter.scaleSprite(wall1, 2, 2);
		wall1.setPosition(meter.toPixels(1, 3));
		wall1.asColumn(11);

		TileStructure& wall2 = *(new TileStructure(wall1));
		wall2.setPosition(meter.toPixels(39, 3));

		TileStructure& platform7 = *(new TileStructure(platform1));
		platform7.asRectangle(8, 2, false);
		platform7.positionRelativeTo(wall1, TileStructure::right, TileStructure::yCenter);
		platform7.movePosition(meter.toPixels(4, -4));

		TileStructure& platform8 = *(new TileStructure(platform7));
		platform8.positionRelativeTo(wall2, TileStructure::left, TileStructure::yCenter);
		platform8.movePosition(meter.toPixels(-4, -4));

		SpriteCollection* room2 = new SpriteCollection;
		room2->addSprite(roof)
			.addSprite(platform1)
			.addSprite(platform2)
			.addSprite(platform3)
			.addSprite(platform4)
			.addSprite(platform5)
			.addSprite(platform6)
			.addSprite(platform7)
			.addSprite(platform8)
			.addSprite(wall1)
			.addSprite(wall2);

		return room2;
	}

	// Room 2 obstacles
	static SpriteCollection* room2Obstacles() {
		Sprite& spikes1 = *(new Sprite("./sprites/pixel_adventure_sprites/Traps/Spike Head/idle.png", 5, 5));
		spikes1.setSubsprite(1, 1, 9, 9);
		meter.scaleSprite(spikes1, 3, 3);
		spikes1.setPosition(meter.toPixels(26, 9));

		Sprite& spikes2 = *(new Sprite(spikes1));
		spikes2.movePosition(meter.toPixels(8, 0));

		Sprite& spikes3 = *(new Sprite(spikes1));
		meter.scaleSprite(spikes3, 5, 5);
		spikes3.movePosition(meter.toPixels(-13, 5));

		SpriteCollection* room2Obstacles = new SpriteCollection;

		room2Obstacles->addSprite(spikes1)
			.addSprite(spikes2)
			.addSprite(spikes3);

		return room2Obstacles;
	}

	static void deleteCollection(SpriteCollection* collection) {
		for (Sprite* sprite : collection->getSprites()) { delete sprite; }
		for (Sprite* sprite : collection->getAnimatedSprites()) { delete sprite; }
		delete collection;
	}

} // namespace demo2

void demos::runDemo2() {
	using namespace demo2setup;

	//// Create map and game objects ////

	GameMap map("room1");
	map.addRoomTop("room2");
	Game game(map, 640, 360, "GameWrench Demo 2!!!");

	//// Set backgrounds ////

	Sprite background1("./sprites/pixel_adventure_sprites/background/Yellow.png", 64, 64);
	meter.scaleSprite(background1, 40, 23);
	background1.setPosition(meter.toPixels(20, 11.25));
	map.curRoom->addSprite(background1);

	Sprite background2("./sprites/pixel_adventure_sprites/background/Blue.png", 64, 64);
	meter.scaleSprite(background2, 40, 23);
	background2.setPosition(meter.toPixels(20, 11.25));
	map.curRoom->top->addSprite(background2);

	Sprite gameOverFlash("./sprites/pixel_adventure_sprites/background/Green.png", 64, 64);
	meter.scaleSprite(gameOverFlash, 40, 23);
	gameOverFlash.setPosition(meter.toPixels(20, 11.25));
	gameOverFlash.hide();
	map.addGlobalSprite(gameOverFlash);

	//// Create room layouts/terrain ////

	SpriteCollection* room1 = buildRoom1();
	map.curRoom->addCollection(*room1);
	SpriteCollection* room2 = buildRoom2();
	map.curRoom->top->addCollection(*room2);

	//// Create player character ////

	ninjaFrog.addAnimation("idle", gw::helpers::rowAnimation(2, 0, 9))
		.addAnimation("run", gw::helpers::rowAnimation(3, 0, 10))
		.addAnimation("jump", gw::helpers::rowAnimation(0, 1, 1))
		.addAnimation("fall", gw::helpers::rowAnimation(0, 0, 0));
	ninjaFrog.setPosition(meter.toPixels(10, 13.5));
	ninjaFrog.defineBehavior(playerActions);
	ninjaFrog.applyGravity(meter.toPixels(0, 100));
	map.addGlobalSprite(ninjaFrog);

	//// Create enemies ////

	SpriteCollection* rockHeads = room1RockHeads();
	for (AnimatedSprite* rockHead : rockHeads->getAnimatedSprites()) {
		rockHead->defineBehavior(rockHeadActions);
	}
	map.curRoom->addCollection(*rockHeads);

	SpriteCollection* enemies = room1Enemies();
	for (AnimatedSprite* enemy : enemies->getAnimatedSprites()) {
		enemy->defineBehavior(enemyActions);
	}
	map.curRoom->addCollection(*enemies);

	SpriteCollection* itemsRoom1 = room1Items();
	map.curRoom->addCollection(*itemsRoom1);

	SpriteCollection* obstacles = room2Obstacles();
	map.curRoom->top->addCollection(*obstacles);

	//// Collision detection ////

	BoxCollider room1Collider(playerCollision, true);
	room1Collider.applyCollision(ninjaFrog)
		.applyCollision(*enemies)
		.canCollideWith(*room1);
	map.curRoom->addCollider(room1Collider);

	BoxCollider rockHeadCollider(rockHeadCollision, true);
	rockHeadCollider.applyCollision(*rockHeads)
		.canCollideWith(*room1);
	map.curRoom->addCollider(rockHeadCollider);

	BoxCollider enemiesCollider(enemyCollision, true);
	enemiesCollider.applyCollision(ninjaFrog)
		.canCollideWith(*rockHeads)
		.canCollideWith(*enemies);
	map.curRoom->addCollider(enemiesCollider);

	BoxCollider room2Collider(playerCollision, true);
	room2Collider.applyCollision(ninjaFrog)
		.canCollideWith(*room2);
	map.curRoom->top->addCollider(room2Collider);

	BoxCollider obstaclesCollider(enemyCollision, true);
	obstaclesCollider.applyCollision(ninjaFrog)
		.canCollideWith(*obstacles);
	map.curRoom->top->addCollider(obstaclesCollider);

	int gameOverFrames = 0;
	while (game.isPlaying()) {
		if (gameOver) { // player got hit by an enemy
			map.curToHead();
			ninjaFrog.setPosition(meter.toPixels(10, 13.5));
			ninjaFrog.setVelocity(0, 0);
			enemies->getAnimatedSprites()[0]->setPosition(meter.toPixels(30, 13.5));
			enemies->getAnimatedSprites()[0]->setVelocity(0, 0);
			gameOverFlash.show();
			gameOverFrames++;
			if (gameOverFrames > 30) {
				gameOverFrames = 0;
				gameOverFlash.hide();
				gameOver = false;
			}
		}

		// Map navigation logic //
		if (map.curRoom->roomName == "room1" && ninjaFrog.getPosition().y < meter.toPixels(-1)) {
			// Jump up to room2
			map.curRoom = map.curRoom->top;
			ninjaFrog.setPosition(ninjaFrog.getPosition().x, meter.toPixels(21));
			ninjaFrog.setVelocity(ninjaFrog.getVelocity().x, meter.toPixels(-40));
		}
		else if (map.curRoom->roomName == "room2" && ninjaFrog.getPosition().y > meter.toPixels(24)) {
			// Fall down to bottom room1
			map.curRoom = map.curRoom->bottom;
			ninjaFrog.setPosition(ninjaFrog.getPosition().x, 0);
		}

		game.outputFrame();
	}

	deleteCollection(room1);
	deleteCollection(room2);
	deleteCollection(rockHeads);
	deleteCollection(enemies);
	deleteCollection(obstacles);
}