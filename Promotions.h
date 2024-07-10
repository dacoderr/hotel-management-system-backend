#ifndef PROMOTIONS_H
#define PROMOTIONS_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Promotion {
private:
    string code;
    int discountRate;
    int maxUses;
    int usesCount;
    time_t expiryDate;

public:
    Promotion(string code, int discountRate, int maxUses, time_t expiryDate)
        : code(code), discountRate(discountRate), maxUses(maxUses), usesCount(0), expiryDate(expiryDate) {}

    string getCode() const { return code; }
    int getDiscountRate() const { return discountRate; }
    int getMaxUses() const { return maxUses; }
    int getUsesCount() const { return usesCount; }
    time_t getExpiryDate() const { return expiryDate; }

    bool isValid() const {
        time_t now = time(0);
        return (usesCount < maxUses) && (now <= expiryDate);
    }

    void use() { usesCount++; }

    friend ostream& operator<<(ostream& os, const Promotion& p) {
        os << p.code << ' '
           << p.discountRate << ' '
           << p.maxUses << ' '
           << p.usesCount << ' '
           << p.expiryDate;
        return os;
    }
};

#endif // PROMOTIONS_H