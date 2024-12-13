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

//warning 뜨는건 나중에 해결하기 
void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fgets(exercise_list[exercise_list_size].exercise_name, MAX_EXERCISES, file) != NULL) {	
        if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}
		//seperate exercises name and calories
		char *context = NULL;    //context for strtok_s
		char *name = strtok_s(exercise_list[exercise_list_size].exercise_name, " ", &context);
		char *calories_b = strtok_s(NULL, " ", &context);
		exercise_list[exercise_list_size].calories_burned_per_minute = atoi(calories_b);    //convert calories_burned info string to integer
		//checking
		printf("%s %d \n", exercise_list[exercise_list_size].exercise_name, exercise_list[exercise_list_size].calories_burned_per_minute);
		//
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
    if (choice > exercise_list_size) {
    	printf("[Error] Invalid option. \n");
        printf("Please try again! \n");
        return;
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
    
    //checking
    printf("%s - %d kcal \n", health_data->exercises[index].exercise_name, health_data->exercises[index].calories_burned_per_minute);
    printf("Total calories burned: %d kcal \n", health_data->total_calories_burned);
    //
    
    health_data->exercise_count++;
}
