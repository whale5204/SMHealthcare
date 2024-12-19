//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

 void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }
    
    int calories_remain = health_data->total_calories_intake - health_data->total_calories_burned - 1300;    //remaining calories
    
    // index of exercise and diet
    int exercise_index = health_data->exercise_count;
    int diet_index = health_data->diet_count;

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for (i=0; i<exercise_index; i++) {
    	fprintf(file, "%s - %d kcal \n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
	}
    fprintf(file, "Total calories burned: %d kcal \n", health_data->total_calories_burned);
    
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
    for (i=0; i<diet_index; i++) {
    	fprintf(file, "%s - %d kcal \n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	}
    fprintf(file, "Total calories intake: %d kcal \n", health_data->total_calories_intake);


    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    fprintf(file, "Basical metabolic rate: 1300 kcal \n");
    fprintf(file, "The remaining calories: %d kcal \n", calories_remain);
    
    
    fclose(file);
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int i;
	int calories_remain = health_data->total_calories_intake - health_data->total_calories_burned - 1300;    //remaining calories
	
	// index of exercise and diet
    int exercise_index = health_data->exercise_count;
    int diet_index = health_data->diet_count;
    
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	
	for (i=0; i<exercise_index; i++) {
		printf("Exercise: %s, Calories burned: %d kcal \n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
	}
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
	
	for (i=0; i<diet_index; i++) {
		printf("Food: %s, Calories intake: %d kcal \n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	}    

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
	
	printf("Basal Metabolic Rate: 1300 kcal \n");
	printf("Total calories burned: %d kcal \n", health_data->total_calories_burned);
	printf("Tatal calories intake: %d kcal \n", health_data->total_calories_intake);
	printf("The remaining calories: %d kcal \n", calories_remain);
 
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    
    if (calories_remain < 0) {
    	printf("[Warning] Too few calories! \n");
    	
    	if (health_data->total_calories_intake == 2000) {
    		printf("Your total calorie intake for today has reached your goal! \n");
		}
		else if (health_data->total_calories_intake < 2000) {
			printf("Your total calorie intake for today has not reached your goal, remember to eat more! \n");
		}
		else
	        printf("You have eaten more calories than planned today, but you have exercised too much! \n");
	}
	
	else if (calories_remain > 0) {
		printf("Please exercise for your health! \n");
		
		if (health_data->total_calories_intake == 2000) {
			printf("Your total calorie intake for today has reached your goal! \n");
		}
		else if (health_data->total_calories_intake < 2000) {
			printf("Your total calorie intake for today has not reached your goal, remember to eat more! \n");
		}
	}
    
	printf("=======================================================================\n");
}
