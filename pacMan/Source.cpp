#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

void DrawBoard(int board[19][19])
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (board[i][j] == 0)
                cout << "\033[1;40m   \033[0m";  //40 # Black
            else if (board[i][j] == 1)
                cout << "\033[1;46m***\033[0m"; //46 # Cyan
            else if (board[i][j] == 2)
                cout << "\033[1;46m   \033[0m";
        }
        cout << '\n';
    }
}

int main()
{
    //0 wall(black)
    //1 coin
    //2 wall(blue)
    int board[19][19] = {
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
         {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
         {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0},
         {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
         {0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0},
         {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    DrawBoard(board);


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