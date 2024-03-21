#include "GameRoom.hpp"

using namespace gw;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

gw::GameRoom::GameRoom(std::string name) :
    roomName(name),
    top(nullptr),
    bottom(nullptr),
    left(nullptr),
    right(nullptr)
{}

gw::GameRoom::~GameRoom() {
    // Disconnect all rooms to ensure this room is deleted only once
    if (top) { top->bottom = nullptr; }
    if (bottom) { bottom->top = nullptr; }
    if (left) { left->right = nullptr; }
    if (right) { right->left = nullptr; }
    // Delete rooms recursively
    delete top;
    delete bottom;
    delete left;
    delete right;
}