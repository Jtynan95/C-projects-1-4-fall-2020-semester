#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
COP 3515 – Fall, 2020
Homework 4: Testing The Vaccine
Joshua Tynan
*/


//Creating four bools for the four companies who have submitted potential vacs
bool astraZeneca = true;
bool johnsonJohnson = true;
bool moderna = true;
bool novavax = true;

/*
Decryption takes the initial encrypted file and creates four new files to store them in
then goes letter by letter shifting them to the left by 3 and because we know how many are in each we can sort them
all by thee phase which all depends on the total count

depending on the count a specific file is then used to place the new decrypted data from the first file.
*/

void decryption(){
    FILE *encrypted;
    FILE *phaseZ;
    FILE *phaseO;
    FILE *phaseT;
    FILE *phaseTH;
    int shift = 3;
    char text[20];
    char newText[20];
    char character;
    int i = 0;
    int sillyFix = 0;
    int phaseFilter = 0;
    int count = 0;

    encrypted = fopen("HW #4 Data - Encrypted.txt", "r");
    phaseZ = fopen("Phase Zero.txt", "w");
    phaseO = fopen("Phase One.txt", "w");
    phaseT = fopen("Phase Two.txt", "w");
    phaseTH = fopen("Phase Three.txt", "w");


    if(encrypted == NULL){
    printf("Error opening file!\n");
}

    while((fscanf(encrypted,"%s",&text))!= EOF){
        count++;
        if (count == 61){
            phaseFilter++;
        }
        if (count == 121){
            phaseFilter++;
        }
        if (count == 321){
            phaseFilter++;
        }
        for(i; i < strlen(text); i++){
            character = text[i];
            character = character - shift;
			newText[i] = character;
		}
		if(sillyFix == 0){
            newText[9] = 0;
            newText[10] = 0;
            sillyFix++;
		}
		if(phaseFilter == 0){
            fprintf(phaseZ,"%s\n",newText);
		}
		if(phaseFilter == 1){
            fprintf(phaseO, "%s\n",newText);
		}
		if(phaseFilter == 2){
            fprintf(phaseT, "%s\n", newText);
		}
		if(phaseFilter == 3){
            fprintf(phaseTH, "%s\n", newText);
		}
        memset(&newText[0], 0, sizeof(newText));
        memset(&text[0], 0, sizeof(text));
		i = 0;
    }
    fclose(encrypted);
    fclose(phaseZ);
    fclose(phaseO);
    fclose(phaseT);
    fclose(phaseTH);
}

/*
PhaseZeroTesting goes through the phase zero text file and checks and sorts them into 4 by 15 groups
by their t count

after sorting them it goes through each group checking the t count, and if the t count is above 1200 it marks a checker for that group
if a group has ten out of fifteen above 1200 that companies vac will not be considered for the running. The rest will move on to the next phase.
*/

void phaseZeroTesting(){
    char sex[100];
    char age[100];
    int tCount = 0;
    int patients[3][15];
    int i = 0;
    int j = 0;
    int checkFifteen = 0;
    FILE *phaseZ;

    phaseZ = fopen("Phase Zero.txt", "r");

    if(phaseZ == NULL){
    printf("Error opening file!\n");
}

    while((fscanf(phaseZ,"%s%s%d",&sex,&age,&tCount))!= EOF){
        patients[i][j] = tCount;
        j++;
        if(j == 15){
            i++;
            j = 0;
        }
}
i = 0;
j = 0;
for(i; i<=3; i++){
    for(j; j<15; j++){
     if(patients[i][j] > 1200){
        checkFifteen++;
        if(checkFifteen == 10){
            if(i == 0){
                astraZeneca = false;
                printf("Astra Zeneca has failed phase zero\n");
            }
            if(i == 1){
                johnsonJohnson = false;
                printf("johnson Johnson has failed phase zero\n");
            }
            if(i == 2){
                moderna = false;
                printf("Moderna has failed phase zero\n");
            }
            if(i == 3){
                novavax = false;
                printf("Novavax has failed phase zero\n");
            }
        }
     }
    }
    checkFifteen = 0;
    j = 0;
}
fclose(phaseZ);
}
/*
PhaseOneTesting opens the phase one text file and takes all the 0s or 1s and puts them into 6 different int variables, if any of them are one
a counter is incremented. After twenty have been counted it checks to see if the percent of side effects is greater then 30 percent of patients
if it is above 30 the company is taken out of the running for their vac

after the count is reset, and the company is incremented
*/
void phaseOneTesting(){
    FILE *phaseO;
    char sex[1000];
    int age;
    int painSwell;
    int mildFever;
    int chills;
    int tired;
    int headache;
    int aches;
    int goodCount = 0;
    int badCount = 0;
    int generalCount = 0;
    int companyNumber = 0;
    double percent;

    phaseO = fopen("Phase One.txt", "r");

    if(phaseO == NULL){
    printf("Error opening file!\n");
}

   while((fscanf(phaseO,"%s%d%d%d%d%d%d%d",&sex,&age,&painSwell,&mildFever,&chills,&tired,&headache,&aches))!= EOF){
        if(painSwell == 1 || mildFever == 1 || chills == 1 || tired == 1 || tired == 1 || headache == 1 || aches == 1){
            badCount++;
            generalCount++;
        }
        else{
            goodCount++;
            generalCount++;
        }
        if(generalCount == 20){
            percent = badCount/goodCount;
            if(percent > .30){
                if(companyNumber == 0 && astraZeneca == true){
                    astraZeneca = false;
                    printf("Astra Zeneca has failed phase one\n");
                }
                if(companyNumber == 1 && johnsonJohnson == true){
                    johnsonJohnson = false;
                    printf("Johnson Johnson has failed phase one\n");
                }
                if(companyNumber == 2){
                    if (moderna == true && novavax == false){
                        moderna = false;
                        printf("Moderna has failed phase one\n");
                    }
                    else{
                        novavax = false;
                        printf("Novavax has failed phase one\n");
                    }
                }
            }
            generalCount = 0;
            goodCount = 0;
            badCount = 0;
            companyNumber++;
        }

   }
    fclose(phaseO);
}

