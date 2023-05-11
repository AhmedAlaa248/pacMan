#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace sf;
using namespace std;

const int rows = 23;
const int columns = 21;
const int maxScore = 225;
const float cellSize = 47;
const float ghostspeed = 1;
const float pacManSpeed = 2;
const float mazeHeight = (rows)*cellSize;
const float mazeWidth = (columns)*cellSize;

struct images
{
    Texture texture;
    Sprite sprite;
};

// 0 wall , 1 coin, 2 redGhostsPlace, 3 pinkGhostsPlace, 4 cyanGhostsPlace, 5 orangeGhostsPlace, 6 pacManPlace, 9 empty cell
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
      {0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0},//9
      {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 9, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},//10
      {7, 1, 1, 1, 1, 1, 1, 1, 0, 4, 5, 3, 0, 1, 1, 1, 1, 1, 1, 1, 7},//11
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

int windowNum;
int xPosition = 0;
int yPositon = 0;
int xStartPosition[9];
int yStartPosition[9];
int modeWidth = 1920, modeHeight = 1080;
float xStart = (modeWidth - mazeWidth) / 2;
float yStart = (modeHeight - mazeHeight) / 2;
Text mainMenuItems[5];
Text resolutionItems[3];
bool nameEntered = false;
bool GameOver = false;
bool muteSound = false;
bool resetGame = false;
bool moveWithWASD = false;
bool moveWithArrows = true;
bool startNewLevel = false;
bool nLevel = false;
int score = 0;
int lives = 3;
int level = 1;
int xDeath = 0;
int xDistanceDev, yDistanceDev;
void returnGameToStart();

SoundBuffer soundBuffer, sB;
Sound sound, s;
Music moveSound;

Font font;

// 0 wall, 1 coin, 2 redGhost, 3 pinkGhost, 4 cyanGhost, 5 orangeGhost, 6 pacMan, 7 menuBg, 8 Black, 9 deathpacman, 10 livespacman , 11 checkMark
images Images[13];

struct Button
{
    Text text;
    RectangleShape rectangle;
    Sprite sprite;

    void createRect(RectangleShape& rect) {
        rect.setFillColor(Color::Transparent);
        rect.setOutlineThickness(2.f);
        rect.setSize(Vector2f(50, 50));
        rect.setOutlineColor(Color::White);

    }
    void createText(Text& t, string s) {
        t.setFont(font);
        t.setCharacterSize(75);
        t.setString(s);
    }
    void textOnClick(Text& T, bool& b) {
        Mouse mouse;
        T.setFillColor(Color::White);
        if (T.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
                sound.setBuffer(soundBuffer);
                if (b)
                    b = false;
                else
                    b = true;

                if (!muteSound)
                    sound.play();

            }
            else
                T.setFillColor(Color::Yellow);
        }
    }
};

struct Ghosts {
    int xA, yA;
    int xDistance, yDistance;
    bool moveVertical, moveHorizontal;

    void ghostCollisionWithPacMan(Sprite& ghost, RenderWindow& window) {
        if (ghost.getGlobalBounds().intersects(Images[6].sprite.getGlobalBounds()))
        {
            lives--;
            soundBuffer.loadFromFile("Sounds/pacman-lose.wav");
            sound.setBuffer(soundBuffer);
            if (!muteSound)
                sound.play();

            //TODO Edit death
            Images[9].texture.loadFromFile("Textures/Death.png");
            Images[6].sprite.setTexture(Images[9].texture);
            Images[6].sprite.setTextureRect(IntRect(16 * xDeath, 0, 16, 16));
            xDeath++;

            returnGameToStart();

        }
        if (lives == 0)
            GameOver = true;
    }
    void ghostCollisionWithWalls(Sprite& ghost, Sprite maze[rows][columns], int& x, int& y, bool& mV, bool& mH) {
        FloatRect ghostBoundes = ghost.getGlobalBounds();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == 0) {
                    FloatRect wallBoundes = maze[i][j].getGlobalBounds();

                    //check collision from left of the wall
                    if (ghostBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                        maze[i][j].getPosition().y,
                        1.0f, maze[i][j].getGlobalBounds().height)))
                    {
                        ghost.setPosition(maze[i][j].getPosition().x - ghostBoundes.width, ghost.getPosition().y);
                        mV = true;
                        x = -x;
                    }
                    //check collision from right of the wall
                    if (ghostBoundes.intersects(FloatRect(maze[i][j].getPosition().x + wallBoundes.width,
                        maze[i][j].getPosition().y,
                        1.0f, maze[i][j].getGlobalBounds().height)))
                    {
                        ghost.setPosition(maze[i][j].getPosition().x + cellSize, ghost.getPosition().y);
                        mV = true;
                        x = -x;
                    }
                    //check collision from top of the wall
                    if (ghostBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                        maze[i][j].getPosition().y,
                        wallBoundes.width, 1.0f))) {
                        ghost.setPosition(ghost.getPosition().x, maze[i][j].getPosition().y - ghostBoundes.height);
                        mH = true;
                        y = -y;
                    }
                    //check collision from bottom of the wall
                    if (ghostBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                        maze[i][j].getPosition().y + wallBoundes.height,
                        wallBoundes.width, 1.0f))) {
                        ghost.setPosition(ghost.getPosition().x, maze[i][j].getPosition().y + cellSize);
                        mH = true;
                        y = -y;
                    }
                }
            }
        }
    }
    void ghostMovement(Sprite& ghost, Sprite maze[rows][columns], int& x, int& y, bool z, bool& mV, bool& mH) {
        Vector2f left_reightghostMovement(x, 0);
        Vector2f up_downghostMovement(0, y);

        if (y == 0)
            y = rand() % 3 - 1;

        if (x == 0)
            x = rand() % 3 - 1;

        if (mV)
        {
            ghost.move(up_downghostMovement);
            mV = 0;
            //Animation
            if (y > 0)
                yA = 3;
            else
                yA = 2;

            xA = 0;
            ghost.setTextureRect(IntRect(xA * 16, yA * 16, 16, 16));
            xA++;
            xA %= 2;

        }
        else if (mH)
        {
            ghost.move(left_reightghostMovement);

            mH = 0;

            //Animation
            if (x > 0)
                yA = 0;
            else
                yA = 1;

            xA = 0;
            ghost.setTextureRect(IntRect(xA * 16, yA * 16, 16, 16));
            xA++;
            xA %= 2;
        }
        else if (!moveVertical && !moveHorizontal)
        {
            if (&ghost == &Images[2].sprite)
            {
                ghost.move(-1, 0);
                yA = 1;
                xA = 1;
                ghost.setTextureRect(IntRect(xA * 16, yA * 16, 16, 16));
                xA++;
                xA %= 2;
            }
            else
            {
                ghost.move(0, -1);
 
                //Animation
                yA = 2;
                xA = 0;
                ghost.setTextureRect(IntRect(xA * 16, yA * 16, 16, 16));
                xA++;
                xA %= 2;
            }
        }

        ghostCollisionWithWalls(ghost, maze, xDistance, yDistance, mV, mH);
    }

};

