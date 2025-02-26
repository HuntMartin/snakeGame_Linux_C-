#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#include<fcntl.h>

using namespace std;

bool overFlag;
const int width = 20;
const int height = 20;

int fruitX, fruitY, score, x, y;

int tailX[100], tailY[100];

int countTails;

enum moveMent{ STOP = 0, LEFT, RIGHT, UP, DOWN};
moveMent dir;

void Draw(){
        for(int i = 0; i < width + 2; i++){
                cout << "#";
        }
        cout << endl;

        for(int i = 0; i < height; i++){
                for(int j = 0; j < width + 2; j++){
                        bool empty = true;
                        if(j == 0){
                                cout << "#";
                        }
                        if(j == width + 1){
                                cout << "#";
                        }
                        if(i == y && j == x && empty == true){
                                cout << "0";
                                empty = false;
                        }
                        if(i == fruitY && j == fruitX + 1 && empty == true){
                                cout << "F";
                                empty = false;
                        }
                        for(int k=0; k < countTails; k++){
                                if(tailY[k] == i && tailX[k]  == j){
                                        cout << "o";
                                        empty = false;
                                }
                        }

                        if(j < width + 1 && j > 0 && empty == true){
                                        cout << " ";
                        }


                }
                cout << endl;

        }

        for(int i = 0; i < width + 2; i++){
                cout << "#";
        }
        cout << endl;
        cout << "Score:" << score << endl;

}

void setNonBlocking(){
        fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

void Setup(){
        overFlag = false;
        //The init loc in game starts from 0,0
        x = width / 2;
        y = height / 2;

        score = 0;

        fruitX = rand() % width;
        fruitY = rand() % height;
        //printf("%d, %d\n", fruitX, fruitY);
}

void Input(){
        char ch;
        if(read(STDIN_FILENO, &ch, 1) > 0){
                switch(ch){
                        case 'a':
                                dir = LEFT;
                                break;
                        case 'd':
                                dir = RIGHT;
                                break;
                        case 'w':
                                dir = UP;
                                break;
                        case 's':
                                dir = DOWN;
                                break;
                        case 'q':
                                overFlag = true;
                                break;
                        default:
                                break;

                }
        }

}
void Logic(){
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for(int i = 1; i <= countTails; i++){
                prev2X = tailX[i];
                prev2Y = tailY[i];
                tailY[i] = prevY;
                tailX[i] = prevX;
                prevX = prev2X;
                prevY = prev2Y;
        }
        switch(dir)
        {
                case LEFT:
                        x--;
                        break;
                case RIGHT:
                        x++;
                        break;
                case UP:
                        y--;
                        break;
                case DOWN:
                        y++;
                        break;
                default:
                        break;
        }
        if(x >= width + 1 || x <= 0 || y >= height || y < 0){
                overFlag = true;
        }

        for(int i = 0; i < countTails; i++){
                if(tailX[i] == x && tailY[i] == y){
                        overFlag = true;
                }
        }

        if(x==fruitX + 1  && y==fruitY){
                score += 10;
                fruitX = rand() % width;
                fruitY = rand() % height;
                countTails++;
        }

        //fruitX = rand() % width;
        //fruitY = rand() % height;
}

int main()
{
        setNonBlocking();
        Setup();
        while(!overFlag)
        {
                system("clear");
                printf("Testing below:\n");
                Draw();
                Input();
                Logic();
                usleep(200000);

        }
        return 0;
}
