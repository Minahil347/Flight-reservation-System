#include <iostream>     // For input/output operations
#include <windows.h>    // For system functions like clearing screen
#include <stdlib.h>     // For system-related functions like exit
#include <string>       // For string usage
#include <fstream>      // For file handling
#include <sstream>      // For string stream operations

using namespace std;

// --- User Registration Arrays ---
string registeredCNICs[100];         // Stores registered user CNICs
string registeredNames[100];         // Stores registered user names
string registeredPhones[100];        // Stores registered user phone numbers
string registeredPasswords[100];     // Stores registered user passwords

// --- Booking Information Arrays ---
string bookingUsers[100];            // Stores CNICs of users who booked
string bookingTravelers[100];        // Stores CNICs of individual travelers

// --- Traveler Details Arrays ---
string travelerNames[100];           // Full names of travelers
string travelerDOB[100];             // Date of birth of travelers
string travelerPassport[100];        // Passport or ID numbers
string travelerNationality[100];     // Nationality of travelers
string travelerEmail[100];           // Email of travelers
string travelerPhone[100];           // Contact number of travelers

// --- Flight Data ---
const int flightCount = 5;   // Total number of flights

// Departure and arrival cities
string travelerDepCity[flightCount] = {"Lahore", "Islamabad", "Karachi", "Peshawar", "Multan"};
string travelerArrCity[flightCount] = {"Karachi", "Dubai", "London", "Doha", "Istanbul"};

// Departure and arrival airports
string travelerDepAirport[flightCount] = {
    "Allama Iqbal International Airport",
    "Islamabad International Airport",
    "Jinnah International Airport",
    "Bacha Khan International Airport",
    "Multan International Airport"
};

string travelerArrAirport[flightCount] = {
    "Jinnah International Airport",
    "Dubai International Airport",
    "London City Airport",
    "Hamad International Airport",
    "Istanbul Airport"
};

// Flight route names (used for display)
const char* flightRoutes[flightCount] = {
    "Lahore    ---->  Karachi",
    "Islamabad ---->  Dubai",
    "Karachi   ---->  London",
    "Peshawar  ---->  Doha",
    "Multan    ---->  Istanbul"
};

// Arrival and departure timings for flights
string arrivalTimes[flightCount] = {
    "10:30  AM - 15/06/2025",
    "03:00  PM - 16/06/2025",
    "06:45  AM - 15/06/2025",
    "09:15  PM - 16/06/2025",
    "01:50  PM - 18/06/2025"
};

string flightTimings[flightCount] = {
    "12:30  PM - 15/06/2025",
    "07:00  PM - 16/06/2025",
    "01:45  PM - 15/06/2025",
    "12:30  AM - 17/06/2025",
    "06:10  PM - 18/06/2025"
};

// Ticket prices for each flight
float ticketPrices[flightCount] = {15000, 45000, 75000, 65000, 90000};

// --- Booking-related Variables ---
int bookingFlights[100];        // Stores flight numbers for each booking
int totalSeats[5] = {200, 150, 100, 80, 180};   // Total seats available per flight
int bookedSeats[5] = {0, 0, 0, 0, 0};           // Number of seats booked per flight
int flightNumbers[5] = {100, 101, 102, 103, 104};  // Unique flight numbers

// --- Counters and State Control ---
int userCount = 0;              // Number of users registered
int bookingCount = 0;           // Number of bookings made
int execution = 1;              // Used to control main loop
string loggedInCNIC = "";       // Stores CNIC of currently logged-in user


// This function clears the console screen
void clearScreen() 
{
    system("CLS"); // Works on Windows to clear the screen
}

// This function pauses the program until the user presses 0 to go back
void pauseScreen() 
{
    int back = 1;

    // Keep asking until user enters 0
    while (back != 0)
    {
        cout << "\n\nPress 0 to go back: ";
        cin >> back;
    }

    // Once user enters 0, clear the screen
    clearScreen();
}

