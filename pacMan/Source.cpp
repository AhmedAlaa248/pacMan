#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
int main()
{
    // Create the window
    RenderWindow window(sf::VideoMode(1920, 1080), "Pac-Man");

    // Set the background color
    window.clear(Color::Black);

    // Load the images
    Texture pacManTexture;
    pacManTexture.loadFromFile("Textures/pcManBg.png");

    // Create the Pac-Man sprite
    Sprite pacMan;
    pacMan.setTexture(pacManTexture);

    //pacMan.setPosition(1920/2, 1080/2);


  /* if (pacMan.getTexture)
   {
       std::cout << "Error loading Pac-Man image" << std::endl;
       return 1;
   }
   else cout << "123464362634";*/

   // Main loop
    while (window.isOpen())
    {
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            // Close the window if the close button is pressed
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        // Move Pac-Man
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            pacMan.move(-1, 0);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            pacMan.move(1, 0);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            pacMan.move(0, -1);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            pacMan.move(0, 1);
        }

        // Draw the Pac-Man sprite
        window.clear(Color::Black);
        window.draw(pacMan);
        window.display();
    }

    return 0;
}