//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    HealthData* health_data_ptr = &health_data;    // pointer of health_data
    
    // Tocode: to read the list of the exercises and diets
    loadExercises(EXERCISEFILEPATH);
    loadDiets(DIETFILEPATH);
    
    int calories_remain = health_data_ptr->total_calories_intake - health_data_ptr->total_calories_burned - 1300;    //remaining calories

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	if (calories_remain == 0) {    //exit the program if remaining calories are zero
            printf("You have consumed all your calories for today! \n");
            exit(0);
            break;
		} 
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(health_data_ptr);
            	saveData(HEALTHFILEPATH, health_data_ptr);
            	
                break;
                
            case 2:
            	inputDiet(health_data_ptr);
            	saveData(HEALTHFILEPATH, health_data_ptr);
            	
                break;
                
            case 3:
            	printHealthData(health_data_ptr);
            	
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
    			exit(0);
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (1);    //infinite loop until exit option

    return 0;
}

