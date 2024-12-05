#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct xTravels {
    int seatNumber[3];
    char gender[3];
    bool seatAlreadyBooked[40] = {false};
    string cities[10];
    string bookings[10];
    string schedules[5];
};


// Function of registering user

void registerUser(string username, string password, bool isRegistered)
{
    cout << " Enter a username: "; // user credentials
    cin >> username;
    do
    {
        cout << "Enter a password (at least 8 characters): "; // input
        cin >> password;
        cout << " \n";
        if (password.length() < 8)
        {
            cout << "Password must be at least 8 characters long.\n";
        }
    } while (password.length() < 8);

    // Store user credentials in a file
    ofstream fout("users.txt", ios::app);
    fout << username << " " << password << endl;
    fout.close(); // closing file
    cout << "User registered successfully!\n";
    isRegistered = true;
}

// Function of adding city

void addCity(xTravels &system, int &cityCount, int maxCities)
{
    if (cityCount >= maxCities)
    {
        cout << "City list is full. \n";
        return;
    }

    // Ignore the leftover newline from previous input
    cin.ignore();

    cout << "Enter the name of the city to add: "; // input
    getline(cin, system.cities[cityCount]);
    cityCount++;

    // Storing cities to a file
    ofstream fout("citiesAdded.txt", ios::app);

    if (!fout) // Checking if the file opens
    {
        cout << "Error opening the file!\n";
        return;
    }

    for (int i = 0; i < cityCount; ++i)
    {
        fout << i + 1 << ". " << system.cities[i] << endl;
    }

    fout.close(); // Closing file

    cout << "City has been added successfully in citiesAdded.txt!\n";
}

// Function of viewBookings
void viewBookings(xTravels &system, int bookingCount)
{
    if (bookingCount == 0)
    {
        cout << "No bookings available yet.\n";
    }
    else
    {
        // Opening the file
        ifstream inFile("bookings.txt");

        if (!inFile) // checking if file opens
        {
            cout << "Error opening file!" << endl;
            return;
        }
        cout << "List of Bookings:\n";
        string booking;
        while (getline(inFile, booking))
        {
            cout << booking << endl;
        }
        inFile.close(); // closing file
    }
}

// Function to updateSchedule
int updateSchedule(xTravels &system, int scheduleCount)
{
    // Read timings from file
    ifstream inFile("timings.txt");
    if (!inFile) // checking if file opens
    {
        cout << "Error opening timings file!\n";
        return -1;
    }

    string timings[5];
    int count = 0;
    while (getline(inFile, timings[count]))
    {
        cout << count + 1 << ". " << timings[count] << endl;
        count++;
    }
    inFile.close(); // file closed

    if (count == 0)
    {
        cout << "No timings available in the file.\n";
        return -1;
    }

    int scheduleChoice;
    cout << "Enter the number of the schedule to update: ";
    cin >> scheduleChoice;

    if (scheduleChoice < 1 || scheduleChoice > scheduleCount)
    {
        cout << "Invalid schedule selection.\n";
        return -1;
    }

    cout << "Enter the updated schedule: ";
    cin.ignore();
    getline(cin, system.schedules[scheduleChoice - 1]);

    // storing schedule in a file
    ofstream fout("schedule.txt", ios::app);
    for (int i = 0; i < scheduleCount; ++i)
    {
        if (!fout) // checking if file opens
        {
            fout << "Error opening the file!\n";
            return -1;
        }
        fout << i + 1 << ". " << system.schedules[i] << endl;
    }
    fout.close(); // closing file
    cout << "Schedule updated successfully in schedule.txt ! \n";
}

