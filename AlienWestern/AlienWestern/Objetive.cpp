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

class Objetive {
private:
    Sprite _alien;
    Texture _alienTexture;
    int _shootDelay;
    bool _isAlive;
    int _shootTime=0;
public:
    bool IsAlie = false;
    Objetive(Vector2f position, int shootDelay)
    {
        _alien.setPosition(position);
        _shootDelay = shootDelay;
        _alien.setScale(0.4f,0.4f);
    }
    void SetPosition(Vector2f position)
    {
        _alien.setPosition(position);
    }
    void Draw(RenderWindow& window) {
        window.draw(_alien);
    }
    void SetTeam()
    {
        if(rand()%100>70)//mayor a 70 es aliado
        {
            IsAlie = true;
            if (rand() % 2 == 0)
                _alienTexture.loadFromFile("sprites/Alien 1.png");
            else
                _alienTexture.loadFromFile("sprites/Alien 2.png");
        }
        else
        {
            IsAlie = false;
            if (rand() % 2 == 0)
                _alienTexture.loadFromFile("sprites/Enemigo 1.png");
            else
                _alienTexture.loadFromFile("sprites/Enemigo2.png");
        }
        _isAlive = true;
        _alien.setTexture(_alienTexture);
        _alien.setOrigin((float)_alienTexture.getSize().x / 2, (float)_alienTexture.getSize().y / 2);
    }
    void ResetTime()
    {
        _shootTime = 0;
    }
    bool TryToShoot()
    {
        if (!IsAlie)
            _shootTime++;
        if (_shootTime > _shootDelay)
        {
            _shootTime = 0;
            return true;
        }
        return false;
    }

    int checkHits(const Vector2i& mousePosition) {
        if (_alien.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
            SetPosition({9999,9999});
            _isAlive = false;
            ResetTime();
            if (IsAlie)
                return 0;
            else
                return 1;
        }
        return -1;
        
    }
};
