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

class AlienBlood {
private:
    Sprite _blood;
    Texture _bloodTexture;
    Vector2f _startPosition;
    bool _doFade = false;
    float _currentFade = 255;
    int _currentTime = 0;
public:
    bool IsAlie = false;
    AlienBlood(Vector2f position, const string& texturePath)
    {
        _blood.setPosition(position);
        _bloodTexture.loadFromFile(texturePath);
        _blood.setTexture(_bloodTexture);
        _startPosition = position;
        _blood.setPosition({ 9999,9999 });
        _blood.setOrigin(_blood.getLocalBounds().width / 2, _blood.getLocalBounds().height / 2);
    }
    void SpawnBlood(int fadeTime)
    {
        _blood.setPosition(_startPosition);
        _doFade = true;
        _currentTime = 0;
        SetAlpha(0);
        _currentFade = 255.0f;
    }
    void Draw(RenderWindow& window) {
        window.draw(_blood);
    }
    void tryFadeOut(int duration) {
        if (!_doFade)
            return;
        if (_currentFade < 0)
        {
            _doFade = false;
            _blood.setPosition({ 9999,9999 });
        }
        float alphaSpeed = 255.0f / duration;
        _currentFade -= alphaSpeed;
        SetAlpha(_currentFade);
    }
    void SetAlpha(float fade)
    {
        sf::Color color = _blood.getColor();
        color.a = static_cast<sf::Uint8>(fade);
        _blood.setColor(color);
    }
};
