This program is a command line flight management system.

Functions:
print_menu(void)

Inputs: none
Outputs: none

This function is the command line GUI, allowing you to choose between menu options (the other program functions).

check_flight_code(const char flightcode[])
Inputs: const flightcode[]: flightcode string e.g. SYD321
Outputs: 0 (True), 1 (False)

This function checks the flightcode to ensure it is valid. Returns 0 if the flightcode is valid, 1 otherwise.

add_flight(flight_t flights[MAX_NUM_FLIGHTS], int numFlights)

Inputs: flights[]: array of flights of type flight_t, numFlights: integer that store the number of flights in flights[].
Outputs: numFlights: integer that stores the number of current flights.

This function adds flights to the flights[] including flightcode, arrival/departure dates and destination city.

display_flights(flight_t flights[], int numFlights)

Inputs: flights[]: array of flights of type flight_t. numFlights: integer that sotres the number of flights in flights[]
Outputs: none

This function displays flights currently in flights[]. It allows you to display all using * or display by arrival city code.

save_flights(flight_t flights[MAX_NUM_FLIGHTS], int numFlights)
Inputs: flight_t flights[]: Our array of flights. int numFlights: the number of current flights.
Outputs: none

This function saves current flights to the database file DB_NAME, in regular text format.

load_flights(flight_t flights[MAX_NUM_FLIGHTS], int numFlights)

Inputs: flight_t flights[]: our array of flights. int numFlights: The number of current flights.
Outputs: int loadedFlights: the number of flights loaded.