void showMenu() 
{
    clearScreen();
    cout << "\n========================================================================================================================\n\n";
    cout << "                                          FLIGHT RESERVATION SYSTEM\n\n";
    cout << "========================================================================================================================\n\n";
    if (execution == 1){
    	cout << "		Welcome to Flight Reservation!\n\n";
    	cout << "========================================================================================================================\n\n";
	}
    cout << "                                                  MAIN MENU\n\n";
	cout << "========================================================================================================================\n\n";
    cout << "		1.	Display Available Flights\n\n";
    cout << "		2.	Book Ticket\n\n";
    cout << "		3. 	Cancel Reservation\n\n";
    cout << "		4.	View Booked Flights\n\n";
    cout << "		5. 	Logout\n\n";
    cout << "========================================================================================================================\n\n";
    cout << "		Enter your choice: ";
}

void accountMenu()
{
	clearScreen();
	cout << "\n========================================================================================================================\n\n";
    cout << "                                          FLIGHT RESERVATION SYSTEM\n";
    cout << "\n========================================================================================================================\n\n";
    cout << " 1. Login\n\n";
    cout << " 2. Sign Up\n\n";
    cout << " 3. Exit\n";
    cout << "\n========================================================================================================================\n";
	cout << "\nChoose an option: ";
}

// Finds the index of a flight based on flight number
// Returns the index if found, otherwise returns -1
int findFlightIndex(int flightNum) 
{
    for (int i = 0; i < flightCount; i++) 
    {
        if (flightNumbers[i] == flightNum) 
        {
            return i; // Flight found
        }
    }
    return -1; // Flight not found
}

// Saves all booked ticket information to a file
void saveBookings() 
{
    ofstream out("bookings.txt"); // Open file for writing

    for (int i = 0; i < bookingCount; i++) 
    {
        // Write each booking's details separated by commas
        out << bookingUsers[i] << "," << bookingTravelers[i] << "," << travelerNames[i] << ","
            << travelerDOB[i] << "," << travelerPassport[i] << "," << travelerNationality[i] << ","
            << travelerEmail[i] << "," << travelerPhone[i] << "," << bookingFlights[i] << "\n";
    }

    out.close(); // Close the file after writing
}

// Loads all booking data from file into arrays
void loadBookings()
{
    ifstream in("bookings.txt"); // Open file for reading
    bookingCount = 0; // Reset booking count

    string line;

    while (getline(in, line)) // Read each line from file
    {
        stringstream ss(line); // Create a stream from the line

        // Read and store each value separated by commas
        getline(ss, bookingUsers[bookingCount], ',');
        getline(ss, bookingTravelers[bookingCount], ',');
        getline(ss, travelerNames[bookingCount], ',');
        getline(ss, travelerDOB[bookingCount], ',');
        getline(ss, travelerPassport[bookingCount], ',');
        getline(ss, travelerNationality[bookingCount], ',');
        getline(ss, travelerEmail[bookingCount], ',');
        getline(ss, travelerPhone[bookingCount], ',');

        // Get flight number as string and convert to integer
        string flightNoStr;
        getline(ss, flightNoStr, ',');

        try {
            bookingFlights[bookingCount] = stoi(flightNoStr); // Convert to int
        } 
        catch (...) 
        {
            // If conversion fails, show error and skip to next line
            cout << "Error converting flight number to integer at line: " << line << endl;
            continue;
        }

        bookingCount++; // Move to next booking
    }

    in.close(); // Close the file after reading
}

// Checks if a traveler has already booked a specific flight
// Returns true if the traveler has a booking on the given flight, otherwise false
bool bookingExists(string travelerCNIC, int flightNum) 
{
    for (int i = 0; i < bookingCount; i++) 
    {
        // Compare both traveler CNIC and flight number
        if (bookingTravelers[i] == travelerCNIC && bookingFlights[i] == flightNum)
            return true; // Booking found
    }
    return false; // No such booking found
}

