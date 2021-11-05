This program is a command line flight management system.

<h2>Functions:</h2>
<b>print_menu(void)</b>

Inputs: none
Outputs: none

This function is the command line GUI, allowing you to choose between menu options (the other program functions).

<b>check_flight_code(const char flightcode[])</b>
<ul>
  <li><p>Inputs: const flightcode[]: flightcode string e.g. SYD321</p></li>
  <li><p>Outputs: 0 (True), 1 (False)</p></li>
  <li><p>This function checks the flightcode to ensure it is valid. Returns 0 if the flightcode is valid, 1 otherwise.</p></li>
</ul>
<b>add_flight(flight_t flights[MAX_NUM_FLIGHTS], int numFlights)</b>
<ul>
  <li><p>Inputs: flights[]: array of flights of type flight_t, numFlights: integer that store the number of flights in flights[].</p></li>  
  <li><p>Outputs: numFlights: integer that stores the number of current flights.</p></li>
  <li><p>This function adds flights to the flights[] including flightcode, arrival/departure dates and destination city.</p></li>
</ul>

<b>display_flights(flight_t flights[], int numFlights)</b>
<ul>
  <li><p>Inputs: flights[]: array of flights of type flight_t. numFlights: integer that sotres the number of flights in flights[]</p></li>
  <li><p>Outputs: none</p></li>
  <li><p>This function displays flights currently in flights[]. It allows you to display all using * or display by arrival city code.</p></li>
</ul>

<b>save_flights(flight_t flights[MAX_NUM_FLIGHTS], int numFlights)</b>
<ul>
  <li><p>Inputs: flight_t flights[]: Our array of flights. int numFlights: the number of current flights.</p></li>
  <li><p>Outputs: none</p></li>
  <li><p>This function saves current flights to the database file DB_NAME, in regular text format.</p></li>
</ul>

<b>load_flights(flight_t flights[MAX_NUM_FLIGHTS], int numFlights)</b>
<ul>
  <li><p>Inputs: flight_t flights[]: our array of flights. int numFlights: The number of current flights.</p></li>
  <li><p>Outputs: int loadedFlights: the number of flights loaded.</p></li>
  <li><p> This function loads flights from the database into memory.</p></li>
</ul>
