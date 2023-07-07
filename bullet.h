#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
class bullet {
public:
	// konstruktor z parametrami - pozwala na ustalenie pocz¹tkowej pozycji, rozmiaru, czasu powstania, czy pocisk jest pociskiem gracza czy przeciwnika, kierunku oraz oba¿eñ
	bullet(float x, float y, float size, float bornTime, bool shouldBeRebel, int bulletDirection =1, int damage=25);

	// funkcja rysuj¹ca pocisk na oknie
	void Draw(sf::RenderWindow* window);

	// funkcja odpowiedzialna za poruszanie siê pocisku
	void Move(sf::Clock* clock, float deltaTime);

	bool isAlive{ true };	// funkcja sprawdzaj¹ca, czy pocisk ¿yje (czy powinien byæ aktualnie wyœwietlany)
	sf::Sprite sprite;		// obiekt sprite'a - reprezentuje grafikê pocisku
	sf::Texture* texture;	// tekstura pocisku - grafika, któr¹ u¿yjemy do sprite'a
	int dmg{ 25 };			// iloœæ obra¿eñ, jakie zadaje pocisk
	//This is the way
	bool isRebel{ false };	// funckja okreœlaj¹ca, czy pocisk jest pociskiem gracza (true) czy przeciwnika (false)

private:
	float speed {1};		// prêdkoœæ ruchu pocisku
	float timeToDie{ 0 };	// czas, po którym pocisk zostanie usuniêty
	float lifeTime{ 3 };	// czas po jakim ma umrzec 
	int direction{ 1 };		// kierunek ruchu pocisku (-1 dla ruchu do góry, 1 dla ruchu do do³u)
};