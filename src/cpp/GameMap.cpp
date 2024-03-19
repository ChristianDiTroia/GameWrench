#include "GameMap.hpp"

using namespace gw;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

gw::GameMap::GameMap(std::string firstRoomName) :
    head(new GameRoom(firstRoomName)),
    curRoom(const_cast<GameRoom*>(head))
{}

gw::GameMap::~GameMap() {
    curToHead();
    delete curRoom;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators
////////////////////////////////////////////////////////////////////////////////////////////////////

void gw::GameMap::addRoomTop(std::string name) {
    curRoom->top = new GameRoom(name);
    curRoom->top->bottom = curRoom;
}

void gw::GameMap::addRoomBottom(std::string name) {
    curRoom->bottom = new GameRoom(name);
    curRoom->bottom->top = curRoom;
}

void gw::GameMap::addRoomLeft(std::string name) {
    curRoom->left = new GameRoom(name);
    curRoom->left->right = curRoom;
}

void gw::GameMap::addRoomRight(std::string name) {
    curRoom->right = new GameRoom(name);
    curRoom->right->left = curRoom;
}