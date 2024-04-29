#include "demos/demos.hpp"

#include "GameWrench.hpp"
#include <SFML/Audio.hpp>

using namespace gw;

namespace demo2setup
{

////////////////////////////////////////////////////////////////////////////////////////////////////
// Global data
////////////////////////////////////////////////////////////////////////////////////////////////////

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
			player.animate("run", 0.06);
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
			player.setVelocity(player.getVelocity().x, speedy);
			player.animate("jump", 1);
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
		meter.scaleSprite(wall1, 2, 2);
		wall1.asColumn(20);
		wall1.positionRelativeTo(floor, TileStructure::left, TileStructure::top);
		wall1.movePosition(meter.toPixels(2, 0));

		TileStructure& wall2 = *(new TileStructure(wall1));
		wall2.positionRelativeTo(floor, TileStructure::right, TileStructure::top);
		wall2.movePosition(meter.toPixels(-2, 0));

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

	static void deleteCollection(SpriteCollection* collection) {
		for (Sprite* sprite : collection->getSprites()) { delete sprite; }
		for (Sprite* sprite : collection->getAnimatedSprites()) { delete sprite; }
		delete collection;
	}

} // namespace demo2

void demos::runDemo2() {
	using namespace demo2setup;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Create map and game objects
////////////////////////////////////////////////////////////////////////////////////////////////////

	GameMap map("room1");
	map.addRoomTop("room2");
	Game game(map, 640, 360, "GameWrench Demo 2!!!");

////////////////////////////////////////////////////////////////////////////////////////////////////
// Set backgrounds
////////////////////////////////////////////////////////////////////////////////////////////////////

	Sprite background1("./sprites/pixel_adventure_sprites/background/Yellow.png", 64, 64);
	meter.scaleSprite(background1, 40, 23);
	background1.setPosition(meter.toPixels(20, 11.25));
	map.curRoom->addSprite(background1);

	Sprite background2("./sprites/pixel_adventure_sprites/background/Blue.png", 64, 64);
	meter.scaleSprite(background2, 40, 23);
	background2.setPosition(meter.toPixels(20, 11.25));
	map.curRoom->top->addSprite(background2);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Create room layouts/terrain
////////////////////////////////////////////////////////////////////////////////////////////////////

	SpriteCollection* room1 = buildRoom1();
	map.curRoom->addCollection(*room1);
	SpriteCollection* room2 = buildRoom2();
	map.curRoom->top->addCollection(*room2);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Create player character
////////////////////////////////////////////////////////////////////////////////////////////////////

	ninjaFrog.addAnimation("idle", helpers::rowAnimation(2, 0, 9))
		.addAnimation("run", helpers::rowAnimation(3, 0, 10))
		.addAnimation("jump", helpers::rowAnimation(0, 1, 1))
		.addAnimation("fall", helpers::rowAnimation(0, 0, 0));
	ninjaFrog.setPosition(meter.toPixels(10, 13.5));
	ninjaFrog.defineBehavior(playerActions);
	ninjaFrog.applyGravity(meter.toPixels(0, 100));
	map.addGlobalSprite(ninjaFrog);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Collision detection
////////////////////////////////////////////////////////////////////////////////////////////////////

	BoxCollider room1Collider(playerCollision, true);
	room1Collider.applyCollision(ninjaFrog)
		.canCollideWith(*room1);
	map.curRoom->addCollider(room1Collider);

	BoxCollider room2Collider(playerCollision, true);
	room2Collider.applyCollision(ninjaFrog)
		.canCollideWith(*room2);
	map.curRoom->top->addCollider(room2Collider);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Run game
////////////////////////////////////////////////////////////////////////////////////////////////////

	while (game.isPlaying()) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////
// Clean up memory
////////////////////////////////////////////////////////////////////////////////////////////////////

	deleteCollection(room1);
	deleteCollection(room2);
}