// Headers
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

// Classes
#include "Rooms.h"
#include "Reservations.h"
#include "Bills.h"
#include "Promotions.h"
#include "Auth.h"

// DB File
const string fileName1 = "DB_Reservations.txt";
const string fileName2 = "DB_Billing_History.txt";
const string fileName3 = "DB_Promotions.txt";
//DB users
const string usersFile = "users.txt";

using namespace std;

// Menu Declarations
void displayHotelDescription();
void displayMenu();
void checkInCustomer();
void checkOutCustomer();
void viewAvailableRooms();
void viewBookedRooms();
void viewBillingSystem();
void viewCustomerEvaluations();

// Files loading and saving
void saveDataToFile();
void Load_DB_File();

// Vectors (lists) declarations
vector<Rooms> availableRooms;
vector<Reservations> bookedRooms;
vector<Billings> Bills;
vector<Promotion> promotions;

void createPromotion();
void RoomsFill();
void bookRoom(int id, string type, int price, string name, string in, string out);
void emptyRoom(int id);
string getFeedBack();
int getStarRating();

#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::milliseconds

//parsing  username and password from txt file
Auth::Auth() {
    ifstream file(usersFile);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ':'); // Use ':' as delimiter for username
        getline(ss, password);     // Password is the remainder of the line
        users.push_back(make_pair(username, password));
    }
    file.close();
}

bool Auth::login(const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.first == username && user.second == password) {
            current_user = username;
            return true;
        }
    }
    return false;
}

string Auth::get_current_user() const {
    return current_user;
}

