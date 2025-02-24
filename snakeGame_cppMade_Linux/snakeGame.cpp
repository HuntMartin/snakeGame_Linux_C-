#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#include<fcntl.h>

using namespace std;

//set a Flag to check if the game is Over!
bool overFlag;

//Init the Screen
const int width = 20;
const int height = 20;

//Init the snake 2D Loc and randomized fruit Loc, also a score to store the player's game stats 
int x, y, fruitX, fruitY, score;

//Init the snake tail length
int tailX[100], tailY[100];

//nTail is for the logic loop while snake is moving
int nTail;

//Build a wasd keyboard movement for user to control the snake
enum moveMent{ STOP = 0, LEFT, RIGHT, UP, DOWN};
moveMent dir;

//void func for setting up(Initializing) the game
void Setup()
{
	overFlag = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height; 
	score = 0;

}

//void func for drawing the game on the terminal screen
void Draw()
{
	system("clear");
	for(int i=0; i<width+1; i++)
	{
		cout << "#";
	}
	cout << endl;

	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width+1; j++)
		{
			if(j==0)
			{
				cout << "#";
			}

			if(j==width-1)
			{
				cout << "#";
			}

			if(i == y && j == x)
			{
				cout << "0";
			}

			else if(i == fruitY && j == fruitX)
			{
				cout << "F";
			}

			else
			{
				bool print = false;
				for(int k = 0; k < nTail; k++)
				{
					if(tailY[k] == i && tailX[k] == j)
					{
						cout << "o";
						print = true;
					}
				}
				if(!print)
				{
					cout << " ";
				}
				
			}
			
		}
		cout << endl;
	}

	for(int i=0; i<width+1; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score:" << score << endl;
}

void setNonBlocking(){
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

void Input()
{
	char ch;
	if (read(STDIN_FILENO, &ch, 1) > 0)
	{
		switch(ch)
		{
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

void Logic()
{
	int prevX = tailX[0];
       	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for(int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
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

	if(x > width|| x < 0 || y > height|| y < 0)
	{
		overFlag = true;
	}

	for(int i = 0; i < nTail; i++)
	{
		if(tailX[i] == x && tailY[i] == y)
		{
			overFlag = true;
		}
	}

	if(x==fruitX && y==fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}


		
}



int main()
{
	setNonBlocking();
	Setup();
	while(!overFlag)
	{
		Draw();
		Input();
		Logic();
		usleep(200000);
	}
	return 0;
}
