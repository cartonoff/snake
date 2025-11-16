#include<iostream>
#include<Windows.h>
#include<ctime>
using namespace std;

void gotoxy(int x, int y){
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

const int WIDTH = 18;
const int HEIGHT = 10;
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT - 2);
const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;

int dir = UP;
bool isRunning = true;

char map[] = 
"#################\n"
"#               #\n"
"#               #\n"
"#               #\n"
"#               #\n"
"#               #\n"
"#               #\n"
"#               #\n"
"#               #\n"
"#################\n";

char snake = '0';

int snake_x[MAX_LEN_SNAKE] = {0};
int snake_y[MAX_LEN_SNAKE] = {0};
int snake_len = 1;

int food_x = 1 + (rand() % (WIDTH-3));
int food_y = 1 + (rand() % (HEIGHT-2));
char food = '*';

int main()
{
    system("cls");
    snake_x[0] = WIDTH/2;
    snake_y[0] = HEIGHT/2;
    int time = clock();
    // Отрисовка карты
    while (isRunning){
        if (GetKeyState('A') & 0x8000){
            dir = LEFT;
        }
        if (GetKeyState('S') & 0x8000){
            if (dir!=UP)
                dir = DOWN;
        }
        if (GetKeyState('D') & 0x8000){
            dir = RIGHT;
        }
        if (GetKeyState('W') & 0x8000){
            if (dir!=DOWN)
                dir = UP;
        }
        if ((clock() - time) / CLOCKS_PER_SEC >= 0.5){  
            time = clock();
            if (snake_x[0] == food_x && snake_y[0] == food_y){
                snake_len++;
                food_x = 1 + (rand() % (WIDTH-3));
                food_y = 1 + (rand() % (HEIGHT-2)); 
            }
            for(int i = snake_len - 2; i >= 0; i--){
                snake_x[i+1] = snake_x[i];
                snake_y[i+1] = snake_y[i];
            }

            switch(dir){
                case UP:
                    snake_y[0]--;
                    break;
                case DOWN:
                    snake_y[0]++;
                    break;
                case RIGHT:
                    snake_x[0]++;
                    break;
                case LEFT:
                    snake_x[0]--;
                    break;
            }
            if (snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == WIDTH - 2 || snake_y[0] == HEIGHT - 2){
                isRunning = false;
            }

            for(int i = 1; i < snake_len; i++){
                if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
                    isRunning = false;
                    break;
                }
            }

            gotoxy(0, 0);
            cout<<"Length: "<<snake_len<<endl;
            map[food_y * WIDTH + food_x] = food;
            for(int i = 0; i < snake_len; i++){
                map[snake_y[i]*WIDTH + snake_x[i]] = snake;
            }
            cout<<map;
            for(int i = 0; i < snake_len; i++){
                map[snake_y[i]*WIDTH + snake_x[i]] = ' ';
            }
        }   
    }

    gotoxy(1, HEIGHT/2);
    cout<<"YOUR SCORE IS "<<snake_len;
    gotoxy(WIDTH, HEIGHT); 
}