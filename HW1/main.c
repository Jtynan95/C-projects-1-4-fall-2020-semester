#include <stdio.h>
#include <stdlib.h>

/*

* COP 3515 – Fall Semester 2020 *

* Homework #1: Helping The Governor Out *

* Joshua Tynan */



int main(){
    // I declared all the variables separately so I can easily change type or size. Plus it was easier for me to keep them in track. f stands for female, m stands for male
    // counter/count variables holds numbers incrementing by 1 every time its called
    // holder variables store data that will eventually be overwritten by new data
    // array variables read in all the data from the file
    // the remaining variables generally store data from the holder variables, and save them for later.
    FILE *entireDataSet;
    char gender[1000];
    int age[1000];
    int height[1000];
    char posNeg[1000];
    int zip[1000];
    int oldestAge = 0;
    int youngestAge = 105;
    float avgAgeFemale = 0;
    float avgAgeFemaleNeg = 0;
    float avgFemaleWeight = 0;
    float avgAgeMale = 0;
    float avgAgeMaleNeg = 0;
    float avgMaleWeight = 0;
    int ageHolder = 0;
    int heightHolder= 0;
    float weightHolder = 0;
    int fPosCounter = 0;
    int fNegCounter = 0;
    int mPosCounter = 0;
    int mNegCounter = 0;
    int femaleCount = 0;
    int maleCount = 0;
    float mBMIHolder = 0;
    float mBMI = 0;
    float fBMIHolder = 0;
    float fBMI = 0;
    int mObeseCount = 0;
    int fObeseCount = 0;
    int olderObeseCount = 0;
    int weight[4];
    float fBMIUnderThirty = 0;
    int fUnderThirtyCount = 0;
    float fBMIBetween = 0;
    int fBetweenCount = 0;
    float fBMIAboveSixty = 0;
    int fAboveSixtyCount = 0;
    float mBMIUnderThirty = 0;
    int mUnderThirtyCount = 0;
    float mBMIBetween = 0;
    int mBetweenCount = 0;
    float mBMIAboveSixty = 0;
    int mAboveSixtyCount = 0;
    float totalCount = 0;
    float totalInfected = 0;
    float avgInfected = 0;


    //Reading in the data into entireDataSet make sure the data is in the same folder as main, if not change code to your location, will get an error otherwise.
    entireDataSet = fopen("HW #1 Data.txt", "r");

    //Checking to see the file actually exists.
    if(entireDataSet == NULL){
    printf("Error opening file!\n");
    return (1);
}
//fscanf makes this simple I have six pieces of data from each row, so I just keep grabbing six of them over and over, and then I won't have to pay attention to the new line
while((fscanf(entireDataSet,"%s%s%s%s%s%s",gender,age,height,weight,posNeg,zip))!= EOF){
    // I place the age height and weight into new variables, converting them from strings to ints with atoi()
   ageHolder = atoi(age);
   heightHolder = atoi(height);
   weightHolder = atoi(weight);

    //finding the oldest age out of all of the positive data
   if(ageHolder > oldestAge){
       //strcmp to compare the current posNeg to find if the string is + if so, we go into the if loop. It is required to have == 0 at the end or it will take in - instead
        if(strcmp(posNeg, "+") == 0){
            oldestAge = ageHolder;
        }
   }
    //same as the above, but instead looking for the youngest age.
     if(ageHolder < youngestAge){
        if(strcmp(posNeg, "+") == 0){
            youngestAge = ageHolder;
        }
   }
    //using strcmp again to find if gender is female
   if(strcmp(gender, "F") == 0){
        //using strcmp to find all negative test results of females and placing them into their own count, and another variable to eventually get the avg female negative age
        if(strcmp(posNeg, "-") == 0){
            fNegCounter++;
            avgAgeFemaleNeg = avgAgeFemaleNeg + ageHolder;
        }
        // the same as the last if statement, but this time looking for positive test results only.
        if(strcmp(posNeg,"+") == 0){
            fPosCounter++;
            //finding the BMI of all positive female test cases
            fBMIHolder = weightHolder/(heightHolder*heightHolder)*703;
            //I take the bmi and find the range of the positive tests within three ranges, <= 30, >30 and <60 and >=60 I then record the count.
            // I then take the BMI and add it into a new container to eventually get the average.
            if(ageHolder <= 30){
                fBMIUnderThirty = fBMIHolder + fBMIUnderThirty;
                fUnderThirtyCount++;
            }
            if(ageHolder > 30 && ageHolder < 60 ){
                fBMIBetween = fBMIHolder + fBMIBetween;
                fBetweenCount++;
            }
            if(ageHolder >= 60){
                fBMIAboveSixty = fBMIHolder + fBMIAboveSixty;
                fAboveSixtyCount++;
            }
            //placing all the female bmi's in the same spot a second time, but this time to get two different new counts, if the female was obese or if they are 80 years or older.
            fBMI = fBMIHolder + fBMI;
            if(fBMIHolder >= 30){
                fObeseCount++;
                if(ageHolder >= 80){
                    olderObeseCount++;
                }
            }
            //basic math to calculate the average female age and weight.
            avgAgeFemale = avgAgeFemale + ageHolder;
            avgFemaleWeight = avgFemaleWeight + weightHolder;
        }
        //counting how many females there are in total.
    femaleCount++;
   }
   //using strcmp again to find if gender is female
   if(strcmp(gender, "M") == 0){
        //using strcmp to find all negative test results of females and placing them into their own count, and another variable to eventually get the avg males negative age
         if(strcmp(posNeg, "-") == 0){
            //finding the BMI of all positive males test cases
            mNegCounter++;
            avgAgeMaleNeg = avgAgeMaleNeg + ageHolder;
        }
   // the same as the last if statement, but this time looking for positive test results only.
        if(strcmp(posNeg,"+") == 0){
            mBMIHolder = weightHolder/(heightHolder*heightHolder) * 703;

            //I take the bmi and find the range of the positive tests within three ranges, <= 30, >30 and <60 and >=60 I then record the count.
            // I then take the BMI and add it into a new container to eventually get the average.
             if(ageHolder <= 30){
                mBMIUnderThirty = mBMIHolder + mBMIUnderThirty;
                mUnderThirtyCount++;
            }
            if(ageHolder > 30 && ageHolder < 60 ){
                mBMIBetween = mBMIHolder + mBMIBetween;
                mBetweenCount++;
            }
            if(ageHolder > 60){
                mBMIAboveSixty = mBMIHolder + mBMIAboveSixty;
                mAboveSixtyCount++;
            }
            //placing all the male bmi's in the same spot a second time, but this time to get two different new counts, if the male was obese or if they are 80 years or older.
            mBMI = mBMIHolder + mBMI;
             if(mBMIHolder >= 30){
                mObeseCount++;
                 if(ageHolder >= 80){
                    olderObeseCount++;
                }
            }
            //basic math to calculate the average male age, weight, and the total count of all positive males.
            avgMaleWeight = avgMaleWeight + weightHolder;
            mPosCounter++;
            avgAgeMale = avgAgeMale + ageHolder;
        }
         //counting how many males there are in total.
    maleCount++;
   }
}
//getting the total amount of all cases
totalCount = maleCount + femaleCount;
//getting the total amount of positive tests
totalInfected = mPosCounter + fPosCounter;
//getting the average of infected from all cases
avgInfected = totalInfected/totalCount * 100;
    //question 1 and 2, in some of the below prints a specific number by dividing one of my counters to get an average result.
    printf(" 1) The total amount of males: %i\n 2) total amount of females: %i\n 1.1) Total males who tested positive: %i\n 2.1) Total females who tested positive: %i\n", maleCount,femaleCount,mPosCounter,fPosCounter);
    //question 3 and 4
    printf(" 3) The average age of males who tested positive:%f\n 4) The average age of females who tested positive: %f\n", avgAgeMale/mPosCounter, avgAgeFemale/fPosCounter);
    //question 5 and 6
    printf(" 5) The age of the oldest positive case: %i\n 6) The age of the youngest positive case: %i\n", oldestAge,youngestAge);
    //question 7
    printf(" 7) The average age of males who tested positive compared to negative: %f to %f\n", avgAgeMale/mPosCounter, avgAgeMaleNeg/mNegCounter);
    //question 8
    printf(" 8) The average age of females who tested positive compared to negative: %f to %f\n", avgAgeFemale/fPosCounter, avgAgeFemaleNeg/fNegCounter);
    //question 9 and 10
    printf(" 9) The average weight of males who tested positive: %f\n 10) The average weight of females who tested positive: %f\n", avgMaleWeight/mPosCounter, avgFemaleWeight/fPosCounter);
    //question 11 and 12
    printf(" 11) The average BMI of males who tested positive: %f\n 12) The average BMI of females who tested positive: %f\n", mBMI/mPosCounter, fBMI/fPosCounter);
    //question 13 and 14
    printf(" 13) The number of obese males who tested positive: %i\n 14) The number of obese females who tested positive: %i\n", mObeseCount,fObeseCount);
    //question 15
    printf(" 15) The number of people older then 80 and obese is: %i\n", olderObeseCount);
    //question 16
    printf(" 16) The average BMI for males under 30: %f\n 16.1) Between 30 and 60: %f\n 16.2) Above 60: %f\n", mBMIUnderThirty/mUnderThirtyCount, mBMIBetween/mBetweenCount,mBMIAboveSixty/mAboveSixtyCount);
    //question 17
    printf(" 17) The average BMI for females under 30: %f\n 17.1) Between 30 and 60: %f\n 17.2) Above 60: %f\n", fBMIUnderThirty/fUnderThirtyCount, fBMIBetween/fBetweenCount,fBMIAboveSixty/fAboveSixtyCount);
    //question 18
    printf(" The average infection rate for all people tested is: %f\n", avgInfected);

    //closing the file
    fclose(entireDataSet);

    return 0;
}

