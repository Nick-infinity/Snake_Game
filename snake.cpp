#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

const int Cwidth = 40;
const int Cheight = 20;
int x, y, fx, fy;
enum Dir { STOP = 0, LEFT, RIGHT, UP, DOWN };
Dir dir;
bool gameOver;
int score;
int tailX[100], tailY[100]; // max tail lenght
int tail_len; // current tail len

void init()
{
	srand(time(0));
	gameOver = false;
	score = 0;
	x =  Cwidth/2;
	y = Cheight/2;
	fx = rand() % Cwidth;
	fy = rand() % Cheight;
	dir = STOP;
	

}
void draw()
{
	
	system("cls");

	for (int i = 0; i < Cheight; i++)
	{
		for (int j = 0; j < Cwidth; j++)
		{
			if (i == 0 || i == Cheight-1 || j== Cwidth-1 || j ==0)
			{
				cout << "#";  // box boundary
			}
			else if (i == y && j == x)
			{
				cout << "x";   // snake head
			}
			else if (i == fy && j == fx)
			{
				cout << "o";  // fruit
			}
			else
			{								// tail display logic
				bool print = false;
				for (int k = 0; k < tail_len; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout <<"o";
						print = true;
					}
					
				}
				if (!print)
				{
					cout << " ";
				}
			}


		}
		cout << endl;

	}
	cout << " SCORE: " << score;

}
void inp()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		{
			dir = UP;
			break;
		}
		case 'a':
		{
			dir = LEFT;
			break;
		}
		case 's':
		{
			dir = DOWN;
			break;
		}
		case 'd':
		{
			dir = RIGHT;
			break;
		}
		case ' ':
		{
			gameOver = true;
			break;
		}
		}
	}
}
void logic()
{
							// tail segment movement logic
	int prevX = tailX[0];
	int prevY = tailY[0];
	int tempX,  tempY;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tail_len; i++)
	{
		tempX = tailX[i];
		tempY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;


	}
	switch (dir)  // adjust coordinates based on input
	{
	case UP:
	{
		y--;
		break;
	}
	case DOWN:
	{
		y++;
		break;
	}
	case LEFT:
	{
		x--;
		break;
	}
	case RIGHT:
	{
		x++;
		break;
	}
	}

	if (x == 0 || x == Cwidth-1) // make boundaries transparent for snake to pass
	{
		x = Cwidth - x - 1;
	}
	if (y == 0 || y == Cheight - 1)
	{
		y = Cheight - y - 1;
	}

	for (int i = 0; i < tail_len; i++)  // stop when snake bites itself
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fx && y == fy)  // change fruit location and increase score
	{
		score = score + 10;
		fx = rand() % Cwidth;
		fy = rand() % Cheight;
		tail_len++;
		
	}
}

int main()
{
	init();
	while (!gameOver)
	{
		
		draw();
		inp();
		logic();
		Sleep(2);
		
	}
}