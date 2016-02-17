// RepeatedForwardA.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include <fstream>
using namespace std;
#include "RepeatedForwardA.h"
#define N 101 //10

int map[N][N];

/*int map[N][N] = 
{0,0,0,0,1,1,0,0,0,1,
 0,0,0,0,0,0,0,0,0,1,
 1,1,1,0,0,0,0,0,0,1,
 1,1,1,0,1,0,0,0,0,1,
 1,1,1,0,1,0,0,0,0,0,
 0,0,0,0,1,0,0,0,0,0,
 0,0,0,1,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,
 0,0,0,1,1,0,0,0,0,0,
 0,0,0,0,1,0,0,0,0,0};*/

/*int map[N][N] = 
{0,0,0,0,0,
 0,0,1,0,0,
 0,0,1,1,0,
 0,0,1,1,0,
 0,0,0,1,0};*/

Point maze[N][N];

int mapknown[N][N] = {0};

void InsertWithSmallG(Point* OpenList[], Point* start, int& opencounter, int& expandedcells)
{
	OpenList[opencounter + 1] = start;
	int i = opencounter + 1;
	while(i > 1)
	{
		int parent = i / 2;
		if(OpenList[i]->f < OpenList[parent]->f)
		{
			Point* temp;
			temp = OpenList[parent];
			OpenList[parent] = OpenList[i];
			OpenList[i] = temp;
		}
		if(OpenList[i]->f == OpenList[parent]->f)
		{
			if(OpenList[i]->g < OpenList[parent]->g)
			{
				Point* temp;
				temp = OpenList[parent];
				OpenList[parent] = OpenList[i];
				OpenList[i] = temp;
			}
		}
		i = parent;
	}
	opencounter++;
	expandedcells++;
}

void InsertWithLargeG(Point* OpenList[], Point* start, int& opencounter, int& expandedcells)
{
	OpenList[opencounter + 1] = start;
	int i = opencounter + 1;
	while(i > 1)
	{
		int parent = i / 2;
		if(OpenList[i]->f < OpenList[parent]->f)
		{
			Point* temp;
			temp = OpenList[parent];
			OpenList[parent] = OpenList[i];
			OpenList[i] = temp;
		}
		if(OpenList[i]->f == OpenList[parent]->f)
		{
			if(OpenList[i]->g > OpenList[parent]->g)
			{
				Point* temp;
				temp = OpenList[parent];
				OpenList[parent] = OpenList[i];
				OpenList[i] = temp;
			}
		}
		i = parent;
	}
	opencounter++;
	expandedcells++;
}


void RemoveMin(Point* OpenList[], int& opencounter, int index)
{
	OpenList[index] = OpenList[opencounter];
	int c = index;
	int l = 2*c;
	Point* tmp = OpenList[index];
	
	while(l < opencounter)
	{
		if(l < opencounter - 1 && OpenList[l]->f > OpenList[l+1]->f)
			l++;
		if(tmp->f <= OpenList[l]->f)
			break;
		else
		{
			OpenList[c] = OpenList[l];
			c = l;
			l = 2*c;		
		}
	}
	OpenList[c] = tmp;
	opencounter--;
	
}
void RemoveInOpenList(Point* a, Point *OpenList[], int& opencounter)
{
	for(int i = 1; i <= opencounter; i++)
	{
		if(a == OpenList[i])
		{
			RemoveMin(OpenList, opencounter, i);
		}
	}
}
void FindPath(int x0, int y0, int counter, Point* s, Point *OpenList[], Point* end, int& opencounter, int& expandedcells)
{
	Point* a = &maze[x0][y0];
	if (a->visited < counter) {
		a->visited = counter;
	}
	else
	{
		return;
	}
	if(a->search < counter)
	{
		a->g = 100000;
		a->search = counter;
	}
	if(a->g > s->g + 1)
	{
		a->g = s->g + 1;
		a->parent = s;
		a->h = abs(a->getX() - end->getX()) + abs(a->getY() - end->getY());
		a->f = a->g + a->h;
		RemoveInOpenList(a,OpenList,opencounter);
		InsertWithSmallG(OpenList, a, opencounter, expandedcells);
		//InsertWithLargeG(OpenList, a, opencounter);
	}
}
int ComputePath(Point* OpenList[], int counter, Point* start, Point* end, int opencounter, int &expandedcells)
{
	/*if(start.getX()-1 >= 0 && map[start.getX()-1][start.getY()] == 1)
		mapknown[start.getX()-1][start.getY()] = 1;
	if(start.getX()+1 < N && 0 &&map[start.getX()+1][start.getY()] == 1)
		mapknown[start.getX()+1][start.getY()] = 1;
	if(start.getY()-1 >= 0 && map[start.getX()][start.getY()-1] == 1)
		mapknown[start.getX()][start.getY()-1] = 1;
	if(start.getY()+1 < N && map[start.getX()][start.getY()+1] == 1)
		mapknown[start.getX()][start->getY()+1] = 1;*/
	while(true)
	{
		Point* s = OpenList[1];
		if (end->g <= s->f) 
			break;

		RemoveMin(OpenList, opencounter, 1);
		

		int x0 = s->getX();
		int y0 = s->getY();
		if(x0 > 0 && mapknown[x0-1][y0] != 1)
		{
			FindPath(x0-1, y0, counter, s, OpenList, end, opencounter, expandedcells);
		}
		if(x0 < N-1 && mapknown[x0+1][y0] != 1)
		{
			FindPath(x0+1, y0, counter, s, OpenList, end, opencounter, expandedcells);
		}
		if(y0 < N-1 && mapknown[x0][y0+1] != 1)
		{
			FindPath(x0, y0+1, counter, s, OpenList, end, opencounter, expandedcells);
		}
		if(y0 > 0 && mapknown[x0][y0-1] != 1)
		{
			FindPath(x0, y0-1, counter, s, OpenList, end, opencounter, expandedcells);
		}
	}

	return opencounter;
}