// Function to selectCities
bool selectCities(xTravels &system, string &startCity, string &destCity, int &cityCount)
{
    cout << "\n";
    cout << "*_______________________________*_______________________________*" << endl;
    cout << "\n"
         << "                            AVAILABLE CITIES                     " << endl;
    cout << "*_______________________________*_______________________________*" << endl;
    cout << "\n";

    // Read cities from file
    ifstream inFile("cities.txt");
    if (!inFile) // checking if file opens
    {
        cout << "Error opening cities file!" << endl;
        return false;
    }

    cityCount = 0;
    while (getline(inFile, system.cities[cityCount]))
    {
        cout << cityCount + 1 << ". " << system.cities[cityCount] << endl;
        cityCount++;
    }
    inFile.close(); // closing file

    int startCityIndex, destCityIndex;
    cout << "\nSelect the starting city (1-" << cityCount << "): "; // input
    cin >> startCityIndex;

    if (startCityIndex < 1 || startCityIndex > cityCount)
    {
        cout << "Invalid starting city.\n";
        return false;
    }

    cout << "Select the destination city (1-" << cityCount << "): "; // input
    cin >> destCityIndex;
    if (destCityIndex < 1 || destCityIndex > cityCount)
    {
        cout << "Invalid destination city.\n";
        return false;
    }

    // Checking  for the same starting and destination cities
    if (startCityIndex == destCityIndex)
    {
        cout << "Starting and destination cities cannot be the same.\n";
        return false;
    }

    startCity = system.cities[startCityIndex - 1];
    destCity = system.cities[destCityIndex - 1];

    // storing cities to a file
    ofstream fout("displaycities.txt", ios::app);
    if (!fout) // checking if file opens
    {
        cout << "Error creating output file!" << endl;
        return false;
    }
    fout << "Cities selected: " << startCity << " to " << destCity << endl;
    fout.close(); // closing file

    cout << "\nCities selected successfully in  displaycities.txt !\n";
    return true;
}

// Function to selectTiming
int selectTiming()
{
    cout << "\n";
    cout << "*_______________________________*_______________________________*" << endl;
    cout << '\n'
         << "                            SELECTING TIMING                    " << endl;
    cout << "*_______________________________*_______________________________*" << endl;
    cout << "\n";

    // Read timings from the file
    ifstream inFile("timings.txt");
    if (!inFile)
    { // Check if file opens successfully
        cout << "Error opening timings file!\n";
        return -1;
    }

    string timings[3];
    int count = 0;

    while (count < 3 && getline(inFile, timings[count]))
    {
        cout << count + 1 << ". " << timings[count] << endl;
        count++;
    }
    inFile.close(); // Close the file

    if (count == 0)
    {
        cout << "No timings available in the file.\n";
        return -1;
    }

    // Validate user input for selecting a timing
    int timingChoice;
    while (true)
    {
        cout << "\nSelect the timing (1-" << count << "): ";
        cin >> timingChoice;

        // Check for input failure or invalid range
        if (cin.fail() || timingChoice < 1 || timingChoice > count)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid timing selection. Please enter a number between 1 and " << count << ".\n";
        }
        else
        {
            break;
        }
    }

    return timingChoice;
}

// Function to save and display the selected timing
void displayTiming(int timingChoice)
{

    // Save the selected timing to a file
    ofstream fout("display-timings.txt", ios::app);
    if (!fout)
    { // Check if file opens successfully
        cout << "Error: Could not open the output file.\n";
        return;
    }

    fout << "Selected Timing: ";
    switch (timingChoice)
    {
    case 1:
        fout << "6:00 AM to 10:00 AM\n";

        break;
    case 2:
        fout << "6:00 PM to 12:00 AM\n";

        break;
    case 3:
        fout << "12:00 PM to 4:00 PM\n";

        break;
    default:
        fout << "Invalid timing.\n";

        break;
    }

    fout.close(); // Close the file
    cout << "Output has been saved in 'display-timings.txt'.\n";
}

// Function to check if a year is a leap year
bool isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Function to get the maximum days in a month for a given year
int getMaxDaysInMonth(int month, int year)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 0;
    }
}

// Function to validate a given date
bool isValidDate(int day, int month, int year)
{
    if (year < 1 || year > 2024 || year < 2024)
    {
        return false;
    }
    if (month < 1 || month > 12)
    {
        return false;
    }
    int maxDays = getMaxDaysInMonth(month, year);
    return (day >= 1 && day <= maxDays);
}

