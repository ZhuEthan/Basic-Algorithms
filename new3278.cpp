/*************************************************************************
	> File Name: new3278.cpp
	> Author: zhuyisong
	> Mail: zhuyisong1994@gmail.com
	> Created Time: Sun 04 Jan 2015 13:43:08 HKT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100001

using namespace std;

int step[MAX];
bool flag[MAX];
bool success;
int cow;
int queue[MAX];

void BFS (int, int);
int findLocation (int, int);
int search (int);

int main() {
	int FJ;
	int head, tail;

	while (scanf ("%d %d", &FJ, &cow) != EOF ) {

		success = false;
		head = tail = 0;
		memset (step, 0, sizeof (step[0]) * MAX);
		memset (flag, 0, sizeof (flag[0]) * MAX);

		if (FJ >= cow) {
			printf ("%d\n", search(FJ));
			continue;
		}

		queue[tail++] = FJ;
		flag[FJ] = true;

		BFS (head, tail);
	}

	return 0;
}

int search(int FJ) {
	return (FJ - cow);
}

void BFS (int head, int tail) {

	if (head <= tail) {
		int location = queue[head];
		//printf ("%d ", location);
		for (int i = 0; i < 3; i++) {
			int tempLocation = findLocation(location, i);
			if (tempLocation != -1) {
				queue[tail++] = tempLocation;
				if (success == true) {
					printf ("%d\n", step[tempLocation]);
					return;
				}
			}
		}

		head++;
		BFS (head, tail);
	}
}

int findLocation(int location, int i) {

	int tempLocation = location;

	switch (i) {
		case 0:
			tempLocation *= 2;
			break;
		case 1:
			tempLocation--;
			break;
		case 2:
			tempLocation++;
			break;
	}

	if (tempLocation == cow) {
		flag[tempLocation] = true;
		step[tempLocation] = step[location] + 1;
		success = true;
		return tempLocation;
	}

	if (tempLocation < MAX && flag[tempLocation] == false) {
		flag[tempLocation] = true;
		step[tempLocation] = step[location] + 1;
		return tempLocation;
	}

	return -1;

}
