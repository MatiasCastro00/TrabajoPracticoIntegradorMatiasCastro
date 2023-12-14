
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

class Tutorial {
private:
    Sprite _tutorial;
    
public:
    
    Tutorial(const Texture& texture) {
        _tutorial.setTexture(texture);
    }


    bool checkHits(const Vector2i& mousePosition) {

        if (_tutorial.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
            _tutorial.setPosition({ 9999,9999 });
            return true;
        }
        return false;

    }

    void Draw(RenderWindow& window) {
        window.draw(_tutorial);

    }
};