// Function to validate and select a date
int validateDate()
{
    cout << "*_______________________________*_______________________________*" << endl;
    cout << '\n'
         << "                        DATE SELECTION                          " << endl;
    cout << "*_______________________________*_______________________________*" << endl;
    cout << '\n';

    int date, month, year;

    // Validate date input
    while (true)
    {
        cout << "Enter date: ";
        cin >> date;
        if (cin.fail() || date < 1 || date > 31)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input for date. Please enter a valid day (1-31).\n";
        }
        else
        {
            break;
        }
    }

    // Validate month input
    while (true)
    {
        cout << "Enter month: ";
        cin >> month;
        if (cin.fail() || month < 1 || month > 12)
        {
            cin.clear();            // Clear the error flag
            cin.ignore(1000, '\n'); // Ignore invalid input
            cout << "Invalid input for month. Please enter a valid month (1-12).\n";
        }
        else
        {
            break;
        }
    }

    // Validate year input
    while (true)
    {
        cout << "Enter year: ";
        cin >> year;
        if (cin.fail() || year < 1 || year > 2024 || year < 2024)
        {
            cin.clear();            // Clear the error flag
            cin.ignore(1000, '\n'); // Ignore invalid input
            cout << "Invalid input for year. Please enter a valid year (1-2024).\n";
        }
        else
        {
            break;
        }
    }

    cout << "\n";

    // Validate the date logic
    if (!isValidDate(date, month, year))
    {
        cout << "The date is invalid.\n";
        return -1;
    }

    // Save valid date to file
    ofstream fout("display-date.txt", ios::app);
    fout << "The date is valid.\n";
    fout << date << " " << month << " " << year << "\n";
    fout.close();

    cout << "Date has been saved in display-date.txt!" << endl;

    // Display special offers
    if (date == 14 && month == 8)
    {
        cout << "Enjoy up to 10 percent off this Yom-e-Azadi!\n";
    }
    else if (date == 23 && month == 3)
    {
        cout << "Enjoy up to 5 percent off today!\n";
    }
}

// Function of payment

int payment()
{
    cout << " \n";
    cout << "*_______________________________*_______________________________*" << endl;
    cout << '\n'
         << "                            PAYMENT METHOD                       " << endl;
    cout << "*_______________________________*_______________________________*" << endl;
    cout << " \n";

    // Open the file for reading
    ifstream infile("payment.txt");
    if (!infile) // checking if file opens
    {
        cout << "Error: Could not open \n";
        return -1;
    }

    string payment[4];
    int count = 0;

    while (getline(infile, payment[count]))
    {
        cout << count + 1 << ". " << payment[count] << endl;
        count++;
        if (count >= 4)
            break;
    }
    infile.close(); // closing file

    if (count == 0)
    {
        cout << "No payment methods available.\n";
        return -1;
    }
    int paymentChoice;

    while (true)
    {
        cout << "Select the payment type (1-" << count << "): "; // Input prompt
        cin >> paymentChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid number.\n";
        }
        else if (paymentChoice < 1 || paymentChoice > count)
        {
            cout << "Invalid choice. Please select a number between 1 and " << count << ".\n";
        }
        else
        {
            break;
        }
    }

    // storing payments in a file
    ofstream fout("selected-payment.txt", ios::app);
    if (!fout) // checking if file opens
    {
        fout << "Error: Could not open \n";
        return -1;
    }
    else
    {
        string selectedPayment = payment[paymentChoice - 1];
        fout << "\nSelected: " << selectedPayment << endl;
    }

    fout.close(); // closing file

    cout << "Selected payment method has been saved to 'selected-payment.txt'.\n";
    cout << " \n";

    return paymentChoice;
}

