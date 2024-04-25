#include "demos/demos.hpp"

#include "GameWrench.hpp"

using namespace gw;

namespace demo3setup
{
	// Define 1 in-game meter
	helpers::PixelConverter meter(16);

	static void playerCollision(Sprite& sprite, Sprite& collidedWith, Vector2f collision) {

		// Find which axis is colliding more
		bool onX = collision.x > collision.y;
		bool onY = collision.y > collision.x;

		Entity& player = dynamic_cast<Entity&>(sprite);
		if (onY&& collision.x <= 1) { // stop vertical momentum on y-axis collisions
			player.setVelocity(player.getVelocity().x, 0);
			// send player back down if colliding with object above
			if (player.getPosition().y > collidedWith.getPosition().y) { player.addVelocity(0, 1); }
		}

		// Make corrections to push sprite out of collision
		collision.x = collision.x * onX;
		collision.y = collision.y * onY;
		if (sprite.getPosition().x < collidedWith.getPosition().x) { collision.x *= -1; }
		if (sprite.getPosition().y < collidedWith.getPosition().y) { collision.y *= -1; }
		sprite.movePosition(collision);
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
		float speedy = meter.toPixels(-50);
		if (kb::isKeyPressed(kb::Space) && !inAir) {
			player.animate("jump", 1);
			player.setVelocity(player.getVelocity().x, speedy);
		}
		if (inAir) { player.animate("jump", 1); }

		if (player.getVelocity().y == 0) { player.addVelocity(0, 1); } // prevent y-vel == 0 inAir
	}

	static void enemyActions(AnimatedSprite& self, AnimatedSprite& player) {
		Entity& enemy = dynamic_cast<Entity&>(self);
		Entity& playr = dynamic_cast<Entity&>(player);

		// Make an enemy that follows the player when close by
		Vector2f dist = playr.getPosition() - enemy.getPosition();
		if (abs(dist.x) <= meter.toPixels(6) && abs(dist.x) > 1 && abs(dist.y) < meter.toPixels(8)) {
			enemy.setVelocity(meter.toPixels(8), 0);
			if (enemy.isMirroredX()) { enemy.mirrorX(); }
			if (dist.x < 0) { // player towards the left
				enemy.setVelocity(enemy.getVelocity() * -1);
				if (!enemy.isMirroredX()) { enemy.mirrorX(); }
			}
			enemy.animate("run", 0.07);
		}
		else {
			enemy.setVelocity(0, 0);
			enemy.animate("idle", 0.06);
		}
	}
	
} // namespace demo3

void demos::runDemo3() {
	using namespace demo3setup;

	// create map and game objects
	GameMap map;
	Game game(map, 640, 360, "GameWrench First Game!!!");

	// set background
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

	TileStructure platform1(floor);
	platform1.setSubsprite(8, 0, 3, 3);
	platform1.movePosition(meter.toPixels(5), meter.toPixels(-6));
	platform1.asRow(4);

	TileStructure platform2(platform1);
	platform2.movePosition(meter.toPixels(20), 0);

	TileStructure platform3(platform2);
	platform3.setSubsprite(9, 13, 2, 2);
	meter.scaleSprite(platform3, 2, 2);
	platform3.movePosition(meter.toPixels(-12), meter.toPixels(-6));
	platform3.asRow(6);

	TileStructure beam(platform3);
	beam.setSubsprite(8, 15, 1, 3);
	beam.asColumn(4);
	beam.positionRelativeTo(platform3, TileStructure::xCenter, TileStructure::bottom);

	TileStructure wall1(platform3);
	wall1.setSubsprite(4, 17, 3, 3);
	wall1.asColumn(20);
	wall1.positionRelativeTo(floor, TileStructure::left, TileStructure::top);
	wall1.movePosition(meter.toPixels(2), 0);

	TileStructure wall2(wall1);
	wall1.positionRelativeTo(floor, TileStructure::right, TileStructure::top);
	wall1.movePosition(meter.toPixels(-2), 0);

	// put all structures into a collection
	SpriteCollection terrain;
	terrain.addSprite(platform1)
		.addSprite(platform2)
		.addSprite(platform3)
		.addSprite(beam)
		.addSprite(wall1)
		.addSprite(wall2)
		.addSprite(floor); // draw floor last

	map.curRoom->addCollection(terrain);

	// create player character
	Entity ninjaFrog("./sprites/pixel_adventure_sprites/Main characters/Ninja Frog/ninjaFrogSpriteSheet_32x32.png", 32, 32);
	ninjaFrog.addAnimation("idle", gw::helpers::rowAnimation(2, 0, 9))
		.addAnimation("run", gw::helpers::rowAnimation(3, 0, 10))
		.addAnimation("jump", gw::helpers::rowAnimation(0, 0, 0));
	ninjaFrog.setPosition(meter.toPixels(20), meter.toPixels(19.5));
	bool inAir = false;
	ninjaFrog.defineBehavior(playerActions);
	ninjaFrog.applyGravity(0, meter.toPixels(130));

	// create enemy characters
	Entity enemy(ninjaFrog);
	enemy.defineBehavior(
		[&ninjaFrog](AnimatedSprite& self) { enemyActions(self, ninjaFrog); }
	);

	SpriteCollection characters;
	characters.addSprite(ninjaFrog)
		.addSprite(enemy);
	map.curRoom->addCollection(characters);

	// collision detection with the floor
	BoxCollider terrainCollision(playerCollision);
	terrainCollision.applyCollision(ninjaFrog)
		.applyCollision(enemy)
		.canCollideWith(terrain);
	game.addCollider(terrainCollision);

	while (game.isPlaying()) { game.outputFrame(); }
}