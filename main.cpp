/* Aaron Abraham
 * Ms. Dalal
 * Final Project - Grade 11
 * */

// Including libraries
#include <iostream>
#include <string>

// Including files
#include "user.h"
#include "selfcheck.h"
#include "cashiercheck.h"
#include "userinfo.h"

int main() {
    // Declaring variables
    int userIsRegistered = 0; // 0 = not registered, 1 = regular membership, 2 = executive membership

    // Declare initial struct with pre-existing records for users and cashier
    userInfo regRecords[10] = {{10, 34}, {56, 20}};
    userInfo execRecords[10] = {{56, 890}, {61239, 19120}};
    userInfo cashierRecords[10] = {{167, 292}, {891, 290}};

    // Declaring objects
    User initialUser(regRecords, execRecords, cashierRecords, 0, 0, 0);

    initialUser.greeting(); // Giving greeting to user and prompting user to enter ID and password

    // Checking records if user is a registered customer and what type of loyalty they are
    for (int i = 0; i < 10; i ++)
    {
        //
        if (regRecords[i].userID == initialUser.returnID() && regRecords[i].password == initialUser.returnPassword())
        {
            userIsRegistered = 1;
            break;
        }
        else if (execRecords[i].userID == initialUser.returnID() && execRecords[i].password == initialUser.returnPassword())
        {
            userIsRegistered = 2;
            break;
        }
        else
        {
            userIsRegistered = 0;
        }
    }
    initialUser.setLoyalty(userIsRegistered); // Updating record of user class with registration type

    // Initializing additional objects
    SelfCheck selfUser(regRecords, execRecords, cashierRecords, initialUser.returnID(), initialUser.returnPassword(), initialUser.returnLoyalty());
    CashierCheck cashierUser(regRecords, execRecords, cashierRecords, initialUser.returnID(), initialUser.returnPassword(), initialUser.returnLoyalty());

    // If user is already registered, then they will have the choice to either self-checkout or get a checkout with the cashier
    if (userIsRegistered == 1 || userIsRegistered == 2)
    {

        // Starting class flow based on loyalty level
        if (initialUser.returnOption() == 1)
        {
            selfUser.greeting();
        }
        else
        {
            cashierUser.greeting();
        }
    }
    else // If user is not registered, then they will automatically be placed with a cashier
    {
        // If user accidentally wants a self-checkout but is not registered, it will output that they are going to a cashier
        if (initialUser.returnOption() == 1)
        {
            cout << "Transferring to cashier..." << endl;
        }
        cashierUser.greeting();
    }

    cout << "Thank you for using the Risorgimento application. Have a great day!" << endl;

    return 0;
}