// Function to selectBus
bool selectBus(int totalSeats, int countPerLine, string startCity, string destCity, int cityCount)
{
    cout << " \n";
    cout << "*_______________________________*_______________________________*" << endl;
    cout << '\n'
         << "                            AVAILABLE BUSES                      " << endl;
    cout << "*_______________________________*_______________________________*" << endl;

    ifstream infile("bustype.txt");
    if (!infile)
    {
        cout << "Error: Could not open .\n";
        return false;
    }

    string bustype[4];
    int count = 0;
    while (getline(infile, bustype[count]))
    {
        cout << count + 1 << ". " << bustype[count] << endl; // Display each bus type
        count++;
        if (count >= 4)
            break;
    }
    infile.close();

    if (count == 0)
    {
        cout << "No buses available in the file.\n";
        return false;
    }

    int busChoice;

    while (true)
    {
        cout << "Select the bus type (1-" << count << "): "; // Input prompt
        cin >> busChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a valid number.\n";
        }
        else if (busChoice < 1 || busChoice > count)
        {
            cout << "\nInvalid bus choice. Please select a number between 1 and " << count << ".\n";
        }
        else
        {
            break;
        }
    }

    return true; // Return true to indicate successful choice

    string busDetails;
    switch (busChoice)
    {
    case 1:
    case 2:
        busDetails = "Standard/Executive Bus";
        totalSeats = 40;
        countPerLine = 4;
        break;
    case 3:
    case 4:
        busDetails = "Business/Sleeper Bus";
        totalSeats = 36;
        countPerLine = 3;
        break;
    default:
        cout << "\nInvalid bus choice.\n";
        return false;
    }

    // storing bustypes to a file
    ofstream fout("display-bustype.txt", ios::app);
    if (!fout) // checking if file opens
    {
        cout << "Error: Could not open \n";
        return false;
    }

    fout << "Selected Bus Type: " << busDetails << endl;
    fout << "Total Seats: " << totalSeats << endl;
    fout << "Seats Per Line: " << countPerLine << endl;
    fout.close(); // closing file

    cout << "\n Bus details have been saved to 'display-bustype.txt'.\n";
}

// Function to bookSeats

