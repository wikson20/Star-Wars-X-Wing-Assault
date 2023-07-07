#pragma once
#include <vector>
#include "bullet.h"
#include <SFML/Audio.hpp>
class enemy {
public:
	// konstruktor z parametrami
	enemy(sf::Texture* tex, int posX, int posY, std::vector<bullet>* bulletsList, sf::Clock* gameClock, sf::RenderWindow* gameWindow);

	void Move(float deltaTime);				// funcja odpowiedzialna za ruch przeciwnika
	void Shoot();							// funkcja odpowiedzialna za strzelanie 
	void Draw();							// funkcja rysuj¹ca przeciwnika na oknie
	bool isAlive();							// funkcja okreœlaj¹ca czy przeciwnik ¿yje
	void TakeDamage(int dmg);				// funckja odpowiedzialna za otrzymywanie obra¿eñ od gracza
	void MoveDown(float amout);				// funkcja odpowiedzialna za ruch przeciwnika w dó³
	int GetH();								// funckja pobieraj¹ca wysokoœæ, na której znajduje sie tieFighter
	sf::Sprite sprite;						// obiekt sprite'a - reprezentuje grafikê przeciwnika
	
private:
	int hp{ 50 };							// pocz¹tkowy poziom ¿ycia 
	sf::Texture texture;					// tekstura pocisku - grafika, któr¹ u¿yjemy do sprite'a
	std::vector<bullet>* bb{ nullptr };		// wskaŸnik na wektor obiektów typu bullet; nie wskazuje ¿adnego konkretnego obiektu
	float tieFighterSpeed = 0.3f;			// prêdkoœæ przemieszczania siê tieFightera
	float tieFighterXDirection = 1.0f;		// kierunek ruchu tieFighter (1 - prawo, -1 - lewo)
	float rateOfFire{ 2 };					// czêstotliwoœæ strzelania przeciwnika (w sekundach)
	float nextShotTime{ 0 };				// czas kiedy mo¿e wyst¹piæ nastêpny strza³
	sf::SoundBuffer destroySoundBuffer;		// bufor dŸwiêku zniszczenia
	sf::Sound destroySound;					// obiekt dŸwiêku zniszczenia
	sf::Clock* clock;						// adres do zegara gry
	sf::RenderWindow* window;				// adres do okna gry
};