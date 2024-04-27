#include "demos/demos.hpp"

#include "GameWrench.hpp"
#include <iostream>

using namespace gw;

namespace demo2setup
{
	// Define 1 in-game meter
	helpers::PixelConverter meter(16);

	static void playerCollision(Sprite& sprite, Sprite& collidedWith, Vector2f collision) {
		Entity& player = dynamic_cast<Entity&>(sprite);
		if ((collision.y > collision.x) /*&& collision.x <= 1*/) { // collision onY
			// stop vertical momentum on y-axis collisions
			player.setVelocity(player.getVelocity().x, 0);
			if (player.getPosition().y > collidedWith.getPosition().y) player.addVelocity(0, 1); // bumped head - send back down
		}
		else if (collision.x > collision.y) { // collision onX
			// wall cling ability
			if (player.getVelocity().y >= 0) { player.setSubsprite(0, 3); } // don't cling if jumping
			player.setVelocity(player.getVelocity().x, 0); // stop falling when clinging
		}
	};

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

	static SpriteCollection* buildRoom1() {
		// create the floor
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

		TileStructure& platform4 = *( new TileStructure(platform3));
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

		// put all structures into a collection
		SpriteCollection* room1 = new SpriteCollection;
		room1->addSprite(platform1)
			.addSprite(platform2)
			.addSprite(platform3)
			.addSprite(platform4)
			.addSprite(platform5)
			.addSprite(beam)
			.addSprite(wall1)
			.addSprite(wall2)
			.addSprite(floor); // draw floor last

		return room1;
	}

	static SpriteCollection* buildRoom2() {
		TileStructure& roof = *(new TileStructure("./sprites/pixel_adventure_sprites/terrain/Terrain_(16x16).png", 16, 16));
		roof.setSubsprite(0, 0, 3, 3);
		meter.scaleSprite(roof, 2, 2);
		roof.asRow(20);
		roof.setPosition(meter.toPixels(1, 1));

		TileStructure& platform1 = *(new TileStructure(roof));
		platform1.setPosition(meter.toPixels(6.5, 22.5));

		SpriteCollection* room2 = new SpriteCollection;
		room2->addSprite(roof)
			.addSprite(platform1);

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

	// create map and game objects
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

	// create rooms
	SpriteCollection* room1 = buildRoom1();
	map.curRoom->addCollection(*room1);
	SpriteCollection* room2 = buildRoom2();
	map.curRoom->top->addCollection(*room2);

	// create player character
	Entity ninjaFrog("./sprites/pixel_adventure_sprites/Main characters/Ninja Frog/ninjaFrogSpriteSheet_32x32.png", 32, 32);
	ninjaFrog.addAnimation("idle", gw::helpers::rowAnimation(2, 0, 9))
		.addAnimation("run", gw::helpers::rowAnimation(3, 0, 10))
		.addAnimation("jump", gw::helpers::rowAnimation(0, 1, 1))
		.addAnimation("fall", gw::helpers::rowAnimation(0, 0, 0));
	ninjaFrog.setPosition(meter.toPixels(20, 8));
	bool inAir = false;
	ninjaFrog.defineBehavior(playerActions);
	ninjaFrog.applyGravity(meter.toPixels(0, 100));
	map.addGlobalSprite(ninjaFrog);

	// collision detection with the terrain
	BoxCollider room1Collision(playerCollision, true);
	room1Collision.applyCollision(ninjaFrog)
		.canCollideWith(*room1);
	map.curRoom->addCollider(room1Collision);

	while (game.isPlaying()) {

		game.outputFrame();

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
	}

	deleteCollection(room1);
	deleteCollection(room2);
}