// Saves the current number of booked seats for each flight into a file
void saveBookedSeats() 
{
    ofstream fout("booked.txt"); // Open file to write seat data

    for (int i = 0; i < 5; i++) 
    {
        fout << bookedSeats[i] << endl; // Write one value per line
    }

    fout.close(); // Close the file
}

// Loads the number of booked seats for each flight from the file
void loadBookedSeats() 
{
    ifstream fin("booked.txt"); // Open file to read seat data

    for (int i = 0; i < 5; i++) 
    {
        // Try reading a number; if it fails (file corrupted or missing), default to 0
        if (!(fin >> bookedSeats[i])) 
        {
            bookedSeats[i] = 0;
        }
    }

    fin.close(); // Close the file
}

// Function to log in a user
bool login() 
{
    clearScreen(); // Clear the console
    
    cout << "\n========================================================================================================================\n\n";
    cout << "                                                  LOGIN\n";
    cout << "\n========================================================================================================================\n\n";

    // Ask for CNIC and password
    string cnic, password;
    cout << "\nEnter CNIC: ";
    cin >> cnic;
    cout << "\nEnter Password: ";
    cin >> password;

    // Loop through all registered users to find a match
    for (int i = 0; i < userCount; i++) 
	{
        // If both CNIC and password match, login is successful
        if (registeredCNICs[i] == cnic && registeredPasswords[i] == password) 
		{
            loggedInCNIC = cnic; // Store logged-in user's CNIC
            cout << "\nWelcome back, " << registeredNames[i] << "!\n";
    		sleep(2); // Pause briefly before continuing
            return true; // Login success
        }
    }

    // If no match found, show error
    cout << "\nLogin failed. CNIC or password incorrect.\n";
    sleep(2); // Pause briefly before going back
    return false; // Login failed
}

// Function to sign up a new user
void signUp()
{
    clearScreen(); // Clear the console

    cout << "\n========================================================================================================================\n\n";
    cout << "                                                  SIGN UP\n";
    cout << "\n========================================================================================================================\n\n";

	string cnic;
    cout << "Enter CNIC: ";
    cin >> cnic;

    // Check if the CNIC already exists
    for (int i = 0; i < userCount; i++)
	{
        if (registeredCNICs[i] == cnic) 
		{
            cout << "\nUser already exists. Try logging in.\n";
            sleep(2); // Pause before returning
            return; // Don't allow duplicate CNIC
        }
    }

    // Get the rest of the user details
    cin.ignore(); // Clear input buffer for getline
    string name, phone, password;
    cout << "\nEnter Full Name: ";
    getline(cin, name);
    cout << "\nEnter Phone: ";
    getline(cin, phone);
    cout << "\nSet Password: ";
    getline(cin, password);

    // Store user info in arrays
    registeredCNICs[userCount] = cnic;
    registeredNames[userCount] = name;
    registeredPhones[userCount] = phone;
    registeredPasswords[userCount] = password;
    userCount++; // Increase total user count

    // Save all users to file
    ofstream out("users.txt");
    for (int i = 0; i < userCount; i++) 
	{
        out << registeredCNICs[i] << "\n" << registeredNames[i] << "\n"
            << registeredPhones[i] << " " << registeredPasswords[i] << "\n\n";
    }
    out.close(); // Close the file

    cout << "\nAccount created successfully!\n";
    sleep(2); // Pause before returning
    return;
}

// Function to load registered user data from file into arrays
void loadUsers() {
    ifstream in("users.txt");  // Open the file for reading
    userCount = 0;             // Reset user count before loading

    // Loop until end of file is reached
    while (getline(in, registeredCNICs[userCount])) 
	{
        getline(in, registeredNames[userCount]);                       // Read full name (may include spaces)
        in >> registeredPhones[userCount] >> registeredPasswords[userCount]; // Read phone and password from the same line
        in.ignore();   // Skip the remaining newline after phone and password
        in.ignore();   // Skip the blank line between user records (if present)
        userCount++;   // Move to the next user slot
    }
    in.close();  // Close the file after reading
}


