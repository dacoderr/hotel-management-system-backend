#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

class Auth {
private:
    // vector to store username and password pairs
    vector<pair<string, string>> users;
    string current_user;
public:
    Auth();
    bool login(const string& username, const string& password);
    string get_current_user() const;
};

#endif // AUTH_H
