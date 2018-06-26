#include "selfcheck.h"
#include "user.h"

#include <iostream>
using namespace std;

// Overriding base class greeting function
void SelfCheck::greeting() {
    cout << "Welcome to the self-checkout counter. Please indicate how many items you will be buying: " << endl;

    // Using base class functions to complete objective
    User::buyItems();
    User::purchaseSummary();

}
