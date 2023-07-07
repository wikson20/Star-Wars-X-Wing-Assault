#include "enemy.h"

// konstruktor z parametrami - pozwala na ustalenie pocz�tkowej pozycji, rozmiaru, kierunku itp.
enemy::enemy(sf::Texture* tex, int posX, int posY, std::vector<bullet>* bulletsList, sf::Clock* gameClock, sf::RenderWindow* gameWindow)
{
	sprite.setTexture(*tex);					// inicjalizacja sprite'a z za�adowan� tekstur�
	sprite.setScale(sf::Vector2f(0.18, 0.21));  // ustawienie skali tieFightera
	sprite.setPosition(posX, posY);			    // ustawienie pozycji tieFightera na podstawie parametr�w
	bb = bulletsList;							// zapisanie adresu do listy gdzie s� umieszczane pociski
	clock = gameClock;							// zapisanie adresu do g��wnego zegara gry
	window = gameWindow;						// zapisanie adresu do okna gry

	if (!destroySoundBuffer.loadFromFile("kaboom.wav")) {
		std::cout << "Blad ladowania dzwieku" << std::endl;
	}
	destroySound.setBuffer(destroySoundBuffer); // przypisanie wcze�niej za�adowanego bufora d�wi�ku do obiektu d�wi�ku destroySound

	nextShotTime = clock->getElapsedTime().asMilliseconds() + ((rateOfFire/3) * 1000); // op�nienie strza�u po respie
}

// funkcja odpowiedzialna za poruszanie si� tieFightera
// wymaga podania czasu jaki up�yn�� od ostatniej klatki
void enemy::Move(float deltaTime)
{
	if (isAlive() == false) return;// sprawdzenie, czy przeciwnik �yje; je�li nie, zako�cz funkcj�
	sprite.move(tieFighterSpeed * tieFighterXDirection * deltaTime, 0.0f); // przesuni�cie tieFightera w osi X obliczana przez pomno�enie pr�dko�ci, kierunek ruchu i czas, jaki min�� mi�dzy dwiema klatkami animacji

	// sprawdzenie, czy tieFighter przekroczy� granice okna; je�li tak, zmiana kierunku ruchu
	if (sprite.getPosition().x < 0 || sprite.getPosition().x + sprite.getGlobalBounds().width > window->getSize().x)
	{
		tieFighterXDirection = -tieFighterXDirection;  // odwr�cenie kierunku ruchu tieFighter 
	}
	// sprawdzenie, czy przeciwnik mo�e wykona� strza� (up�yn�� odpowiedni czas od ostatniego strza�u)
	// wchodzimy do mieszkania -> (mieszkanie pod adresem)
	// nie mamy obiektu - tylko adres do niego. Dlatego ->
	// czy obecny czas jest wi�kszy od czasu ostatniego strza�u+delay
	if (clock->getElapsedTime().asMilliseconds() >= nextShotTime)
	{
		Shoot(); // wywo�anie funkcji odpowiedzialnej za strzelanie
	}
}

// funckja odpowiedzialna za strzelanie tieFighter
void enemy::Shoot()
{
	nextShotTime = clock->getElapsedTime().asMilliseconds() + (rateOfFire*1000); // zapisanie aktualnego czasu jako czas ostatniego strza�u
	// obliczenie pozycji pocisku tak, aby wypada� on na �rodku tieFightera
	float posX = sprite.getPosition().x -15.0f + sprite.getGlobalBounds().width / 2;
	float posY = sprite.getPosition().y;

	// tworzony jest obiekt bullet; parametry: pozycja X i Y, rozmiar, czas powstania, informacja, �e pocisk nale�y do przeciwnika, kierunek ruchu pocisku, obra�enia
	bullet b = bullet(posX, posY, 0.05f, clock->getElapsedTime().asMilliseconds(), false, -1,10); 
	if(bb)bb->push_back(b); // za�adowanie pocisku do listy pocisk�w
}

// funkcja rysuj�ca tieFighter na ekranie
void enemy::Draw()
{
	if(isAlive()) window->draw(sprite); // rysowanie tieFightera tylko je�li jest on �ywy
}

// funkcja sprawdzaj�ca czy wr�g �yje
bool enemy::isAlive()
{
	return hp > 0; // tieFighter jest �ywy, je�li jego poziom �ycia (hp) jest wi�kszy od zera
	
}

// funkcja odpowiedzialna za zadawanie obra�e� tieFighterowi od gracza
void enemy::TakeDamage(int dmg)
{
	if (hp <= 0) return; //�eby nie zabija� dwa razy
	hp -= dmg;	// zmniejszenie poziomu �ycia przeciwnika o warto�� obra�e� (dmg)
	if (hp <= 0) 
	{
		if (destroySoundBuffer.loadFromFile("kaboom.wav")) { // Sprawdzenie, czy uda�o si� za�adowa� d�wi�k
			destroySound.setBuffer(destroySoundBuffer); // przypisanie wcze�niej za�adowanego bufora d�wi�ku do obiektu d�wi�ku destroySound
			destroySound.play(); // odtwarzanie d�wi�ku "kaboom.wav"
			destroySound.setVolume(3); // ustawienie g�o�no�ci na 3
		}
		//std::cout << "I have low ground" << std::endl;
	}
}

// funkcja przesuwaj�ca tirFightera w d�
void enemy::MoveDown(float amout)
{
	if(isAlive() == true) { // sprawdzenie czy przecinik �yje
	sprite.move(0.0f, amout); // przesuni�cie tieFightera o warto�� amout w osi Y
	}
}

// funkcja pobieraj�ca warto�� wysoko�ci na jakiej znajduje si� tieFighter
int enemy::GetH()
{
	return sprite.getPosition().y; // zwr�cenie warto�ci pozycji Y tieFightera
}