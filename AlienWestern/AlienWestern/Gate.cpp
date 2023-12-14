#ifndef GATE_CPP
#define GATE_CPP
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

class Gate {
private:
    Sprite _gateUp;
    Sprite _gateDown;
    float _gateMovement = 150.0f; 
    float _gateSpeed = 4;
    Vector2f _originalPositionUp; 
    Vector2f _originalPositionDown; 
    bool _isOpening = false;
    bool _isClosing = false;
public:
    Vector2f GetPosition()
    {
        return(_originalPositionDown);
    }
    Gate(const Texture& textureUp, const Texture& textureDown, Vector2f positionUp, Vector2f positionDown) {
        _gateUp.setTexture(textureUp);
        _gateDown.setTexture(textureDown);
        _gateUp.setOrigin((float)textureUp.getSize().x / 2, (float)textureUp.getSize().y / 2);
        _gateDown.setOrigin((float)textureDown.getSize().x / 2, (float)textureDown.getSize().y / 2);
        _gateUp.setPosition(positionUp);
        _gateDown.setPosition(positionDown);
        _gateDown.setRotation(180);
        _originalPositionUp = positionUp;
        _originalPositionDown = positionDown;
    }
    
    void MoveGate(Sprite& gate, float movement) {
        Vector2f currentPosition = gate.getPosition();
        gate.setPosition(currentPosition.x, currentPosition.y + movement * _gateSpeed);
    }

    void TriggerGate(bool open) {
        _isOpening = open;
        _isClosing = !open;
    }
    

    void Update() {

        if (_isOpening) {

            if (_gateUp.getPosition().y > _originalPositionUp.y - _gateMovement)
                MoveGate(_gateUp, -1); 
            if (_gateDown.getPosition().y < _originalPositionDown.y + _gateMovement)
                MoveGate(_gateDown, 1); 
        }
        else if (_isClosing) {

            if (_gateUp.getPosition().y < _originalPositionUp.y)
                MoveGate(_gateUp, 1);
            if (_gateDown.getPosition().y > _originalPositionDown.y)
                MoveGate(_gateDown, -1);
        }
    }

    void Draw(RenderWindow& window) {
        window.draw(_gateUp);
        window.draw(_gateDown);
    }
};
#endif // GATE_CPP
