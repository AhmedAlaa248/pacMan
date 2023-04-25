#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace sf;
using namespace std;

const int rows = 23;
const int columns = 21;
const float cellSize = 47;
const float ghostspeed = 1;
const float pacManSpeed = 1;
const float mazeHeight = (rows)*cellSize;
const float mazeWidth = (columns) * cellSize;


//enum ghostDir {LEFT = 0, RIGHT , UP , DOWN };

struct images
{
    Texture texture;
    Sprite sprite;
};

/*struct Position
{
    float x;
    float y;

   bool operator==(const Position& position)
    {
        return x == position.x && y == position.y;
    }
};
Position target;
*/

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
int xDistance = 0; 
int yDistance = 0;
int xStartPosition[8];
int yStartPosition[8];
int lastDirection = 5;
int modeWidth = 1920, modeHeight = 1080;
float xStart = (modeWidth - mazeWidth) / 2;
float yStart = (modeHeight - mazeHeight) / 2;
Text mainMenuItems[5];
bool moveVertical = false;
bool moveHorizontal = false;
bool nameEntered = false;
bool GameOver = false;
int score = 0;

Font font;

// 0 wall, 1 coin, 2 redGhost, 3 pinkGhost, 4 cyanGhost, 5 orangeGhost, 6 pacMan, 7 menuBg, 8 Black
images Images[9];

void drawMaze(Sprite maze[rows][columns]) {
    Images[0].texture.loadFromFile("Textures/Wall.png");
    Images[1].texture.loadFromFile("Textures/coin.png");
    Images[8].texture.loadFromFile("Textures/black.png");

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
                }
            }
        }
    }
}
void ghostCollisionWithWalls(Sprite ghost,Sprite maze[rows][columns]) {
    FloatRect ghostBoundes = ghost.getGlobalBounds();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == 0) {
                FloatRect wallBoundes = maze[i][j].getGlobalBounds();

                if (ghostBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                    maze[i][j].getPosition().y,
                    1.0f, maze[i][j].getGlobalBounds().height)) ||
                    ghostBoundes.intersects(FloatRect(maze[i][j].getPosition().x + wallBoundes.width,
                        maze[i][j].getPosition().y,
                        1.0f, maze[i][j].getGlobalBounds().height)))
                {
                    moveVertical = true;
                    xDistance = -xDistance;    
                }

                if (ghostBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                    maze[i][j].getPosition().y,
                    wallBoundes.width, 1.0f)) ||
                    ghostBoundes.intersects(FloatRect(maze[i][j].getPosition().x,
                        maze[i][j].getPosition().y + wallBoundes.height,
                        wallBoundes.width, 1.0f))) {
                    moveHorizontal = true;
                    yDistance = -yDistance;
                }

            }
        }
    }
}
void ghostCollisionWithPacMan(Sprite ghost , RenderWindow& window) {
    if (ghost.getGlobalBounds().intersects(Images[6].sprite.getGlobalBounds()))
    {
        GameOver = true;
    }
}

void backToMenu(RenderWindow& window) {
    Text back("Back to main menu", font, 50);
    back.setPosition((window.getSize().x / 6) * 4, (window.getSize().y / 5) * 4);

    Mouse mouse;

    back.setFillColor(Color::White);
    if (back.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            windowNum = 5;
        }
        else
            back.setFillColor(Color::Yellow);
    }

    window.draw(back);
}

void gameOverWindow(RenderWindow& window , string userName) {
    font.loadFromFile("Fonts/almosnow.ttf");
    
    string GoodLuck = "Good luck " + userName + " !";
    
    Text gameOver("Game Over", font, 100);
    Text tryAgain("Try Again", font, 50);
    Text niceTry(GoodLuck, font , 120);
    
    gameOver.setPosition((window.getSize().x / 2) - (gameOver.getGlobalBounds().width / 2), (window.getSize().y / 5) - (gameOver.getGlobalBounds().height / 2));
    gameOver.setFillColor(Color::White);

    tryAgain.setPosition((window.getSize().x / 4), (window.getSize().y / 5) * 4);
    tryAgain.setFillColor(Color::White);

    niceTry.setPosition((window.getSize().x / 2) - (niceTry.getGlobalBounds().width / 2), (window.getSize().y / 4) + (niceTry.getGlobalBounds().height));
    niceTry.setFillColor(Color(155, 114, 205));

    window.clear(Color::Black);
    
    backToMenu(window);
    
    window.draw(gameOver);
    window.draw(tryAgain);
    window.draw(niceTry);

}

//pacMan
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
        Images[i].sprite.setScale(2.5, 2.5);
        Images[i].sprite.setPosition(xStartPosition[i], yStartPosition[i]);
    }
}
void redGhostMovement(Sprite& ghost, Sprite maze[rows][columns]) {

    //TODO intRect for Animations
    if (yDistance == 0)
        yDistance = (rand() % 3) - 1;

    if (xDistance == 0)
        xDistance = (rand() % 3) - 1;
    
    if (moveHorizontal)
    {
        ghost.move(xDistance, 0);
        moveHorizontal = 0;
    }else if(moveVertical)
    {
        ghost.move(0, yDistance);
        moveVertical = 0;
    }
    else 
        ghost.move(xDistance, 0);

    /*if (xDistance != 0)
        ghost.move(xDistance, 0);
    else if (yDistance != 0)
        ghost.move(0, yDistance);
*/
    ghostCollisionWithWalls(ghost, maze);
    
}

