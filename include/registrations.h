#ifndef REGISTRATIONS_H
#define REGISTRATIONS_H

#include "types.h"

aircraft_data_t *new_aircraft();
route_data_t *new_route(aircraft_data_t *aircraft_list);
void insert_aircraft_list_end(aircraft_data_t **list, aircraft_data_t *new_aircraft);
void insert_route_list_end(route_data_t **list, route_data_t *new_route);
aircraft_data_t *locate_aircraft_by_id(int aircraft_id, aircraft_data_t *list);
void change_aircraft_status(aircraft_data_t **aircraft_list);

#endif