Ghosts red, pink, orange, blue;
void returnGameToStart()
{
    if (lives >= 1)
    {
        Images[6].sprite.setTexture(Images[6].texture);
        Sleep(1000);
    }

    for (int i = 2; i <= 6; i++)
    {
        Images[i].sprite.setPosition(Vector2f(xStartPosition[i], yStartPosition[i]));
    }

    blue.yDistance = -1;
    pink.yDistance = -1;
    orange.yDistance = -1;

}

void drawMaze(Sprite maze[rows][columns]) {
    if (level % 2 == 0) {
        Images[0].texture.loadFromFile("Textures/brickwall.png");
        Images[1].texture.loadFromFile("Textures/pound.png");
    }
    else
    {
        Images[0].texture.loadFromFile("Textures/Wall.png");
        Images[1].texture.loadFromFile("Textures/coin.png");
        Images[8].texture.loadFromFile("Textures/black.png");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            switch (board[i][j])
            {
            case 0:
                maze[i][j].setTexture(Images[0].texture);
                maze[i][j].setPosition(xStart + j * cellSize, yStart + i * cellSize);
                maze[i][j].setScale(2.9, 2.9);
                break;

            case 1:
                maze[i][j].setTexture(Images[1].texture);
                maze[i][j].setPosition(xStart + j * cellSize, yStart + i * cellSize);
                if (level % 2 == 0)
                    maze[i][j].setScale(0.9, 0.9);
                break;

                // setting initial pos for monsters
            case 2:
                yStartPosition[2] = yStart + i * cellSize;
                xStartPosition[2] = xStart + j * cellSize;
                break;

            case 3:
                yStartPosition[3] = yStart + i * cellSize;
                xStartPosition[3] = xStart + j * cellSize;
                break;

            case 4:
                yStartPosition[4] = yStart + i * cellSize;
                xStartPosition[4] = xStart + j * cellSize;
                break;

            case 5:
                yStartPosition[5] = yStart + i * cellSize;
                xStartPosition[5] = xStart + j * cellSize;
                break;

                // setting initial pos for pacMan
            case 6:
                yStartPosition[6] = yStart + i * cellSize;
                xStartPosition[6] = xStart + j * cellSize;
                break;
            case 7:
                maze[i][j].setTexture(Images[8].texture);
                maze[i][j].setPosition(xStart + j * cellSize, yStart + i * cellSize);
                maze[i][j].setScale(2.9, 2.9);
                break;
            default:
                break;
            }
        }
    }
}

bool backToMenu(RenderWindow& window) {
    Text back("Back to main menu", font, 50);
    back.setPosition((window.getSize().x / 6) * 4, (window.getSize().y / 5) * 4);

    Mouse mouse;

    back.setFillColor(Color::White);
    if (back.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
            sound.setBuffer(soundBuffer);
            if (!muteSound)
                sound.play();
            windowNum = 5;
            lives = 3;
            nameEntered = false;
            resetGame = true;
            nLevel = false;
            startNewLevel = false;
            level = 1;
            
            return true;
        }
        else
            back.setFillColor(Color::Yellow);
    }
    if (GameOver)
        GameOver = false;

    window.draw(back);

}