void scoreDraw(RenderWindow& window) {
    String scoredisplay = "SCORE: " + to_string(score);

    font.loadFromFile("Fonts/actionj.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(45);
    scoreText.setFillColor(Color::Yellow);
    scoreText.setPosition(xStart + mazeWidth + 85, 30);
    scoreText.setString(scoredisplay);
        
    window.draw(scoreText);

    if (score != 0 && GameOver) {
        ofstream offile;
        offile.open("Scores.txt", ios::app);
        offile << score << '*' << endl;
        offile.close();
     
    }
}
void timerDraw(RenderWindow& window, Clock clock) {
    font.loadFromFile("Fonts/actionj.ttf");
    Text timeText;

    timeText.setFont(font);
    timeText.setCharacterSize(45);
    timeText.setFillColor(Color::Yellow);
    timeText.setPosition(xStart - 200, 30);;

    Time passed;
    passed += clock.restart();

    int minutes = passed.asSeconds() / 60;
    int seconds = passed.asSeconds() - minutes * 60;

    string timeWord = (minutes < 10 ? "0" : "") + to_string(minutes) + ':'
        + (seconds < 10 ? "0" : "") + to_string(seconds);

    timeText.setString(timeWord);

    window.draw(timeText);
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
                    return i;
                }
                else
                    mainMenuItems[i].setFillColor(Color::Yellow);
            }
        }
    }
    void moveRandomly(Text text, RenderWindow& window) {
        
        text.move(xDistance , yDistance);
        //cout << xDistance;
        if (text.getPosition().x < 0 || text.getPosition().x > window.getSize().x - text.getGlobalBounds().width) {
             xDistance = -xDistance;
            
        }
         if (text.getPosition().y < 0 || text.getPosition().y > window.getSize().y - text.getGlobalBounds().height)
        {
             xDistance = -yDistance;
        }
         
}
    void newGameItem(RenderWindow& window, Sprite maze[rows][columns], Clock clock) {

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

            window.clear(Color::Black);

            movingPacman(Images[6].sprite, xPosition, yPositon);
            wallCollision(Images[6].sprite, maze);
            teleport(Images[6].sprite, maze);
            teleport(Images[2].sprite, maze);
            redGhostMovement(Images[2].sprite, maze);
            ghostCollisionWithPacMan(Images[2].sprite, window);
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

            timerDraw(window, clock);
            scoreDraw(window);
            window.display();

            if (GameOver)
            {
                windowNum = 6;
                break;
            }
        }
    }
    void bestScoreItem(RenderWindow& window) {

        Font font;
        font.loadFromFile("Fonts/Lightdot-13x6.ttf");
        Text bestscoredraw[100];

        for (int i = 0; i < 100; i++) {
            bestscoredraw[i].setFont(font);
            bestscoredraw[i].setFillColor(Color::White);
            bestscoredraw[i].setCharacterSize(50);

        }
        ifstream infile;
        infile.open("Scores.txt", ios::in);

        vector<string> lines;
        string line;

        while (getline(infile, line, '*')) {
            lines.push_back(line);
        }

        //adding at first
        /* for (int i = line.getSize() - 1, j = 0; i >= 0; i--, j++) {
            bestscoredraw[i].setString(lines[i]);
            bestscoredraw[i].setPosition(50, j * 100);
        } */


        //adding at end
        for (int i = 0; i < lines.size(); i++) {
            bestscoredraw[i].setString(lines[i]);
            bestscoredraw[i].setPosition(50, 100 * i);
        }

        backToMenu(window);

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            /* if (Keyboard::isKeyPressed(Keyboard::Key::Up))
                 if (Keyboard::isKeyPressed(Keyboard::Key::Down))*/
        }

        for (int i = 0; i < lines.size(); i++)
            window.draw(bestscoredraw[i]);
    }
    void settingsItem(RenderWindow& window) {
        //hot el code y 3l22

        backToMenu(window);

    }
    void developersItem(RenderWindow& window) {
        font.loadFromFile("Fonts/actionj.ttf");
        
        Text ourNames , FCIS;
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


        moveRandomly(ourNames, window);

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
                        nameEntered = true;
                        break;
                    }
                    else
                        start.setFillColor(Color::Yellow);
                }

                if (Keyboard::isKeyPressed(Keyboard::Enter) && enter_player_name.size() > 1) {
                    nameEntered = true;
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

int main()
{
    srand(time(0));

    // Create the window
    RenderWindow window(VideoMode(modeWidth, modeHeight), "Pac-Man");
    window.setFramerateLimit(60);
    
    Sprite maze[rows][columns];
    Clock clock;
    string userName;

    Mainmenu mainMenu; 
    drawMaze(maze);
    pacManDrawing();
    ghostsDrawing();
    
    xDistance = (rand() % 3) - 1;
    yDistance = (rand() % 3) - 1;

    windowNum = 5;
    
    // Main loop
    while (window.isOpen())
    {
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
        
        switch (windowNum)
        {
        case 0:
            if (nameEntered == false)
                userName = mainMenu.playername(window);
            else
                mainMenu.newGameItem(window, maze, clock);
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
             gameOverWindow(window , userName);
            break;
        }

        window.display();
    }
    return 0;
}