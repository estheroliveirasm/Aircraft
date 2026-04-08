#include "../include/searches.h"
#include "../include/utils.h"
#include "../include/reports.h"
#include "../include/registrations.h"
#include "../include/types.h"
#include "../include/menus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

long long convert_to_comparative_long(int day, int month, int year, int hour, int min) {
    return (long long)year * 100000000LL + 
           (long long)month * 1000000LL + 
           (long long)day * 10000LL + 
           (long long)hour * 100LL + 
           (long long)min;
}

void search_aircraft_by_registration(aircraft_data_t *list)
{
    char search_reg[STR_SIZE];
    int found = FALSE;
    aircraft_data_t *current = list;

    printf(".....SEARCH AIRCRAFT BY REGISTRATION.....\n");
    printf("Enter registration..................: ");
    fgets(search_reg, STR_SIZE, stdin);
    remove_newline(search_reg);
    to_upper_string(search_reg);

    while(current != NULL){
        if(strcmp(current->registration, search_reg) == 0){ 
            show_aircraft_data(current, stdout);
            found = TRUE;
            break;
        }
        current = current->next;
    }

    if(found == FALSE){
        printf(" No aircraft found with the provided registration.\n");
    }

    message("Press ENTER to continue.");
}

void list_aircraft_by_manufacturer(aircraft_data_t *list)
{
    char search_manuf[STR_SIZE];
    int found = FALSE;
    aircraft_data_t *current = list;

    printf("....LIST AIRCRAFT BY MANUFACTURER...\n");
    printf("Enter manufacturer name.............: ");
    fgets(search_manuf, STR_SIZE, stdin);
    remove_newline(search_manuf);
    to_upper_string(search_manuf);

    printf("\n Aircraft from manufacturer %s:\n", search_manuf);

    while(current != NULL){
        if(strcmp(current->manufacturer, search_manuf) == 0){
            show_aircraft_data(current, stdout);
            found = TRUE;
        }
        current = current->next;
    }

    if(found == FALSE){
        printf(" No aircraft found for this manufacturer.\n");
    }

    message("Press ENTER to continue.");
}

void list_aircraft_by_type(aircraft_data_t *list)
{
    int chosen_type;
    int found = FALSE;
    aircraft_data_t *current = list;

    printf(".......LIST AIRCRAFT BY TYPE......\n");
    printf("Type (1- CARGO | 2- PASSENGER)......: ");
    scanf("%i", &chosen_type);
    while (getchar() != '\n');

    if(chosen_type != CARGO && chosen_type != PASSENGER) {
        printf("\n Error: Invalid aircraft type.\n");
        message("Press ENTER to continue.");
        return;
    }

    if(chosen_type == CARGO){
        printf("\n Cargo aircraft:\n");
    }
    else {
        printf("\n Passenger aircraft:\n");
    }

    while(current != NULL) {
        if(current->type == (aircraft_type_t)chosen_type){
            show_aircraft_data(current, stdout);
            found = TRUE;
        }
        current = current->next;
    }

    if(found == FALSE){
        printf(" No aircraft found for the informed type.\n");
    }

    message("Press ENTER to continue.");
}

void list_aircraft_by_model(aircraft_data_t *list)
{
    char search_model[STR_SIZE];
    int found = FALSE;
    aircraft_data_t *current = list;

    printf("......SEARCH AIRCRAFT BY MODEL.....\n");
    printf("Enter aircraft model................: ");
    fgets(search_model, STR_SIZE, stdin);
    remove_newline(search_model);
    to_upper_string(search_model);

    printf("\n Aircraft of model %s:\n", search_model);

    while(current != NULL){
        if(strcmp(current->model, search_model) == 0){
            show_aircraft_data(current, stdout);
            found = TRUE;
        }
        current = current->next;
    }

    if(found == FALSE){
        printf(" No aircraft found for this model.\n");
    }

    message("Press ENTER to continue.");
}

