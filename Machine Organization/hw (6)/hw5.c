#include"elevator.h"
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>


// Array of this?
pthread_mutex_t passenger_lock;
pthread_mutex_t elevator_lock;
pthread_cond_t passenger_wait[PASSENGERS];
pthread_cond_t elevator_wait[ELEVATORS];

int elevator_floor=0;
int elevator_direction=1;

// conditional variables to use
// pthread_cond_t or pthread_barrier_t



void scheduler_init() { // initializing all of our locks here

    // pthread for every passenger and elevator
    for(int i =0; i < ELEVATORS; i++){
        pthread_mutex_init(&elevator_lock,0);
        pthread_cond_init(&elevator_wait[i],0);
        pthread_mutex_lock(&elevator_lock);
     }
     for(int i =0; i < PASSENGERS;i++){
        pthread_mutex_init(&passenger_lock,0);
        pthread_cond_init(&passenger_wait[i],0);
        pthread_mutex_lock(&passenger_lock);
     }
}

// conditional order
// 1 - capacity
// 2 - direction
// 3 - comparative distance from request floor 
    // If 2 elevators going same direction closest one to request floor opens up
// 4 - in_use elevator stops moving if no passengers

static struct ElevatorStats {
    int id;
	int at_floor;
    int direction;
    bool in_use; 
    int distance;
	int capacity;
    // variable for elevator occupency
    // need stat variable enum(stat variable) arrived to a specific floor elevator open closed 
} elevator_stats[ELEVATORS];

static struct PassengerStats {
    int id;
	int at_floor;
    int to_floor; 
	bool paseengerEnter;
    bool passengerExit;
} passenger_stats[PASSENGERS];


// use queues
static struct ForwardList {
    struct PassengerStats;
    struct ForwardList* next;
}upList;

static struct BackList {
    struct PassengerStats;
    struct BackList* next;
}downList;

static struct List {
    struct PassengerStats* passenger;
    struct List* next;
    struct List* prev;
}List;


// 2 functions add to list + remove from list
// passenger struct
// whenevr passenger is riding or waiting or completed update functions
// create using linked lists

void passenger_request(int passenger, int from_floor, int to_floor, void (*enter)(int, int), void(*exit)(int, int)) {
    // use conditional variables
    // 1 elevator at a time make 4 work
    // reduce checkin bumpin
    // use structures maybe 3
    // reduce 1 sec variable to people

    // passenger requests elevator where passenger is
    // passenger get in only when elevator on the floor
    // door open + space available
    // check through while loop?
    // while elevator + conditions with structs

    while(elevator_floor == from_floor){
    
    }

    //pthread_mutex_lock(&passenger_lock);

      // original code
    /*while(1) {
        pthread_mutex_lock(&elevator_lock);
        if(elevator_floor == from_floor) {
            enter(passenger,elevator_stats[1].id);
            //elevator_stats[0].capacity += 1;
            elevator_stats[0].to_floor = to_floor;
            pthread_mutex_unlock(&elevator_lock);
            break;
        } 
        // when dealing with global can other threads access it to make a lock about it
        pthread_mutex_unlock(&elevator_lock);
    }
    while(1) {
        pthread_mutex_lock(&elevator_lock);
        if(elevator_floor == to_floor) { 
            exit(passenger,0);
            pthread_mutex_unlock(&elevator_lock);
            break;
        }
        pthread_mutex_unlock(&elevator_lock);
    }
    pthread_mutex_unlock(&passenger_lock);*/

}

void elevator_ready(int elevator, int at_floor, void(*move_direction)(int, int), void(*door_open)(int), void(*door_close)(int)) {
    // consider switch cases?

    if(elevator == 0) {

        // if one of the passenger's floors open else keep going
        // consider conditional statement for valid floor

        // passenger requests elevator where passenger is
      // passenger get in only when elevator on the floor
      // door open + space available
     // check through while loop?
     // while elevator + conditions with structs

     // pthread_cond_init + weight functions + logs
     // barrier weight functions
 

        //elevator_stats[0].id = 0;
        //elevator_stats[0].at_floor = at_floor;
        
       // elevator_stats[0].direction = ;
        //elevator_stats[0].in_use = true;
        //elevator_stats[0].distance = ;


        // implement hint 3
        if(at_floor == FLOORS-1)
            elevator_direction = -1;
        if(at_floor == 0)  
            elevator_direction = 1;
            
        door_open(elevator); // don't need to open door at every floor'


        pthread_mutex_unlock(&elevator_lock);

        usleep(1); // give another thread a chance to grab the lock
        // run a check if passenger exit

        pthread_mutex_lock(&elevator_lock);
        door_close(elevator);          
          
        move_direction(elevator,elevator_direction);
        elevator_floor = at_floor+elevator_direction;
    }
    /*
    if(elevator == 1) {
        
    }
    if(elevator == 2) {
        
    }
    if(elevator == 3) {
        
    }*/

}
