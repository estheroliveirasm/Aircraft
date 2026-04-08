#include "../include/menus.h"
#include "../include/utils.h"
#include "../include/types.h"
#include <stdio.h>

int main_menu()
{
    int opt;
    clear_screen();
    printf("..........MAIN MENU..........\n");
    printf(" 1. Registration (Aircraft or Route)\n");
    printf(" 2. Reports\n");
    printf(" 3. Searches and Consultations\n");
    printf(" 4. Change aircraft status\n");
    printf(" 5. Maintenance history\n");
    printf(" 6. Files and Export\n");
    printf(" 0. Exit program\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int registration_menu()
{
    int opt;
    clear_screen();
    printf("............REGISTRATION.............\n");
    printf(" 1. Register new aircraft\n");
    printf(" 2. Register new route\n");
    printf(" 0. Back to main menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int reports_menu()
{
    int opt;
    clear_screen();
    printf("...........REPORTS............\n");
    printf(" 1. List all aircraft\n");
    printf(" 2. List all routes\n");
    printf(" 3. Routes with most passengers\n");
    printf(" 4. Routes with least passengers\n");
    printf(" 0. Back to main menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int search_choice_menu()
{
    int opt;
    clear_screen();
    printf(".......SEARCHES AND CONSULTATIONS........\n");
    printf(" 1. Aircraft\n");
    printf(" 2. Routes\n");
    printf(" 3. Statistics\n");
    printf(" 0. Back to main menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int aircraft_search_menu()
{
    int opt;
    clear_screen();
    printf("...........AIRCRAFT.............\n");
    printf(" 1. Search by registration\n");
    printf(" 2. List by manufacturer\n");
    printf(" 3. List by type\n");
    printf(" 4. List by model\n");
    printf(" 5. List by manufacture year\n");
    printf(" 6. List by current status\n");
    printf(" 0. Back to previous menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int route_search_menu()
{
    int opt;
    clear_screen();
    printf("..............ROUTES..............\n");
    printf(" 1. Consult route by date\n");
    printf(" 2. Consult route by origin\n");
    printf(" 3. Consult route by destination\n");
    printf(" 4. Temporal status (Past/Future)\n");
    printf(" 0. Back to previous menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int statistics_menu()
{
    int opt;
    clear_screen();
    printf("..........STATISTICS...........\n");
    printf(" 1. Total fuel consumption\n");
    printf(" 2. Flight percentage by aircraft\n");
    printf(" 3. Flight percentage by destination\n");
    printf(" 0. Back to previous menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int files_menu()
{
    int opt;
    clear_screen();
    printf("......FILES AND EXPORT......\n");
    printf(" 1. Save data (Binary)\n");
    printf(" 2. Export Aircraft (TXT/CSV/HTML)\n");
    printf(" 3. Export Routes (TXT/CSV/HTML)\n");
    printf(" 0. Back to previous menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int export_aircraft_menu()
{
    int opt;
    clear_screen();
    printf(".......EXPORT AIRCRAFT........\n");
    printf(" 1. TXT Format\n");
    printf(" 2. CSV Format\n");
    printf(" 3. HTML Format\n");
    printf(" 0. Back to previous menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}

int export_routes_menu()
{
    int opt;
    clear_screen();
    printf(".........EXPORT ROUTES.........\n");
    printf(" 1. TXT Format\n");
    printf(" 2. CSV Format\n");
    printf(" 3. HTML Format\n");
    printf(" 0. Back to previous menu\n");
    printf(" Option: ");
    scanf("%d", &opt);
    getchar();
    return opt;
}