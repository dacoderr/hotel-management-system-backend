#include <iostream>
#include <string>
#ifndef Rooms_class 
#define Rooms_class

using namespace std;

class Rooms {
private:
	int roomId;
	string type;
	int price;

public:
	//constructors
	const static int Nrooms = 100;
	Rooms() {};
	Rooms(int roomId, string type, int price) : roomId(roomId), type(type), price(price) {};

	//setters
	void set_id(int id) { roomId = id; }
	void set_type(string ty) { type = ty; }
	void set_price(int pr) { price = pr; }

	//getters
	int get_id() { return roomId; }
	string get_type() { return type; }
	int get_price() { return price; }

	//overloading
	friend ostream& operator<<(ostream& os, Rooms& r) {
		os << "Room ID: " << r.roomId << " | Type: " << r.type << " | Price: " << r.price << endl;
		return os;
	}


};
#endif // !Rooms_class
