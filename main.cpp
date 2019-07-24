#include <bits/stdc++.h>
using namespace std;
#include <iostream>
#include <conio.h>

void setup();
void Draw();
void Input();
void Logic();
void print_inst();

bool GameOver;
const int width = 30;
const int height = 20;
vector< vector<char> > board;
int head_x, head_y, fruit_x, fruit_y, score;
char dir;
deque <pair<int,int> > v;

void print_inst(){
    cout << "!! WELCOME !!" << endl << "Press any key to continue.";
    getch();
    system("cls");
    cout << "Game Instructions:" << endl << endl;
    cout << "-> Use (a,s,d,w) to move the snake (left, down, right, up)" << endl;
    cout << "-> Food is provided at different places on the board and is represented by \"F\"" << endl;
    cout << "-> Every time snake eats the fruit, its length increases by 1 unit" << endl;
    cout << "-> If snake hits a wall or hits its own body then the game will be over" << endl << endl;
    cout << "Press any key to play (and press esc to quit)";
    if(getch() == 27)
        GameOver = true;
}

void setup(){
    GameOver = false;
    print_inst();
    head_x = width/2;
    head_y = height/2;
    v.push_back({head_x, head_y});
    //m[{head_x,head_y}] = true;
    fruit_x = head_x+2;
    fruit_y = head_y+2;
    //fruit_x = ( rand() % (width-2))+1;
    //fruit_y = ( rand() % (height-2))+1;
    cout << fruit_x << " " << fruit_y << endl;
    score = 0;
    dir = '0';
}

void Draw(){
    system("cls");
    vector< vector<char> > board1(height,vector<char>(width,' '));
    board = board1;
    for(int i = 0 ; i < width ; i++){
        board[0][i] = '#';
        board[height-1][i] = '#';
    }
    for(int i = 0 ; i < height ; i++){
        board[i][0] = '#';
        board[i][width-1] = '#';
    }
    board[fruit_y][fruit_x] = 'F';
    for(int i = 0 ; i < v.size() ; i++){
        int a = v[i].second, b = v[i].first;
        if(v[i].first == head_x && v[i].second == head_y)
            board[a][b] = 'O';
        else board[a][b] = 'o';
    }
    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++)
            cout << board[i][j];
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void Input(){
    if(_kbhit()){
        char x = _getch();
        if(x == 'a')
            dir = 'l';
        else if(x == 's')
            dir = 'd';
        else if(x == 'd')
            dir = 'r';
        else if(x == 'w')
            dir = 'u';
        else if(x == 'q')
            GameOver = true;
    }
}

void Logic(){
    if(dir == 'u'){
        head_y--;
        v.push_back({head_x,head_y});
    }
    else if(dir == 'd'){
        head_y++;
        v.push_back({head_x,head_y});
    }
    else if(dir == 'l'){
        head_x--;
        v.push_back({head_x,head_y});
    }
    else if(dir == 'r'){
        head_x++;
        v.push_back({head_x,head_y});
    }
    if(head_x <= 0 || head_x >= width-1 ||head_y <= 0 || head_y >= height-1){
        GameOver = true;
        cout << endl << "Uh Oh! You just hit a wall!" << endl << "Final Score: " << score << endl;
        return;
    }
    else{
        if(head_x == fruit_x && head_y == fruit_y){
            score++;
            fruit_x = ( rand() % (width-2))+1;
            fruit_y = ( rand() % (height-2))+1;
        }
        else if(dir != '0')
            v.pop_front();
    }
    for(int i = 0 ; i < v.size()-1 ; i++){
        if(v[i].first == head_x && v[i].second == head_y){
            GameOver = true;
            cout << endl << "Uh Oh! You just hit your tail!" << endl << "Final Score: " << score << endl;
        }
    }
}

int main()
{
    setup();
    while(!GameOver){
        Draw();
        Input();
        Logic();
        _sleep(100);
    }
    return 0;
}
