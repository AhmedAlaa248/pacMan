#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Animation.h"
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

class Movement
{
public:
    Movement() {};

    void movementDirection(const int& dir, sf::Sprite& spritesheet)
    {
        switch (dir) {
        case 0:
            spritesheet.move(sf::Vector2f(0, -.5));
            break;
        case 1:
            spritesheet.move(sf::Vector2f(0, .5));
            break;
        case 2:
            spritesheet.move(sf::Vector2f(.5, 0));
            break;
        case 3:
            spritesheet.move(sf::Vector2f(-.5, 0));
            break;
        }
    }
};

int main()
{
    int x = 0;
    int y = 0;
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
    Vector2i source(DIRECTION_X_DOWN_INITAL, DIRECTION_Y_DOWN_INITAL);
    Movement movement;
    

    // Set the background color
    window.clear(Color::Black);

    // Load the images
    Texture pacManTexture;
    pacManTexture.loadFromFile("Textures/pacmansprite.png");

    // Create the Pac-Man sprite
    Sprite pacMan;
    pacMan.setTexture(pacManTexture);
    
    pacMan.setTextureRect(IntRect(x*17, y *15 ,17, 15));
    pacMan.setPosition(960, 500);
    pacMan.setScale(5, 5);
    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();

   
   
  /*  Animation animation(&pacManTexture, Vector2u(3, 4), 0.3f);
    float deltaTime = 0.0f;
    sf::Clock clock;*/
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
        //deltaTime = clock.restart().asSeconds();

        // Handle events
        Event event;
        while (window.pollEvent(event))
          
        {
            sf::Time elapsedTime = clock.getElapsedTime() - prevTime;
            prevTime = prevTime + elapsedTime;
            // Close the window if the close button is pressed
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        // Move Pac-Man
        
        if (Keyboard::isKeyPressed(Keyboard::Left)&& pacMan.getPosition().x>0)
        {
            movement.movementDirection(3, pacMan);
            source.x = DIRECTION_X_LEFT_INITAL;
            source.y = DIRETION_Y_LEFT_INITAL;
            x++;
            x %= 3;
            y =1 ;
            pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));
                
           }
        else if (Keyboard::isKeyPressed(Keyboard::Right)&& pacMan.getPosition().x < 1864)
        {
            movement.movementDirection(2, pacMan);
            source.x = DIRECTION_X_RIGHT_INITAL;
            source.y = DIRECTION_Y_RIGHT_INITAL;
            x++;
            x %= 3;
            y = 0;
            pacMan.setTextureRect(IntRect(x * 16, y*15 ,16, 15));
            
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up)&&pacMan.getPosition().y >0)
        {
            movement.movementDirection(0, pacMan);
            source.x = DIRECTION_X_UP_INITAL;
            source.y = DIRECTION_Y_UP_INITAL;
          
            x++;
            x %= 3;
            y = 2;
            pacMan.setTextureRect(IntRect(x * 15.5, y * 16, 15.5, 16));
            
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down)&& pacMan.getPosition().y<1024)
        {
            movement.movementDirection(1, pacMan);
            source.x = DIRECTION_X_DOWN_INITAL;
            source.y = DIRECTION_Y_DOWN_INITAL;
            x++;
            x %= 3;
            y = 3;
            pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));
            
        }
        //animation.updateImage(0, deltaTime, true);
      //  pacMan.setTextureRect(animation.uvRect);
        // Draw the Pac-Man sprite
        window.clear(Color::Black);
        window.draw(pacMan);
        window.display();
    }

    return 0;
}