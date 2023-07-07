#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class gracz {
public:
	gracz(sf::Texture* tex, std::vector<bullet>* bb, sf::Clock* gameClock, sf::RenderWindow* gameWindow); // konstruktor z parametrami

	void InputMove(sf::Event* inputEvent);		// poruszanie si�
	void Move(float deltaTime);					// funcja odpowiedzialna za ruch gracza
	void Shoot();								// funkcja odpowiedzialna za strzelanie
	void Draw();								// funkcja rysuj�ca gracza na oknie
	bool isAlive();								// funkcja okre�laj�ca czy gracz �yje
	void TakeDamage(int dmg);					// funckja odpowiedzialna za otrzymywanie obra�e� od przeciwnika
	void ResetPlayer();							// funkcja resetuj�ca gracza (respawn)
	sf::Sprite sprite;							// obiekt sprite'a - reprezentuje grafik� gracza

private:
	int hp{100};								// pocz�tkowy poziom �ycia
	sf::Texture texture;						// tekstura reprezentuj�ca wygl�d gracza
	std::vector<bullet>* bullets{ nullptr };	// wska�nik na wektor obiekt�w typu bullet; nie wskazuje �adnego konkretnego obiektu
	float playerSpeed{ 3 };						// pr�dko�� poruszania si� gracza

	sf::Vector2f input { 0,0 };					// bufor wejscia
	sf::Font font;								// font do wy�wietlania tekstu 
	sf::Text healthText;						// wy�wietlanie informacji o stanie �ycia na ekranie
	sf::SoundBuffer shootSoundBuffer;			// bufor d�wi�ku strza�u
	sf::Sound shootSound;						// obiekt d�wi�ku strza�u
	sf::Clock* clock;							// adres do zegara gry
	sf::RenderWindow* window;					// adres do okna

	float timeToShoot{ 0 };						// czas po kt�rym pocisk b�dzie m�g� by� wystrzelony
	float shotDelay{ 0.2f };					// op�nienie w sekundach
};