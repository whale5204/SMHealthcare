//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fgets(exercise_list[exercise_list_size].exercise_name, MAX_EXERCISES, file) != NULL) {	//read file and put all the information(exercise name and calories) in exercise_list.exercise_name
        if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}

		//seperate exercises name and calories
		char *name = strtok(exercise_list[exercise_list_size].exercise_name, " ");    //use strtok to seperate exercise name and calories by space
		char *calories_burned = strtok(NULL, " ");
		exercise_list[exercise_list_size].calories_burned_per_minute = atoi(calories_burned);    //convert calories_burned info string to integer

		exercise_list_size++;
    }
    fclose(file);
}
//


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
    for (i=0; i<exercise_list_size; i++) {
    	printf("%d. %s \n", (i + 1), exercise_list[i].exercise_name);
	}
	printf("%d. exit \n", (exercise_list_size + 1));


    // ToCode: to enter the exercise to be chosen with exit option
    printf("Enter the choice of exercise: ");
    scanf("%d", &choice);
    
    // exit option
    if (choice == exercise_list_size + 1)
        return;
    
    // invalid option
    if (choice < 1 || choice > (exercise_list_size + 1)) {
    	printf("[Error] Invalid option. \n");
        printf("Please try again! \n");
        return;    // go to main menu
	}
    
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    int index = health_data->exercise_count;    // index of selected exercise
    
    // enter the selected exercise and calories burned in the health data
    health_data->exercises[index] = exercise_list[choice - 1];
    health_data->exercises[index].calories_burned_per_minute *= duration;
    
    // enter total calories burned in the health data
    health_data->total_calories_burned += health_data->exercises[index].calories_burned_per_minute;
    
    health_data->exercise_count++;
}