// Function to display all available flights in a formatted way
void AvailableFlights()
{
	clearScreen();  // Clear the console

    cout << "\n========================================================================================================================\n\n";
    cout << "                                          Available Flights\n";
	cout << "\n========================================================================================================================\n\n";
    cout << " Flight No              Route                  Arrival - Date         Departure - Date       Seats Left	  Ticket Price\n";
    cout << "========================================================================================================================\n\n";

    bool found = false;  // Track if any available flights are found

    // Loop through all flights
    for (int i = 0; i < flightCount; i++) 
	{
        int available = totalSeats[i] - bookedSeats[i];  // Calculate how many seats are left

        if (available > 0)  // Only show flights that still have available seats
		{
            cout <<"    " << flightNumbers[i];

            // Align spacing depending on number of digits in flight number
            if (flightNumbers[i] < 10)
                cout << "         "; 
            else if (flightNumbers[i] < 100)
                cout << "        "; 
            else  
                cout << "       "; 

            // Print flight route and align spacing
            cout << flightRoutes[i];
            int routeLen = 0;
            while (flightRoutes[i][routeLen] != '\0') routeLen++;
            for (int j = routeLen; j < 28; j++) cout << " ";
            cout << "  ";

            // Print arrival time and align
            cout << " " << arrivalTimes[i];
            int arrivalLen = 0;
            while (arrivalTimes[i][arrivalLen] != '\0') arrivalLen++;
            for (int j = arrivalLen; j < 15; j++) cout << " ";
            cout << "   ";
            
            // Print departure time and align
			cout << flightTimings[i];
            int timeLen = 0;
            while (flightTimings[i][timeLen] != '\0') timeLen++;
            for (int j = timeLen; j < 20; j++) cout << " ";
            cout << "     ";

            // Print available seats and align
            cout << available;
            int temp = available, digits = 0;
            if (temp == 0)
                digits = 1;
            else 
                while (temp) { digits++; temp /= 10; }

            for (int j = digits; j < 10; j++) cout << " ";

            // Print ticket price
            cout << "  Rs." << ticketPrices[i] << "\n";

            // Add spacing for neat output
            for (int j = digits; j < 10; j++) cout << " ";
            cout << "\n";

            found = true;  // Mark that we found at least one flight
        }
    }

    // If no flights were found
    if (!found)
        cout << "No available flights.\n";

    cout << "========================================================================================================================\n\n";

    pauseScreen();  // Wait for user input to go back
}

void bookTicket() 
{
    clearScreen();    // Clear the console
    cout << "\n========================================================================================================================\n\n";
    cout << "                                          Ticket Booking\n";
    cout << "\n========================================================================================================================\n\n";

    int flightNum;
    cout << "Enter flight number to book: ";
    cin >> flightNum;

    // Find the index of the flight
    int foundIndex = findFlightIndex(flightNum);

    // If flight is not found, show error and return
    if (foundIndex == -1) 
    {
        cout << "Flight not found!\n";
        pauseScreen();
        return;
    }

    // Check if seats are available for booking
    if (totalSeats[foundIndex] - bookedSeats[foundIndex] <= 0) 
    {
        cout << "No seats available.\n";
        pauseScreen();
        return;
    }

    cin.ignore();    // Clear input buffer

    cout << "\n--- Enter Traveler Details ---\n";

    string travelerCNIC;
    cout << "\nEnter CNIC of the traveler: ";
    cin >> travelerCNIC;
    cin.ignore();

    // Check if a booking already exists for this traveler on this flight
    if (bookingExists(travelerCNIC, flightNum)) 
    {
        cout << "\nYou have already booked flight " << flightNum << " against CNIC: " << travelerCNIC << ".\n";
        pauseScreen();
        return;
    }

    // Collect traveler-specific details
    cout << "\nFull Name: ";
    getline(cin, travelerNames[bookingCount]);

    cout << "\nDate of Birth (DD/MM/YYYY): ";
    getline(cin, travelerDOB[bookingCount]);

    cout << "\nPassport/ID Number: ";
    getline(cin, travelerPassport[bookingCount]);

    cout << "\nNationality: ";
    getline(cin, travelerNationality[bookingCount]);

    cout << "\nEmail: ";
    getline(cin, travelerEmail[bookingCount]);

    cout << "\nPhone: ";
    getline(cin, travelerPhone[bookingCount]);

    // Store booking information
    bookingUsers[bookingCount] = loggedInCNIC;
    bookingTravelers[bookingCount] = travelerCNIC;
    bookingFlights[bookingCount] = flightNum;

    // Update booked seats for the selected flight
    bookedSeats[foundIndex]++;
    saveBookedSeats();    // Persist booked seat data to file

    bookingCount++;       // Increase booking counter
    saveBookings();       // Save all updated booking data

    cout << "\nBooking Successful!\n";
    pauseScreen();        // Wait for user input before returning
}

