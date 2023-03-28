#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pac-Man");

    // Set the background color
    window.clear(sf::Color::Black);

    // Load the images
    sf::Texture pacManTexture;
    if (!pacManTexture.loadFromFile("images/pacman.png"))
    {
        std::cout << "Error loading Pac-Man image" << std::endl;
        return 1;
    }

    // Create the Pac-Man sprite
    sf::Sprite pacMan(pacManTexture);
    pacMan.setPosition(1920/2, 1080/2);
    pacMan.setTexture(pacManTexture);
    pacMan.setScale(3, 3);

    Animation(pacManTexture, 0.5f , sf::Vector2u(3, 4));
    float deltaTime = 0.0f;
    sf::Clock clock;


    // Main loop
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window if the close button is pressed
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Move Pac-Man
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            pacMan.move(-1, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            pacMan.move(1, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pacMan.move(0, -1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pacMan.move(0, 1);
        }
        updateImage(0, deltaTime,false);
        pacMan.setTextureRect(uvRect);
        // Draw the Pac-Man sprite
        window.clear(sf::Color::Black);
        window.draw(pacMan);
        window.display();
       
    }

    return 0;
}