#include "include/types.h"
#include "include/menus.h"
#include "include/registrations.h"
#include "include/reports.h"
#include "include/searches.h"
#include "include/files.h"
#include "include/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

int main ()
{
    aircraft_data_t *aircraft_list = NULL;
    route_data_t *route_list = NULL;
    int main_opt, sub_opt, sub_sub_opt; 
    char file_name[STR_SIZE];
    
    read_aircraft_data_bin(AIRCRAFT_FILE, &aircraft_list);
    read_route_data_bin(ROUTES_FILE, &route_list);
    
    do { 
        main_opt = main_menu();

        switch (main_opt) {
            case 1: 
                do {
                    sub_opt = registration_menu();
                    if(sub_opt == 1) {
                        aircraft_data_t *new_node = new_aircraft();
                        if(new_node != NULL) {
                            insert_aircraft_list_end(&aircraft_list, new_node);
                            message("Success: Aircraft registered.");
                        }
                    } else if(sub_opt == 2) {
                        route_data_t *new_node = new_route(aircraft_list); 
                        if(new_node != NULL){
                            insert_route_list_end(&route_list, new_node);
                            message("Success: Route registered.");
                        }
                    }
                } while (sub_opt != 0);
                break;

            case 2:
                do {
                    sub_opt = reports_menu();
                    if (sub_opt != 0) {
                        clear_screen();
                        switch (sub_opt) {
                            case 1: aircraft_report(aircraft_list, stdout); break;
                            case 2: routes_report(route_list, stdout); break;
                            case 3: list_routes_highest_passengers(route_list, stdout); break;
                            case 4: list_routes_lowest_passengers(route_list, stdout); break;
                        }
                    }
                } while (sub_opt != 0);
                break;

            case 3: 
                do {
                    sub_opt = search_choice_menu();
                    if(sub_opt == 1) { 
                        do {
                            sub_sub_opt = aircraft_search_menu();
                            switch (sub_sub_opt) {
                                case 1: search_aircraft_by_registration(aircraft_list); break;
                                case 2: list_aircraft_by_manufacturer(aircraft_list); break;
                                case 3: list_aircraft_by_type(aircraft_list); break;
                                case 4: list_aircraft_by_model(aircraft_list); break;
                                case 5: list_aircraft_by_manufacture_year(aircraft_list); break;
                                case 6: list_aircraft_by_status(aircraft_list); break;
                            }
                            if(sub_sub_opt != 0) message("Search finished.");
                        } while (sub_sub_opt != 0);
                    } 
                    else if (sub_opt == 2) {
                        do {
                            sub_sub_opt = route_search_menu();
                            switch (sub_sub_opt) {
                                case 1: search_route_by_date(route_list); break;
                                case 2: search_route_by_origin(route_list); break;
                                case 3: search_route_by_destination(route_list); break;
                                case 4: list_routes_by_temporal_status(route_list); break;
                            }
                            if(sub_sub_opt != 0) message("Search finished.");
                        } while (sub_sub_opt != 0);
                    }
                    else if (sub_opt == 3) {
                        do {
                            sub_sub_opt = statistics_menu();
                            switch (sub_sub_opt) {
                                case 1: total_fuel_consumption_by_date(route_list); break;
                                case 2: flight_percentage_by_aircraft(route_list, aircraft_list); break;
                                case 3: flight_percentage_by_destination_and_date(route_list); break;
                            }
                            if(sub_sub_opt != 0) message("Statistics generated.");
                        } while (sub_sub_opt != 0);
                    }
                } while (sub_opt != 0);
                break;

            case 4:
                change_aircraft_status(&aircraft_list);
                break;

            case 5: 
                search_maintenance_count_by_aircraft(aircraft_list);
                break;

            case 6: 
                do {
                    sub_opt = files_menu();
                    if (sub_opt == 1) {
                        save_aircraft_data_bin(aircraft_list, AIRCRAFT_FILE);
                        save_route_data_bin(route_list, ROUTES_FILE);
                        message("Success: Data saved in binary.");
                    } 
                    else if (sub_opt == 2) { 
                        do {
                            sub_sub_opt = export_aircraft_menu();
                            if (sub_sub_opt >= 1 && sub_sub_opt <= 3) {
                                printf(" File name (without extension).....: ");
                                fgets(file_name, STR_SIZE, stdin);
                                remove_newline(file_name);

                                if (sub_sub_opt == 1) { strcat(file_name, ".txt"); export_aircraft_txt(aircraft_list, file_name); }
                                else if (sub_sub_opt == 2) { strcat(file_name, ".csv"); export_aircraft_csv(aircraft_list, file_name); }
                                else if (sub_sub_opt == 3) { strcat(file_name, ".html"); export_aircraft_html(aircraft_list, file_name); }
                                message("Success: Export completed.");
                            }
                        } while (sub_sub_opt != 0);
                    } 
                    else if (sub_opt == 3) { 
                        do {
                            sub_sub_opt = export_routes_menu();
                            if (sub_sub_opt >= 1 && sub_sub_opt <= 3) {
                                printf(" File name (without extension).....: ");
                                fgets(file_name, STR_SIZE, stdin);
                                remove_newline(file_name);

                                if (sub_sub_opt == 1) { strcat(file_name, ".txt"); export_routes_txt(route_list, file_name); }
                                else if (sub_sub_opt == 2) { strcat(file_name, ".csv"); export_routes_csv(route_list, file_name); }
                                else if (sub_sub_opt == 3) { strcat(file_name, ".html"); export_routes_html(route_list, file_name); }
                                message("Success: Export completed.");
                            }
                        } while (sub_sub_opt != 0);
                    }
                } while (sub_opt != 0);
                break;

            case 0: 
                printf("\n Finalizing system and saving data...\n");
                save_aircraft_data_bin(aircraft_list, AIRCRAFT_FILE);
                save_route_data_bin(route_list, ROUTES_FILE);
                printf(" Database updated successfully.\n");
                break;
        }

    } while (main_opt != 0);

    return 0;
}