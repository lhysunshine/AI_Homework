// MazeGeneration.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>


#include "MazeGeneration.h"

using namespace std;

currentNode Maze[N][N];
vector<currentNode> DFSMaze;
int visited[N * N + 1];
void initial()
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			Maze[i][j].state = EMPTY;
			Maze[i][j].preID = -1;
		}
}

void SearchMap(currentNode curNode, int x1, int y1)
{
	int ID = x1 * N + y1;
	//counter++;
	//flag = 1;
	
	//srand((unsigned)time(NULL));
	int random;
	random = rand() % 10;
	if(random <= 3)
		Maze[x1][y1].state = 1;
	else
	{
		//DFSMaze.pop_back();
		currentNode newNode;
		newNode.preID = curNode.x * N + curNode.y;
		newNode.x = x1;
		newNode.y = y1;
		Maze[x1][y1].preID = curNode.x * N + curNode.y;

		DFSMaze.push_back(newNode);
	}
	//return curNode;
}
void DFS(int x0, int y0)
{
	int flag = 0;
	int counter = 0;
	currentNode curNode;
	curNode.x = x0;
	curNode.y = y0;
	curNode.preID = -1;
	DFSMaze.push_back(curNode);
	while(counter < N * N && DFSMaze.size() > 0)
	{
		curNode = DFSMaze.back();
		DFSMaze.pop_back();
		visited[curNode.x * N + curNode.y] = 1;
		
		if(curNode.x >= 0 && curNode.x < N && curNode.y >=0 && curNode.y < N)
		{
			
			flag = 0;
			int ID = curNode.x * N + curNode.y;
			if(curNode.x - 1 >= 0 && visited[ID - N] == 0 && Maze[curNode.x - 1][curNode.y].state == 0) // up
			{
				SearchMap(curNode, curNode.x - 1, curNode.y);
				counter++;
				flag = 1;
				
			}
			if(curNode.x + 1 < N && visited[ID + N] == 0 && Maze[curNode.x + 1][curNode.y].state == 0)
			{
				SearchMap(curNode, curNode.x + 1, curNode.y);
				counter++;
				flag = 1;
			}
			if(curNode.y + 1 < N && visited[ID + 1] == 0 && Maze[curNode.x][curNode.y + 1].state == 0)
			{
				SearchMap(curNode, curNode.x, curNode.y + 1);
				counter++;
				flag = 1;
			}
			if(curNode.y - 1 >=0 && visited[ID - 1] == 0 && Maze[curNode.x][curNode.y - 1].state == 0)
			{
				SearchMap(curNode, curNode.x, curNode.y - 1);
				counter++;
				flag = 1;
			}

			if(flag == 0 && curNode.preID >= 0) //deadend, pop the last one, and set the current last one in vector to be the curNode
			{
				visited[curNode.preID] = 0;
				currentNode newNode;
				newNode.x = curNode.preID / N;
				newNode.y = curNode.preID % N;
				newNode.preID = Maze[newNode.x][newNode.y].preID;
				DFSMaze.push_back(newNode);
				//curNode.preID = DFSMaze.back().preID;
			}
		}
		
	}
}
int main()
{
	initial();
	srand((unsigned)time(NULL));
	int a[2];
	for(int i = 0; i < 2; i++)
	{
		a[i] = rand() % (N - 1);
	}
	DFS(a[0], a[1]);
	ofstream out("map.txt");
	if(out.is_open())
	{
		 for(int i = 0; i< N; i++)
		{
			for(int j = 0; j< N; j++)
			{
				out << Maze[i][j].state << " ";
			}
			out << "\n";
		}
		 out.close();
	}
	
	
	/*for(int i = 0; i< N; i++)
	{
		for(int j = 0; j< N; j++)
		{
			cout << Maze[i][j] << " ";
		}
		cout << "\n";
	}
	system("pause");*/
	return 0;
}

