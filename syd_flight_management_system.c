#include <stdio.h> /* printf scanf fopen fclose fprintf fscanf fgets getchar */
#include <string.h> /* strlen strcpy strncpy strcmp */
#include <stdlib.h>

#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"

/******************************************************************************
 * List structs
******************************************************************************/
struct date_time {
    int month, day, hour, minute;
};

typedef struct date_time date_time_t;

struct flight {
    char flightcode[MAX_FLIGHTCODE_LEN+1];
    date_time_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN+1];
    date_time_t arrival_dt;
};

typedef struct flight flight_t;

/******************************************************************************
 * Function prototypes
******************************************************************************/
void print_menu (void);
int add_flight (flight_t flights[], int numFlights);
int check_flight_code (const char flightcode[]);
void display_flights (flight_t flights[], int numFlights);
void save_flights (flight_t flights[MAX_NUM_FLIGHTS], int numFlights);
int load_flights (flight_t flights[MAX_NUM_FLIGHTS], int numFlights);

/******************************************************************************
 * Main
******************************************************************************/
int main(void) {
    flight_t flights[MAX_NUM_FLIGHTS]; /* initalise our flights */
    int numFlights = 0; /* count the number of flights we have */
    int choice = 0; /* menu choice number */

    while (!(choice == 5)) {

        if (choice >= 1 || choice <= 5) {

            print_menu();
            scanf("%d", &choice);

            if (choice == 1) { 
                numFlights = add_flight(flights, numFlights);
            }

            if (choice == 2) { 
                display_flights(flights, numFlights);
            }
            if (choice == 3) { 
                save_flights(flights, numFlights);
            }
            if (choice == 4) { 
                numFlights = load_flights(flights, numFlights);
            }
            if (choice == 5) { /* exit program if choice is 5 */
                return 0;
            }
            if (choice > 5 || choice < 1) {
                printf("Invalid choice\n"); /* input outside 1-5. */
            }

        }
        else { /* input outside 1-5. */
            printf("Invalid choice\n");
        }
    }
    return 0;
}

/******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
******************************************************************************/
void print_menu (void)
{
    printf("\n"
    "1. add a flight\n"
    "2. display all flights to a destination\n"
    "3. save the flights to the database file\n"
    "4. load the flights from the database file\n"
    "5. exit the program\n"
    "Enter choice (number between 1-5)>\n");
}

/******************************************************************************
 * This function checks the flightcode to ensure it is valid. Returns 0 if the
 * flightcode is valid, 1 otherwise.
 * inputs:
 * - const flightcode[]: flightcode string - const because we don't need to
 *                       change it.
 * outputs:
 * - 0: True
 * - 1: False
******************************************************************************/

int check_flight_code (const char flightcode[]) {

    if ((strlen(flightcode) > (MAX_FLIGHTCODE_LEN + 1))) {
        return 1; /* flightcode is longer than MAX_FLIGHTCODE_LEN, invalid. */
    }

        /* Use ASCII Ranges to check that first two chars are between A-Z. */
        if ((flightcode[0] >= 65 && flightcode[0] <= 90) &&
            (flightcode[1] >= 65 && flightcode[1] <= 90)) { 

            /* Use ASCII ranges to check nums are valid, up to max 4 numbers */
            if (strlen(flightcode) == 4 && (flightcode[2] >= 48 && 
                flightcode[2] <= 57)) {
                return 0; /* valid flightcode */
            } 
            else if (strlen(flightcode) == 5 && (flightcode[2] >= 48 && 
                     flightcode[2] <= 57) && (flightcode[3] >= 48 && 
                     flightcode[3] <= 57)) {
                return 0; /* valid flightcode */
            } 
            else if (strlen(flightcode) == 6 && (flightcode[2] >= 48 && 
                     flightcode[2] <= 57) && (flightcode[3] >= 48 && 
                     flightcode[3] <= 57) && (flightcode[4] >= 48 && 
                     flightcode[4] <= 57)) {
                return 0; /* valid flightcode */
            } 
            else if (strlen(flightcode) == 7 && (flightcode[2] >= 48 && 
                     flightcode[2] <= 57) && (flightcode[3] >= 48 && 
                     flightcode[3] <= 57) && (flightcode[4] >= 48 && 
                     flightcode[4] <= 57) && (flightcode[5] >= 48 && 
                     flightcode[5] <= 57)) {
                return 0; /* valid flightcode */
            }
        }
        else {
            return 1; /* chars are not correct, fail.*/
        }
    return 1; /* deafult case - fail. */
}

