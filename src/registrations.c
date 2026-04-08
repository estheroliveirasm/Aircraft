#include "../include/registrations.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

aircraft_data_t *new_aircraft() {
    aircraft_data_t *aircraft = (aircraft_data_t*)malloc(sizeof(aircraft_data_t));
    int type_num, status_num;
    if(aircraft == NULL) return NULL;
    
    aircraft->maintenance_qty = 0;
    printf(".........AIRCRAFT REGISTRATION.........\n");
    printf("Aircraft identification.............: ");
    scanf("%d", &aircraft->aircraft_id);
    while (getchar() != '\n');

    printf("Aircraft model......................: ");
    fgets(aircraft->model, STR_SIZE, stdin);
    remove_newline(aircraft->model);
    to_upper_string(aircraft->model); 

    printf("Aircraft manufacturer...............: ");
    fgets(aircraft->manufacturer, STR_SIZE, stdin);
    remove_newline(aircraft->manufacturer);
    to_upper_string(aircraft->manufacturer);

    printf("Aircraft registration...............: ");
    fgets(aircraft->registration, STR_SIZE, stdin);
    remove_newline(aircraft->registration);
    to_upper_string(aircraft->registration);

    printf("Manufacture year....................: ");
    scanf("%d", &aircraft->manufacture_year);
    
    printf("Type (1- CARGO | 2- PASSENGER)......: ");
    scanf("%d", &type_num);
    while (getchar() != '\n');
    aircraft->type = (aircraft_type_t)type_num;

    if(aircraft->type == PASSENGER) {
        printf("Number of passengers................: ");
        scanf("%d", &aircraft->num_passengers);
        aircraft->useful_cargo_qty = 0;
    } else { 
        aircraft->num_passengers = 0;
        printf("Useful cargo quantity (kg)..........: ");
        scanf("%d", &aircraft->useful_cargo_qty);
    }
    while (getchar() != '\n');

    printf("Status (1- OPERATION | 2- MAINTENANCE): ");
    scanf("%d", &status_num);
    while (getchar() != '\n');
    aircraft->status = (status_t)status_num;
    
    if(aircraft->status == MAINTENANCE) aircraft->maintenance_qty++;

    printf("Required crew.......................: ");
    scanf("%d", &aircraft->num_crew);
    while (getchar() != '\n');

    aircraft->next = NULL;
    return aircraft;
}

route_data_t *new_route(aircraft_data_t *aircraft_list) {
    route_data_t *route = (route_data_t*)malloc(sizeof(route_data_t));
    if(route == NULL) return NULL;
    
    int valid_aircraft = 0;
    aircraft_data_t *aero_ref = NULL;

    clear_screen();
    printf("..........ROUTE REGISTRATION..........\n");

    do {
        printf("\nAircraft to be allocated (ID).......: ");
        scanf("%d", &route->aircraft_id);
        while (getchar() != '\n');
        aero_ref = locate_aircraft_by_id(route->aircraft_id, aircraft_list);

        if(!aero_ref) printf(" Error: Aircraft not located.\n");
        else if (aero_ref->status != OPERATION) printf(" Error: Aircraft unavailable (in maintenance).\n");
        else valid_aircraft = 1;
    } while(!valid_aircraft);

    printf("Route code.........................: ");
    scanf("%d", &route->route_code);
    while (getchar() != '\n');

    printf("Flight date (DD/MM/YYYY)...........: ");
    scanf("%d/%d/%d", &route->date_time.day, &route->date_time.month, &route->date_time.year);
    while (getchar() != '\n');

    printf("Departure time (HH:MM).............: ");
    scanf("%d:%d", &route->date_time.hour, &route->date_time.min);
    while (getchar() != '\n');

    printf("Departure location.................: ");
    fgets(route->departure_location, STR_SIZE, stdin);
    remove_newline(route->departure_location);
    to_upper_string(route->departure_location);

    printf("Arrival location...................: ");
    fgets(route->arrival_location, STR_SIZE, stdin);
    remove_newline(route->arrival_location);
    to_upper_string(route->arrival_location);

    printf("Fuel required (liters).............: ");
    scanf("%f", &route->flight_fuel);
    while (getchar() != '\n');

    if (aero_ref->type == PASSENGER) {
        do {
            printf("Passenger quantity (Max %d): ", aero_ref->num_passengers);
            scanf("%d", &route->passenger_qty);
            while (getchar() != '\n');
        } while(route->passenger_qty > aero_ref->num_passengers);
        route->useful_cargo = 0;
    } else {
        do {
            printf("Cargo quantity (Max %d kg)....: ", aero_ref->useful_cargo_qty);
            scanf("%d", &route->useful_cargo);
            while (getchar() != '\n');
        } while(route->useful_cargo > aero_ref->useful_cargo_qty);
        route->passenger_qty = 0;
    }

    do {
        printf("Number of crew members (Min %d).....: ", aero_ref->num_crew);
        scanf("%d", &route->member_num);
        while (getchar() != '\n');
    } while (route->member_num < aero_ref->num_crew || route->member_num > 10);

    for(int i = 0; i < route->member_num; i++) {
        printf("Member name %d.....................: ", i + 1);
        fgets(route->member_names[i], STR_SIZE, stdin);
        remove_newline(route->member_names[i]);
        to_upper_string(route->member_names[i]);
    }

    route->next = NULL;
    return route;
}

void insert_aircraft_list_end(aircraft_data_t **list, aircraft_data_t *new_aircraft) {
    if (new_aircraft == NULL) return;
    if (*list == NULL) {
        *list = new_aircraft;
    } else {
        aircraft_data_t *last = *list;
        while (last->next != NULL) last = last->next;
        last->next = new_aircraft;
    }
}

void insert_route_list_end(route_data_t **list, route_data_t *new_route) {
    if (new_route == NULL) return;
    if (*list == NULL) {
        *list = new_route;
    } else {
        route_data_t *last = *list;
        while (last->next != NULL) last = last->next;
        last->next = new_route;
    }
}

aircraft_data_t *locate_aircraft_by_id(int aircraft_id, aircraft_data_t *list) {
   if(list == NULL) return NULL;
   if(list->aircraft_id == aircraft_id) return list;
   return locate_aircraft_by_id(aircraft_id, list->next);
}

void change_aircraft_status(aircraft_data_t **aircraft_list) {
    int chosen_id, new_status;
    aircraft_data_t *aircraft = NULL;

    printf("\n--- STATUS CHANGE ---\n");
    printf("Inform the Aircraft ID.............: ");
    scanf("%d", &chosen_id);
    while (getchar() != '\n');

    aircraft = locate_aircraft_by_id(chosen_id, *aircraft_list);
    if(!aircraft) {
        printf(" Error: Aircraft not located.\n");
        message("Press ENTER to return to menu.");
        return;
    }

    printf("New status (1- OPERATION | 2- MAINTENANCE): ");
    scanf("%d", &new_status);
    while (getchar() != '\n');

    if((status_t)new_status == MAINTENANCE && aircraft->status != MAINTENANCE) {
        aircraft->maintenance_qty++;
        printf(" Record: Aircraft in maintenance for the %d time.\n", aircraft->maintenance_qty);
    }

    aircraft->status = (status_t)new_status;
    printf("\n Success: Aircraft %d status changed to %s.\n", chosen_id, 
          (aircraft->status == OPERATION) ? "OPERATION" : "MAINTENANCE");
    message("Press ENTER to continue.");
}