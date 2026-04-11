#include "../include/reports.h"
#include "../include/utils.h"
#include "../include/types.h"
#include <stdio.h>

void show_aircraft_data(aircraft_data_t *aircraft, FILE *fp) {
    fprintf(fp, "\n.........AIRCRAFT DATA.........\n");
    fprintf(fp, "Identification....................: %d\n", aircraft->aircraft_id);
    fprintf(fp, "Model.............................: %s\n", aircraft->model);
    fprintf(fp, "Manufacturer......................: %s\n", aircraft->manufacturer);
    fprintf(fp, "Registration......................: %s\n", aircraft->registration);
    fprintf(fp, "Manufacture year..................: %d\n", aircraft->manufacture_year);
    
    if(aircraft->type == CARGO){
        fprintf(fp, "Type..............................: CARGO (CAPACITY: %d KG)\n", aircraft->useful_cargo_qty);
    } else {
        fprintf(fp, "Type..............................: PASSENGERS (CAPACITY: %d)\n", aircraft->num_passengers);
    }

    if(aircraft->status == OPERATION){
        fprintf(fp, "Status............................: IN OPERATION\n");
    } else {
        fprintf(fp, "Status............................: IN MAINTENANCE (MAINTENANCE QTY: %d)\n", aircraft->maintenance_qty);
    }
    fprintf(fp, "Required crew members.............: %d\n", aircraft->num_crew);
}

void show_route_data(route_data_t *route, FILE *fp) {
    fprintf(fp, "\n...........ROUTE DATA...........\n");
    fprintf(fp, "Route code........................: %d\n", route->route_code);
    fprintf(fp, "Allocated aircraft................: %d\n", route->aircraft_id);
    fprintf(fp, "Flight date.......................: %02d/%02d/%04d\n", 
            route->date_time.day, route->date_time.month, route->date_time.year);
    fprintf(fp, "Flight time.......................: %02d:%02d\n", 
            route->date_time.hour, route->date_time.min);
    fprintf(fp, "Departure location................: %s\n", route->departure_location);        
    fprintf(fp, "Arrival location..................: %s\n", route->arrival_location);
    fprintf(fp, "Fuel required.....................: %.2f LITERS\n", route->flight_fuel);
    fprintf(fp, "Passenger quantity................: %d\n", route->passenger_qty);
    fprintf(fp, "Useful cargo quantity.............: %d\n", route->useful_cargo);
    fprintf(fp, "Number of crew members............: %d\n", route->member_num);

    for(int i = 0; i < route->member_num; i++){
        fprintf(fp, "  - Member %d: %s\n", i + 1, route->member_names[i]);
    }
}

void aircraft_report(aircraft_data_t *list, FILE *fp) {
    aircraft_data_t *current = list;
    int counter = 0;
    if(list == NULL){
        printf(" No aircraft registered.\n");
        message("Press ENTER to continue.");
        return;
    }
    printf("......AIRCRAFT REPORT.......\n");
    while(current != NULL) {
        printf("\n--- AIRCRAFT %d ---\n", counter + 1);
        show_aircraft_data(current, stdout);
        counter++;
        current = current->next;
    }
    printf("\n Total aircraft: %d\n", counter); 
    message("Press ENTER to continue.");
}

void routes_report(route_data_t *list, FILE *fp) {
    route_data_t *current = list;
    int counter = 0;
    if(list == NULL){
        printf(" No routes registered.\n");
        message("Press ENTER to continue.");
        return;
    }
    printf("........ROUTES REPORT.........\n");
    while(current != NULL) {
        printf("\n--- ROUTE %d ---\n", counter + 1);
        show_route_data(current, stdout);
        counter++;
        current = current->next;
    }
    printf("\n Total routes: %d\n", counter); 
    message("Press ENTER to continue.");
}

void list_routes_highest_passengers(route_data_t *list, FILE *fp) {
    int max_passengers = -1;
    route_data_t *current = list;
    if(list == NULL){
        printf(" No routes registered.\n");
        message("Press ENTER to continue.");
        return;
    }
    while(current != NULL) {
        if(current->passenger_qty > max_passengers) max_passengers = current->passenger_qty;
        current = current->next;
    }
    printf("....ROUTES WITH MOST PASSENGERS (%d)....\n", max_passengers);
    current = list; 
    while(current != NULL) {
        if(current->passenger_qty == max_passengers) show_route_data(current, stdout);
        current = current->next;
    }
    message("Press ENTER to continue.");
}

void list_routes_lowest_passengers(route_data_t *list, FILE *fp) {
    int min_passengers = 2147483647; 
    route_data_t *current = list;
    if(list == NULL){
        printf(" No routes registered.\n");
        message("Press ENTER to continue.");
        return;
    }
    while(current != NULL) {
        if(current->passenger_qty < min_passengers) min_passengers = current->passenger_qty;
        current = current->next;
    }
    printf("....ROUTES WITH LEAST PASSENGERS (%d)....\n", min_passengers);
    current = list; 
    while(current != NULL) {
        if(current->passenger_qty == min_passengers) show_route_data(current, stdout);
        current = current->next;
    }
    message("Press ENTER to continue.");
}