#include <stdio.h>
#include <stdlib.h>

/*
A basic structure that will hold all the patients that I will pass to either Scenario one or two
just takes an int and a single character
*/
struct patients {
    int timeLeft;
    char gender;
    };


/*
ScenarioOne takes a struct array as a paramater
*/
void scenarioOne(struct patients tower[]){
    //I like to define my variables separated so I have a general idea of where all of them are.
    int floor = 0;
    int room = 0;
    int index = 0;
    int time[10][10];
    char sex[10][10];
    int covid = 1;
    int whileFloor = 0;
    int whileRoom = 0;
    int checkbedFloor = 0;
    int checkbedRoom = 0;
    int infected = 100;
    int clean = 0;
    int checkTen = 0;
    int infectedFloors = 10;
    int cleanFloors = 0;
    int freeBeds = 0;
    int checkFloor = 0;

    //Taking all of the information from the struct(the paramater) and placing them into two different arrays

    for (floor; floor < 10;floor++){
        for(room;room <10;room++){
        time[floor][room] = tower[index].timeLeft;
        sex[floor][room] = tower[index].gender;
         index++;
        }
        room = 0;
    }
//While covid = 1 this while loop will keep running.
    while(covid){
        for(whileFloor; whileFloor < 10; whileFloor++){
            for(whileRoom; whileRoom < 10; whileRoom++){
                //subtracting 1 from every time in the time array to eventually reach 0
                time[whileFloor][whileRoom]--;
            //when the time does reach 0, the program changes the sex, takes away an infected, adds a clean, and adds 1 to the checkTen Counter
            //CheckTen is a easy way to keep track of when to print out information after 10 people go home.
            if(time[whileFloor][whileRoom] == 0){
                sex[whileFloor][whileRoom] = '.';
                infected--;
                clean++;
                checkTen++;
                }
            //when checkTen equals 10 it goes back to 0 and the current status of the rooms gets printed out
            if(checkTen == 10){
                checkTen = 0;
                 printf("Printing out list of occupied and unoccupied beds:\n");
                    for(checkbedFloor; checkbedFloor < 10; checkbedFloor++){
                        for(checkbedRoom;checkbedRoom<10; checkbedRoom++){
                           printf(" %c",sex[checkbedFloor][checkbedRoom]);
                        }
                        printf("\n");
                        checkbedRoom = 0;
                    }
                    checkbedFloor = 0;
            }
            //checking to see if the floor is completely cleared out, if it is the program subtracts a infected floor and adds a clean floor
            if(time[whileFloor][whileRoom] < 1){
                checkFloor++;
                if(checkFloor == 10){
                    //setting one room time to a very large number so it never double counts a floor.
                    time[whileFloor][whileRoom] = 10000;
                    cleanFloors++;
                    infectedFloors--;
                    //printing out the current status of infected floors, clean floors, clean patients, and infected patients
                    printf("Number of Covid - 19 patients: %d\n", infected);
                    printf("Number of empty beds: %d\n", clean);
                    printf("Number of Covid-19 floors: %d\n", infectedFloors);
                    printf("Number of Non-Covid-19 floors: %d\n\n", cleanFloors);

                        }
                    }
            //when all patients are clean the while loop will finally end.
            if (clean == 100){
                covid = 0;
                }
            }
        //setting the initial room number back to 0, and checkfloor back to 0 for the next floor
        checkFloor = 0;
        whileRoom = 0;
        }
    //setting floor back to 0 to start the whole process over again.
    whileFloor = 0;
    }
}



/*
ScenarioTwo takes a struct array as a paramater
*/

