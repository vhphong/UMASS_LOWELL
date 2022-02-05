/**********************************************************************
Program: program 2 - Ferry Loading
Author: Phong Vo
Date: 07/30/2019
Time spent: 3 days
Purpose: The purpose of this program is to simulate loading and 
			unloading cars of a single lane ferry across a river.
			There are 2 queues of car on the left and right banks.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ferry.h"

int main(int argc, char * argv[]){
	int num;
	scanf("%d",&num);

	for (int i = 0; i < num ; i++){
		int ferry_length;
		int num_of_cars;
		
		scanf("%d %d", &ferry_length, &num_of_cars);
		ferry_length = ferry_length * 100;
		QUEUE hRight = NULL;
		QUEUE hLeft	= NULL;
		hRight = queue_init_default();
		hLeft = queue_init_default();
		int car_length;
		char place[7];
		for (int j = 0; j < num_of_cars; j++){
			scanf("%d",&car_length);
			fgetc(stdin);
			scanf("%s",place);
			if (place[0] == 'l' || place[0] == 'L'){
				queue_enqueue(hLeft,car_length);
			}
			else if (place[0] == 'r' || place[0] == 'R'){
				queue_enqueue(hRight,car_length);
			}
		}
		int trip_count = 0;
		int ferry;
		Position ferry_position = LEFT;
		Status left_status = SUCCESS;
		Status right_status = SUCCESS;
		while(!queue_empty(hLeft) || !queue_empty(hRight)){
			ferry = 0;
			if (ferry_position == LEFT){
				while(!queue_empty(hLeft) && (ferry + queue_front(hLeft,&left_status)) <= ferry_length)
				{
					ferry = ferry + queue_front(hLeft,&left_status);
					queue_dequeue(hLeft);
				}
				ferry_position = RIGHT;
			}
			else if (ferry_position == RIGHT){
				while(!queue_empty(hRight) && (ferry + queue_front(hRight,&right_status)) <= ferry_length)
				{
					ferry = ferry + queue_front(hRight,&right_status);
					queue_dequeue(hRight);
				}
				ferry_position = LEFT;
			}
			trip_count++;
		}
		printf("%d\n",trip_count);
		queue_destroy(&hLeft);
		queue_destroy(&hRight);
		
	}
}