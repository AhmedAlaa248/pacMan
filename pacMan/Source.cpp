#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

int xPosition = 0;
int yPositon = 0;
const int arrSize = 19;

struct images
{
    Texture texture;
    Sprite sprite;
};

images Images[6];

void drawMaze(Sprite maze[arrSize][arrSize], Texture& wall, Texture& coin) {

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
         {0, 0, 0, 0, 1, 0, 1, 0, 0, 2, 0, 0, 1, 0, 1, 0, 0, 0, 0},//10
         {1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1},//11
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
                maze[i][j].setPosition(480+j*50 ,45.5+ i*50);
                maze[i][j].setScale(3.4, 3.4);
            }
            else if (board[i][j] == 1) {
                maze[i][j].setTexture(coin);
                maze[i][j].setPosition(480+j*50.5, 45.5 + i* 50.5);
            }
            
        }
    }

}

void movingPacman(Sprite& pacMan , int& x , int& y) {
    if (Keyboard::isKeyPressed(Keyboard::Left) && pacMan.getPosition().x > 0)
    {
        pacMan.move(-0.5, 0);
        x++;
        x %= 3;
        y = 1;
        pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));

    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) && pacMan.getPosition().x < 1864)
    {
        pacMan.move(0.5, 0);
        x++;
        x %= 3;
        y = 0;
        pacMan.setTextureRect(IntRect(x * 16, y * 15, 16, 15));

    }
    else if (Keyboard::isKeyPressed(Keyboard::Up) && pacMan.getPosition().y > 0)
    {
        pacMan.move(0, -0.5);
        x++;
        x %= 3;
        y = 2;
        pacMan.setTextureRect(IntRect(x * 15.5, y * 16, 15.5, 16));

    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && pacMan.getPosition().y < 1024)
    {
        pacMan.move(0, 0.5);
        x++;
        x %= 3;
        y = 3;
        pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));

    }

}

Sprite pacMandrawing(Texture& texture) {
    
    Sprite pacManSprite;
    pacManSprite.setTexture(texture);
    pacManSprite.setTextureRect(IntRect(xPosition * 17, yPositon * 15, 17, 15));
    pacManSprite.setPosition(960, 500);
    pacManSprite.setScale(3, 3);

    return pacManSprite;
}

Sprite ghostsDrawing(Texture& texture) {

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(xPosition * 16, yPositon * 16, 16, 16));
    sprite.setScale(2.5, 2.5);

    return sprite;
}

int main()
{
    // Create the window
    RenderWindow window(VideoMode(1920, 1080), "Pac-Man");
    
    int board[arrSize][arrSize];
    
    // Intializing textures
    Texture wall, coin;

    // Load the images
    Images[0].texture.loadFromFile("Textures/pacmansprite.png");
    Images[1].texture.loadFromFile("Textures/redGhost.png");
    Images[2].texture.loadFromFile("Textures/pinkGhost.png");
    Images[3].texture.loadFromFile("Textures/cyanGhost.png");
    Images[4].texture.loadFromFile("Textures/orangeGhost.png");
    
    wall.loadFromFile("Textures/Wall.png");
    coin.loadFromFile("Textures/coin.png");

    // Intializing sprites
    Sprite maze[arrSize][arrSize];
    Images[0].sprite = pacMandrawing(Images[0].texture);
    Images[1].sprite = ghostsDrawing(Images[1].texture);
    Images[2].sprite = ghostsDrawing(Images[2].texture);
    Images[3].sprite = ghostsDrawing(Images[3].texture);
    Images[4].sprite = ghostsDrawing(Images[4].texture);

    Images[2].sprite.setPosition(50, 50);
    Images[3].sprite.setPosition(50, 300);
    Images[4].sprite.setPosition(50, 200);

    drawMaze(maze, wall, coin);

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


        movingPacman(Images[0].sprite, xPosition , yPositon);
        
        //Draw the Pac-Man sprite
        
        window.clear(Color::Black);
        window.draw(Images[0].sprite);
        window.draw(Images[1].sprite);
        window.draw(Images[2].sprite);
        window.draw(Images[3].sprite);
        window.draw(Images[4].sprite);
        
        // Draw the maze
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