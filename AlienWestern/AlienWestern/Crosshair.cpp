#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "iostream"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
using namespace sf;
using namespace std;

class Crosshair {
private:
	Sprite _sprite;
	Texture _texture;

public:
	Crosshair(const string& texturePath) {
		if (!_texture.loadFromFile(texturePath)) {
			// Handle error
		}
		_sprite.setTexture(_texture);
		_sprite.setScale(0.5f, 0.5f);
		_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
	}

	void updatePosition(const Vector2i& mousePosition) {
		_sprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
	}

	void draw(RenderWindow& window) {
		window.draw(_sprite);
	}
};