#ifndef UTILS_H
#define UTILS_H

#include "types.h"

void clear_screen();
void to_upper_string(char *str);
int date_greater_or_equal(date_t first_date, date_t second_date);
void message(char* msg);
void remove_newline(char *str);
int validate_aircraft(int aircraft_id, aircraft_data_t *list);

#endif