/******************************************************************************
 * This function adds flights to the flights[] including flightcode, arrival/ 
 * departure dates and destination city.
 * inputs:
 * - flights[]: array of flights of type flight_t
 * - numFlights: integer that stores the number of flights in flights[]
 * outputs:
 * - numFlights: integer that stores the number of flights currently.
******************************************************************************/

int add_flight (flight_t flights[MAX_NUM_FLIGHTS], int numFlights) {
    int check = -1; /* used to check and control for valid input */
    int ch; /* used to clear stdin for fgets */
    char flightcodeTemp[2500]; /* for user input, 2500 for large input */

    if (numFlights <= MAX_NUM_FLIGHTS-1) { /* Ensure max flights is 5. */
        while ((ch = getchar()) != '\n' && ch != EOF); /* clear stdin*/

        while (check < 1) { /* get input flightcode and check validity. */

            printf("Enter flight code>\n");
            fgets(flightcodeTemp, 2500, stdin); /* size 2500 for large input*/

            if (strlen(flightcodeTemp) > 0 && 
                strlen(flightcodeTemp) <= MAX_FLIGHTCODE_LEN + 1) {
                if ((check_flight_code(flightcodeTemp)) == 0) {
                    check = 1;
                    /* use strncpy to copy valid flightcode to new flight */
                    strncpy(flights[numFlights].flightcode, 
                        flightcodeTemp, strlen(flightcodeTemp)-1);
                }
                else {
                    printf("Invalid input\n"); /* Failed check_flight_code */
                    check = 0;
                }
            }
            else {
                printf("Invalid input\n"); /* flightcodeTemp size is wrong. */
                check = 0;
            }
        }

        check = 0;

        /********* DEPARTURE INFO *********/

        printf("Enter departure info for the flight leaving SYD.\n");

        while (check == 0) { /* Get input depature info and check validity. */
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &flights[numFlights].departure_dt.month,
            &flights[numFlights].departure_dt.day, 
            &flights[numFlights].departure_dt.hour, 
            &flights[numFlights].departure_dt.minute);

            /* Ensure dates and times are correct. */
            if ((flights[numFlights].departure_dt.minute >= 0 && 
                flights[numFlights].departure_dt.minute <= 59) &&
                (flights[numFlights].departure_dt.hour >= 0 && 
                flights[numFlights].departure_dt.hour <= 23) &&
                (flights[numFlights].departure_dt.day >= 1 && 
                flights[numFlights].departure_dt.day <= 31) &&
                (flights[numFlights].departure_dt.month >= 1 && 
                flights[numFlights].departure_dt.month <= 12)) {
                check = 1;
            }
            else {
                check = 0;
                printf("Invalid input\n"); /* dates/time incorrect. */
            }
        }

        /********* ARRIVAL CITY *********/

        char arrivalCityTemp[500]; /* for input, size 500 for large input. */
        printf("Enter arrival city code>\n"); /* Get input arrival city from user. */
        scanf("%s", arrivalCityTemp);
        arrivalCityTemp[3] = '\0'; /* Ensure string before copying */
        strncpy(flights[numFlights].arrival_city, arrivalCityTemp, 4);

        check = 0;

        /********* ARRIVAL INFO *********/

        printf("Enter arrival info.\n");

        while (check == 0) { /* Get input arrival info from user and check if its valid. */
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &flights[numFlights].arrival_dt.month, 
            &flights[numFlights].arrival_dt.day, &flights[numFlights].arrival_dt.hour, 
            &flights[numFlights].arrival_dt.minute);

            /* Ensure dates and times are correct. */
            if ((flights[numFlights].arrival_dt.minute >= 0 && flights[numFlights].arrival_dt.minute <= 59) &&
                (flights[numFlights].arrival_dt.hour >= 0 && flights[numFlights].arrival_dt.hour <= 23) &&
                (flights[numFlights].arrival_dt.day >= 1 && flights[numFlights].arrival_dt.day <= 31) &&
                (flights[numFlights].arrival_dt.month >= 1 && flights[numFlights].arrival_dt.month <= 12)) {
                check = 1;
                numFlights = numFlights + 1;
            }
            else {
                check = 0;
                printf("Invalid input\n"); /* dates/time incorrect. */
            }
        }
    }
    else { /* We already have the max number of flights. */
        printf("Cannot add more flights - memory full\n");
    }

    return numFlights;

}

