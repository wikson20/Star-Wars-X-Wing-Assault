#include "enemy.h"

// konstruktor z parametrami - pozwala na ustalenie pocz¹tkowej pozycji, rozmiaru, kierunku itp.
enemy::enemy(sf::Texture* tex, int posX, int posY, std::vector<bullet>* bulletsList, sf::Clock* gameClock, sf::RenderWindow* gameWindow)
{
	sprite.setTexture(*tex);					// inicjalizacja sprite'a z za³adowan¹ tekstur¹
	sprite.setScale(sf::Vector2f(0.18, 0.21));  // ustawienie skali tieFightera
	sprite.setPosition(posX, posY);			    // ustawienie pozycji tieFightera na podstawie parametrów
	bb = bulletsList;							// zapisanie adresu do listy gdzie s¹ umieszczane pociski
	clock = gameClock;							// zapisanie adresu do g³ównego zegara gry
	window = gameWindow;						// zapisanie adresu do okna gry

	if (!destroySoundBuffer.loadFromFile("kaboom.wav")) {
		std::cout << "Blad ladowania dzwieku" << std::endl;
	}
	destroySound.setBuffer(destroySoundBuffer); // przypisanie wczeœniej za³adowanego bufora dŸwiêku do obiektu dŸwiêku destroySound

	nextShotTime = clock->getElapsedTime().asMilliseconds() + ((rateOfFire/3) * 1000); // opóŸnienie strza³u po respie
}

// funkcja odpowiedzialna za poruszanie siê tieFightera
// wymaga podania czasu jaki up³yn¹³ od ostatniej klatki
void enemy::Move(float deltaTime)
{
	if (isAlive() == false) return;// sprawdzenie, czy przeciwnik ¿yje; jeœli nie, zakoñcz funkcjê
	sprite.move(tieFighterSpeed * tieFighterXDirection * deltaTime, 0.0f); // przesuniêcie tieFightera w osi X obliczana przez pomno¿enie prêdkoœci, kierunek ruchu i czas, jaki min¹³ miêdzy dwiema klatkami animacji

	// sprawdzenie, czy tieFighter przekroczy³ granice okna; jeœli tak, zmiana kierunku ruchu
	if (sprite.getPosition().x < 0 || sprite.getPosition().x + sprite.getGlobalBounds().width > window->getSize().x)
	{
		tieFighterXDirection = -tieFighterXDirection;  // odwrócenie kierunku ruchu tieFighter 
	}
	// sprawdzenie, czy przeciwnik mo¿e wykonaæ strza³ (up³yn¹³ odpowiedni czas od ostatniego strza³u)
	// wchodzimy do mieszkania -> (mieszkanie pod adresem)
	// nie mamy obiektu - tylko adres do niego. Dlatego ->
	// czy obecny czas jest wiêkszy od czasu ostatniego strza³u+delay
	if (clock->getElapsedTime().asMilliseconds() >= nextShotTime)
	{
		Shoot(); // wywo³anie funkcji odpowiedzialnej za strzelanie
	}
}

// funckja odpowiedzialna za strzelanie tieFighter
void enemy::Shoot()
{
	nextShotTime = clock->getElapsedTime().asMilliseconds() + (rateOfFire*1000); // zapisanie aktualnego czasu jako czas ostatniego strza³u
	// obliczenie pozycji pocisku tak, aby wypada³ on na œrodku tieFightera
	float posX = sprite.getPosition().x -15.0f + sprite.getGlobalBounds().width / 2;
	float posY = sprite.getPosition().y;

	// tworzony jest obiekt bullet; parametry: pozycja X i Y, rozmiar, czas powstania, informacja, ¿e pocisk nale¿y do przeciwnika, kierunek ruchu pocisku, obra¿enia
	bullet b = bullet(posX, posY, 0.05f, clock->getElapsedTime().asMilliseconds(), false, -1,10); 
	if(bb)bb->push_back(b); // za³adowanie pocisku do listy pocisków
}

// funkcja rysuj¹ca tieFighter na ekranie
void enemy::Draw()
{
	if(isAlive()) window->draw(sprite); // rysowanie tieFightera tylko jeœli jest on ¿ywy
}

// funkcja sprawdzaj¹ca czy wróg ¿yje
bool enemy::isAlive()
{
	return hp > 0; // tieFighter jest ¿ywy, jeœli jego poziom ¿ycia (hp) jest wiêkszy od zera
	
}

// funkcja odpowiedzialna za zadawanie obra¿eñ tieFighterowi od gracza
void enemy::TakeDamage(int dmg)
{
	if (hp <= 0) return; //¿eby nie zabijaæ dwa razy
	hp -= dmg;	// zmniejszenie poziomu ¿ycia przeciwnika o wartoœæ obra¿eñ (dmg)
	if (hp <= 0) 
	{
		if (destroySoundBuffer.loadFromFile("kaboom.wav")) { // Sprawdzenie, czy uda³o siê za³adowaæ dŸwiêk
			destroySound.setBuffer(destroySoundBuffer); // przypisanie wczeœniej za³adowanego bufora dŸwiêku do obiektu dŸwiêku destroySound
			destroySound.play(); // odtwarzanie dŸwiêku "kaboom.wav"
			destroySound.setVolume(3); // ustawienie g³oœnoœci na 3
		}
		//std::cout << "I have low ground" << std::endl;
	}
}

// funkcja przesuwaj¹ca tirFightera w dó³
void enemy::MoveDown(float amout)
{
	if(isAlive() == true) { // sprawdzenie czy przecinik ¿yje
	sprite.move(0.0f, amout); // przesuniêcie tieFightera o wartoœæ amout w osi Y
	}
}

// funkcja pobieraj¹ca wartoœæ wysokoœci na jakiej znajduje siê tieFighter
int enemy::GetH()
{
	return sprite.getPosition().y; // zwrócenie wartoœci pozycji Y tieFightera
}