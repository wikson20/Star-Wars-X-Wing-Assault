#include "bullet.h"

// przeci¹¿ony/prze³adowany konstruktor z parametrami - pozwala na ustalenie pocz¹tkowej pozycji, rozmiaru, kierunku itp.
bullet::bullet(float x, float y, float size, float bornTime, bool shouldBeRebel, int bulletDirection, int damage)
{
	texture = new sf::Texture(); // tworzenie nowej tekstury i zapisanie adresu do niej
	if (texture->loadFromFile("bullet.png") == false) // ³adowanie obrazka dla tekstury pocisku
	{
		std::cout << "Blad ladowania obrazka" << std::endl;
	}

	sprite.setTexture(*texture);				// inicjalizacja sprite'a z za³adowan¹ tekstur¹
	sprite.setScale(sf::Vector2f(size, size));	// ustawienie skali pocisku (zgodnie z przekazanym rozmiarem)
	sprite.setPosition(sf::Vector2f(x, y));		// ustawienie pozycji pocisku na przekazane wspó³rzêdne (x, y)

	isRebel = shouldBeRebel;		// okreœlenie, czy pocisk powinien byæ pociskiem gracza czy przeciwnika
	direction = bulletDirection;	// okreœlenie kierunku pocisku (1 dla ruchu do góry, -1 dla ruchu do do³u)
	dmg = damage;					// przypisania wartoœci zmiennej damage do zmiennej dmg

	timeToDie = bornTime + lifeTime;	// ustawienie czasu, po którym pocisk powinien zostaæ usuniêty (czas ¿ycia)
}

// funkcja rysuj¹ca pocisk na ekranie
void bullet::Draw(sf::RenderWindow* window)
{
	if (isAlive && window != nullptr)	// sprawdzenie, czy pocisk ¿yje (czy powinien byæ rysowany na ekranie)
		window->draw(sprite);			// rysowanie sprite'a pocisku na oknie
}

// funkcja odpowiedzialna za poruszanie siê pocisku
void bullet::Move(sf::Clock* clock, float deltaTime)
{
	sprite.move(0.0f, -speed * direction * deltaTime);	// przesuniêcia pozycji pocisku w osi Y na podstawie wartoœci prêdkoœci, kierunku i czasu od ostatniej klatki animacji 

	// czy gracz jest ¿ywy, czy clock istnieje, czy nadszed³ czas umieraæ
	if (isAlive && clock != nullptr && (clock->getElapsedTime().asSeconds() > timeToDie))
	{
		isAlive = false;	// jeœli czas ¿ycia pocisku min¹³, ustaw flagê na "false" - pocisk zostanie usuniêty
	}
}