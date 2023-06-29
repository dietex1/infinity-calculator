
#include "Number.h"
#include <string>
using namespace std;

// Help function to compare the  values of two vectors representing numbers
bool Number::isGreaterOrEqual(const vector<int> &a, const vector<int> &b) const {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    for (std::size_t i = a.size() - 1; i != std::size_t(-1); --i) {
        if (a[i] != b[i])
        {
            return a[i] > b[i];
        }
    }
    return true;
}

string Number::vectorToString(const vector<int> &vVector) const{
    string result;
    if (vVector.empty()) {
        return result;
    }
    for (int cisl : vVector) {
        result += to_string(cisl);
    }
    return result;
}

