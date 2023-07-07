#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
class bullet {
public:
	// konstruktor z parametrami - pozwala na ustalenie pocz�tkowej pozycji, rozmiaru, czasu powstania, czy pocisk jest pociskiem gracza czy przeciwnika, kierunku oraz oba�e�
	bullet(float x, float y, float size, float bornTime, bool shouldBeRebel, int bulletDirection =1, int damage=25);

	// funkcja rysuj�ca pocisk na oknie
	void Draw(sf::RenderWindow* window);

	// funkcja odpowiedzialna za poruszanie si� pocisku
	void Move(sf::Clock* clock, float deltaTime);

	bool isAlive{ true };	// funkcja sprawdzaj�ca, czy pocisk �yje (czy powinien by� aktualnie wy�wietlany)
	sf::Sprite sprite;		// obiekt sprite'a - reprezentuje grafik� pocisku
	sf::Texture* texture;	// tekstura pocisku - grafika, kt�r� u�yjemy do sprite'a
	int dmg{ 25 };			// ilo�� obra�e�, jakie zadaje pocisk
	//This is the way
	bool isRebel{ false };	// funckja okre�laj�ca, czy pocisk jest pociskiem gracza (true) czy przeciwnika (false)

private:
	float speed {1};		// pr�dko�� ruchu pocisku
	float timeToDie{ 0 };	// czas, po kt�rym pocisk zostanie usuni�ty
	float lifeTime{ 3 };	// czas po jakim ma umrzec 
	int direction{ 1 };		// kierunek ruchu pocisku (-1 dla ruchu do g�ry, 1 dla ruchu do do�u)
};