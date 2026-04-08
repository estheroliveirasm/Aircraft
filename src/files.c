#include "../include/files.h"
#include "../include/registrations.h"
#include "../include/types.h"
#include "../include/reports.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void save_aircraft_data_bin(aircraft_data_t *list, string file_name) {
    FILE *fp = fopen(file_name, "wb"); 
    if (!fp) {
        printf("\n Error saving aircraft file: %s\n", file_name);
        return;
    }
    aircraft_data_t *current = list;
    while (current) {
        if (fwrite(current, sizeof(aircraft_data_t), 1, fp) != 1) break;
        current = current->next;
    }
    fclose(fp); 
}

void read_aircraft_data_bin(string file_name, aircraft_data_t **list) {
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        printf("\n File %s not found. Starting new database...\n", file_name);
        return;
    }
    *list = NULL;
    size_t read;
    while (1) {
        aircraft_data_t *new_node = (aircraft_data_t*)malloc(sizeof(aircraft_data_t));
        if (!new_node) break;
        read = fread(new_node, sizeof(aircraft_data_t), 1, fp);
        if (read != 1) {
            free(new_node);
            break;
        }
        new_node->next = NULL;
        insert_aircraft_list_end(list, new_node);
    }
    fclose(fp);
}

void save_route_data_bin(route_data_t *list, string file_name) {
    FILE *fp = fopen(file_name, "wb");
    if (!fp) {
        printf("\n Error saving routes file: %s\n", file_name);
        return;
    }
    route_data_t *current = list;
    while (current) {
        if (fwrite(current, sizeof(route_data_t), 1, fp) != 1) break;
        current = current->next;
    }
    fclose(fp);
}

void read_route_data_bin(string file_name, route_data_t **list) {
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        printf("\n File %s not found. Starting new database...\n", file_name);
        return;
    }
    *list = NULL;
    size_t read;
    while (1) {
        route_data_t *new_node = (route_data_t*)malloc(sizeof(route_data_t));
        if (!new_node) break;
        read = fread(new_node, sizeof(route_data_t), 1, fp);
        if (read != 1) {
            free(new_node);
            break;
        }
        new_node->next = NULL;
        insert_route_list_end(list, new_node);
    }
    fclose(fp);
}

void export_aircraft_txt(aircraft_data_t *aircraft_list, string file_name) {
    FILE *fp = fopen(file_name, "w");
    if (!fp) {
        printf("\n Error opening text file: %s\n", file_name);
        return;
    }
    aircraft_data_t *current = aircraft_list;
    while (current) {
        show_aircraft_data(current, fp);
        fprintf(fp, "\n------------------------------\n");
        current = current->next;
    }
    fclose(fp);
    printf("\n Aircraft data exported successfully to TXT.\n");
    printf(" Generated file: %s\n", file_name);
}

void export_aircraft_csv(aircraft_data_t *aircraft_list, string file_name) {
    FILE *fp = fopen(file_name, "w");
    if (!fp) {
        printf("\n Error opening CSV file: %s\n", file_name);
        return;
    }
    fprintf(fp, "ID;REGISTRATION;MODEL;MANUFACTURER;YEAR;TYPE;STATUS;PASSENGERS;CARGO;CREW;MAINTENANCE\n");
    
    aircraft_data_t *current = aircraft_list;
    while (current) {
        fprintf(fp, "%i;%s;%s;%s;%i;%s;%s;%i;%i;%i;%i\n", 
            current->aircraft_id, current->registration, current->model, current->manufacturer, 
            current->manufacture_year, 
            (current->type == CARGO) ? "CARGO" : "PASSENGER", 
            (current->status == OPERATION) ? "OPERATION" : "MAINTENANCE",
            current->num_passengers, current->useful_cargo_qty, 
            current->num_crew, current->maintenance_qty);
        current = current->next;
    }
    fclose(fp);
    printf("\n Aircraft data exported successfully to CSV.\n");
    printf(" Generated file: %s\n", file_name);
}

