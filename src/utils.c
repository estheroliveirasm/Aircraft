#include "../include/utils.h"
#include "../include/types.h"
#include "../include/registrations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void clear_screen()
{
    system("clear || cls"); 
}

void to_upper_string(char *str)
{
    for(int i = 0; str[i] != '\0'; i++){
        str[i] = toupper(str[i]);
    }
}

int date_greater_or_equal(date_t first_date, date_t second_date)
{
    if(first_date.year > second_date.year) return 1;
    if(first_date.year == second_date.year) {
        if(first_date.month > second_date.month) return 1;
        if(first_date.month == second_date.month){
            if(first_date.day >= second_date.day) return 1;
        }
    }
    return 0;
}

void message(char* msg)
{
    printf("\n %s\n", msg);
    getchar();
}

void remove_newline(char *str)
{
    if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}

int validate_aircraft(int aircraft_id, aircraft_data_t *list)
{
    return locate_aircraft_by_id(aircraft_id, list) != NULL;
}