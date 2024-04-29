#include "GameWrench.hpp"

#include "./demos/demos.hpp"

int main() {

    demos::runDemo3();
}


//// Utility to detect when a button is released
//class Released
//{
//public:
//
//	Released(sf::Keyboard::Key key) : key(key), isPressed(false), wasPressed(false) {}
//
//	bool operator () () {
//		bool released = false;
//
//		if (sf::Keyboard::isKeyPressed(key)) isPressed = true;
//		else isPressed = false;
//
//		if (wasPressed && !isPressed) released = true;
//
//		if (isPressed) wasPressed = true;
//		else wasPressed = false;
//
//		return released;
//	}
//
//private:
//	sf::Keyboard::Key key;
//	bool isPressed;
//	bool wasPressed;
//};
//
//Released bRelease(sf::Keyboard::B);