void scenarioTwo(struct patients tower[]){
    //I like to define my variables separated so I have a general idea of where all of them are.
    int floor = 0;
    int room = 0;
    int index = 0;
    int time[10][10];
    char sex[10][10];
    int covid = 1;
    int whileFloor = 0;
    int whileRoom = 0;
    int checkbedFloor = 9;
    int checkbedRoom = 9;
    int infected = 100;
    int clean = 0;
    int checkTen = 0;
    int infectedFloors = 10;
    int cleanFloors = 0;
    int freeBeds = 0;
    int checkFloor = 0;
    int floorChecker = 9;
    int roomChecker = 9;

     //Taking all of the information from the struct(the paramater) and placing them into two different arrays

    for (floor; floor < 10; floor++){
        for(room;room < 10; room++){
        time[floor][room] = tower[index].timeLeft;
        sex[floor][room] = tower[index].gender;
        index++;
        }
        room = 0;
    }

   //While covid = 1 this while loop will keep running.
    while(covid){
        for(whileFloor; whileFloor < 10; whileFloor++){
            for(whileRoom; whileRoom < 10; whileRoom++){
            //subtracting 1 from every time in the time array to eventually reach 0, but only if the time is greater than 0
            if(time[whileFloor][whileRoom] > -1){
                time[whileFloor][whileRoom]--;
            }

               //checking to see if the floor is completely cleared out, if it is the program subtracts a infected floor and adds a clean floor
            if(time[whileFloor][whileRoom] == -1){
                checkFloor++;
                if(checkFloor == 10){
                    time[whileFloor][whileRoom] = -10000;
                    cleanFloors++;
                    infectedFloors--;
                    printf("Number of Covid - 19 patients: %d\n", infected);
                    printf("Number of empty beds: %d\n", clean);
                    printf("Number of Covid-19 floors: %d\n", infectedFloors);
                    printf("Number of Non-Covid-19 floors: %d\n\n", cleanFloors);

                        }
                    }

                    //when the time does reach 0, the program changes the sex, takes away an infected, adds a clean, and adds 1 to the checkTen Counter
            //CheckTen is a easy way to keep track of when to print out information after 10 people go home.
            if(time[whileFloor][whileRoom] == 0){
                sex[whileFloor][whileRoom] = '.';
                checkTen++;
                clean++;
                infected--;
                //when the sex is . we will begin moving people from the upper floors to lower floors
                if(sex[whileFloor][whileRoom] == '.'){
                        for(floorChecker; floorChecker >= 0; floorChecker--){
                            for(roomChecker;roomChecker >= 0; roomChecker--){
                                //checking to make sure we are swapping to occupied rooms
                                if(sex[floorChecker][roomChecker] != '.'){
                                    //placing someone into the empty room
                                    sex[whileFloor][whileRoom] = sex[floorChecker][roomChecker];
                                    //old room becomes empty
                                    sex[floorChecker][roomChecker] = '.';
                                    //new room needs to carry the time over too
                                    time[whileFloor][whileRoom] = time[floorChecker][roomChecker];
                                    //set the time of the old room to -1 so it doesn't get subtracted anymore
                                    time[floorChecker][roomChecker] = -1;
                                    //ending the loop so it doesn't rearrange all of the rooms
                                    floorChecker = 0;
                                    roomChecker = 0;
                                }
                            }
                            roomChecker = 9;
                        }
                        floorChecker = 9;
                }
            }
            //when checkTen equals 10 it goes back to 0 and the current status of the rooms gets printed out
            if(checkTen == 10){
                checkTen = 0;
                 printf("Printing out list of occupied and unoccupied beds:\n");
                    for(checkbedFloor; checkbedFloor >= 0; checkbedFloor--){
                        for(checkbedRoom;checkbedRoom >= 0; checkbedRoom--){
                           printf(" %c",sex[checkbedFloor][checkbedRoom]);
                        }
                        printf("\n");
                        checkbedRoom = 9;
                    }
                    checkbedFloor = 9;
            }

            //the while loop will end when all floors are clean.
            if (infected == 0){
                covid = 0;
                }
            }
        //setting the initial room number back to 0, and checkfloor back to 0 for the next floor
        checkFloor = 0;
        whileRoom = 0;
        }
    //setting floor back to 0 to start the whole process over again.
    whileFloor = 0;
    }
}


int main()
{
   FILE *entireDataSet;
   struct patients tower[100];
   char genders[101];
   int time;
   int floor = 0;
   int room = 0;
   char scenario;
   int count = 0;


    //make sure your data set is in the same folder as main, or else it will return a error.
   entireDataSet = fopen("HW #2 Data.txt", "r");

    //checking to see if the file exists, if it doesn't an error msg will be sent.
   if(entireDataSet == NULL){
    printf("Error opening file!\n");
    return (1);
}
//gets information from the file until it reaches the end
while((fscanf(entireDataSet,"%s %d",&genders,&time))!= EOF){
    printf("%s", genders);
    //placing time in our struct
    tower[count].timeLeft = time;
    //checking to see if gender is male or female and placing them accordingly
    if(strcmp(genders, "F") == 0){
    tower[count].gender = 'F';
        }
    if(strcmp(genders, "M") == 0){
       tower[count].gender = 'M';
        }
        count++;
}
    //gives the user the option of selecting either scenario one or two, if neither is selected a msg will pop up and the program will end
    printf("Would you like to load scenario 1 or 2 (1/2): ");
    scanf("%c", &scenario);
    if(scenario == '1'){
        scenarioOne(tower);
    }
    else if(scenario == '2'){
        scenarioTwo(tower);
    }
    else{
        printf("Not a option, goodbye.");
    }

    //closing the file and ending the program.
    fclose(entireDataSet);
    return 0;
}
