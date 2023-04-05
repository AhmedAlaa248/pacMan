#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Animation.h"
using namespace sf;
using namespace std;

const int arrSize = 19;

void drawMaze(int arr[arrSize][arrSize], Sprite maze[arrSize][arrSize], Texture& wall, Texture& coin) {

    //0 wall
    //1 coin
    int board[arrSize][arrSize] = {
       // 1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
         {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},//2
         {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},//3
         {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},//4
         {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},//5
         {0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},//6
         {0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},//7
         {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},//8
         {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},//9
         {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},//10
         {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},//11
         {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},//12
         {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},//13
         {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},//14
         {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},//15
         {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},//16
         {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},//17
         {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},//18
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//20
    };

    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < arrSize; j++) {
            if (board[i][j] == 0){
                maze[i][j].setTexture(wall);
                maze[i][j].setPosition(480+j*50,50+ i*50);
                maze[i][j].setScale(3.4, 3.4);
            }
            else if (board[i][j] == 1) {
                maze[i][j].setTexture(coin);
                maze[i][j].setPosition(480+j*50.5,50+ i* 50.5);
            }
            
        }
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

    // Create the window
    RenderWindow window(sf::VideoMode(1920, 1080), "Pac-Man");
    Vector2i source(DIRECTION_X_DOWN_INITAL, DIRECTION_Y_DOWN_INITAL);
    Movement movement;
    

    int boar[arrSize][arrSize];
    Texture wall, coin;
    wall.loadFromFile("Textures/Wall.png");
    coin.loadFromFile("Textures/coin.png");

    Sprite maze[arrSize][arrSize];

    drawMaze(boar, maze, wall, coin);

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
    pacMan.setScale(3, 3);
    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();

   
   
  /*  Animation animation(&pacManTexture, Vector2u(3, 4), 0.3f);
    float deltaTime = 0.0f;
    sf::Clock clock;*/
    //pacMan.setPosition(1920/2, 1080/2);


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
        for (int i = 0 ; i < arrSize; i++)
        {
            for (int j = 0; j < arrSize; j++) {
                window.draw(maze[i][j]);
            }
        }
        window.display();
    }

    return 0;
}