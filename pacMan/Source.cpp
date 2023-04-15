#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

const int rows = 23;
const int columns = 21;
const float pacManSpeed = 0.6;

int score=0;

Font font;

struct images
{
    Texture texture;
    Sprite sprite;
};

// 0 wall
   // 1 coin
   // 2 redGhostsPlace
   // 3 pinkGhostsPlace
   // 4 cyanGhostsPlace
   // 5 orangeGhostsPlace
   // 6 pacManPlace
   // 9 empty cell

int board[rows][columns] = {
    // 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//0
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},//1
      {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},//2
      {0, 1, 0, 9, 0, 1, 0, 9, 0, 1, 0, 1, 0, 9, 0, 1, 0, 9, 0, 1, 0},//3
      {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},//4
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},//5
      {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},//6
      {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},//7
      {0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0},//8
      {0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0},//9
      {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 2, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},//10
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 4, 5, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1},//11
      {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},//12
      {0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 6, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0},//13
      {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},//14
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},//15
      {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},//16
      {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},//17
      {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0},//18
      {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},//19
      {0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0},//20
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},//21
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//22
};

int xPosition = 0;
int yPositon = 0;
int xStartPosition[8];
int yStartPosition[8];

// 0 wall, 1 coin, 2 redGhost, 3 pinkGhost, 4 cyanGhost, 5 orangeGhost, 6 pacMan 
images Images[8];

void drawMaze(Sprite maze[rows][columns]) {
    Images[0].texture.loadFromFile("Textures/Wall.png");
    Images[1].texture.loadFromFile("Textures/coin.png");
    
   

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            switch (board[i][j])
            {
                case 0:
                    maze[i][j].setTexture(Images[0].texture);
                    maze[i][j].setPosition(480 + j * 45, 10 + i * 45);
                    maze[i][j].setScale(2.9, 2.9);
                    break;

                case 1:
                    maze[i][j].setTexture(Images[1].texture);
                    maze[i][j].setPosition(480 + j * 45, 10 + i * 45);
                    break;
            
                // setting initial pos for monsters
                case 2:
                    yStartPosition[2] = 10 + i *45;
                    xStartPosition[2] = 480 + j *45;
                    break;

                case 3:
                    yStartPosition[3] = 10 + i * 45;
                    xStartPosition[3] = 480 + j * 45;
                    break;

                case 4:
                    yStartPosition[4] = 10 + i * 45;
                    xStartPosition[4] = 480 + j * 45;
                    break;

                case 5:
                    yStartPosition[5] = 10 + i * 45;
                    xStartPosition[5] = 480 + j * 45;
                    break;

                // setting initial pos for pacMan
                case 6:
                    yStartPosition[6] = 10 + i * 45;
                    xStartPosition[6] = 480 + j * 45;
            default:
                break;
            }
        
        }
    }

}

void pacManDrawing() {
    Images[6].texture.loadFromFile("Textures/pacmansprite.png");

    Images[6].sprite.setTexture(Images[6].texture);
    Images[6].sprite.setTextureRect(IntRect(xPosition * 17, yPositon * 15, 17, 15));
    Images[6].sprite.setPosition(xStartPosition[6], yStartPosition[6]);
    Images[6].sprite.setScale(2.5, 2.5);

}

void movingPacman(Sprite& pacMan, int& x, int& y) {
    if (Keyboard::isKeyPressed(Keyboard::Left) && pacMan.getPosition().x > 0)
    {
        pacMan.move(-pacManSpeed, 0);
        x++;
        x %= 3;
        y = 1;
        pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));

    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) && pacMan.getPosition().x < 1864)
    {
        pacMan.move(pacManSpeed, 0);
        x++;
        x %= 3;
        y = 0;
        pacMan.setTextureRect(IntRect(x * 16, y * 15, 16, 15));

    }
    else if (Keyboard::isKeyPressed(Keyboard::Up) && pacMan.getPosition().y > 0)
    {
        pacMan.move(0, -pacManSpeed);
        x++;
        x %= 3;
        y = 2;
        pacMan.setTextureRect(IntRect(x * 15.5, y * 16, 15.5, 16));

    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && pacMan.getPosition().y < 1024)
    {
        pacMan.move(0, pacManSpeed);
        x++;
        x %= 3;
        y = 3;
        pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));

    }
}

