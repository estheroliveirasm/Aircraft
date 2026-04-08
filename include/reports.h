#ifndef REPORTS_H
#define REPORTS_H

#include "types.h"

void show_aircraft_data(aircraft_data_t *aircraft, FILE *fp);
void show_route_data(route_data_t *route, FILE *fp);
void aircraft_report(aircraft_data_t *list, FILE *fp);
void routes_report(route_data_t *list, FILE *fp);
void list_routes_highest_passengers(route_data_t *list, FILE *fp);
void list_routes_lowest_passengers(route_data_t *list, FILE *fp);

#endif