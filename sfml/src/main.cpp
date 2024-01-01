#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Template");

    // enable VSync
    window.setVerticalSyncEnabled(true);

    // create circle with radius
    sf::CircleShape circle(50);

    // set the circle color
    circle.setFillColor(sf::Color(100, 250, 50));

    // main event loop
    while (window.isOpen()) {
        // get all events
        sf::Event event;

        // loop through events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw the shapes
        window.draw(circle);

        // display all
        window.display();
    }
}
