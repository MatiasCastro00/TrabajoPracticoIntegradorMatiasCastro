#ifndef GATE_H
#define GATE_H

#include <SFML/Graphics.hpp>

class Gate {
private:
    sf::Sprite _gateUp;
    sf::Sprite _gateDown;
    float _gateMovement = 150.0f;
    float _gateSpeed = 4;
    sf::Vector2f _originalPositionUp;
    sf::Vector2f _originalPositionDown;
    bool _isOpening = false;
    bool _isClosing = false;

public:
    Gate(const sf::Texture& textureUp, const sf::Texture& textureDown, sf::Vector2f positionUp, sf::Vector2f positionDown);
    sf::Vector2f GetPosition();
    void MoveGate(sf::Sprite& gate, float movement);
    void TriggerGate(bool open);
    void Update();
    void Draw(sf::RenderWindow& window);
};

#endif // GATE_H