void list_aircraft_by_manufacture_year(aircraft_data_t *list)
{
    int search_year;
    int found = FALSE;
    aircraft_data_t *current = list;

    printf("...LIST BY MANUFACTURE YEAR.....\n");
    printf("Enter manufacture year..............: ");
    scanf("%i", &search_year);
    while(getchar() != '\n');

    printf("\n Aircraft manufactured in year %i:\n", search_year);

    while(current != NULL){
        if(current->manufacture_year == search_year){
            show_aircraft_data(current, stdout);
            found = TRUE;
        }
        current = current->next;
    }

    if(found == FALSE){
        printf(" No aircraft manufactured in the informed year.\n");
    }

    message("Press ENTER to continue.");
}

void list_aircraft_by_status(aircraft_data_t *list)
{
    int chosen_status;
    int found = FALSE;
    aircraft_data_t *current = list;

    printf(".....LIST AIRCRAFT BY STATUS....\n");
    printf("Status (1- OPERATION | 2- MAINTENANCE): ");
    scanf("%i", &chosen_status);
    while (getchar() != '\n');

    if(chosen_status != OPERATION && chosen_status != MAINTENANCE) {
        printf("\n Error: Invalid status.\n");
        message("Press ENTER to continue.");
        return;
    }

    if(chosen_status == OPERATION){
        printf("\n Aircraft in operation:\n");
    }
    else {
        printf("\n Aircraft in maintenance:\n");
    }

    while(current != NULL) {
        if(current->status == (status_t)chosen_status){
            show_aircraft_data(current, stdout);
            found = TRUE;
        }
        current = current->next;
    }

    if(found == FALSE){
        printf(" No aircraft found in this status.\n");
    }

    message("Press ENTER to continue.");
}

void search_route_by_date(route_data_t *list)
{
    date_t search_date;
    int found = FALSE;
    route_data_t *current = list;

    printf(".......SEARCH ROUTE BY DATE.......\n");
    printf("Enter date (dd/mm/yyyy)............: ");
    scanf("%i/%i/%i", &search_date.day, &search_date.month, &search_date.year);
    getchar();

    printf("\n Routes for the day %02i/%02i/%i:\n", search_date.day, search_date.month, search_date.year);

    while(current != NULL){
        if(current->date_time.day == search_date.day &&
           current->date_time.month == search_date.month &&
           current->date_time.year == search_date.year){
                show_route_data(current, stdout);
                found = TRUE;
            }
        current = current->next;
    }

    if(found == FALSE){
        printf(" No route located for this date.\n");
    }

    message("Press ENTER to continue.");
}

void search_route_by_origin(route_data_t *list)
{
    char search_orig[STR_SIZE];
    int found = FALSE;
    route_data_t *current = list;

    printf("......SEARCH ROUTE BY ORIGIN......\n");
    printf("Enter departure location............: ");
    fgets(search_orig, STR_SIZE, stdin);
    remove_newline(search_orig);
    to_upper_string(search_orig);

    while(current != NULL){
        if(strcmp(current->departure_location, search_orig) == 0){
            show_route_data(current, stdout);
            found = TRUE;
        }
        current = current->next;
    }

    if (found == FALSE){
        printf(" No route found for the informed origin.\n");
    }

    message("Press ENTER to continue.");
}

void search_route_by_destination(route_data_t *list)
{
    char search_dest[STR_SIZE];
    int found = FALSE;
    route_data_t *current = list;

    printf(".....SEARCH ROUTE BY DESTINATION......\n");
    printf("Enter arrival location..............: ");
    fgets(search_dest, STR_SIZE, stdin);
    remove_newline(search_dest);
    to_upper_string(search_dest);

    printf("\n Routes with destination in %s:\n", search_dest);

    while(current != NULL){
        if(strcmp(current->arrival_location, search_dest) == 0){
            show_route_data(current, stdout);
            found = TRUE;
        }
        current = current->next;
    }

    if (found == FALSE){
        printf(" No route found for the informed destination.\n");
    }

    message("Press ENTER to continue.");
}

