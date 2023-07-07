#include "bullet.h"

// przeci��ony/prze�adowany konstruktor z parametrami - pozwala na ustalenie pocz�tkowej pozycji, rozmiaru, kierunku itp.
bullet::bullet(float x, float y, float size, float bornTime, bool shouldBeRebel, int bulletDirection, int damage)
{
	texture = new sf::Texture(); // tworzenie nowej tekstury i zapisanie adresu do niej
	if (texture->loadFromFile("bullet.png") == false) // �adowanie obrazka dla tekstury pocisku
	{
		std::cout << "Blad ladowania obrazka" << std::endl;
	}

	sprite.setTexture(*texture);				// inicjalizacja sprite'a z za�adowan� tekstur�
	sprite.setScale(sf::Vector2f(size, size));	// ustawienie skali pocisku (zgodnie z przekazanym rozmiarem)
	sprite.setPosition(sf::Vector2f(x, y));		// ustawienie pozycji pocisku na przekazane wsp�rz�dne (x, y)

	isRebel = shouldBeRebel;		// okre�lenie, czy pocisk powinien by� pociskiem gracza czy przeciwnika
	direction = bulletDirection;	// okre�lenie kierunku pocisku (1 dla ruchu do g�ry, -1 dla ruchu do do�u)
	dmg = damage;					// przypisania warto�ci zmiennej damage do zmiennej dmg

	timeToDie = bornTime + lifeTime;	// ustawienie czasu, po kt�rym pocisk powinien zosta� usuni�ty (czas �ycia)
}

// funkcja rysuj�ca pocisk na ekranie
void bullet::Draw(sf::RenderWindow* window)
{
	if (isAlive && window != nullptr)	// sprawdzenie, czy pocisk �yje (czy powinien by� rysowany na ekranie)
		window->draw(sprite);			// rysowanie sprite'a pocisku na oknie
}

// funkcja odpowiedzialna za poruszanie si� pocisku
void bullet::Move(sf::Clock* clock, float deltaTime)
{
	sprite.move(0.0f, -speed * direction * deltaTime);	// przesuni�cia pozycji pocisku w osi Y na podstawie warto�ci pr�dko�ci, kierunku i czasu od ostatniej klatki animacji 

	// czy gracz jest �ywy, czy clock istnieje, czy nadszed� czas umiera�
	if (isAlive && clock != nullptr && (clock->getElapsedTime().asSeconds() > timeToDie))
	{
		isAlive = false;	// je�li czas �ycia pocisku min��, ustaw flag� na "false" - pocisk zostanie usuni�ty
	}
}