//pacMan
void pacManDrawing() {
    Images[6].texture.loadFromFile("Textures/pacmansprite.png");

    Images[6].sprite.setTexture(Images[6].texture);
    Images[6].sprite.setTextureRect(IntRect(xPosition * 17, yPositon * 15, 17, 15));
    Images[6].sprite.setPosition(xStartPosition[6], yStartPosition[6]);
    Images[6].sprite.setScale(2.5, 2.5);
}
void movingPacmanWithArrows(Sprite& pacMan, int& x, int& y, Sprite maze[rows][columns]) {

    Vector2f leftpacManMovement(-pacManSpeed, 0);
    Vector2f rightpacManMovement(pacManSpeed, 0);
    Vector2f uppacManMovement(0, -pacManSpeed);
    Vector2f downpacManMovement(0, pacManSpeed);

    if (Keyboard::isKeyPressed(Keyboard::Left) && pacMan.getPosition().x > 0)
    {
        pacMan.move(leftpacManMovement);
        x++;
        x %= 3;
        y = 1;
        pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && pacMan.getPosition().x < 1864)
    {
        pacMan.move(rightpacManMovement);
        x++;
        x %= 3;
        y = 0;
        pacMan.setTextureRect(IntRect(x * 16, y * 15, 16, 15));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up) && pacMan.getPosition().y > 0)
    {
        pacMan.move(uppacManMovement);
        x++;
        x %= 3;
        y = 2;
        pacMan.setTextureRect(IntRect(x * 15.5, y * 16, 15.5, 16));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && pacMan.getPosition().y < 1024)
    {
        pacMan.move(downpacManMovement);
        x++;
        x %= 3;
        y = 3;
        pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));
    }
}
void movingPacmanWithWASD(Sprite& pacMan, int& x, int& y, Sprite maze[rows][columns]) {

    Vector2f leftpacManMovement(-pacManSpeed, 0);
    Vector2f rightpacManMovement(pacManSpeed, 0);
    Vector2f uppacManMovement(0, -pacManSpeed);
    Vector2f downpacManMovement(0, pacManSpeed);

    if (Keyboard::isKeyPressed(Keyboard::A) && pacMan.getPosition().x > 0)
    {
        pacMan.move(leftpacManMovement);
        x++;
        x %= 3;
        y = 1;
        pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));
    }
    if (Keyboard::isKeyPressed(Keyboard::D) && pacMan.getPosition().x < 1864)
    {
        pacMan.move(rightpacManMovement);
        x++;
        x %= 3;
        y = 0;
        pacMan.setTextureRect(IntRect(x * 16, y * 15, 16, 15));
    }
    else if (Keyboard::isKeyPressed(Keyboard::W) && pacMan.getPosition().y > 0)
    {
        pacMan.move(uppacManMovement);
        x++;
        x %= 3;
        y = 2;
        pacMan.setTextureRect(IntRect(x * 15.5, y * 16, 15.5, 16));
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) && pacMan.getPosition().y < 1024)
    {
        pacMan.move(downpacManMovement);
        x++;
        x %= 3;
        y = 3;
        pacMan.setTextureRect(IntRect(x * 16, y * 16, 16, 16));
    }
}

void teleport(Sprite& body, Sprite maze[rows][columns]) {
    FloatRect playerBoundes = body.getGlobalBounds();
    FloatRect wallBoundesLeft = maze[11][0].getGlobalBounds();
    FloatRect wallBoundesRight = maze[11][20].getGlobalBounds();

    if (playerBoundes.intersects(FloatRect(maze[11][0].getPosition().x,
        maze[11][0].getPosition().y,
        1.0f, wallBoundesLeft.height))) {
        body.setPosition(wallBoundesRight.left, wallBoundesRight.top);
    }
    if (playerBoundes.intersects(FloatRect(maze[11][20].getPosition().x + wallBoundesRight.width,
        maze[11][20].getPosition().y,
        1.0f, maze[11][20].getGlobalBounds().height))) {
        body.setPosition(wallBoundesLeft.left + 10, wallBoundesLeft.top);
    }
}

// collisions FN
void wallCollision(Sprite& body, Sprite maze[rows][columns]) {
    FloatRect playerBoundes = body.getGlobalBounds();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == 0) {
                FloatRect wallBoundes = maze[i][j].getGlobalBounds();
                //check collision from right of the wall
                if (playerBoundes.intersects(FloatRect(maze[i][j].getPosition().x + wallBoundes.width,
                    maze[i][j].getPosition().y,
                    1.0f, wallBoundes.height))) {
                    body.move(pacManSpeed, 0);
                }

                //check collision from left of the wall
                if (playerBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                    maze[i][j].getPosition().y,
                    1.0f, maze[i][j].getGlobalBounds().height))) {
                    body.move(-pacManSpeed, 0);
                }

                //check collision from top of the wall
                if (playerBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                    maze[i][j].getPosition().y,
                    wallBoundes.width, 1.0f))) {
                    body.move(0, -pacManSpeed);
                }

                //check collision from bottom of the wall
                if (playerBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                    maze[i][j].getPosition().y + wallBoundes.height,
                    wallBoundes.width, 1.0f))) {
                    body.move(0, pacManSpeed);
                }
            }
        }
    }
}
void coinCollision(Sprite maze[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (Images[6].sprite.getGlobalBounds().intersects(maze[i][j].getGlobalBounds())) {
                if (board[i][j] == 1) {
                    maze[i][j].setPosition(2000000, 2000000);
                    score++;
                    if (score % 7 == 0)
                        nLevel = true;
                    soundBuffer.loadFromFile("Sounds/chomp2.wav");
                    sound.setBuffer(soundBuffer);
                    if (!muteSound)
                        sound.play();
                }
            }
        }
    }
}

