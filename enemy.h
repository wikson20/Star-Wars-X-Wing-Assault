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
	void Draw();							// funkcja rysuj�ca przeciwnika na oknie
	bool isAlive();							// funkcja okre�laj�ca czy przeciwnik �yje
	void TakeDamage(int dmg);				// funckja odpowiedzialna za otrzymywanie obra�e� od gracza
	void MoveDown(float amout);				// funkcja odpowiedzialna za ruch przeciwnika w d�
	int GetH();								// funckja pobieraj�ca wysoko��, na kt�rej znajduje sie tieFighter
	sf::Sprite sprite;						// obiekt sprite'a - reprezentuje grafik� przeciwnika
	
private:
	int hp{ 50 };							// pocz�tkowy poziom �ycia 
	sf::Texture texture;					// tekstura pocisku - grafika, kt�r� u�yjemy do sprite'a
	std::vector<bullet>* bb{ nullptr };		// wska�nik na wektor obiekt�w typu bullet; nie wskazuje �adnego konkretnego obiektu
	float tieFighterSpeed = 0.3f;			// pr�dko�� przemieszczania si� tieFightera
	float tieFighterXDirection = 1.0f;		// kierunek ruchu tieFighter (1 - prawo, -1 - lewo)
	float rateOfFire{ 2 };					// cz�stotliwo�� strzelania przeciwnika (w sekundach)
	float nextShotTime{ 0 };				// czas kiedy mo�e wyst�pi� nast�pny strza�
	sf::SoundBuffer destroySoundBuffer;		// bufor d�wi�ku zniszczenia
	sf::Sound destroySound;					// obiekt d�wi�ku zniszczenia
	sf::Clock* clock;						// adres do zegara gry
	sf::RenderWindow* window;				// adres do okna gry
};