void export_aircraft_html(aircraft_data_t *aircraft_list, string file_name) {
    FILE *fp = fopen(file_name, "w");
    if (!fp) {
        printf("\n Error opening HTML file: %s\n", file_name);
        return;
    }
    fprintf(fp, "<html><head><meta charset='UTF-8'><style>table{width:100%%;border-collapse:collapse;}th,td{border:1px solid #ddd;padding:8px;text-align:left;}th{background-color:#4CAF50;color:white;}tr:nth-child(even){background-color:#f2f2f2;}</style></head><body>");
    fprintf(fp, "<h1>Aircraft Report</h1><table><tr><th>ID</th><th>Registration</th><th>Model</th><th>Type</th><th>Status</th></tr>");
    
    aircraft_data_t *current = aircraft_list;
    while (current) {
        fprintf(fp, "<tr><td>%i</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>", 
            current->aircraft_id, current->registration, current->model,
            (current->type == CARGO) ? "Cargo" : "Passenger",
            (current->status == OPERATION) ? "In Operation" : "In Maintenance");
        current = current->next;
    }
    fprintf(fp, "</table></body></html>");
    fclose(fp);
    printf("\n Aircraft data exported successfully to HTML.\n");
    printf(" Generated file: %s\n", file_name);
}

void export_routes_txt(route_data_t *route_list, string file_name) {
    FILE *fp = fopen(file_name, "w");
    if (!fp) {
        printf("\n Error opening text file: %s\n", file_name);
        return;
    }
    route_data_t *current = route_list;
    while (current) {
        show_route_data(current, fp);
        fprintf(fp, "\n------------------------------\n");
        current = current->next;
    }
    fclose(fp);
    printf("\n Route data exported successfully to TXT.\n");
    printf(" Generated file: %s\n", file_name);
}

void export_routes_csv(route_data_t *route_list, string file_name) {
    FILE *fp = fopen(file_name, "w");
    if (!fp) {
        printf("\n Error opening CSV file: %s\n", file_name);
        return;
    }
    fprintf(fp, "CODE;AIRCRAFT_ID;DATE;TIME;ORIGIN;DESTINATION;DURATION;FUEL;PASSENGERS;CARGO;CREW\n");
    
    route_data_t *current = route_list;
    while (current) {
        fprintf(fp, "%i;%i;%02i/%02i/%i;%02i:%02i;%s;%s;%.2f;%.2f;%i;%i;%i\n", 
            current->route_code, current->aircraft_id,
            current->date_time.day, current->date_time.month, current->date_time.year,
            current->date_time.hour, current->date_time.min,
            current->departure_location, current->arrival_location,
            current->estimated_time, current->flight_fuel,
            current->passenger_qty, current->useful_cargo, current->member_num);
        current = current->next;
    }
    fclose(fp);
    printf("\n Route data exported successfully to CSV.\n");
    printf(" Generated file: %s\n", file_name);
}

void export_routes_html(route_data_t *route_list, string file_name) {
    FILE *fp = fopen(file_name, "w");
    if (!fp) {
        printf("\n Error opening HTML file: %s\n", file_name);
        return;
    }
    fprintf(fp, "<html><head><meta charset='UTF-8'><style>table{width:100%%;border-collapse:collapse;}th,td{border:1px solid #ddd;padding:8px;text-align:left;}th{background-color:#2196F3;color:white;}tr:nth-child(even){background-color:#f9f9f9;}</style></head><body>");
    fprintf(fp, "<h1>Routes Report</h1><table><tr><th>Code</th><th>Aero ID</th><th>Date/Time</th><th>Origin</th><th>Destination</th></tr>");
    
    route_data_t *current = route_list;
    while (current) {
        fprintf(fp, "<tr><td>%i</td><td>%i</td><td>%02i/%02i/%i %02i:%02i</td><td>%s</td><td>%s</td></tr>", 
            current->route_code, current->aircraft_id,
            current->date_time.day, current->date_time.month, current->date_time.year,
            current->date_time.hour, current->date_time.min,
            current->departure_location, current->arrival_location);
        current = current->next;
    }
    fprintf(fp, "</table></body></html>");
    fclose(fp);
    printf("\n Route data exported successfully to HTML.\n");
    printf(" Generated file: %s\n", file_name);
}