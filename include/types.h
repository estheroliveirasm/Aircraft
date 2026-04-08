#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STR_SIZE 100
#define END 0
#define TRUE 1
#define FALSE 0
#define AIRCRAFT_FILE "aircraft.bin"
#define ROUTES_FILE "routes.bin"

typedef char string[STR_SIZE];
typedef enum {OPERATION = 1, MAINTENANCE = 2} status_t;
typedef enum {CARGO = 1, PASSENGER = 2} aircraft_type_t;

typedef struct aircraft_data {
    int aircraft_id;
    string model;
    string manufacturer;
    string registration;
    int manufacture_year;
    aircraft_type_t type;
    int num_passengers;
    int useful_cargo_qty;
    status_t status;
    int num_crew;
    int maintenance_qty;
    struct aircraft_data *next;
} aircraft_data_t;

typedef struct date {
    unsigned int day;
    unsigned int month;
    unsigned int year;
    unsigned int hour;
    unsigned int min;
} date_t;

typedef struct route_data {
    int route_code;
    date_t date_time;
    string departure_location;
    string arrival_location;
    float estimated_time;
    float flight_fuel;
    int passenger_qty;
    int useful_cargo;
    string member_names[10];
    int member_num;
    int aircraft_id;
    struct route_data *next;
} route_data_t;

#endif