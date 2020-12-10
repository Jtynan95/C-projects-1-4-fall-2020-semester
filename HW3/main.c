#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

/*
Creating 6 global variables so I don't have to pass them around and potentially alter the number incorrectly
*/
int infected = 100;
int purpleCount = 0;
int redCount = 0;
int yellowCount = 0;
int greenCount = 0;
int released = 0;

/*
struct patient is the structure used throughout the whole program. It has 6 inputs
sex or gender, status what color they are at, age, gettingBetter to check if they are on the road to recovery or not
countDown which keeps track if each patient has waited the 3 days to get better
finally released to check if patient has gone home, so the program just skips over them and runs quick if they are
released
*/
struct patient{
    char sex;
    char status;
    int age;
    bool gettingBetter;
    int countDown;
    bool released;
};
// Creating a global patient struct
 struct patient patient[10][10];
/*
getting a random number from 1 to 100.
*/
 int randomNumber(){
     return (rand() % 100);
 }
/*
endOfDatReport prints out the current counts of all the statuses of the patients
it also prints out the current tower, showing which rooms are filled, and which are not.
*/
 char endOfDayReport(){
    int floor = 0;
    int room = 0;

    printf("Total number of Purple patients: %d\n", purpleCount);
    printf("Total number of Red patients: %d\n", redCount);
    printf("Total number of Yellow patients: %d\n", yellowCount);
    printf("Total number of Green patients: %d\n", greenCount);
    printf("Total number of Released patients: %d\n\n", released);

    for(floor; floor < 10; floor++){
        for(room; room < 10; room++){
            printf("%c ", patient[floor][room].sex);
        }
        printf("\n");
        room = 0;
    }
    floor = 0;
 }

 void patientTower(){
     int floor = 0;
     int room = 0;
     int randomGetBetter = 0;
     int randomGetWorse = 0;
     //the program will keep running while the global infected variable is not 0
     while(infected != 0){
            for(floor;floor<10;floor++){
                for(room;room<10;room++){
                    //generating two random numbers one for getting worse, to see if a patient goes down a color and getting better for the opposite.
                    randomGetBetter = randomNumber();
                    randomGetWorse = randomNumber();
                    //the first day starts, so we increment everyones countdown by one
                    patient[floor][room].countDown = patient[floor][room].countDown + 1;
                    //patients can not get worse once the start to get better
                    if(patient[floor][room].gettingBetter == false){
                        /*
                        If a random roll from random number occurs if it is less then or equal to the next worse for the patient
                        the patient will transition from one stage to the the next, and purple does not get any worse
                        if a patient does get worse their countdown is reset, and the global counters are either incremented or decremented.
                        */
                        if(patient[floor][room].status == 'R' && randomGetWorse <= 20){
                            patient[floor][room].status = 'P';
                            purpleCount++;
                            redCount--;
                            patient[floor][room].countDown = 0;
                        }
                         if(patient[floor][room].status == 'Y' && randomGetWorse <= 40){
                            patient[floor][room].status = 'R';
                            redCount++;
                            yellowCount--;
                            patient[floor][room].countDown = 0;
                         }
                         if(patient[floor][room].status == 'G' && randomGetWorse <= 50){
                            patient[floor][room].status = 'Y';
                            yellowCount++;
                            greenCount--;
                            patient[floor][room].countDown = 0;
                        }
                    }
                    // checking to see if the patient has not been released yet and their countdown is 3 or greater
                    if(patient[floor][room].released == false && patient[floor][room].countDown >= 3){
                        /*
                        checking the status of each patient and if randomGetBetter is less then or equal to the corresponding status the patient
                        will start to get better, their status will change or in the case of green they will get released
                        then all the corresponding counts are either incremented or decremented
                        */
                         if(patient[floor][room].status == 'G' && randomGetBetter <= 75){
                            patient[floor][room].status = '.';
                            patient[floor][room].sex ='.';
                            patient[floor][room].released = true;
                            greenCount--;
                            infected--;
                            released++;
                        }
                            if(patient[floor][room].status == 'Y' && randomGetBetter <= 60){
                            patient[floor][room].status = 'G';
                            patient[floor][room].gettingBetter = true;
                            yellowCount--;
                            greenCount++;
                          }

                           if(patient[floor][room].status == 'R' && randomGetBetter <= 40){
                            patient[floor][room].status = 'Y';
                            patient[floor][room].gettingBetter = true;
                            redCount--;
                            yellowCount++;
                        }
                            if(patient[floor][room].status == 'P' && randomGetBetter <= 30){
                            patient[floor][room].status = 'R';
                            patient[floor][room].gettingBetter = true;
                            purpleCount--;
                            redCount++;
                        }
                        }
                    }
                    //resetting the room for loop
                    room = 0;
                }
        //resetting the floor for loop, and call endofdayreport to print out the current results.
        floor = 0;
        endOfDayReport();
    }
}

int main()
{
 //calling srand so it is true random, based off of your computer time, so no two runs of this program will be the same, remove it if you want consistent results
 srand(time(NULL));
 FILE *entireDataSet;

 char sex[100];
 char status[100];
 int age = 0;
 int floor = 0;
 int room = 0;
 //Make sure your text file is in the same folder as the main of this program or you will get an error.
 entireDataSet = fopen("HW #3 Data.txt", "r");

  if(entireDataSet == NULL){
    printf("Error opening file!\n");
    return (1);
}
//scanning the file and placing the corresponding information into the correct spot in the struct
while((fscanf(entireDataSet,"%s %s %d",&sex,&status,&age))!= EOF){
        if(strcmp(sex, "F") == 0){
            patient[floor][room].sex = 'F';
        }
        if(strcmp(sex, "M") == 0){
            patient[floor][room].sex = 'M';
        }
        if(strcmp(status, "G") == 0){
            patient[floor][room].status = 'G';
            greenCount++;
        }
        if(strcmp(status, "Y") == 0){
            patient[floor][room].status = 'Y';
            yellowCount++;
        }
        if(strcmp(status, "R") == 0){
            patient[floor][room].status = 'R';
            redCount++;
        }
        if(strcmp(status, "P") == 0){
            patient[floor][room].status = 'P';
            purpleCount++;
        }
        patient[floor][room].age = age;
        patient[floor][room].gettingBetter = false;
        patient[floor][room].released = false;
        patient[floor][room].countDown = 0;
        //incrementing the spots in the 2d array, when room reaches 10 it will return to 0 and floor will increment.
        room++;
        if(room == 10){
            floor++;
            room = 0;
        }
}
//calls patientTower which handles the rest of the program and finally closes the data set and returns 0
patientTower();
fclose(entireDataSet);

return 0;
}