int main()
{
	std::vector <Point*> path;
	std::vector <Point*> finalPath;
	Point* OpenList[N*N];
	int opencounter = 0;
	int expandedcells = 0;
	int counter = 0;
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			maze[i][j].setX(i);
			maze[i][j].setY(j);
			maze[i][j].search = 0;
		}
	}

	std::ifstream in;
	in.open("map.txt");
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			in >> map[i][j];
		}
	}

	Point* start = &maze[0][0]; 
	Point* end = &maze[1][9];
	finalPath.push_back(start);
	while(start != end)
	{
		memset(OpenList, 0, sizeof(void*) * N * N);
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				maze[i][j].parent = NULL;
			}
		}
		opencounter = 0;
		expandedcells = 0;
		counter = counter + 1;
		start->g = 0;
		start->search = counter;
		end->g = 100000;
		end->search = counter;
		start->h = abs(start->getX() - end->getX()) + abs(start->getY() - end->getY());
		start->f = start->g + start->h;
		InsertWithSmallG(OpenList, start, opencounter, expandedcells);
		//InsertWithLargeG(OpenList, start, opencounter);
		opencounter = ComputePath(OpenList, counter, start, end, opencounter, expandedcells);

		
		if(opencounter == 0)
		{
			cout << " I cannot reach the target.";
			break;
		}
		Point *c = end;
		path.clear();
		while(c != NULL)
		{
			path.push_back(c);
			c = c->parent;
		}
		for(int i = path.size() - 1; i >= 0; i--)
		{
			int xx = path[i]->getX();
			int yy = path[i]->getY();
			//cout << "xx and yy:" << xx << ", " << yy << endl;
			if(map[xx][yy] == 1)
			{
				start = path[i + 1];
				mapknown[xx][yy] = 1;
				
				//cout << "[Collision] xx and yy:" << xx << ", " << yy << endl;
				break;
			}
			if (i < path.size() - 1)
				finalPath.push_back( path[i]);
			if(xx == end->getX() && yy == end->getY())
				start = end;
		}
	}
	
	for(int i = 0; i < finalPath.size(); i++)
	{
		map[finalPath[i]->getX()][finalPath[i]->getY()]  = 2;
		cout << '(' << finalPath[i]->getX() << ','<<  finalPath[i]->getY() << ')' << "\n";
	}
	//cout << "# of counters: " << counter << endl;
	//cout << "Expandedcells:"<<expandedcells << "\n";
	for(int i= 0; i < 2; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(map[i][j] == 2)
				cout << "*" << " ";
			else
				cout << map[i][j] << " ";
		}
		cout << "\n";
	}
	system("pause");
	return 0;
}

