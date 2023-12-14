#include <SFML/Graphics.hpp>
#include "Gate.cpp" 
#include "Objetive.cpp"  
#include "Crosshair.cpp"  
#include "tutorial.cpp" 
#include "AlienBlood.cpp"  
#include "iostream"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>

#include <cstdlib>

using namespace std;

void waveManager(Gate* gates[4], float& currentDelay, Objetive& objetive, float delay)
{
    if (currentDelay < delay)
    {
        currentDelay++;
    }
    else
    {
        currentDelay = 0;
        int randomNum = rand() % 4;
        cout << randomNum;
        gates[randomNum]->TriggerGate(true);
        objetive.SetPosition(gates[randomNum]->GetPosition());
        objetive.SetTeam();
        objetive.ResetTime();
    }
    if (currentDelay == delay*0.8)
    for (int i = 0; i < 4; i++) {
            gates[i]->TriggerGate(false);
    }
        return;
}
int main() {
    srand(time(NULL));
    Vector2f _size = { 1280 ,1080 };
    sf::RenderWindow window(sf::VideoMode(_size.x, _size.y), "DefendTheAliens!!");
    window.setFramerateLimit(60);
    Texture _gatetexture;
    Texture _backgroundTexture;
    Texture _frontTexture;
    Texture _tutorialTexture;
    Texture _gameOvertTexture;


    float _spawnTime = 0;
    float  _spawnDelay = 200;
    float _spawnDelayMin = 50;
    _gameOvertTexture.loadFromFile("sprites/GameOver.png");
    _tutorialTexture.loadFromFile("sprites/Tutorial.png");
    _backgroundTexture.loadFromFile("sprites/Fondo.png");
    _frontTexture.loadFromFile("sprites/MarcosDeLataberna.png");
    _gatetexture.loadFromFile("sprites/Compuerta.png");
    Sprite _background;
    _background.setTexture(_backgroundTexture);
    Sprite _front;
    _front.setTexture(_frontTexture);
    Gate _gate(_gatetexture, _gatetexture, Vector2f(190, 550), Vector2f(190, 650));
    Gate _gate2(_gatetexture, _gatetexture, Vector2f(820, 550), Vector2f(820, 650));
    Gate _gate3(_gatetexture, _gatetexture, Vector2f(380, 220), Vector2f(380, 320));
    Gate _gate4(_gatetexture, _gatetexture, Vector2f(640, 220), Vector2f(640, 320));
    Tutorial _tutorial(_tutorialTexture);
    Objetive _objetive(Vector2f(190, 550), _spawnDelay);
    Crosshair _crosshair("sprites/crosshair.png");
    AlienBlood _alienBlood({ _size.x/2,_size.y/2}, "sprites/Sangre.png");
    Gate* _gates[4];
    Sprite _gameOver;
    _gameOver.setTexture(_gameOvertTexture);
    _gates[0] = &_gate;
    _gates[1] = &_gate2;
    _gates[2] = &_gate3;
    _gates[3] = &_gate4;

    int _score = 0;
    int _health = 3;
    Font _font;
    _font.loadFromFile("sprites/Daydream.ttf");
    Font _loseFont;
    _loseFont.loadFromFile("sprites/LoseFont.ttf");
    Text _scoreText;
    Text _healthText;
    _scoreText.setFont(_font);
    _healthText.setFont(_font);
    _scoreText.setString("Score: " + to_string(_score));
    _healthText.setString("Health: " + to_string(_health));
    _scoreText.setCharacterSize(30);
    _scoreText.setPosition(1010, 0);
    _healthText.setCharacterSize(30);
    _healthText.setPosition(1010, 60);
    bool _tutorialClosed=false;
    bool _lose = false;
    while (window.isOpen()) {
        sf::Event event;
        window.clear();
        if (_lose)
        {
            _scoreText.setFont(_loseFont);
            _scoreText.setOrigin(_scoreText.getLocalBounds().width / 2, _scoreText.getLocalBounds().width / 2);
            _scoreText.setCharacterSize(170);
            _scoreText.setPosition(640, 520);
            window.draw(_gameOver);
            window.draw(_scoreText);
            window.display();
            continue;
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Vector2i mousePos = Mouse::getPosition(window);
        if (!_tutorialClosed)
        {
            if (event.type == Event::MouseButtonPressed) {
			    if (event.mouseButton.button == Mouse::Left) {
                    _tutorialClosed=_tutorial.checkHits(mousePos);
			    }
		    }
            _tutorial.Draw(window);
            window.display();
            continue;
        }
        _tutorialClosed = true;
        window.setMouseCursorVisible(false);
        waveManager(_gates, _spawnTime,_objetive, _spawnDelay);

        for (int i = 0; i < 4; i++) {
            _gates[i]->Update();
        }
        _gates[0]->Update();
        int _hitEnemie = 0;
        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                _hitEnemie=_objetive.checkHits(mousePos);
                if (_hitEnemie==1)
                {
                    _score++;
                    _scoreText.setString("Score: " + to_string(_score));
                }
                else if (_hitEnemie == 0)
                {
                    _health--;
                    _score-=10;
                    _scoreText.setString("Score: " + to_string(_score));
                    _healthText.setString("Health: " + to_string(_health));
                }
            }
        }
        
        if (_health <= 0)
        {
            _lose = true;
            _scoreText.setString(to_string(_score));
        }
        if (_objetive.TryToShoot())
        {
            _health--;
            _alienBlood.SpawnBlood(120);
            _healthText.setString("Health: " + to_string(_health));
            _spawnTime = _spawnDelay;
        }

        
        _gate.Update();
        _gate2.Update();
        _gate3.Update();
        _gate4.Update();
        _alienBlood.tryFadeOut(90);
        _crosshair.updatePosition(mousePos);

        window.draw(_background);
        _objetive.Draw(window);
        _gate.Draw(window);
        _gate2.Draw(window);
        _gate3.Draw(window);
        _gate4.Draw(window);
        window.draw(_front);
        _alienBlood.Draw(window);
        window.draw(_scoreText);
        window.draw(_healthText);
        _crosshair.draw(window);
       window.display();
    }

    return 0;
}
