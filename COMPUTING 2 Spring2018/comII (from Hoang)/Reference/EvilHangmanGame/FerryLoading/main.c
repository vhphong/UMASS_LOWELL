
/**********************************************************************
 Program: Ferry Queue
 Author: Viet Tran Quoc Hoang
 Date: 3/4/2016
 Time spent: 2 days
 Purpose: The purpose of this program is to simulate loading and unloading cars of a single lane ferry across a river. There are 2 queues of car on the left and right banks.
 ***********************************************************************/

#include "linked_queue.h"
#include "status.h"
#define PRINTF//debug comments
#define uva_will_accept_this
//#define alternate_string_method
//#include <string.h>//need this to use string functions(strcmp,strtok)

int main(int argc, const char * argv[]) {
    int counter;
    scanf("%d",&counter);
    int i;
    for (i = 0; i < counter; i++) {
        int ferry_length;
        int number_of_cars;
        scanf("%d %d",&ferry_length,&number_of_cars);
        ferry_length *= 100;
#ifdef PRINTF
        printf("Ferry length = %d number of cars = %d\n",ferry_length,number_of_cars);
#endif
        int j = 0;
        QUEUE hRightQueue = NULL;
        QUEUE hLeftQueue = NULL;
        hRightQueue = queue_init_default();
        hLeftQueue = queue_init_default();
        
#ifdef alternate_string_method
        int STRING_SIZE = 12; // 9|9|9|9| |R|I|G|H|T|\|0 and +1 to account for empty spaces
        int car_length;
        char line[STRING_SIZE];
        fgetc(stdin);
        while ( j < number_of_cars && fgets(line, STRING_SIZE, stdin) != NULL) {
#ifdef PRINTF
            printf("%s",line);
#endif
            char* string_car_length = strtok(line, " ");//cut at empty space
            char* string_car_position = strtok(NULL,"\n");
            car_length = (int)strtol(string_car_length, NULL, 10);
            if (!strcmp(string_car_position, "left")) {
                hLeftQueue->enqueue(hLeftQueue,car_length);
            }
            else if (!strcmp(string_car_position, "right")){
                hRightQueue->enqueue(hRightQueue,car_length);
           }
            j++;
        }
#endif
        

        
#ifdef uva_will_accept_this
        int car_length;
        int STRING_SIZE = 7; // R|I|G|H|T|\|0 and +1 to account for empty spaces
        char car_position[STRING_SIZE];
        for (j = 0; j < number_of_cars; j++) {
            scanf("%d",&car_length);
            fgetc(stdin);
            scanf("%s",car_position);
            if (car_position[0] == 'l') {
                hLeftQueue->enqueue(hLeftQueue,car_length);
            }
            else{
                hRightQueue->enqueue(hRightQueue,car_length);
            }
        }
#endif
    
#ifdef PRINTF
        
        printf("Left queue:");hLeftQueue->print(hLeftQueue);
        printf("Right queue:");hRightQueue->print(hRightQueue);
        printf("\n");
        
#endif
        
        int trip_counter = 0;
        int ferry_load;
        Status left_queue_status = SUCCESS;
        Status right_queue_status = SUCCESS;
        Position ferry_position = LEFT;
        while (!hRightQueue->empty(hRightQueue) || !hLeftQueue->empty(hLeftQueue)) {
            ferry_load = 0;//reset ferry load after each trip
            if (ferry_position == LEFT){
                while (!hLeftQueue->empty(hLeftQueue) && ferry_load + hLeftQueue->front(hLeftQueue,&left_queue_status)<= ferry_length) {
                    ferry_load += hLeftQueue->front(hLeftQueue,&left_queue_status);
                    hLeftQueue->service(hLeftQueue);
#ifdef PRINTF
                    printf("left loop\n");
                    printf("load = %d\n",ferry_load);
                    printf("Left queue:");hLeftQueue->print(hLeftQueue);
#endif
                }
                ferry_position = RIGHT;//ferry is full,ferry makes the trip
            }
            else if (ferry_position == RIGHT) {
                while (!hRightQueue->empty(hRightQueue) && ferry_load+ hRightQueue->front(hRightQueue,&right_queue_status)<=ferry_length) {
                    ferry_load += hRightQueue->front(hRightQueue,&right_queue_status);
                    hRightQueue->service(hRightQueue);
#ifdef PRINTF
                    printf("right loop\n");
                    printf("load = %d\n",ferry_load);
                    printf("Right queue:");hRightQueue->print(hRightQueue);
#endif
                }
                ferry_position = LEFT;//ferry is full,ferry makes the trip
            }
#ifdef PRINTF
            printf("++\n");
#endif
            trip_counter++;
        }

        
        
#ifdef PRINTF
        printf("\n");
        printf("Left queue:");hLeftQueue->print(hLeftQueue);
        printf("Right queue:");hRightQueue->print(hRightQueue);
        printf("trip counter =");
#endif
        printf("%d\n",trip_counter);
        hLeftQueue->destroy(&hLeftQueue);
        hRightQueue->destroy(&hRightQueue);

    }

    return 0;
}
