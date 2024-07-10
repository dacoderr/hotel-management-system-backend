
#include <iostream>
#include <string>
#include "Reservations.h"
#ifndef BILLINGS_H
#define BILLINGS_H

using namespace std;

class Billings : public Reservations {
private:
    int billId;
    double totalCost;
    int star_rating;
    string customerFeedback;
public:

    // constructor
    Billings(int roomId, string type, int price, string customerName, string checkInDate, string checkOutDate, int billId, double totalCost,int star_rating , string customerFeedback)
        : Reservations(roomId, type, price, customerName, checkInDate, checkOutDate), billId(billId), totalCost(totalCost) , star_rating(star_rating) , customerFeedback(customerFeedback){}

    // getters 
    int getBillId() { return billId; }
    double getTotalCost()  { return totalCost; }
    int get_rid(Reservations& s) { return s.get_id(); }
    int getStar_rating () { return star_rating;}
    string getCustomerFeedback() { return customerFeedback;}
    //setter
    // overloading
    friend ostream& operator<<(ostream& os, Billings& b) {
        os << "Bill ID: " << b.billId << " | Customer Name: " << b.get_name() << " | Room ID: " << b.get_id()
            << " | Check-In Date: " << b.get_in() << " | Check-Out Date: " << b.get_out() << " | Total Cost: SAR " << b.totalCost << " | Customer star rating: " <<  b.star_rating << " | FeedBack: " <<  b.customerFeedback << '\n';
        return os;
    }

    //Overloading ! to help save to database
    string operator ! (){
        stringstream ss;
        //room ID room type price customer name Check-In Date Check-Out Date billid Total Cost: SAR 
        ss << get_id() << ' ' << get_type() << ' ' <<get_price() << ' '<<get_name() << ' ' << get_in() << ' ' << get_out() << ' ' << billId << ' ' << totalCost <<' ' << star_rating << ' '<<customerFeedback<<'\n';
        string buffer = ss.str();
        return buffer;
    }
};

#endif // BILLINGS_H