void list_routes_by_temporal_status(route_data_t *route_list)
{
    if (route_list == NULL) {
        printf(" No routes registered.\n");
        message("Press ENTER to continue.");
        return;
    }

    time_t t = time(NULL);
    struct tm current_date = *localtime(&t);
    
    long long now = convert_to_comparative_long(
        current_date.tm_mday, 
        current_date.tm_mon + 1, 
        current_date.tm_year + 1900, 
        current_date.tm_hour, 
        current_date.tm_min
    );

    printf("\n.......COMPLETED ROUTES........\n");
    route_data_t *current = route_list;
    int found_past = FALSE;
    while (current) {
        long long route_date = convert_to_comparative_long(
            current->date_time.day, current->date_time.month, current->date_time.year,
            current->date_time.hour, current->date_time.min
        );
        if (route_date < now) {
            printf(" [%02i/%02i/%i %02i:%02i] Code: %i | %s -> %s\n",
                   current->date_time.day, current->date_time.month, current->date_time.year,
                   current->date_time.hour, current->date_time.min,
                   current->route_code, current->departure_location, current->arrival_location);
            found_past = TRUE;
        }
        current = current->next;
    }
    if (!found_past) printf(" No completed routes found.\n");

    printf("\n........UPCOMING ROUTES.........\n");
    current = route_list;
    int found_future = FALSE;
    while (current) {
        long long route_date = convert_to_comparative_long(
            current->date_time.day, current->date_time.month, current->date_time.year,
            current->date_time.hour, current->date_time.min
        );
        if (route_date >= now) {
            printf(" [%02i/%02i/%i %02i:%02i] Code: %i | %s -> %s\n",
                   current->date_time.day, current->date_time.month, current->date_time.year,
                   current->date_time.hour, current->date_time.min,
                   current->route_code, current->departure_location, current->arrival_location);
            found_future = TRUE;
        }
        current = current->next;
    }
    if (!found_future) printf(" No scheduled routes found.\n");
    
    message("\nPress ENTER to return.");
}

double total_fuel_consumption_by_date(route_data_t *list)
{
    date_t start_date, end_date;
    double total_cons = 0.0;
    route_data_t *current = list;
    int found_flight = FALSE;

    printf(".......FUEL CONSUMPTION........\n");
    printf("Initial date (dd/mm/yyyy)...........: ");
    scanf("%i/%i/%i", &start_date.day, &start_date.month, &start_date.year);
    while(getchar() != '\n');

    printf("Final date (dd/mm/yyyy).............: ");
    scanf("%i/%i/%i", &end_date.day, &end_date.month, &end_date.year);
    while(getchar() != '\n');

    long long start = convert_to_comparative_long(start_date.day, start_date.month, start_date.year, 0, 0);
    long long end = convert_to_comparative_long(end_date.day, end_date.month, end_date.year, 23, 59);

    while(current != NULL){
        long long flight_date = convert_to_comparative_long(current->date_time.day, current->date_time.month, current->date_time.year, current->date_time.hour, current->date_time.min);
        
        if(flight_date >= start && flight_date <= end) {
            total_cons += current->flight_fuel;
            found_flight = TRUE;
        }
        current = current->next;
    }

    printf("\n.......CONSUMPTION RESULT.........\n");
    printf(" Period: %02i/%02i/%i to %02i/%02i/%i\n", start_date.day, start_date.month, start_date.year, end_date.day, end_date.month, end_date.year);
    
    if(found_flight == FALSE) {
        printf(" No routes found for the period.\n");
    } else {
        printf(" Total consumption: %.2f Liters\n", total_cons);
    }

    message("Press ENTER to continue.");
    return total_cons;
}

