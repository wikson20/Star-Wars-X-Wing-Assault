#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gracz.h"
#include "enemy.h"
#include "bullet.h"

int main()
{
    // inicjalizacja okna
    sf::RenderWindow window(sf::VideoMode(900, 900), "Star Wars: X-Wing Assault", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true); //włączenie synchronizacji pionowej

    int WINDOW_W = window.getSize().x; // zmienna przechowująca szerokość okna
    int WINDOW_H = window.getSize().y; // zmienna przechowująca wysokość okna

    // ładowanie tekstury tła
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("backgroundstars.png"))
    {
        std::cout << "Blad ladowania obrazka" << std::endl;
    }
    
    sf::Music musicbackground;          // obiekt klasy sf::Music służący do odtwarzania muzyki w tle
    sf::SoundBuffer startSoundBuffer;   // bufor dźwięku strzału
    sf::Sound startSound;               // obiekt dźwięku strzału

    if (!musicbackground.openFromFile("tlo1.wav")) {
        std::cout << "Blad ladowania muzyki" << std::endl;
    }
    if (!startSoundBuffer.loadFromFile("start.wav")) {
        std::cout << "Blad ladowania muzyki" << std::endl;
    }
    startSound.setBuffer(startSoundBuffer); // przypisanie wcześniej załadowanego bufora dźwięku do obiektu dźwięku startSound
    musicbackground.play();                 // odtwarzanie muzyki w tle 
    musicbackground.setLoop(true);          // ustawienie zapętlania muzyki

    sf::Texture textures[3];
    textures[0].loadFromFile("xwing.jpg");      // textura gracza (X-Wing)
    textures[1].loadFromFile("tie.png");        // textura przeciwnika (TIE-Fighter)
    textures[2].loadFromFile("bullet.png");     // textura pocisku

    sf::Sprite backgroundSprite;                    // obiekt sprite'a - reprezentuje grafikę tła
    backgroundSprite.setTexture(backgroundTexture); // ustawienie tekstury tła na sprite backgroundSprite

    sf::Font font; // obiekt klasy sf::Font przechowujący informacje o czcionce
    if (!font.loadFromFile("Starjedi.ttf")) {
        std::cout << "Blad ladowania fonta!" << std::endl;
    }

    // text z liczbą punktów
    sf::Text points;                // obiekt klasy sf::Text reprezentujący tekst z liczbą punktów
    points.setFont(font);           // ustawienie fonta dla tekstu points
    points.setString("Points");     // ustawienie treści tekstu points na "Points"

    // text game over
    sf::Text gameOverText;                              // obiekt klasy sf::Text reprezentujący tekst informujący o zakończeniu gry
    gameOverText.setFont(font);                         // ustawienie fonta dla tekstu gameOverText
    gameOverText.setString("press space to play");      // treść
    gameOverText.setCharacterSize(60);                  // wielkość tekstu
    gameOverText.setFillColor(sf::Color(255,255,0));    // kolor tekstu
    gameOverText.setPosition((WINDOW_W/2)- (gameOverText.getCharacterSize()*6.25f), WINDOW_H/2.5f); // pozycja tekstu

    sf::Clock clock; // zegar gry

    // lista pocisków
    std::vector<bullet> bullets;

    // tworzenie gracza (X-wing) i listy przeciwników
    gracz xwing = gracz(&textures[0],&bullets, &clock, &window); // obiekt xwing typu gracz; wskaźnik do tekstury, wektora pocisków, zegara (&clock), okna
    std::vector<enemy> enemies; // lista przeciwników
    
    float lastFrame{ 0 };           // czas kiedy pojawila sie poprzednia klatka
    float nextWaveTime{ 2.5f };     // czas oczekiania na nastepna fale w sekundach
    float nextWave{ 0 };            // czas kiedy pojawi sie nastepna fala
    
    bool inGame = true;             // flaga wskazująca, czy gra jest w toku
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asMilliseconds() - lastFrame;  // czas jaki minął między dwoma klatkami animacji
        lastFrame = clock.getElapsedTime().asMilliseconds();                    // przechowuje czas ostatniej klatki animacji 

        // etap obslugi wejscia gracza
        sf::Event event;                // przechowuje informacje o zdarzeniach
        while (window.pollEvent(event)) // pobiera zdarzenia i zapisuje do zmiennej event
        {
            switch (event.type) 
            {
                case sf::Event::Closed: // sprawdza czy zostało zamknięte okno
                    window.close();
                    break;

                case sf::Event::KeyPressed:                                 // sprawdza czy został naciśnięty klawisz
                    if (event.key.code == sf::Keyboard::Space && !inGame)   // sprawdza czy został naciśnięty klawisz spacji oraz czy nie jesteśmy w grze
                    {
                        //rozpoczęcie gry po naciśnięciu spacji po przegranej
                        //restart
                        inGame = true;          // jesteśmy w grze
                        nextWave = clock.getElapsedTime().asMilliseconds() + (nextWaveTime*1000); // czas pojawienia się następnej fali
                        bullets.clear();        // wyczyszczenie listy pocisków
                        enemies.clear();        // wyczyszczenie listy przeciwników
                        xwing.ResetPlayer();    // reset gracza
                        startSound.play();      // odtwarzanie dźwięku startowego
                    }
                    break;
                default:
                    break;
            }
            xwing.InputMove(&event); // przekazujemy adres eventu do obiektu xwing
        }  

        // najpierw czyscimy okno, a potem na nim cos narysujemy
        window.clear();
        window.draw(backgroundSprite);

        if (inGame)
        {
            // generowanie nowej fali, gdy obecny czas jest większy od oczekiwanego czasu pojawienia się kolejnej fali
            if(clock.getElapsedTime().asMilliseconds() >= nextWave)
            {
                // przeciwnicy ruszaja sie w dol by zrobic miejsce dla nowych
                for (int i{ 0 }; i < enemies.size(); i++)
                {
                    enemies[i].MoveDown(100);
                }

                // tworzenie nowych przeciwników
                int number = (rand() % 5) + 1; // losowanie przeciwników w zakresie od 1 do 5
                for(int i{0};i<number;i++)
                {
                    // dodawanie przeciwników do enemy przekazując tekstury, losowe pozycje ((rand() % 800) dla osi X i 100 dla osi Y), adres wektora bullets, adres zegara clock, adres okna window
                    enemies.push_back(enemy(&textures[1], (rand() % 800), 100, &bullets, &clock, &window)); 
                }

                // obliczamy czas kiedy ma się pojawić nowa fala
                nextWave = clock.getElapsedTime().asMilliseconds() + (nextWaveTime * 1000);
            }

            // pętla, w której poruszamy wszystkimi przeciwnikami na mapie
            // rysowanie wszystkich przeciwników i sprawdzanie, czy dolecieli do dołu ekranu
            for (int i{ 0 }; i < enemies.size(); i++)
            {
                enemies[i].Move(deltaTime);
                enemies[i].Draw();

                // przeciwnik jest zbyt nisko - gracz przegrywa
                if (enemies[i].GetH() >= 700 && enemies[i].isAlive())
                {
                    inGame = false;
                }
            }
            
            xwing.Move(deltaTime);  // obsługa ruchu gracza, przekazujemy kopię deltaTime
            xwing.Draw();           // rysowanie gracza (X-wing)

            // kolizje z pociskami
            for (int i{ 0 }; i < bullets.size(); i++)
            {
                if (bullets[i].isAlive)
                {
                    bullets[i].Move(&clock, deltaTime); // ruch pocisku 
                    bullets[i].Draw(&window);           // rysowanie pocisku 
                    
                    if(bullets[i].isRebel == true) // jeżeli pocisk jest gracza
                    {
                        for (int j{ 0 }; j < enemies.size(); j++)
                        {
                            // sprawdzeie czy zaszła kolizja
                            bool isColliding = enemies[j].sprite.getGlobalBounds().intersects(bullets[i].sprite.getGlobalBounds());
                            if (enemies[j].isAlive() && isColliding) // jeżeli pocisk jest żywy i zaszła kolizja
                            {
                                enemies[j].TakeDamage(bullets[i].dmg);  // odebranie punktów życia przeciwnikowi w przypadku trafienia przez pocisk gracza
                                bullets[i].isAlive = false;             // pocisk zostaje usunięty po trafieniu
                            }
                        }
                    }
                    else 
                    {
                        // sprawdzeie czy zaszła kolizja
                        bool isColliding = xwing.sprite.getGlobalBounds().intersects(bullets[i].sprite.getGlobalBounds());
                        if (isColliding) // jeżeli zaszła kolizja
                        {
                            xwing.TakeDamage(bullets[i].dmg); // odebranie punktów życia gracza w przypadku trafienia przez wrogi pocisk
                            bullets[i].isAlive = false;       // pocisk zostaje usunięty po trafieniu
                        }
                    }
                    
                }
            }

            // obliczanie wyniku na podstawie ilości wraków
            int score{ 0 };
            for (int i{ 0 }; i < enemies.size(); i++)
            {
                if (enemies[i].isAlive() == false) score++; // jeżeli przeciwnik nie żyje, dodajemy punkty
            }
            points.setString("Score: "+std::to_string(score)); // przypisanie aktualnej liczby punktów do points

            // jezeli wciaz nie przegralismy, to sprawdzamy jeszcze czy gracz ma jakies HP
            if (inGame) 
            {
                inGame = xwing.isAlive();
            }

            window.draw(points); // rysowanie na ekranie liczby punktów
        }
        else 
        {
            window.draw(gameOverText);// wyświetlenie tekstu "Game Over" po przegranej
        }
        
        window.display(); // wyświetlanie aktualnego stanu okna
    }
    return 0;
}