/*
PhaseTwoTesting opens the phase two text files and takes the most important part out the days immune.

depending on if they are immune for 60 or more days they are placed into two different counts

after 100 are counted it seems if less then 50% are immune for 60 or more days. if one of the remaining companies is less then 50% they are out of the running


Uses something similar to a half adder alg to figure out which company is getting eliminated.

it does this for all 200 results.
*/

void phaseTwoTesting(){
   FILE *phaseT;
   char sex[201];
   int age = 0;
   int daysImmune= 0;
   int count = 0;
   int underSixty = 0;
   double aboveSixty = 0;
   double aboveHalf = 0;
   int company = 0;

   phaseT = fopen("Phase Two.txt", "r");

    if(phaseT == NULL){
    printf("Error opening file!\n");
}

   while((fscanf(phaseT,"%s%d%d",&sex,&age,&daysImmune)) != EOF){
                count++;
                if(daysImmune < 60){
                    underSixty++;
                }
                if(daysImmune >= 60){
                    aboveSixty++;
                }
                if (count == 100){
                    aboveHalf = aboveSixty/count;
                    if (aboveHalf < .50 && company == 0){
                        if(astraZeneca == false && johnsonJohnson == true){
                            johnsonJohnson = false;
                            printf("Johnson Johnson has failed phase two\n");
                        }
                        else if(astraZeneca == true && johnsonJohnson == false){
                            astraZeneca = false;
                            printf("Astra Zeneca has failed phase two\n");
                        }
                        else if(astraZeneca == true && johnsonJohnson == true){
                            astraZeneca = false;
                            printf("Astra Zeneca has failed phase two\n");
                        }
                        else{
                            moderna = false;
                            printf("Moderna has failed phase two\n");
                        }
                    }
                    if (aboveHalf < .50 && company == 1){
                        if(moderna == false && novavax == true){
                            novavax = false;
                            printf("Novavax has failed phase two\n");
                            }
                        else if(moderna == true && novavax == false){
                            moderna = false;
                            printf("Moderna has failed phase two\n");
                        }
                        else if(astraZeneca == true && johnsonJohnson == true){
                            johnsonJohnson = false;
                            printf("Johnson Johnson has failed phase two\n");
                        }
                        else{
                            novavax = false;
                            printf("Novavax has failed phase two\n");
                        }
                        }
                    count = 0;
                    underSixty = 0;
                    aboveSixty = 0;
                    company++;
                }
            }
    fclose(phaseT);
}
/*
PhaseThreeTesting opens the phase three text doc, and sees if the patients got sick or not sick.

First however, it finds out which company is the last company left.

finally it puts the 500 results into two int counts, if they got sick or not. after all 500 are counted for
if less then 20% of the patients got sick. That medicine will pass all the phases, if not, not medication will.
*/

void phaseThreeTesting(){
    FILE *phaseTH;
    char sex[10];
    int age;
    int gotSick;
    int notSick;
    int sick;
    char company[30];
    double aboveTwenty;

   phaseTH = fopen("Phase Three.txt", "r");

    if(phaseTH == NULL){
    printf("Error opening file!\n");
}

    if(astraZeneca == true){
        strcpy(company, "Astra Zeneca");
    }
    if(johnsonJohnson == true){
        strcpy(company, "Johnson Johnson");
    }
    if(moderna == true){
       strcpy(company, "Moderna");
    }
    if(novavax == true){
        strcpy(company, "Novavax");
    }

   while((fscanf(phaseTH,"%s%d%d",&sex,&age,&gotSick)) != EOF){
        if(gotSick == 1){
            sick++;
        }
        if(gotSick == 0){
            notSick++;
        }
    }
    aboveTwenty = sick/notSick;
    if(aboveTwenty < .20){
        printf("%s has passed all phases", company);
    }
    else{
        printf("No company has passed all phases");
    }
}
/*
main only calls the methods in order from decryption to phase three
*/
int main()
{
decryption();
phaseZeroTesting();
phaseOneTesting();
phaseTwoTesting();
phaseThreeTesting();
return 0;
}
