#ifndef SEARCHES_H
#define SEARCHES_H

#include "types.h"

void search_aircraft_by_registration(aircraft_data_t *list);
void list_aircraft_by_manufacturer(aircraft_data_t *list);
void list_aircraft_by_type(aircraft_data_t *list);
void list_aircraft_by_model(aircraft_data_t *list);
void list_aircraft_by_manufacture_year(aircraft_data_t *list);
void list_aircraft_by_status(aircraft_data_t *list);
void search_route_by_date(route_data_t *list);
void search_route_by_origin(route_data_t *list);
void search_route_by_destination(route_data_t *list);
void list_routes_by_temporal_status(route_data_t *list); 
double flight_percentage_by_destination_and_date(route_data_t *list);
double flight_percentage_by_aircraft(route_data_t *route_list, aircraft_data_t *aircraft_list);
double total_fuel_consumption_by_date(route_data_t *list);
int search_maintenance_count_by_aircraft(aircraft_data_t *list);

#endif