#include <iostream> 
#include <cstdlib>   // For rand() and system("cls")
#include <windows.h> // For Sleep(), cursor manipulation
#include <conio.h>   // For kbhit() and getch() - Console IO
#include <ctime> // For time()
using namespace std;

bool gameOver;
const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';
#define MaxLength 1000

const int width = 50;    
const int height = 25;

int score = 0;
int highestScore = 0;

class Point{
public:
    int x, y;

    Point(){}

    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

class Food{
public:
    Point position;

    Food(){}

    Food(Point p[], int l){
        spawnFood(p,l);
    }

    void spawnFood(Point p[], int l){
        bool foodOverlap = true;
        while(foodOverlap){
            foodOverlap = false;
            position.x = 1 + rand() % (width - 2);  
            position.y = 1 + rand() % (height - 2); 

            for(int i = 0; i < l; i++){
                if(p[i].x == position.x && p[i].y == position.y){
                    foodOverlap = true;  
                    break;
                }
            }
        }
    }

    ~Food(){}
};

class Snake{
public:
    Point body[MaxLength];
    int length;
    char direction;

    Snake(){
        length = 3;
        direction = UP;
        for(int i = 0; i < length; i++){
            body[i] = Point(width / 2 - i, height / 2);
        }
    }

    void changeDirection(char newDirection){
        if(newDirection == UP && direction != DOWN){
            direction = newDirection;
        }
        else if(newDirection == DOWN && direction != UP){
            direction = newDirection;
        }
        else if(newDirection == LEFT && direction != RIGHT){
            direction = newDirection;
        }
        else if(newDirection == RIGHT && direction != LEFT){
            direction = newDirection;
        }
    }

    void move(){
        for(int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        if(direction == UP) 
            body[0].y--;
        else if(direction == DOWN) 
            body[0].y++;
        else if(direction == LEFT) 
            body[0].x--;
        else if(direction == RIGHT) 
            body[0].x++;
    }

    void grow(){
        if(length < MaxLength){
            body[length] = body[length - 1];
            length++;
        }
    }

    bool checkCollision(){
        if(body[0].x <= 0 || body[0].x >= width - 1 || body[0].y <= 0 || body[0].y >= height - 1)
            return true;
        for(int i = 1; i < length; i++){
            if(body[0].x == body[i].x && body[0].y == body[i].y)
                return true;
        }
        return false;
    }

    ~Snake(){}
};

HANDLE hConsole;

class GameBoard{
public:
    Snake snake;    
    Food food1, food2;
    
    GameBoard(){
        score  = 0;
        gameOver = false;
        food1 = Food(snake.body, snake.length);
        food2 = Food(snake.body, snake.length);
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void draw(){
        // system("cls");
        cout << "\033[H";

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(j == 0 || j == width-1 || i == 0 || i == height-1){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
                    cout << "#";
                }   
                else if(i == food1.position.y && j == food1.position.x){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << "o";
                }     
                else if(i == food2.position.y && j == food2.position.x){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << "o";
                }    
                else{
                    bool checkPrint = false;
                    for(int k = 0; k < snake.length; k++){
                        if (snake.body[k].x == j && snake.body[k].y == i){
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                            cout << (k == 0 ? "O" : "o");
                            checkPrint = true;
                            break;
                        }
                    }
                    if(checkPrint == false){
                        cout << " ";
                    }
                }
            }
            cout << "\n";
        }
        // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "Score: " << score << "   |   High Score: " << highestScore << "\n\n";
    }

    void input(){
        if(kbhit()){
            int key = getch();
            if(key == 'w' || key == 'W'){
                snake.changeDirection(UP);
            }
            else if(key == 'a' || key == 'A'){
                snake.changeDirection(LEFT);
            }
            else if(key == 's' || key == 'S'){
                snake.changeDirection(DOWN);
            }
            else if(key == 'd' || key == 'D'){
                snake.changeDirection(RIGHT);
            }
        }
    }

    void update(){
        snake.move();

        if(snake.body[0].x == food1.position.x && snake.body[0].y == food1.position.y){
            score += 10;
            food1.spawnFood(snake.body,snake.length);
            snake.grow();
        }
        if(snake.body[0].x == food2.position.x && snake.body[0].y == food2.position.y){
            score += 10;
            food2.spawnFood(snake.body,snake.length);
            snake.grow();
        }
        if(snake.body[0].x <= 0 || snake.body[0].x >= width - 1 || snake.body[0].y <= 0 || snake.body[0].y >= height - 1){
            gameOver = true;
        }
        if(snake.checkCollision()){
            gameOver = true;
        }
        if(score > highestScore){
            highestScore = score;
        }
    }  

    void restart(){
        score = 0;
        snake = Snake();
        food1 = Food(snake.body,snake.length);
        food2 = Food(snake.body,snake.length);
        gameOver = false;
    }
};

void speedController(Snake& snake){
    if (snake.direction == UP || snake.direction == DOWN){
        if(score <= 50)
            Sleep(80);  
        else if(score > 50 && score <= 100)
            Sleep(60);
        else
            Sleep(50);
    } 
    else{
        if(score <= 50)
            Sleep(60);
        else if(score > 50 && score <= 100)
            Sleep(40);
        else
            Sleep(30);
    }
}

void hideCursor(){
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(hConsole, &cursor);
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursor);
}

int main(){

    srand(time(0));
    GameBoard game;
    gameOver = false;

    hideCursor();

    system("cls");
        
    cout << "================== SNAKE GAME ==================\n";
    cout << "Welcome to the classic Snake game!\n";
    cout << "Control the snake using:\n";
    cout << "  W - Move Up\n";
    cout << "  A - Move Left\n";
    cout << "  S - Move Down\n";
    cout << "  D - Move Right\n";
    cout << "Eat food (o) to grow and increase your score(+10).\n";
    cout << "Avoid hitting the walls and yourself!\n";
    cout << "Press 'ENTER' key to start...\n";
    cin.get();
    cout << "================= GAME STARTED! =================";
    Sleep(500);
    
    while(true){
        while(gameOver == false){
            game.draw();
            game.input();
            game.update();

            speedController(game.snake);
        }

        system("cls");
        cout << "\n\n================== GAME OVER! ==================\n\n";
        cout << "Final Score: " << score << "\n";
        cout << "Highest Score: " << highestScore << "\n\n\n";
        cout << "Press 'R' to Restart or 'Q' to Quit: ";
        char choice = _getch();
        if(choice == 'r' || choice == 'R'){
            game.restart();
            gameOver = false;
        } 
        else if(choice == 'q' || choice == 'Q'){
            break; 
        }
    }

    return 0;
}