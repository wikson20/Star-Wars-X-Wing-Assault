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

	void InputMove(sf::Event* inputEvent);		// poruszanie siê
	void Move(float deltaTime);					// funcja odpowiedzialna za ruch gracza
	void Shoot();								// funkcja odpowiedzialna za strzelanie
	void Draw();								// funkcja rysuj¹ca gracza na oknie
	bool isAlive();								// funkcja okreœlaj¹ca czy gracz ¿yje
	void TakeDamage(int dmg);					// funckja odpowiedzialna za otrzymywanie obra¿eñ od przeciwnika
	void ResetPlayer();							// funkcja resetuj¹ca gracza (respawn)
	sf::Sprite sprite;							// obiekt sprite'a - reprezentuje grafikê gracza

private:
	int hp{100};								// pocz¹tkowy poziom ¿ycia
	sf::Texture texture;						// tekstura reprezentuj¹ca wygl¹d gracza
	std::vector<bullet>* bullets{ nullptr };	// wskaŸnik na wektor obiektów typu bullet; nie wskazuje ¿adnego konkretnego obiektu
	float playerSpeed{ 3 };						// prêdkoœæ poruszania siê gracza

	sf::Vector2f input { 0,0 };					// bufor wejscia
	sf::Font font;								// font do wyœwietlania tekstu 
	sf::Text healthText;						// wyœwietlanie informacji o stanie ¿ycia na ekranie
	sf::SoundBuffer shootSoundBuffer;			// bufor dŸwiêku strza³u
	sf::Sound shootSound;						// obiekt dŸwiêku strza³u
	sf::Clock* clock;							// adres do zegara gry
	sf::RenderWindow* window;					// adres do okna

	float timeToShoot{ 0 };						// czas po którym pocisk bêdzie móg³ byæ wystrzelony
	float shotDelay{ 0.2f };					// opóŸnienie w sekundach
};