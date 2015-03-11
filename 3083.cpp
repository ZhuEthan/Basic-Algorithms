/*************************************************************************
	> File Name: 3083.cpp
	> Author: zhuyisong
	> Mail: zhuyisong1994@gmail.com
	> Created Time: Sat 27 Dec 2014 20:01:31 HKT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

using namespace std;

#define MAX 41

typedef struct graph {
	int x;
	int y;
	struct graph* pre;
} location;

char graph[MAX][MAX];
int test;
bool success;
int count;

int createGraph(int row, int coloum, location* firstLocation); 
void DFS_LF (location* currentLocation, int &direction); 
bool findPath(location* currentLocation, location*& nextLocation, int direction, int priority); 
void display (location* lastLocation); 

int main() {
	scanf("%d", &test);
	int row, coloum;
	int direction;

	location* firstLocation = (location*) malloc (sizeof (location));

	while (test--) {
		success = false;
		count = 0;

		scanf("%d %d", &coloum, &row);
		direction = createGraph(row, coloum, firstLocation);

		DFS_LF (firstLocation, direction);

//		DFS_RF (firstLocation, direction);
	}

	return 0;
}

int createGraph(int row, int coloum, location* firstLocation) {

	int direction;

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			graph[i][j] = '#';
		}
	}

	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= coloum; j++) {
			scanf(" %c", &graph[i][j]);			
			if (graph[i][j] == 'S') {
				firstLocation->x = j;
				firstLocation->y = i;
				firstLocation->pre = NULL;
				if (i == row) {
					direction = 0;
				} else if (i == 1) {
					direction = 2;
				} else if (j == 1) {
					direction = 1;
				} else if (j == coloum) {
					direction = 3;
				}
			}
		}
	}

	return direction;
}

void DFS_LF (location* currentLocation, int &direction) {
	
	location* nextLocation = NULL;
	count++;

	for (int i = 0; i < 4; i++) {
		if (findPath(currentLocation, nextLocation, direction+i, 3)) {
			direction = (direction+i+3) % 4;
			DFS_LF (nextLocation, direction);
			if (success) {
				return;
			}
			i = -1;
		}
	}

	if (success) {
		printf("%d\n", count);
		return;
	}
	
	count++;
	direction = (direction+2) % 4;
	free(currentLocation);
}

bool findPath(location* currentLocation, location*& nextLocation, int direction, int priority) {
	int choice = (direction + priority) % 4;
	int tempX = currentLocation->x;
	int tempY = currentLocation->y;

	switch (choice) {
		case 0:
			tempY--;
			break;
		case 1:
			tempX++;
			break;
		case 2:
			tempY++;
			break;
		case 3:
			tempX--;
			break;
		default:
			break;
	}

	if (graph[tempY][tempX] == '.') {
		nextLocation = (location*) malloc (sizeof (location));
		nextLocation->x = tempX;
		nextLocation->y = tempY;
		nextLocation->pre = currentLocation;
		
		graph[tempY][tempX] = '#';

		return true;
	} else if (graph[tempY][tempX] == 'E') {
		nextLocation = (location*) malloc (sizeof (location));
		nextLocation->x = tempX;
		nextLocation->y = tempY;
		nextLocation->pre = currentLocation;

		success = true;

		graph[tempY][tempX] = '#';

		return true;
	}

	return false;
}

void display (location* lastLocation) {
	while (lastLocation != NULL) {
		printf("(%d, %d)", lastLocation->x, lastLocation->y);
		lastLocation = lastLocation->pre;
	}
}