//ghosts
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
        Images[i].sprite.setScale(2.3, 2.3);
        Images[i].sprite.setPosition(xStartPosition[i], yStartPosition[i]);
    }
}

void gameOverWindow(RenderWindow& window, string userName, Sprite maze[rows][columns]) {
    font.loadFromFile("Fonts/almosnow.ttf");

    Mouse mouse;
    string GoodLuck = "Good luck " + userName + " !";

    Text gameOver("Game Over", font, 200);
    Text tryAgain("Try Again", font, 50);
    Text niceTry(GoodLuck, font, 120);

    gameOver.setPosition((window.getSize().x / 2) - (gameOver.getGlobalBounds().width / 2), (window.getSize().y / 5) - (gameOver.getGlobalBounds().height / 2));
    gameOver.setFillColor(Color::White);

    tryAgain.setPosition((window.getSize().x / 4), (window.getSize().y / 5) * 4);
    tryAgain.setFillColor(Color::White);

    niceTry.setPosition((window.getSize().x / 2) - (niceTry.getGlobalBounds().width / 2), (window.getSize().y / 4) + (niceTry.getGlobalBounds().height));
    niceTry.setFillColor(Color(155, 114, 205));


    while (window.isOpen())
    {
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            // Close the window if the close button is pressed
            if (event.type == Event::Closed)
                window.close();
        }

        tryAgain.setFillColor(Color::White);
        if (tryAgain.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
                sound.setBuffer(soundBuffer);
                if (!muteSound)
                    sound.play();
                windowNum = 0;
                if (resetGame)
                {
                    lives = 3;
                    level = 1;
                    drawMaze(maze);
                    pacManDrawing();
                    ghostsDrawing();
                    resetGame = false;
                    score = 0;
                    soundBuffer.loadFromFile("Sounds/start-game.wav");
                    sound.setBuffer(soundBuffer);
                    if (!muteSound)
                        sound.play();
                }
            }
            else
                tryAgain.setFillColor(Color::Yellow);
        }
        window.clear(Color::Black);

        window.draw(gameOver);
        window.draw(tryAgain);
        window.draw(niceTry);

        if (backToMenu(window))
            break;

        window.display();

    }
}
void newlevelwindow(RenderWindow& window, string userName, Sprite maze[rows][columns]) {
    font.loadFromFile("Fonts/almosnow.ttf");
    Mouse mouse;
    string congratulations = "Congratulations " + userName + " !";
    Text levelPassed("Level Passed", font, 200);
    Text nextLevel("Next Level", font, 50);
    Text niceTry(congratulations, font, 120);

    levelPassed.setPosition((window.getSize().x / 2) - (levelPassed.getGlobalBounds().width / 2), (window.getSize().y / 5) - (levelPassed.getGlobalBounds().height / 2));
    levelPassed.setFillColor(Color::White);

    nextLevel.setPosition((window.getSize().x / 4), (window.getSize().y / 5) * 4);
    nextLevel.setFillColor(Color::White);

    niceTry.setPosition((window.getSize().x / 2) - (niceTry.getGlobalBounds().width / 2), (window.getSize().y / 4) + (niceTry.getGlobalBounds().height));
    niceTry.setFillColor(Color(155, 114, 205));

    while (window.isOpen())
    {
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            // Close the window if the close button is pressed
            if (event.type == Event::Closed)
                window.close();
        }
        if (level < 2)
        {
            nextLevel.setFillColor(Color::White);
            if (nextLevel.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
                    sound.setBuffer(soundBuffer);
                    if (!muteSound)
                        sound.play();

                    windowNum = 0;
                    if (startNewLevel)
                    {
                        level++;
                        drawMaze(maze);
                        pacManDrawing();
                        ghostsDrawing();
                        startNewLevel = false;
                        soundBuffer.loadFromFile("Sounds/start-game.wav");
                        sound.setBuffer(soundBuffer);
                        if (!muteSound)
                            sound.play();
                        break;
                    }
                }
                else
                    nextLevel.setFillColor(Color::Yellow);
            }
            window.clear(Color::Black);
        }

        if (level < 2)
            window.draw(nextLevel);
        window.draw(levelPassed);
        window.draw(niceTry);

        if (backToMenu(window))
            break;

        window.display();

    }

}

