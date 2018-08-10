/* Racing Cars using doubly link list */
/* User commands: add(add to end), addstart(add to start), insert, delete */
/* User enters car name space speed for adding new car */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct S_RacingCar{
    char name[12];
    int speed;
    struct S_RacingCar *next;
    struct S_RacingCar *previous;
}Racing_car;


void PrintList(Racing_car *start) {
    Racing_car *currentCar = start;
    int count = 0;

    Racing_car *ahead = NULL;
    Racing_car *behind = NULL;

    while(currentCar != NULL) {
        count++;
        ahead = currentCar -> next;
        behind = currentCar -> previous;

        printf("Car: %d Name: %s Speed: %d Ahead:%s Behind:%s\n",
               count, currentCar->name, currentCar->speed,
               (ahead==NULL)? "None": ahead->name,
               (behind==NULL)? "None": behind->name);
        currentCar = currentCar -> next;
        ahead = NULL;
        behind = NULL;
    }
    printf("Total cars: %d\n", count);
}

Racing_car *MakeNewCar() {
    printf("Enter name and speed: ");
    char input[16];

    Racing_car *newCar = malloc(sizeof(Racing_car));

    fgets(input, 15, stdin);
    sscanf(input, "%s %d", newCar->name, &newCar->speed);
    printf("Added: %s Speed: %d\n", newCar->name, newCar->speed);

    newCar -> next = NULL;
    newCar -> previous = NULL;

    return newCar;
}


Racing_car *AddToStart(Racing_car *startPtr){
    Racing_car *newCar = MakeNewCar();
    if(startPtr != NULL) {
        startPtr -> previous = newCar;
        newCar -> next = startPtr;
    }
    return newCar;
}


Racing_car *AddToEnd(Racing_car *startPtr){
    Racing_car *returnPtr = startPtr;
    Racing_car *newCar = NULL;
    if(startPtr == NULL) {
        newCar = AddToStart(startPtr);
        returnPtr = newCar;
    } else {
        Racing_car *indexCar = startPtr;
        while(indexCar->next != NULL) {
            indexCar = indexCar -> next;
        }
        newCar = MakeNewCar();
        indexCar ->next = newCar;
        newCar -> next = NULL;
        newCar -> previous = indexCar;
    }
    return returnPtr;
}


Racing_car *Delete(Racing_car *startPtr){
    printf("Enter name to Delete: ");
    char input[16];
    fgets(input, 15, stdin);
    Racing_car *carRef = startPtr;
    Racing_car *carToDelete = NULL;

    while(carRef != NULL) {
        if((strncmp(input, carRef->name, strlen(carRef->name))== 0)) {
            carToDelete = carRef;
            printf("DELETING CAR: %s\n", carToDelete->name);
            break;
        }
        carRef = carRef -> next;
    }
    if((startPtr != NULL) && carToDelete == startPtr) {
        if(carToDelete -> next != NULL) {   // if it is first node out of many cars
            carToDelete -> next->previous = NULL;
            startPtr = carToDelete -> next;
        }
        else {
            startPtr = NULL;    // if there is only one car/node
        }
    } else {                // if midle node to delete
        printf("Car is in middle\n");
        if(carToDelete != NULL) {
            if(carToDelete -> previous != NULL) {
               carToDelete -> previous -> next = carToDelete -> next;
            }
            if(carToDelete -> next != NULL) {
                carToDelete ->next -> previous = carToDelete -> previous;
            }
        }
    }
    if(carToDelete != NULL) {
        carToDelete = NULL;
        free(carToDelete);
    }
    return startPtr;
}

// inserting after some car name
Racing_car *Insert(Racing_car *startPtr){
    printf("Insert a new Car After: ");
    char input[16];
    fgets(input, 15, stdin);

    Racing_car *afterCar = startPtr;
    Racing_car *newCar = NULL;

    if(strncmp(input, afterCar->name, strlen(afterCar->name)) == 0){
        printf("Create new CAR!!\n");
        newCar = MakeNewCar();
    } else {
        while(afterCar -> next != NULL) {
            afterCar = afterCar -> next;
            if(strncmp(input,afterCar->name, strlen(afterCar->name))== 0) {
                newCar = MakeNewCar();
                break;
            }
        }
    }
    if(newCar != NULL) {
        newCar -> next = afterCar -> next;
        if(newCar ->next != NULL) {
            newCar -> next -> previous = newCar;
        }
        afterCar -> next = newCar;
        newCar -> previous = afterCar;
    } else {
        printf("Car Not Found\n");
    }
    return startPtr;
}


void CeanUp(Racing_car *startPtr){
    Racing_car *freeMe = startPtr;
    Racing_car *holdMe = NULL;

    while(freeMe != NULL) {
        holdMe = freeMe -> next;
        printf("Free Name: %s Speed: %d\n",
               freeMe -> name,freeMe->speed);
        free(freeMe);
        freeMe = holdMe;
    }
}


int main() {
    Racing_car *start = NULL;
    char input[16];
    char command[16];

    while(1) {
        printf("Enter your command\n");
        fgets(input, 15, stdin);
        sscanf(input, "%s", command);

        if(strncmp(command, "print", 5) == 0) {
            PrintList(start);
        } else if (strncmp(command, "addStart", 3) == 0) {
            start = AddToStart(start);
            PrintList(start);
        } else if(strncmp(command, "add", 3) == 0) {
            start = AddToEnd(start);
            PrintList(start);
        } else if(strncmp(command, "delete", 6) == 0) {
            start = Delete(start);
            PrintList(start);
        } else if(strncmp(command, "insert", 6) == 0){
            start = Insert(start);
            PrintList(start);
        } else if(strncmp(command, "quit", 4) == 0){
            printf("\n\nBreaking\n");
            break;
        }
    }
    CeanUp(start); // free pointer(allocated space for structure)
    return 0;
}
