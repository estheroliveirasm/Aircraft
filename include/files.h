#ifndef FILES_H
#define FILES_H

#include "types.h"

void save_aircraft_data_bin(aircraft_data_t *list, string file_name);
void read_aircraft_data_bin(string file_name, aircraft_data_t **list);
void save_route_data_bin(route_data_t *list, string file_name);
void read_route_data_bin(string file_name, route_data_t **list);
void export_aircraft_txt(aircraft_data_t *aircraft_list, string file_name);
void export_aircraft_csv(aircraft_data_t *aircraft_list, string file_name);
void export_aircraft_html(aircraft_data_t *aircraft_list, string file_name);
void export_routes_txt(route_data_t *route_list, string file_name);
void export_routes_csv(route_data_t *route_list, string file_name);
void export_routes_html(route_data_t *route_list, string file_name);

#endif