void cancelReservation() 
{
    clearScreen();    // Clear console screen
    cout << "\n========================================================================================================================\n\n";
    cout << "                                              Cancellation\n";
    cout << "\n========================================================================================================================\n\n";

    string travelerCNIC;
    cout << "\nEnter CNIC of the traveler: ";
    cin >> travelerCNIC;

    int flightNum;
    cout << "\nEnter flight number to cancel: ";
    cin >> flightNum;

    bool found = false;    // Flag to track if booking was found

    for (int i = 0; i < bookingCount; i++) 
    {
        // Check if this booking belongs to the logged-in user and matches the CNIC and flight number
        if (bookingUsers[i] == loggedInCNIC && bookingTravelers[i] == travelerCNIC && bookingFlights[i] == flightNum) 
        {
            // Display booking details
            cout << "\n--- Booking Found ---\n";
            cout << "\nTraveler Name: " << travelerNames[i];
            cout << "\nDOB: " << travelerDOB[i];
            cout << "\nPassport/ID: " << travelerPassport[i];
            cout << "\nNationality: " << travelerNationality[i];
            cout << "\nEmail: " << travelerEmail[i];
            cout << "\nPhone: " << travelerPhone[i];

            char confirm;
            cout << "\n\nAre you sure you want to cancel this reservation? (Y/N): ";
            cin >> confirm;

            // If user confirms cancellation
            if (confirm == 'Y' || confirm == 'y') 
            {
                // Decrease booked seat count for the flight
                int foundIndex = findFlightIndex(flightNum);
                if (foundIndex != -1) 
                {
                    bookedSeats[foundIndex]--;
                    saveBookedSeats();
                }

                // Shift remaining bookings up in the array to overwrite this one
                for (int j = i; j < bookingCount - 1; j++) 
                {
                    bookingUsers[j] = bookingUsers[j + 1];
                    bookingTravelers[j] = bookingTravelers[j + 1];
                    travelerNames[j] = travelerNames[j + 1];
                    travelerDOB[j] = travelerDOB[j + 1];
                    travelerPassport[j] = travelerPassport[j + 1];
                    travelerNationality[j] = travelerNationality[j + 1];
                    travelerEmail[j] = travelerEmail[j + 1];
                    travelerPhone[j] = travelerPhone[j + 1];
                    bookingFlights[j] = bookingFlights[j + 1];
                }

                bookingCount--;    // Reduce total booking count
                saveBookings();    // Save updated booking data

                cout << "\nReservation cancelled successfully!\n";
            } 
            else 
            {
                cout << "\nCancellation aborted.\n";
            }

            found = true;    // Booking was found and handled
            break;
        }
    }

    // If no matching booking was found
    if (!found) 
    {
        cout << "\nNo reservation found for the provided details.\n";
    }

    pauseScreen();    // Wait for user input before returning
}

