#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<string.h>
int grade, quantity;//first input
int student[12][10002] = {};
int queue[1002] = {};
int queueNo[1002] = {};
int* serve[1002];
int served[1002] = {};
bool end = {};
int e = 1, d = 1;
void queueTask(int* e);
void serveTask(int* d, int* e);
int main() {
	scanf("%d %d",&grade,&quantity);
	if (grade > 0 && grade <= 10 && quantity > 0 && quantity <= 1000) {
		int i = 0;
		for (i = 0; i < quantity; i++) {
			int stdGrade = 0, stdID = 0;
			scanf("%d %d", &stdGrade, &stdID);
			if (student[stdGrade][stdID] < 1) { student[stdGrade][stdID]+=1; }
			else return 0;
		}
		if (i != quantity) {
			return 0;
		}
		else {
			while (end == false) {
				int len = 0;
				char task, inp[2];
				scanf("%s", &inp);
				len = strlen(inp);
				if (len == 1) {
					task = inp[0];
				}
				else return 0;
				
				if (task == 'E' || task == 'D') {
					if (task == 'E') {
						
						queueTask(&e);
					}
					else if (task == 'D') {
						
						serveTask(&d,&e);
					}
				}
				else if (task == 'X') {
					if (queue[1] == 0) {
						printf("empty\n");
					}
					else {
						for (int i = 1; i < d; i++) {
							printf("%d\n", served[i]);
						}
						printf("0\n");
					}
					end = true;
				}
				else return 0;
			}
		}
	}
	return 0;
}
void queueTask(int *e)
{
	int num = *e;
	int stdid=0;
	scanf("%d", &stdid);
	
	if (num < 2) {
		queue[num] = stdid;
		for (int i = 1; i < grade + 1; i++) {
			if (student[i][stdid] == 1) {
				queueNo[num] = i;
			}
		}
	}
	else if (num >= 2) {
		int gradeQueue = 0;
		for (int i = 1; i < grade + 1; i++) {
			if (student[i][stdid] == 1) gradeQueue = i;
		}
		for (int j = 1; j < num + 1; j++) {
			if (j < num) {
				if (gradeQueue == queueNo[j]) {
					if (queueNo[j + 1] != gradeQueue && queueNo[j + 1] != 0) {
						for (int i = num; i > j + 1; i--) {
							queue[i] = queue[i-1];
						}
						queue[j + 1] = stdid;
						break;
					}
				}
			}
			else if (j == num) {
				queue[num] = stdid;
			}
		}
		for (int i = 1; i < num + 1; i++) {
			int num;
			num = queue[i];
			for (int k = 1; k < grade + 1; k++) {
				if (student[k][num] == 1) {
					queueNo[i] = k;
				}
			}
		}
		for (int p = num+1; p < 1001; p++) {
			if (queueNo[p] != 0) {
				queueNo[p] = 0;
			}
			else continue;
		}
	}
	*e += 1;
}
void serveTask(int *d,int *e)
{							
	int numS = *d;
	int numQ = *e-1;
	serve[numS] = &queue[1];
	served[numS] = *serve[numS];
	for (int k = 1; k < numQ; k++) {
		queue[k] = queue[k + 1];
	}
	for (int i = 1; i < numQ ; i++) {
		int num;
		num = queue[i];
		for (int k = 1; k < grade + 1; k++) {
			if (student[k][num] == 1) {
				queueNo[i] = k;
			}
		}
	}
	for (int p = numQ; p < 1001; p++) {
		queueNo[p] = 0;
	}
	*e -= 1;
	*d += 1;
}