int bookSeats(int totalSeats, int countPerLine, int count, xTravels &system)
{
    // Display seat layout
    cout << "*_______________________________*_______________________________*" << endl;
    cout << '\n'
         << "                            SEAT BOOKING                         " << endl;
    cout << "*_______________________________*_______________________________*" << endl;
    cout << "_________________________\n";

    for (int i = 1; i <= totalSeats; i++)
    {
        if (system.seatAlreadyBooked[i - 1])
        {
            cout << "X\t"; // Mark booked seats with 'X'
        }
        else
        {
            cout << i << "\t";
        }
        if (i % countPerLine == 0)
        {
            cout << "|\n";
        }
    }
    cout << "_________________________\n";

    // Booking seats
    cout << " \n";
    cout << "Enter number of seats to book (max 3): "; // input
    int seats;
    cin >> seats;

    // Validate input
    while (cin.fail() || seats < 1 || seats > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number between 1 and 3: ";
        cin >> seats;
    }

    for (int i = 0; i < seats; i++)
    {
        while (true)
        {
            cout << "Enter seat number: ";
            cin >> system.seatNumber[i];

            // Validate input
            if (cin.fail() || system.seatNumber[i] < 1 || system.seatNumber[i] > totalSeats)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Enter a valid seat number between 1 and " << totalSeats << ": ";
                continue;
            }

            // Check if seat is already booked
            if (!system.seatAlreadyBooked[system.seatNumber[i] - 1])
            {
                cout << "Enter Gender (M/F): ";
                cin >> system.gender[system.seatNumber[i] - 1];

                // Validate gender input
                while (cin.fail() || (system.gender[system.seatNumber[i] - 1] != 'M' && system.gender[system.seatNumber[i] - 1] != 'm' &&
                                      system.gender[system.seatNumber[i] - 1] != 'F' && system.gender[system.seatNumber[i] - 1] != 'f'))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout
                        << "Invalid input. Please enter M or F: ";
                    cin >> system.gender[system.seatNumber[i] - 1];
                }

                system.seatAlreadyBooked[system.seatNumber[i] - 1] = true;
                count++;
                break;
            }
            else
            {
                cout << "Seat already booked. Please choose another seat.\n";
            }
        }
    }

   

    // here
     // Updated seating chart
    cout << "\nSeating chart after booking:\n";
    cout << "_________________________\n";
    for (int i = 1; i <= totalSeats; i++)
    {
        if (system.seatAlreadyBooked[i - 1])
        {
            cout << system.gender[i - 1] << "\t";
        }
        else
        {
            cout  << i << "\t"; // Use setw for alignment
        }
        if (i % countPerLine == 0)
        {
            cout << "|\n";
        }
    }
    cout << "_________________________\n";

    return count;
}
// MAIN FUNCTION
int main()
{

  
    cout << " _____________________________*______________________________________*________________________________*___________________________   " << endl;
    cout << " \n";
    cout << "    [||||||]      [|||]         [||||||||]    (********)      ******    [^^]      [^^]    [||||||]     []          [||||||||]      " << endl;
    cout << "       ||||       |||               ||         ||     ||     ||    ||    ||        ||     ||           ||           |||    |       " << endl;
    cout << "         |||     ||                 ||         ||     ||     ||    ||    ||        ||     ||           ||           |||            " << endl;
    cout << "             <>                     ||         ||   ||       || ** ||    ||        ||     [||||||]     ||           |||||||||      " << endl;
    cout << "           ||  ||                   ||         ||***                                                                                 " << endl;
    cout << "         |||     ||                 ||         ||   ||       ||    ||     ||      ||      ||           ||                 |||      " << endl;
    cout << "       |||         |||              ||         ||     ||     ||    ||       ||   ||       ||           ||                 |||      " << endl;
    cout << "     [|||]        [||||||]         [||]        ||      ||    ||    ||         |||         [|||||||]    [|||||||]   [||||||||]      " << endl;
    cout << " \n";
    cout << " _____________________________*______________________________________*________________________________*___________________________ " << endl;
    cout << " \n";
     xTravels system;
    const int maxCities = 10;
    const int maxBookings = 10;
    const int maxSchedules = 5;

    bool isRegistered = false;
    string username, password;
    int paymentChoice;
    string startCity, destCity, prompt;
    int date, month, year;
    int cityCount = 8, scheduleCount = 3, count = 0, totalSeats = 40, countPerLine = 4;


    cout << " *** Welcome to the Bus Reservation System *** \n";
    cout << " \n";
    int choice;
    cout << "1. Register as User\n2. Admin Login\n";
    cout << " \n";
    cout << " Enter your choice :"; // input
    cin >> choice;
    cout << " \n";

    if (choice == 1)
    {

        cout << " ... Registering as user ... \n";
        cout << " \n";
        if (isRegistered)
        {
            cout << "User already registered! Proceeding with booking.\n";
        }
        else
        {
            registerUser(username, password, isRegistered);
        }

        if (selectCities(system, startCity, destCity, cityCount))
        {
            int timingChoice = selectTiming();
            if (timingChoice != -1)
            {

                // timing function called
                displayTiming(timingChoice);
                // date  function called
                validateDate();

                // selectBus function called
                selectBus(totalSeats, countPerLine, startCity, destCity, cityCount);

                // bookSeats function called
                bookSeats(totalSeats, countPerLine, count, system);

                // payment function called
                int selectedPayment = payment();
                if (selectedPayment == -1)
                {
                    cout << "\nPayment process aborted due to invalid selection.\n";
                }
            }
            cout << " \n";
            // displaying bye message
            cout << " ..... HAVE A SAFE JOURNEY ..... !" << endl;
        }
    }
    else if (choice == 2)
    {
        // admin login
        cout << " ... logging as admin ...";
        cout << " \n";
        cout << " \n";
        string adminUsername = "admin"; // admin credentials
        string adminPassword = "admin123";
        cout << "Enter admin username: ";
        cin >> username;
        cout << "Enter admin password: ";
        cin >> password;
        cout << " \n";

        if (username == adminUsername && password == adminPassword)
        {
            cout << "Admin's login successful!\n";
            cout << " \n";
            int adminChoice;
            cout << " Would you like to :" << endl;
            cout << " \n";
            cout << "1. View Bookings\n2. Add City\n3. Update Schedule\n";
            cout << " Enter your choice :";
            cin >> adminChoice;
            cout << " \n";

            switch (adminChoice)
            {
            case 1:
                viewBookings(system, 5);
                break;
            case 2:
                addCity(system, cityCount, maxCities);
                break;
            case 3:
                updateSchedule(system, scheduleCount);
                break;
            default:
                cout << "Invalid option.\n";
            }
        }
        else
        {
            cout << "Invalid choice. Exiting program.\n";
        }
    }
    else
    {
        cout << "invalid entry !";
    }
}