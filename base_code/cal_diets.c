//
//  cal_diets.c
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

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

//warning 뜨는 건 나중에 해결하기 
void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fgets(diet_list[diet_list_size].food_name, MAX_DIETS, file) != NULL) {
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
		//seperate diets name and calories
		char *context = NULL;    //context for strtok_s
		char *name = strtok_s(diet_list[diet_list_size].food_name, " ", &context);
		char *calories_i = strtok_s(NULL, " ", &context);
		diet_list[diet_list_size].calories_intake = atoi(calories_i);    //convert calories_intake info string to integer
		//checking
		printf("%s %i\n", diet_list[diet_list_size].food_name, diet_list[diet_list_size].calories_intake);
		//
		diet_list_size++;
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for (i=0; i<diet_list_size; i++) {
    	printf("%d. %s \n", (i + 1), diet_list[i].food_name);
	}
	printf("%d. exit \n", (diet_list_size + 1));
    
	// ToCode: to enter the diet to be chosen with exit option
    printf("Enter the choice of diet: ");
    scanf("%d", &choice);
    
    // exit option
    if (choice == diet_list_size + 1)
        return;
    
    // invalid option
    if (choice > diet_list_size) {
    	printf("[Error] Invalid option. \n");
        printf("Please try again! \n");
        return;
	}

    // ToCode: to enter the selected diet in the health data
    int index = health_data->diet_count;    // index of selected diet
    
    health_data->diet[index] = diet_list[choice -1];

    // ToCode: to enter the total calories intake in the health data
    health_data->total_calories_intake += health_data->diet[index].calories_intake;
    
    //checking
    printf("%s - %d kcal \n", health_data->diet[index].food_name, health_data->diet[index].calories_intake);
    printf("Total calories intake: %d kcal \n", health_data->total_calories_intake);
    //
    
    health_data->diet_count++;
}