int* startTime(Clock& clock) {
    Time passed;
    passed = clock.getElapsedTime();

    int* time = new int[3];

    time[0] = passed.asSeconds() / 60;              //minutes
    time[1] = passed.asSeconds() - time[0] * 60;    //seconds
    return time;
}

void scoreDraw(RenderWindow& window, string name) {

    string scoredisplay = "SCORE: " + to_string(score);

    font.loadFromFile("Fonts/actionj.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(45);
    scoreText.setFillColor(Color::Yellow);
    scoreText.setPosition(xStart + mazeWidth + 85, 30);
    scoreText.setString(scoredisplay);

    window.draw(scoreText);

    vector<pair <int, string>> lines;
    pair <int, string> line;
    line.first = score;
    line.second = name;
    lines.push_back(line);

    sort(lines.begin(), lines.end());


    if (score != 0 && GameOver) {

        ofstream offile;
        offile.open("dashboard.txt", ios::app);
        for (int i = 0; i < lines.size(); i++) {
            offile << lines[i].second << "\t" << lines[i].first << endl;
            offile.close();
        }
    }
}
void timerDraw(RenderWindow& window, Clock& clock) {
    font.loadFromFile("Fonts/actionj.ttf");
    Text timeText;

    timeText.setFont(font);
    timeText.setCharacterSize(45);
    timeText.setFillColor(Color::Yellow);
    timeText.setPosition(xStart - 200, 30);;

    Time passed;
    passed = clock.getElapsedTime();

    int minutes = passed.asSeconds() / 60;
    int seconds = passed.asSeconds() - minutes * 60;

    string timeWord = (minutes < 10 ? "0" : "") + to_string(minutes) + ':'
        + (seconds < 10 ? "0" : "") + to_string(seconds);

    timeText.setString(timeWord);

    window.draw(timeText);
}
void livesDraw(RenderWindow& window) {

    string scoredisplay = "LIVES:" + to_string(lives);
    Texture pacmanlive1;


    Sprite pacmanlivesprite[3];
    for (int i = 0; i < 3; i++)
    {
        pacmanlivesprite[i].setTexture(Images[6].texture);
        pacmanlivesprite[i].setTextureRect(IntRect(16, 0, 16, 16));
        pacmanlivesprite[i].setPosition(xStart - 200 + (cellSize * i), window.getSize().y / 2 + cellSize);
        pacmanlivesprite[i].setScale(2.5, 2.5);
    }

    font.loadFromFile("Fonts/actionj.ttf");

    Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(45);
    livesText.setFillColor(Color::Yellow);
    livesText.setPosition(xStart - 200, window.getSize().y / 2);
    livesText.setString(scoredisplay);

    window.draw(livesText);
    for (int i = 0; i < lives; i++)
    {
        window.draw(pacmanlivesprite[i]);
    }

}
void levelsDraw(RenderWindow& window) {
    Text levelT;
    string leveldisplay = "Level:" + to_string(level);

    font.loadFromFile("Fonts/actionj.ttf");
    levelT.setFont(font);
    levelT.setCharacterSize(50);
    levelT.setFillColor(Color::Yellow);
    levelT.setString(leveldisplay);
    levelT.setPosition(xStart + mazeWidth + 85, window.getSize().y / 2);
    window.draw(levelT);
}

struct Mainmenu
{
    void drawing(RenderWindow& window) {
        Images[7].texture.loadFromFile("Textures/pcManBg.png");
        Images[7].sprite.setTexture(Images[7].texture);

        font.loadFromFile("Fonts/almosnow.ttf");

        mainMenuItems[0].setString("New game");
        mainMenuItems[1].setString("Best Scores");
        mainMenuItems[2].setString("Settings");
        mainMenuItems[3].setString("Devlopers");
        mainMenuItems[4].setString("Exit");

        window.draw(Images[7].sprite);
        for (int i = 0; i < 5; i++) {
            mainMenuItems[i].setFont(font);
            mainMenuItems[i].setCharacterSize(75);
            mainMenuItems[i].setPosition(100, 290 + i * 100);
            window.draw(mainMenuItems[i]);
        }
    }
    int SelectedItem() {
        Mouse mouse;
        Keyboard keyboard;
        Event event;
        for (int i = 0; i < 5; i++)
        {
            mainMenuItems[i].setFillColor(Color::White);
            if (mainMenuItems[i].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
                    sound.setBuffer(soundBuffer);
                    if (!muteSound)
                        sound.play();
                    return i;
                }
                else
                    mainMenuItems[i].setFillColor(Color::Yellow);
            }
        }
    }
    void newGameItem(RenderWindow& window, Sprite maze[rows][columns], Clock clock, string name) {

        Clock ck, ck1;
        while (window.isOpen())
        {
            int* time = startTime(ck1);

            if (resetGame)
            {
                drawMaze(maze);
                pacManDrawing();
                ghostsDrawing();
                resetGame = false;
                score = 0;
            }

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

            window.clear(Color::Black);
            if (time[1] >= 4 || time[0] > 0)
            {
                if (moveWithArrows)
                    movingPacmanWithArrows(Images[6].sprite, xPosition, yPositon, maze);
                else if (moveWithWASD)
                    movingPacmanWithWASD(Images[6].sprite, xPosition, yPositon, maze);

                wallCollision(Images[6].sprite, maze);

                teleport(Images[2].sprite, maze);
                teleport(Images[5].sprite, maze);
                teleport(Images[6].sprite, maze);

                red.ghostMovement(Images[2].sprite, maze, red.xDistance, red.yDistance, false, red.moveVertical, red.moveHorizontal);
                orange.ghostMovement(Images[5].sprite, maze, orange.xDistance, orange.yDistance, true, orange.moveVertical, orange.moveHorizontal);
                orange.ghostCollisionWithPacMan(Images[5].sprite, window);
                red.ghostCollisionWithPacMan(Images[2].sprite, window);


                if (time[1] == 10 && time[0] == 0)
                    Images[3].sprite.setPosition(Vector2f(xStartPosition[5], yStartPosition[5]));

                if (time[1] >= 10 || time[0] > 0)
                {
                    teleport(Images[3].sprite, maze);
                    pink.ghostMovement(Images[3].sprite, maze, pink.xDistance, pink.yDistance, false, pink.moveVertical, pink.moveHorizontal);
                    pink.ghostCollisionWithPacMan(Images[3].sprite, window);
                }

                if (time[1] == 15 && time[0] == 0)
                    Images[4].sprite.setPosition(Vector2f(xStartPosition[5], yStartPosition[5]));

                if (time[1] >= 15 || time[0] > 0)
                {
                    teleport(Images[4].sprite, maze);
                    blue.ghostMovement(Images[4].sprite, maze, blue.xDistance, blue.yDistance, false, blue.moveVertical, blue.moveHorizontal);
                    blue.ghostCollisionWithPacMan(Images[4].sprite, window);
                }
            }
            delete[] time;
            coinCollision(maze);

            // Draw the maze
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    window.draw(maze[i][j]);
                }
            }

            //Drawing sprites
            for (int i = 2; i < 7; i++) {
                window.draw(Images[i].sprite);
            }

            timerDraw(window, ck);
            scoreDraw(window, name);
            livesDraw(window);
            levelsDraw(window);
            window.display();

            if (GameOver)
            {
                windowNum = 6;
                resetGame = true;
                break;
            }
            if (nLevel && score != 0)
            {
                soundBuffer.loadFromFile("Sounds/winningSound.wav");
                sound.setBuffer(soundBuffer);
                if (!muteSound)
                    sound.play();

                windowNum = 7;
                startNewLevel = true;
                nLevel = false;
                break;

            }
        }
    }
    void bestScoreItem(RenderWindow& window) {
        Images[12].texture.loadFromFile("Textures/bgFromRightUp.png");
        Images[12].sprite.setTexture(Images[12].texture);

        Font font;
        font.loadFromFile("Fonts/Lightdot-13x6.ttf");
        Text bestscoredraw[100];
        Text title; String header = "Best Scores";
        title.setFont(font);
        title.setFillColor(Color::Magenta);
        title.setCharacterSize(100);
        title.setString(header);
        title.setPosition(100, 50);

        ifstream infile;
        infile.open("dashboard.txt", ios::in);

        vector<pair<int, string>> lines;
        pair<int, string> line;


        while (infile >> line.second >> line.first) {
            lines.push_back(line);
        }

        sort(lines.rbegin(), lines.rend());

        for (int i = 0; i < lines.size(); i++) {
            bestscoredraw[i].setFont(font);
            bestscoredraw[i].setFillColor(Color::White);
            bestscoredraw[i].setCharacterSize(50);
            bestscoredraw[i].setString(lines[i].second + '\t' + to_string(lines[i].first));
            bestscoredraw[i].setPosition((window.getSize().x / 3), 100 * i + 200);
        }

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.draw(Images[12].sprite);
        backToMenu(window);
        window.draw(title);

        for (int i = 0; i < lines.size(); i++)
            window.draw(bestscoredraw[i]);
    }
    void settingsItem(RenderWindow& window) {
        Images[11].texture.loadFromFile("Textures/check_mark.png");
        Images[12].texture.loadFromFile("Textures/bgFromLeft.png");
        Images[12].sprite.setTexture(Images[12].texture);

        Font font;
        font.loadFromFile("Fonts/almosnow.ttf");

        Mouse mouse;

        Text resolutionText, settingsText, playText;

        Button soundBTN, wasdBTN, arrowsBTN;

        soundBTN.createText(soundBTN.text, "Mute");
        wasdBTN.createText(wasdBTN.text, "\tW-A-S-D");
        arrowsBTN.createText(arrowsBTN.text, "ARROWS\t-");

        soundBTN.sprite.setTexture(Images[11].texture);
        soundBTN.createRect(soundBTN.rectangle);

        wasdBTN.sprite.setTexture(Images[11].texture);
        wasdBTN.createRect(wasdBTN.rectangle);

        arrowsBTN.sprite.setTexture(Images[11].texture);
        arrowsBTN.createRect(arrowsBTN.rectangle);

        settingsText.setFont(font);
        playText.setFont(font);
        resolutionText.setFont(font);

        settingsText.setFillColor(Color::Yellow);

        settingsText.setCharacterSize(75);
        playText.setCharacterSize(75);
        resolutionText.setCharacterSize(75);

        settingsText.setString("SETTINGS");

        playText.setString("PLAY WITH : ");

        resolutionText.setString("RESOLUTION:");
        resolutionItems[0].setString("2560 * 1600\t-");
        resolutionItems[1].setString("\t1980 * 1060\t-");
        resolutionItems[2].setString("\t1680 * 1050");

        soundBTN.text.setPosition(70, 130);
        soundBTN.rectangle.setPosition(10, 155);
        soundBTN.sprite.setPosition(10, 155);
        wasdBTN.text.setPosition(860, 265);
        wasdBTN.rectangle.setPosition(860, 290);
        wasdBTN.sprite.setPosition(860, 290);
        arrowsBTN.text.setPosition(500, 265);
        arrowsBTN.rectangle.setPosition(445, 290);
        arrowsBTN.sprite.setPosition(440, 290);

        playText.setPosition(10, 265);
        resolutionText.setPosition(10, 425);

        soundBTN.sprite.setScale(0.1, 0.1);
        wasdBTN.sprite.setScale(0.1, 0.1);
        arrowsBTN.sprite.setScale(0.1, 0.1);

        soundBTN.textOnClick(soundBTN.text, muteSound);

        //arrows button click
        arrowsBTN.text.setFillColor(Color::White);
        if (arrowsBTN.text.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
                sound.setBuffer(soundBuffer);
                if (moveWithArrows)
                {
                    moveWithArrows = false;
                    moveWithWASD = true;
                }
                else
                {
                    moveWithArrows = true;
                    moveWithWASD = false;
                }

                if (!muteSound)
                    sound.play();

            }
            else
                arrowsBTN.text.setFillColor(Color::Yellow);
        }

        //wasd button click
        wasdBTN.text.setFillColor(Color::White);
        if (wasdBTN.text.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
                sound.setBuffer(soundBuffer);
                if (moveWithWASD)
                {
                    moveWithWASD = false;
                    moveWithArrows = true;
                }
                else
                {
                    moveWithWASD = true;
                    moveWithArrows = false;
                }

                if (!muteSound)
                    sound.play();
            }
            else
                wasdBTN.text.setFillColor(Color::Yellow);
        }

        window.draw(Images[12].sprite);

        for (int i = 0; i < 3; i++) {
            resolutionItems[i].setFont(font);
            resolutionItems[i].setCharacterSize(65);
            resolutionItems[i].setPosition(500 + i * 360, 425);
            window.draw(resolutionItems[i]);
        }

        for (int i = 0; i < 3; i++)
        {
            resolutionItems[i].setFillColor(Color::White);
            if (resolutionItems[i].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
                    sound.setBuffer(soundBuffer);
                    if (!muteSound)
                        sound.play();
                }
                else
                    resolutionItems[i].setFillColor(Color::Yellow);
            }
        }

        if (muteSound)
            window.draw(soundBTN.sprite);

        if (moveWithArrows)
            window.draw(arrowsBTN.sprite);

        if (moveWithWASD)
            window.draw(wasdBTN.sprite);

        window.draw(settingsText);
        window.draw(resolutionText);
        window.draw(playText);
        window.draw(soundBTN.text);
        window.draw(soundBTN.rectangle);
        window.draw(wasdBTN.text);
        window.draw(wasdBTN.rectangle);
        window.draw(arrowsBTN.text);
        window.draw(arrowsBTN.rectangle);
        backToMenu(window);
    }
    void developersItem(RenderWindow& window) {
        Images[12].texture.loadFromFile("Textures/devBG.png");
        Images[12].sprite.setTexture(Images[12].texture);

        font.loadFromFile("Fonts/actionj.ttf");

        Text ourNames, FCIS;
        String names;
        names = "Ahmed Alaa\n \nAhmed Essam\n \nAhmed Mahmoud\n \nAbdallah Yasser\n \nAbelrahman Maamon\n \nOmar Khattab\n \nSalah Eldein Tarek\n \nZiad Saeed";

        ourNames.setFont(font);
        ourNames.setString(names);
        ourNames.setCharacterSize(40);
        ourNames.Bold;
        ourNames.setFillColor(Color::Red);
        ourNames.setPosition((window.getSize().x / 2) - (ourNames.getGlobalBounds().width / 2), (window.getSize().y / 2) - (ourNames.getGlobalBounds().height / 2));

        FCIS.setFont(font);
        FCIS.setString("FCIS 26");
        FCIS.setCharacterSize(75);
        FCIS.setFillColor(Color::Magenta);
        FCIS.setPosition(35, 20);

        window.draw(Images[12].sprite);
        backToMenu(window);

        window.draw(FCIS);
        window.draw(ourNames);
    }
    string playername(RenderWindow& window) {
        Mouse mouse;

        Font font;
        font.loadFromFile("Fonts/Lightdot-13x6.ttf");
        Text EnterName, Name;
        string enter_player_name;
        RectangleShape rectangle;

        rectangle.setFillColor(Color::Transparent);
        rectangle.setOutlineThickness(7.f);
        rectangle.setOutlineColor(Color::White);

        Text start("START", font, 50);
        Text back("Back", font, 50);
        start.setPosition((window.getSize().x / 3), (window.getSize().y / 5) * 4);
        back.setPosition((window.getSize().x / 6) * 4, (window.getSize().y / 5) * 4);

        if (enter_player_name.empty())
            enter_player_name.clear();

        EnterName.setFont(font);
        EnterName.setCharacterSize(100);
        EnterName.Bold;
        EnterName.setFillColor(Color::Magenta);
        EnterName.setString("Enter your name:");
        EnterName.setPosition((window.getSize().x / 2) - (EnterName.getGlobalBounds().width / 2), (window.getSize().y / 3) - (EnterName.getGlobalBounds().height / 2));

        Name.setFont(font);
        Name.setCharacterSize(55);
        Name.setFillColor(Color::Blue);
        Name.setPosition(30 + (window.getSize().x / 2) - (EnterName.getGlobalBounds().width / 2), (window.getSize().y / 2) - (EnterName.getGlobalBounds().height / 2));

        rectangle.setPosition(15 + (window.getSize().x / 2) - (EnterName.getGlobalBounds().width / 2), -2.5 + (window.getSize().y / 2) - (EnterName.getGlobalBounds().height / 2));
        rectangle.setSize(Vector2f(EnterName.getGlobalBounds().width - 30, 60.0));

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed()) {
                    window.close();
                }
                if (event.type == Event::TextEntered) {
                    enter_player_name += static_cast<char>(event.text.unicode);
                }
                if (Keyboard::isKeyPressed(Keyboard::BackSpace) && enter_player_name.size() > 0) {
                    enter_player_name.resize(enter_player_name.size() - 1);
                }

                start.setFillColor(Color::White);
                if (start.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
                    if (Mouse::isButtonPressed(Mouse::Left) && enter_player_name.size() > 1) {
                        soundBuffer.loadFromFile("Sounds/start-game.wav");
                        sound.setBuffer(soundBuffer);

                        nameEntered = true;
                        if (!muteSound)
                            sound.play();
                        break;
                    }
                    else
                        start.setFillColor(Color::Yellow);
                }

                if (Keyboard::isKeyPressed(Keyboard::Enter) && enter_player_name.size() > 1) {
                    soundBuffer.loadFromFile("Sounds/start-game.wav");
                    sound.setBuffer(soundBuffer);

                    nameEntered = true;
                    if (!muteSound)
                        sound.play();
                    break;
                }
                Name.setString(enter_player_name);
                window.clear();
                window.draw(EnterName);
                window.draw(rectangle);
                window.draw(Name);
                window.draw(start);
                window.draw(back);
                window.display();
            }
            if (nameEntered)
                break;

            back.setFillColor(Color::White);
            if (back.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    soundBuffer.loadFromFile("Sounds/pressed_sound.wav");
                    sound.setBuffer(soundBuffer);
                    if (!muteSound)
                        sound.play();
                    windowNum = 5;
                    break;
                }
                else
                    back.setFillColor(Color::Yellow);
            }
        }
        return enter_player_name;
    }

};

