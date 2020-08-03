#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(500.0f, 500.0f), "Game", Style::Close);
    Event event;
    //Bat
    RectangleShape entity(Vector2f(100.0f,30.0f));
    entity.setFillColor(Color::Cyan);
    entity.setPosition(250.0f,0.0f);
    //Ball
    Texture ball;
    ball.loadFromFile("BALL.PNG");
    RectangleShape subject(Vector2f(50.0f,50.0f));
    subject.setTexture(&ball);
    subject.setPosition(225.0f, 225.0f);

    float xvel = 0.2;
    float yvel = -0.3;
    //sf::Clock clock;
    
    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) cout << "Text: " << (char)event.text.unicode << endl;
            }
        }
        //Bat System
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            entity.move(0.5f, 0.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            entity.move(-0.5f, 0.0f);
        }
        //Ball System
        subject.move(xvel, yvel);
        bool hitbat = subject.getGlobalBounds().top <= 30.0f &&
            ( subject.getGlobalBounds().left < entity.getGlobalBounds().left + 100.0f &&
              subject.getGlobalBounds().left < entity.getGlobalBounds().left + 100.0f );
        if (hitbat) {
            yvel *= -1;
        }
        if ((subject.getGlobalBounds().top + 50.0f) >= 500.0f) {
            yvel *= -1;
        }
        if ((subject.getGlobalBounds().left <= 0.0f) || ((subject.getGlobalBounds().left + 50.0f) >= 500.0f)) {
            xvel *= -1;
        }
        if (subject.getGlobalBounds().top <= 0){
            window.close();
        }
        window.clear(Color::Black);

        window.draw(entity);
        window.draw(subject);

        window.display();
    }

}