double flight_percentage_by_aircraft(route_data_t *route_list, aircraft_data_t *aircraft_list)
{
    int search_id;
    int aircraft_flights = 0;
    int total_routes = 0;
    route_data_t *current_route = route_list;
    aircraft_data_t *searched_aircraft = NULL;
    double percentage = 0.0;

    printf(".....FLIGHT PERCENTAGE BY AIRCRAFT....\n");

    if(route_list == NULL){
        printf(" No routes registered for calculation.\n");
        message("Press ENTER to continue.");
        return 0.0;
    }

    printf("Enter aircraft ID...................: ");
    scanf("%i", &search_id);
    while(getchar() != '\n');

    searched_aircraft = locate_aircraft_by_id(search_id, aircraft_list);
    if(searched_aircraft == NULL){
        printf(" Error: Aircraft ID %i not found.\n", search_id);
        message("Press ENTER to continue.");
        return 0.0;
    }

    while(current_route != NULL) {
        total_routes++;
        if(current_route->aircraft_id == search_id){
            aircraft_flights++;
        }
        current_route = current_route->next;
    }
    
    if (total_routes != 0) {
        percentage = (double)aircraft_flights / total_routes * 100.0;
    }

    printf("\n.......PERCENTAGE RESULT.......\n");
    printf(" Aircraft: %s (ID %i)\n", searched_aircraft->registration, search_id);
    printf(" Total system routes: %i\n", total_routes);
    printf(" Flights of this aircraft: %i\n", aircraft_flights);
    printf(" Share of total: %.2f%%\n", percentage);

    message("Press ENTER to continue.");
    return percentage;
}

double flight_percentage_by_destination_and_date(route_data_t *list)
{
    date_t start_date, end_date;
    char search_dest[STR_SIZE];
    int interval_flights = 0;
    int destination_flights = 0;
    route_data_t *current = list;

    printf(".......PERCENTAGE BY DESTINATION........\n");

    if(list == NULL){
        printf(" No routes registered for calculation.\n");
        message("Press ENTER to continue.");
        return 0.0;
    }

    printf("Initial date (dd/mm/yyyy)...........: ");
    scanf("%i/%i/%i", &start_date.day, &start_date.month, &start_date.year);
    while(getchar () != '\n');

    printf("Final date (dd/mm/yyyy).............: ");
    scanf("%i/%i/%i", &end_date.day, &end_date.month, &end_date.year);
    while(getchar() != '\n');

    long long start = convert_to_comparative_long(start_date.day, start_date.month, start_date.year, 0, 0);
    long long end = convert_to_comparative_long(end_date.day, end_date.month, end_date.year, 23, 59);

    printf("Destination for verification........: ");
    fgets(search_dest, STR_SIZE, stdin);
    remove_newline(search_dest);
    to_upper_string(search_dest);

    while(current != NULL){
        long long flight_date = convert_to_comparative_long(current->date_time.day, current->date_time.month, current->date_time.year, current->date_time.hour, current->date_time.min);

        if(flight_date >= start && flight_date <= end){
            interval_flights++;
            if(strcmp(current->arrival_location, search_dest) == 0){
                destination_flights++;
            }
        }
        current = current->next;
    }

    if(interval_flights == 0){
        printf(" No routes found in the period.\n");
        message("Press ENTER to continue.");
        return 0.0;
    }

    double percentage = (double)destination_flights / interval_flights * 100.0;

    printf("\n.......PERCENTAGE RESULT.......\n");
    printf(" Period: %02i/%02i/%i to %02i/%02i/%i\n", start_date.day, start_date.month, start_date.year, end_date.day, end_date.month, end_date.year);
    printf(" Total flights in period: %i\n", interval_flights);
    printf(" Flights to %s: %i\n", search_dest, destination_flights);
    printf(" Destination share: %.2f%%\n", percentage);

    message("Press ENTER to continue.");
    return percentage;
}

int search_maintenance_count_by_aircraft(aircraft_data_t *list)
{
    int search_id;
    aircraft_data_t *aircraft = NULL;

    printf(".......MAINTENANCE HISTORY.......\n");
    printf("Enter aircraft ID...................: ");
    scanf("%i", &search_id);
    while (getchar() != '\n');

    aircraft = locate_aircraft_by_id(search_id, list);

    if(aircraft != NULL){
        printf("\n Aircraft: %s (ID %i)\n", aircraft->registration, search_id);
        printf(" Total maintenance records: %i\n", aircraft->maintenance_qty);
    }
    else{
        printf(" Error: Aircraft not found.\n");
    }

    message("Press ENTER to continue.");
    return (aircraft != NULL) ? aircraft->maintenance_qty : 0;
}