/******************************************************************************
 * This function displays flights currently in flights[]. It allows you to
 * display all using '*' or display by arrival city code.
 * inputs:
 * - flights[]: array of flights of type flight_t
 * - numFlights: integer that stores the number of flights in flights[]
 * outputs:
 * - none
******************************************************************************/
void display_flights (flight_t flights[], int numFlights) {

    char selectCityCode[100]; /* For user input, large incase input is large.*/
    int i, alreadyPrinted; /* iterator, checker */

    printf("Enter arrival city code or enter * to show all destinations>\n");
    scanf("%s", selectCityCode);

    if (selectCityCode[0] == '*' && numFlights > 0) { /* display all flights */

        printf("Flight Origin          Destination\n");
        printf("------ --------------- ---------------\n");

        for( i = 0; i < numFlights; i++) {
            printf("%-6s %s %.2d-%.2d %.2d:%.2d %-3s %.2d-%.2d %.2d:%.2d\n",
                flights[i].flightcode, "SYD", flights[i].departure_dt.month,
                flights[i].departure_dt.day, flights[i].departure_dt.hour,
                flights[i].departure_dt.minute, flights[i].arrival_city,
                flights[i].arrival_dt.month, flights[i].arrival_dt.day,
                flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
        }
    }
    else if (numFlights > 0) { /* for input other than '*' */
        alreadyPrinted = 1;

        for ( i = 0; i < numFlights; i++) {
            if (strcmp(selectCityCode, flights[i].arrival_city) == 0) {

                if (alreadyPrinted == 1) {
                    printf("Flight Origin          Destination\n");
                    printf("------ --------------- ---------------\n");
                    alreadyPrinted = 0;
                }

                printf("%-6s %s %.2d-%.2d %.2d:%.2d %-3s %.2d-%.2d %.2d:%.2d\n",
                    flights[i].flightcode, "SYD", flights[i].departure_dt.month,
                    flights[i].departure_dt.day, flights[i].departure_dt.hour,
                    flights[i].departure_dt.minute, flights[i].arrival_city,
                    flights[i].arrival_dt.month, flights[i].arrival_dt.day,
                    flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
            }

        }
        if (alreadyPrinted == 1) { /* No matches found */
            printf("No flights\n");
        }
    }
    else { /* catch all and if there are no flights */
        printf("No flights\n");
    }    
}

/*************************************************************************
* This function saves current flights to the database file "database", 
* in regular text format.
* inputs: 
* - flight_t flights[]: our array of flights.
* - int numFlights: the number of current flights.
* outputs:
* - none
*************************************************************************/

void save_flights (flight_t flights[MAX_NUM_FLIGHTS], int numFlights) {

    int i; /* iterator */
    FILE *fp = NULL;

    fp = fopen(DB_NAME, "w"); /* Open the file in write mode, to save flights.*/

    if (fp == NULL) { /* Check for an error in file opening.*/
        printf("Write error\n");
    }

    if (fp) {

        for (i = 0; i < numFlights; i++) { /* Write flights to database file. */

            fprintf(fp, "%s SYD %02d %02d %02d %02d %s %02d %02d %02d %02d\n",
                flights[i].flightcode, flights[i].departure_dt.month,
                flights[i].departure_dt.day, flights[i].departure_dt.hour,
                flights[i].departure_dt.minute, flights[i].arrival_city,
                flights[i].arrival_dt.month, flights[i].arrival_dt.day,
                flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
        }
    }
    else {
        printf("Write error\n");
    }

    fclose(fp); /* Close the database file stream */
}

/******************************************************************************
* This function loads flights from the database file "database".
* input:
* - flight_t flights[]: our array of flights.
* - int numFlights: the number of current flights.
* output:
* - int loadedFlights: the number of flights we loaded.
******************************************************************************/
int load_flights (flight_t flights[MAX_NUM_FLIGHTS], int numFlights) {

    int loadedFlights = 0; /* number of flights we load */
    FILE *fp;

    fp = fopen(DB_NAME, "r"); /* Open the database file stream, read mode */

    if (fp == NULL) { /* Check for an error in file opening.*/
        printf("Read error\n");
        return 0;
    }

    if (fp) {
    
        /* fscanf until we reach an empty line*/
        while (fscanf(fp,"%s SYD %02d %02d %02d %02d %s %02d %02d %02d %02d\n", 
            flights[numFlights].flightcode, &flights[numFlights].departure_dt.month,
            &flights[numFlights].departure_dt.day, &flights[numFlights].departure_dt.hour,
            &flights[numFlights].departure_dt.minute, flights[numFlights].arrival_city,
            &flights[numFlights].arrival_dt.month, &flights[numFlights].arrival_dt.day,
            &flights[numFlights].arrival_dt.hour, 
            &flights[numFlights].arrival_dt.minute) != EOF) {

            loadedFlights = loadedFlights + 1;
        }
    }
    else {
        printf("Read error\n");
        return 0;
    }
    fclose(fp); /* Close the database file stream */
    return loadedFlights;
}
