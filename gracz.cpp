#include "gracz.h"

gracz::gracz(sf::Texture* tex, std::vector<bullet>* bb, sf::Clock* gameClock, sf::RenderWindow* gameWindow) // konstruktor z parametrami
{
    sprite.setTexture(*tex);                        // inicjalizacja obiektu klasy sf::Sprite za pomoc� przekazanej tekstury (tex)
    sprite.setScale(sf::Vector2f(0.15, 0.18));      // ustawienie skali gracza
    sprite.setPosition(sf::Vector2f(375, 750));     // ustawienie pocz�tkowej pozycji gracza
    bullets = bb;                                   // zapisanie adresu do listy gdzie s� umieszczane pociski
    clock = gameClock;                              // zapisanie adresu do g��wnego zegara gry
    window = gameWindow;                            // zapisanie adresu do okna gry
    if (!font.loadFromFile("Starjedi.ttf"))
    {
        std::cout << "Error while loading font!" << std::endl;
    }

    // ustawienie tekstu napisu "Health" na ekranie
    healthText.setFont(font);           // ustawienie fonta dla tekstu healthText
    healthText.setString("Health");     // ustawienie tre�ci tekstu healthText na Health
    healthText.setPosition(0,50);       // ustawienie pozycji napisu na ekranie (0, 50)


    if (!shootSoundBuffer.loadFromFile("strzal1.wav")) {
        std::cout << "Blad ladowania dzwieku" << std::endl;
    }
    shootSound.setBuffer(shootSoundBuffer); // przypisanie wcze�niej za�adowanego bufora d�wi�ku do obiektu d�wi�ku shootSound
}

// obsluga przyciskow
void gracz::InputMove(sf::Event* inputEvent)
{
    if (inputEvent == nullptr) return;  // sprawdza czy podany wska�nik istnieje, je�eli nie istnieje zako�cz funkcj�
    if (isAlive() == false) return;     // je�li gracz nie �yje, zako�cz funkcj�
        switch (inputEvent->type) 
        {
        case sf::Event::KeyPressed: 
        case sf::Event::KeyReleased:
            {
                bool leftButton{ sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) };
                bool rightButton{ sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) };
                bool shootButton{ sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) };

                if (leftButton && !rightButton) //ruch w lewo
                {
                    input.x = -1.0f;
                }

                if (rightButton && !leftButton) //ruch w prawo
                {
                    input.x = 1.0f;
                }

                if (leftButton == rightButton)//oba wcisniete lub oba niewcisniete
                {
                    input.x = 0;
                }

                if (shootButton) //strza�
                {
                    Shoot(); // wywo�anie funkcji odpowiedzialnej za strzelanie
                }
            }
            break;
        
        default:
            break;
        }
}

// funkcja odpowiedzialna za ruch gracza 
void gracz::Move(float deltaTime)
{
    if (window == nullptr) return;                  // sprawdzanie czy istnieje okno, je�eli nie - zako�cz dzia�anie funkcji
    sprite.move(playerSpeed * deltaTime * input);   // przesuwa pozycj� gracza na podstawie pr�dko�ci, czasu mi�dzy klatkami animacji i warto�ci wej�cia

    // zabezpieczenie z lewej
    if (sprite.getPosition().x < 0) 
    {
        sprite.setPosition(0, sprite.getPosition().y);
    }

    // zabezpieczenie z prawej
    if (sprite.getPosition().x + sprite.getGlobalBounds().width > window->getSize().x) 
    {
        sprite.setPosition(window->getSize().x - sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}

// funkcja odpowiedzialna za strzelanie 
void gracz::Shoot()
{
    if (bullets == nullptr) return; // je�eli nie ma pocisk�w na li�cie, zako�cz dzia�anie funkcji
    if (clock->getElapsedTime().asMilliseconds() <= timeToShoot) return; // je�eli aktualny czas jest mniejszy od czasu na strza�, zako�cz dzia�anie funkcji

    float posX = sprite.getPosition().x + 26.0f + sprite.getGlobalBounds().width/2;     // ustawienie pozycji na osi x
    float posY = sprite.getPosition().y;                                                // ustawienie pozycji na osi y

    // tworzony jest obiekt bullet; parametry: pozycja X i Y, rozmiar, czas powstania, informacja, �e pocisk nale�y do gracza, kierunek ruchu pocisku, obra�enia
    bullet b = bullet(posX, posY, 0.05f, clock->getElapsedTime().asSeconds(), true, 1, 25);
    bullets->push_back(b); // pocisk dodany do listy pocisk�w

    float posX2 = sprite.getPosition().x -26.0f;
    bullet c = bullet(posX2, posY, 0.05f, clock->getElapsedTime().asSeconds(), true);
    bullets->push_back(c);

    shootSound.play();          // odtwarzanie d�wi�ku strza�u
    shootSound.setVolume(15);   // ustawienie g�o�no�ci na 15

    timeToShoot = clock->getElapsedTime().asMilliseconds() + (shotDelay * 1000); // zmienna przechowuj�ca czas, kiedy mo�na ponownie odda� strza�
    
}

//funckja rysuj�ca gracza na ekranie
void gracz::Draw()
{
    if ((isAlive() == false) || (window == nullptr)) return;        // je�li gracz nie �yje, lub nie istnieje okno
    std::string healthString = "Health: " + std::to_string(hp);     // ustawienie tesktu wy�wietlaj�cego ilo�� �ycia
    healthText.setString(healthString);                             // healthText przechowuje warto�� healthString

    window->draw(healthText);   // narysuj tekst z ilo�ci� �ycia
    window->draw(sprite);       // narysuj gracza (sprite)
}

// sprawdzanie czy gracz �yje
bool gracz::isAlive()
{
	return hp > 0; // gracz jest �ywy, je�li jego poziom �ycia (hp) jest wi�kszy od zera
}

// funkcja odpowiedzialna za zadawanie obra�e� graczowi od przeciwnika
void gracz::TakeDamage(int dmg) 
{
   hp -= dmg; // zmniejszenie poziomu �ycia przeciwnika o warto�� obra�e� (dmg)
}

// funckja resetuj�ca gracza (respawn)
void gracz::ResetPlayer()
{
    hp = 100; // nadanie pocz�tkowej ilo�ci �ycia
    sprite.setPosition(sf::Vector2f(375, 750)); // ustalenie pozycji gracza
}