void ghostsDrawing() {
    
    Images[2].texture.loadFromFile("Textures/redGhost.png");
    Images[3].texture.loadFromFile("Textures/pinkGhost.png");
    Images[4].texture.loadFromFile("Textures/cyanGhost.png");
    Images[5].texture.loadFromFile("Textures/orangeGhost.png");

    Sprite sprite;
    for (int i = 2; i < 6; i++)
    {
        Images[i].sprite.setTexture(Images[i].texture);
        Images[i].sprite.setTextureRect(IntRect(xPosition * 16, yPositon * 16, 16, 16));
        Images[i].sprite.setScale(2.5, 2.5);
        Images[i].sprite.setPosition(xStartPosition[i], yStartPosition[i]);

    }
}

void wallCollision(Sprite& body , Sprite maze[rows][columns]) {
    FloatRect playerBoundes = body.getGlobalBounds();
    for (int i = 0; i < rows; i++)
    { 
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == 0) {
                //check collision from left of the wall
                if (playerBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                                                                 maze[i][j].getPosition().y,
                                                                 1.0f, maze[i][j].getGlobalBounds().height))) {
                    body.move(-pacManSpeed, 0);
                }
               
                //check collision from right of the wall
                if (playerBoundes.intersects(FloatRect(maze[i][j].getPosition().x + maze[i][j].getGlobalBounds().width,
                                                                maze[i][j].getPosition().y,
                                                                 1.0f , maze[i][j].getGlobalBounds().height))) {
                    body.move(pacManSpeed, 0);
                }

                //check collision from top of the wall
                if (playerBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                                                                maze[i][j].getPosition().y,
                                                                maze[i][j].getGlobalBounds().width , 1.0f))) {
                    body.move(0, -pacManSpeed);
                }

                //check collision from bottom of the wall
                if (playerBoundes.intersects(FloatRect(maze[i][j].getPosition().x ,
                                                                maze[i][j].getPosition().y + maze[i][j].getGlobalBounds().height,
                                                                maze[i][j].getGlobalBounds().width, 1.0f))) {
                    body.move(0, pacManSpeed);
                }

            }
        }
    }
    }

int coinCollision(Sprite maze[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (Images[6].sprite.getGlobalBounds().intersects(maze[i][j].getGlobalBounds())) {
                if (board[i][j] == 1) {
                    maze[i][j].setPosition(2000000, 2000000);
                    score++;
                }
            }
        }
    }
    return score;
}

void scoreDraw(RenderWindow& window) {
    String scoredisplay = "SCORE: " + to_string(score);

    font.loadFromFile("Fonts/actionj.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(Color::Yellow);
    scoreText.setPosition(120, 50);
    scoreText.setString(scoredisplay);

    window.draw(scoreText);
}

void timerDraw(RenderWindow& window  , Clock clock) {
    font.loadFromFile("Fonts/actionj.ttf");
    Text timeText;

    timeText.setFont(font);
    timeText.setCharacterSize(45);
    timeText.setPosition(1500, 25);

    Time passed;
    passed += clock.restart();

    int minutes = passed.asSeconds() / 60;
    int seconds = passed.asSeconds() - minutes * 60;

    string timeWord = (minutes < 10 ? "0" : "") + to_string(minutes) + ':'
        + (seconds < 10 ? "0" : "") + to_string(seconds);

    timeText.setString(timeWord);

    window.draw(timeText);
}

int main()
{
    // Create the window
    RenderWindow window(VideoMode(1920, 1080), "Pac-Man");
    
    Sprite maze[rows][columns];
    Clock clock;
    
    drawMaze(maze);
    pacManDrawing();
    ghostsDrawing();
    
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

        movingPacman(Images[6].sprite, xPosition , yPositon);
        wallCollision(Images[6].sprite, maze);
        coinCollision(maze);
        
        //Drawing sprites
        window.clear(Color::Black);
        for (int i = 2; i < 7; i++) {
            window.draw(Images[i].sprite);
        }

        // Draw the maze
        for (int i = 0 ; i < rows; i++){
            for (int j = 0; j < columns; j++){
                window.draw(maze[i][j]);
            }
        }

        timerDraw(window, clock);
        scoreDraw(window);
        
        window.display();
   
    }
    return 0;
}