void intializeVariables() {

    red.xDistance = (rand() % 3) - 1;
    red.yDistance = 1;
    pink.xDistance = (rand() % 3) - 1;
    pink.yDistance = (rand() % 3) - 1;
    orange.xDistance = (rand() % 3) - 1;
    orange.yDistance = (rand() % 3) - 1;
    blue.xDistance = (rand() % 3) - 1;
    blue.yDistance = (rand() % 3) - 1;

    red.moveHorizontal = false;
    red.moveVertical = false;
    pink.moveHorizontal = false;
    pink.moveVertical = false;
    orange.moveHorizontal = false;
    orange.moveVertical = false;
    blue.moveHorizontal = false;
    blue.moveVertical = false;

    xDistanceDev = 10;
    yDistanceDev = 10;

    windowNum = 5;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(modeWidth, modeHeight), "Pac-Man");

    Sprite maze[rows][columns];
    Clock clock;
    string userName;

    Mainmenu mainMenu;
    drawMaze(maze);
    pacManDrawing();
    ghostsDrawing();

    intializeVariables();

    // Main loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear(Color::Black);

        switch (windowNum)
        {
        case 0:
            if (nameEntered == false)
                userName = mainMenu.playername(window);
            else
                mainMenu.newGameItem(window, maze, clock, userName);
            break;
        case 1:
            mainMenu.bestScoreItem(window);
            break;
        case 2:
            mainMenu.settingsItem(window);
            break;
        case 3:
            mainMenu.developersItem(window);
            break;
        case 4:
            window.close();
            break;
        case 5:
            mainMenu.drawing(window);
            windowNum = mainMenu.SelectedItem();
            break;
        case 6:
            gameOverWindow(window, userName, maze);
            break;
        case 7:
            newlevelwindow(window, userName, maze);
            break;
        }


        window.display();
    }
    return 0;
}