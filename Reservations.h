#ifndef Res_class
#define Res_class
#include "Rooms.h"
#include <sstream>

class Reservations: public Rooms {
private:
    string customerName;
    string checkInDate;
    string checkOutDate;
public:
    //constructors
    Reservations() {};


    Reservations(int roomId, string type, int price, string customerName, string checkInDate, string checkOutDate)
        : Rooms(roomId, type, price), customerName(customerName), checkInDate(checkInDate), checkOutDate(checkOutDate) {}

    //setters
    void set_customer(string cust) { customerName = cust; }
    void set_checkin(string in) { checkInDate = in; }
    void set_checkout(string out) { checkOutDate = out; }

    //getters
    string get_name() { return customerName; }
    string get_in() { return checkInDate; }
    string get_out() { return checkOutDate; }

    //overloading
    friend ostream& operator<<(ostream& os, Reservations& r) {
        os << "Room ID : " << r.get_id() << " | Type : " << r.get_type() << " | Price : " << r.get_price() << " | Customer Name : " << r.customerName << " | Check - In : " << r.checkInDate << " | Check - Out : " << r.checkOutDate << endl;
        return os;
    }
    //Returns space seperated values for Database saving
    string operator ! (){
        stringstream ss;
        ss<< get_id() << ' ' << get_type() << ' ' << get_price() << ' ' << customerName << ' ' << checkInDate << ' ' << checkOutDate << endl;
        string buffer = ss.str();
        return buffer;
    }

        
};
#endif // !Res_class