int main()
{
    system("cls");
    // filling the vector
    RoomsFill();
    // Loading database file
    try
    {
        Load_DB_File();
    }
    catch (const char *s)
    {
        // if fresh program No Database exist so error is thrown
    }

    //init Auth class
    Auth auth;
    string username, password;
    cout << "+----------------------------------------------------+" << endl;
    cout << "|            ~ Welcome to Mandarin Oriental ~        |" << endl;
    cout << "|            ~ Where Comfort Meets Luxury   ~        |" << endl;
    cout << "+----------------------------------------------------+" << endl;
    cout << "|            ~         Login page           ~        |" << endl;
    cout << "+----------------------------------------------------+" << endl;
    cout << "Enter username:"<<endl;
    cout << " ->  ";
    cin >> username;
    cout << "Enter password:"<<endl;
    cout << "->  ";
    cin >> password;

    if (auth.login(username, password)) {
        cout << "Login successful. Welcome, " << auth.get_current_user() << "!" << endl;
        system("pause");
        while (true){
            int choice;
            system("cls");

            displayMenu();

            cin >> choice;

            switch (choice)
            {
            case 1:
                displayHotelDescription();
                system("pause");
                break;
            case 2:
                checkInCustomer();
                system("pause");
                break;
            case 3:
                checkOutCustomer();
                system("pause");
                break;
            case 4:
                viewAvailableRooms();
                system("pause");
                break;
            case 5:
                viewBookedRooms();
                system("pause");
                break;
            case 6:
                viewBillingSystem();
                system("pause");
                break;
            case 7:
                viewCustomerEvaluations();
                system("pause");
                break;
            case 8:
                createPromotion();
                break;
            case 0:
                saveDataToFile();
                cout << "Exiting...\n";
                system("pause");
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    } else {
        cout << "Invalid username or password. Exiting..." << endl;
        return 1;
    }
}

// vectors (lists) declerations
void RoomsFill()
{
    for (int i = 100; i <= 160; i++)
    {
        availableRooms.push_back(Rooms(i, "Standard", 1000));
    }
    for (int i = 161; i <= 190; i++)
    {
        availableRooms.push_back(Rooms(i, "Deluxe", 1400));
    }
    for (int i = 191; i <= 200; i++)
    {
        availableRooms.push_back(Rooms(i, "Suite", 3000));
    }
}
void bookRoom(int id, string type, int price, string name, string in, string out)
{
    vector<Rooms>::iterator iter;
    for (iter = availableRooms.begin(); iter < availableRooms.end(); iter++)
    {
        if ((*iter).get_id() == id)
        {
            bookedRooms.push_back(Reservations(id, type, price, name, in, out));
            availableRooms.erase(iter);
            break;
        }
    }
}

void emptyRoom(int id) {
    vector<Reservations>::iterator iter = bookedRooms.begin();
    while (iter != bookedRooms.end()) {
        if (iter->get_id() == id) {
            availableRooms.push_back(Rooms(iter->get_id(), iter->get_type(), iter->get_price()));
            iter = bookedRooms.erase(iter);
        }
        else {
            ++iter;
        }
    }
}

void displayMenu() {
    cout << "+----------------------------------------------------+\n";
    cout << "|            ~ Welcome to Mandarin Oriental ~        |\n";
    cout << "|            ~ Where Comfort Meets Luxury ~          |\n";
    cout << "+----------------------------------------------------+\n";
    cout << "|  1. Display Hotel Description                      |\n";
    cout << "|  2. Check In                                       |\n";
    cout << "|  3. Check Out                                      |\n";
    cout << "|  4. View Available Rooms                           |\n";
    cout << "|  5. View Booked Rooms                              |\n";
    cout << "|  6. View Billing History                           |\n";
    cout << "|  7. View Customer Evaluation                       |\n";
    cout << "|  8. Create Promotion Code                          |\n";
    cout << "|  0. Exit and Save                                  |\n";
    cout << "+----------------------------------------------------+\n";
    cout << "Enter your choice: ";
}

// menu declerations
void displayHotelDescription()
{
    cout << "\n";
    cout << "+-----------------------------------------------------------------------+\n";
    cout << "|              ~ Mandarin Oriental, Riyadh: A Luxurious Oasis ~         |\n";
    cout << "|                  ~ in the Heart of the Capital ~                      |\n";
    cout << "+-----------------------------------------------------------------------+\n";
    cout << "|                               Rooms                                   |\n";
    cout << "+-----------------------------------------------------------------------+\n";
    cout << "|  * Standard Room: 60 Rooms (Price: SAR 1000/night)                    |\n";
    cout << "|  * Deluxe Room:  30 Rooms (Price: SAR 1400/night)                     |\n";
    cout << "|  * Suite:        10 Rooms (Price: SAR 3000/night)                     |\n";
    cout << "+-----------------------------------------------------------------------+\n";
    cout << "|                             Amenities                                 |\n";
    cout << "+-----------------------------------------------------------------------+\n";
    cout << "|  * Fully equipped Gym with personal trainers.                         |\n";
    cout << "|  * Indoor pool for relaxation and swimming.                           |\n";
    cout << "|  * Meeting & event spaces for conferences, weddings, and gatherings.  |\n";
    cout << "|  * 24-hour butler service.                                            |\n";
    cout << "+-----------------------------------------------------------------------+\n";
    cout << "|                             Location                                  |\n";
    cout << "+-----------------------------------------------------------------------+\n";
    cout << "|  Centrally located in Riyadh, adjacent to Al Faisaliah Tower.         |\n";
    cout << "+-----------------------------------------------------------------------+\n";
    cout << "\n";
}

void checkInCustomer()
{
    string name, in, out;
    int type, id;
    cout << "Enter customer Full name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Check-in Date (DD.MM.YYYY): ";
    getline(cin, in);
    cout << "Enter Check-out Date (DD.MM.YYYY): ";
    getline(cin, out);
    while (true)
    {
        cout << "Choose room type: 1.Standard  2.Deluxe  3.Suite: ";
        cin >> type;
        if (type > 4 || type <= 0)
        {
            cout << "Invalid Room Type. Please try again.\n";
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (type == 1)
        {
            cout << "Enter room Id (100 - 160): ";
            cin >> id;
        }
        else if (type == 2)
        {
            cout << "Enter room Id (161 - 190): ";
            cin >> id;
        }
        else if (type == 3)
        {
            cout << "Enter room Id (191 - 200): ";
            cin >> id;
        }

        if ((type == 1 && (id < 100 || id > 160)) ||
            (type == 2 && (id < 161 || id > 190)) ||
            (type == 3 && (id < 191 || id > 200)))
        {
            cout << "Invalid room ID for the selected type. Please try again.\n";
            continue;
        }
        else
        {

            bool isAvailable = false;
            vector<Rooms>::iterator iter;
            for (iter = availableRooms.begin(); iter != availableRooms.end(); iter++)
            {
                if ((*iter).get_id() == id)
                {
                    isAvailable = true;
                    break;
                }
            }

            if (isAvailable)
            {
                break;
            }
            else
            {
                cout << "Room " << id << " is not available. Please choose another room.\n";
            }
        }
    }
    string rtype;
    int price;

    switch (type)
    {
    case (1):
        rtype = "Standard";
        price = 1000;
        bookRoom(id, rtype, price, name, in, out);
        break;
    case (2):
        rtype = "Deluxe";
        price = 1400;
        bookRoom(id, rtype, price, name, in, out);
        break;
    case (3):
        rtype = "Suite";
        price = 3000;
        bookRoom(id, rtype, price, name, in, out);
        break;
    }

    cout << endl
         << "Customer Checked-in Succesfully" << endl;
}

int getStarRating()
{
    int star_rating;
    cout << "\n**********************\n";
    cout << "* STAR RATING SYSTEM *\n";
    cout << "**********************\n";
    cout << "Please give a star rating (1-5): ";
    cin >> star_rating;

    if (star_rating > 5)
    {
        cout << "Customer rating is capped at 5.\n";
        star_rating = 5;
    }
    else if (star_rating < 1)
    {
        cout << "Customer rating is minimum 1.\n";
        star_rating = 1;
    }

    cout << "Customer rating: " << star_rating << " stars\n";
    return star_rating;
}

string getFeedBack()
{
    string feedback;
    cout << "\n***************************\n";
    cout << "* CUSTOMER FEEDBACK FORM *\n";
    cout << "***************************\n";
    cout << "Write your Feedback: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, feedback);
    cout << "Thank you for your feedback!\n\n";
    return feedback;
}


void checkOutCustomer() {
    int id;
    cout << "\nEnter Room ID for checkout: ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid input. Please enter a valid room ID." << endl;
        return;
    }

    bool roomFound = false;
    vector<Reservations>::iterator iter = bookedRooms.begin();
    while (iter != bookedRooms.end()) {
        if (iter->get_id() == id) {
            roomFound = true;
            int billId = Bills.size() + 100;

            // calculate stay days
            int price = iter->get_price();
            string in_date = iter->get_in();
            string out_date = iter->get_out();
            cout << endl << "Check-in Date: " << in_date << " | Check-out Date: " << out_date << endl;
            int days;
            cout << "Enter the number of days stayed: ";
            cin >> days;
            
            double total = days * price;
            cout << "Total cost for " << days << " days: " << total << endl;

            // Apply promotion
            string tmp_promotion;
            cout << "Have a promotion code? Enter it here (or skip)!: ";
            cin >> tmp_promotion;

            Promotion* promotion = nullptr;
            for (auto& promo : promotions) {
                if (promo.getCode() == tmp_promotion && promo.isValid()) {
                    promotion = &promo;
                    break;
                }
            }
            if (promotion != nullptr) {
                total *= (1 - promotion->getDiscountRate() / 100.0);
                promotion->use();
                cout << "Promotion applied. New total: " << total << endl;
            }
            else {
                cout << "Invalid or expired promotion code.\n";
            }

            // Getting Feedback
            cout << "Your Feedback matters: \n";
            int star_rating = getStarRating();
            string cus_feedBack = getFeedBack();
            cout << "Adding Bill: " << billId << endl;
            Billings new_bill(iter->get_id(), iter->get_type(), iter->get_price(), iter->get_name(), iter->get_in(), iter->get_out(), billId, total, star_rating, cus_feedBack);
            Bills.push_back(new_bill);

            iter = bookedRooms.erase(iter);
            break;
        }
        else {
            ++iter;
        }
    }

    if (roomFound) {
        emptyRoom(id);
        cout << "Checkout and billing completed successfully." << endl;
    }
    else {
        cout << "Room ID not found in booked rooms." << endl;
    }
}

void createPromotion() {
    string code;
    int discountRate;
    int maxUses, validityDays;

    cout << "Enter promotion code: ";
    cin >> code;
    cout << "Enter discount rate (as a percentage): ";
    cin >> discountRate;
    cout << "Enter maximum uses: ";
    cin >> maxUses;
    cout << "Enter validity period (in days): ";
    cin >> validityDays;

    time_t now = time(0);
    time_t expiryDate = now + validityDays * 86400;

    promotions.push_back(Promotion(code, discountRate, maxUses, expiryDate));
    cout << "Promotion code created!\n";
}

void viewAvailableRooms()
{
    if (availableRooms.size() == 0)
    {
        cout << endl
             << "No Available Rooms" << endl;
    }
    else
    {
        vector<Rooms>::iterator iter;
        for (iter = availableRooms.begin(); iter < availableRooms.end(); iter++)
        {
            cout << (*iter) << endl;
        }
    }
}

void viewBookedRooms()
{

    cout << endl;
    if (bookedRooms.size() == 0)
    {
        cout << endl
             << "No Booked Rooms" << endl;
    }
    else
    {
        vector<Reservations>::iterator iter;
        for (iter = bookedRooms.begin(); iter < bookedRooms.end(); iter++)
        {
            cout << (*iter) << endl;
        }
    }
}

void viewBillingSystem()
{

    if (Bills.size() == 0)
    {
        cout << endl
             << "No Bills Available" << endl;
    }
    else
    {
        vector<Billings>::iterator iter;
        for (iter = Bills.begin(); iter < Bills.end(); iter++)
        {
            cout << (*iter) << endl;
        }
    }
}

// This displays the last 5 customer evaluatiosn
void viewCustomerEvaluations()
{
    if (Bills.size() == 0)
    {
        cout << endl
             << "New Hotel , No Customer Evaluation present" << endl;
    }
    else
    {
        vector<Billings>::iterator iter;
        iter = Bills.end();
        // MAx number of reviews to display is 5
        int Number_of_reviews_available = Bills.size() >= 5 ? 5 : Bills.size();
        for (int i = 0; i < Number_of_reviews_available; i++)
        {
            iter--;
            int length = iter->getStar_rating(); // Example length of asterisk string
            cout << "Feedback Given by : " << iter->get_name() << "\nStars: " << length << '\n'
                 << iter->getCustomerFeedback() << endl;
        }
    }
}

void saveDataToFile()
{
    // Saves reservations
    ofstream out(fileName1.c_str());
    for (int i = 0; i < bookedRooms.size(); i++)
    {
        string buffer = !bookedRooms[i];
        out << buffer;
    }
    out.close();

    // Saves bills
    ofstream out2(fileName2.c_str());
    for (int i = 0; i < Bills.size(); i++)
    {
        string buffer = !Bills[i];
        out2 << buffer;
    }
    out2.close();

    // Save promotions
    ofstream out3(fileName3.c_str());
    for (int i = 0; i < promotions.size(); i++) {
        out3 << promotions[i];
    }
    out3.close();
}

void Load_DB_File()
{
    // Loads reservations
    ifstream in(fileName1.c_str());
    if (!in)
    {
        throw "Error: Database Not Found ";
    }
    int id, price;
    string type, name, in2, out;
    while (!in.eof())
    {
        in >> id;
        in >> type;
        in >> price;
        in >> name;
        in >> in2;
        in >> out;
        bookRoom(id, type, price, name, in2, out);
    }
    in.close();
    // Loads bills
    ifstream myReadBills(fileName2.c_str());
    if (!myReadBills)
    {
        throw "Error: Bills history Not Found ";
    }
    int x = myReadBills.eof();
    int billId;
    double totalCost;
    int star_rating;
    string feedback;
    while (!myReadBills.eof())
    {
        myReadBills >> id;
        if (myReadBills.fail())
        {
            break;
        }
        myReadBills >> type;
        myReadBills >> price;
        myReadBills >> name;
        myReadBills >> in2;
        myReadBills >> out;
        myReadBills >> billId;
        myReadBills >> totalCost;
        myReadBills >> star_rating;
        getline(myReadBills, feedback, '\n');
        Bills.push_back(Billings(id, type, price, name, in2, out, billId, totalCost, star_rating, feedback));
    }
    myReadBills.close();

    // Load promotions
    ifstream inPromotions(fileName3.c_str());
    if (!inPromotions) {
        cerr << "Error: Promotions DB Not Found\n";        
    }
    string code;
    time_t expiryDate;
    int discountRate, maxUses, usesCount;
    while (inPromotions >> code >> discountRate >> maxUses >> usesCount >> expiryDate) {
        promotions.push_back(Promotion(code, discountRate, maxUses, expiryDate));
    }
    inPromotions.close();
}