void viewBookedFlights() 
{
    clearScreen();    // Clear console
    cout << "\n========================================================================================================================\n\n";
    cout << "                                         Your Booked Flights\n";
    cout << "\n========================================================================================================================\n\n";

    loadBookings();   // Load bookings from file
    bool found = false;

    for (int i = 0; i < bookingCount; i++) 
    {
        // Show only bookings made by the currently logged-in user
        if (bookingUsers[i] == loggedInCNIC) 
        {
            found = true;
            cout << "\n--- Ticket #" << i + 1 << " ---\n";
            cout << "\nCNIC: " << bookingTravelers[i];
            cout << "\nFlight No: " << bookingFlights[i];
            cout << "\nName: " << travelerNames[i];
            cout << "\nDOB: " << travelerDOB[i];
            cout << "\nPassport/ID: " << travelerPassport[i];
            cout << "\nNationality: " << travelerNationality[i];
            cout << "\nEmail: " << travelerEmail[i];
            cout << "\nPhone: " << travelerPhone[i];

            // Find flight details based on flight number
            int j = 0;
            while (j < 5)
            {
                if (bookingFlights[i] == flightNumbers[j])
                    break;
                j++;
            }

            // Display corresponding flight info
            cout << "\nFrom: " << travelerDepCity[j] << " (" << travelerDepAirport[j] << ")";
            cout << "\nTo: " << travelerArrCity[j] << " (" << travelerArrAirport[j] << ")";
            cout << "\nDeparture: " << flightTimings[j];
            cout << "\nTicket Price: Rs. " << ticketPrices[j] << "\n";
        }
    }

    // If no bookings exist for this user
    if (!found)
        cout << "No bookings found.\n";

    pauseScreen();    // Wait for user input before returning
}



int main() 
{
    string loggedInCNIC = ""; // This will store the CNIC of the user who logs in

    loadUsers();           // Load user account data from file
    loadBookings();        // Load existing booking records from file
    loadBookedSeats();     // Load booked seat data for all flights

    int option;
    while (true)  // Loop until the user successfully logs in or exits
	{
        clearScreen();     // Clear the console screen for a clean menu view
        accountMenu();     // Display the login/signup menu
		cin >> option;

        if (option == 1)  // User chooses to login
		{
			if(login())   // If login is successful, move to main menu
			{
				break;	
			}
			else          // If login fails, pause and let the user try again
			{
            	pauseScreen();
			}
		}
        else if (option == 2)  // User chooses to sign up
		{
			signUp();         // Call sign-up function
		}
        else if (option == 3)  // User chooses to exit
		{
            cout << "\nThank you for using the system.\n";
            sleep(2);         // Pause for 2 seconds before exiting
            exit(0);          // Exit the program completely
        }
        else  // User enters an invalid option in login/signup menu
        {
        	cout << "\nInvalid option.\n";
			pauseScreen();	
		}
    }

    int choice;
    while (true)  // Main flight reservation menu loop after login
	{
        clearScreen();   // Clear screen before showing menu
		showMenu();      // Show main menu options
        cin >> choice;

        if (choice == 1)
        {
        	AvailableFlights();    // Show list of available flights
		}
        else if (choice == 2) 
		{
			bookTicket();          // Start ticket booking process
		}
        else if (choice == 3)
        {
        	cancelReservation();   // Start ticket cancellation process
		}
        else if (choice == 4)
        {
        	viewBookedFlights();   // Show the list of flights booked by the user
		}
        else if (choice == 5) 
		{
            cout << "\nLogging Out....\n";
            sleep(2);             // Pause before logging out
            return main();        // Go back to login/signup menu
        }
        else 
		{
            cout << "Invalid option.\n"; // If user enters wrong input in main menu
            pauseScreen();               // Pause so user can read the message
        }

        execution++;  // Track how many actions user has performed (used elsewhere)
    }

    return 0; // End of main (this is actually never reached)
}