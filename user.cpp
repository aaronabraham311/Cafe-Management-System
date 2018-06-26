// Including libraries and files
#include "user.h"
#include "userinfo.h"

#include <iostream>
#include <string>

using namespace std;

// Greeting function and sends user to get ID and password
void User:: greeting() {
    cout << "Hello, user! Welcome to Risorgimento" << endl;
    getInfo();
    cout << "Please enter your numerical ID and password, if applicable. Otherwise, enter 0 for both fields: " << endl;
    getUserCredentials();
}

// Collects ID and password of user
void User:: getUserCredentials() {
    do
    {
        cout << "User ID: ";
        cin >> userID;

        cout << "Password: ";
        cin >> password;
    } while (option == 1 && validateUser(userID, password) == false); // Will continue asking for ID and password if user wants to self-checkout and enters incorrect ID and password
}

// Returns user ID
int User:: returnID() {
    return userID;
}


// Sets user ID
void User:: setID(int id) {
    userID = id;
}

// Returns user password
int User::returnPassword() {
    return password;
}

// Sets user password
void User:: setPassword(int uPassword) {
    password = uPassword;
}

// Asks user if they want to check out by themselves or with a cashier
void User:: getInfo() {
    do {
        cout << "Option 1: Self check out --- Enter 1" << endl;
        cout << "Option 2: Check out by cashier --- Enter 2" << endl;
        cin >> option;
    } while (option != 1 && option != 2); // Validates option
}

// Returns option
int User:: returnOption() {
    return option;
}

// Returns loyalty
int User:: returnLoyalty() {
    return loyaltyType;
}

// Set loyalty
void User:: setLoyalty(int level) {
    loyaltyType = level;
}

// Checks if entered ID is unique
bool User:: checkUniqueID(int proposedID) {
    bool unique = true;

    for (int i = 0; i < 10; i ++)
    {
        // If proposedID is same as any previous ID, it will return false
        if (prevRegularID[i] == proposedID || prevExecID[i] == proposedID)
        {
            unique = false;
            break;
        }
    }

    return unique;
}

// Functiob buy items
void User:: buyItems() {
    cout << "Please enter the number of items you would like to purchase." << endl;

    // Outputs items and gets number of items bought
    for (int i = 0; i < 10; i ++)
    {
        do {
            cout << inventoryName[i] << " ($" << inventoryPrice[i] << "): ";
            cin >> itemsBought[i];
        } while (itemsBought[i] < 0); // Makes sure user doesn't enter negative number
    }

    calculatePrice(); // Calls function to calculate price
}

void User:: calculatePrice() {
    for (int i = 0; i < 10; i ++)
    {
        totalPrice += itemsBought[i] * inventoryPrice[i]; // Calculates total price by multiplying number of items bought with price
    }
}

// Summarizes purchases and asks for money
void User:: purchaseSummary() {
    float userAmount;

    cout << "Here is a summary of your purchases: " << endl;

    // Reading off user's purchases from two arrays (name of item and price of item)
    for (int i = 0; i < 10; i ++)
    {
        cout << inventoryName[i] << ": " << itemsBought[i] << " bought" << endl;
    }

    // Outputting total purchase price
    cout << "Subtotal: $" << totalPrice << endl;

    // Loyalty discount
    if (loyaltyType == 0) {
        cout << "Total: $" << totalPrice << endl;
    }
    else if (loyaltyType == 1) {
        cout << "Total with 10% discount: $" << totalPrice * 0.9 << endl;
        totalPrice = totalPrice * 0.9;
    }
    else {
        cout << "Total with 20% discount: $" << totalPrice * 0.8 << endl;
        totalPrice = totalPrice * 0.8;
    }

    // Ensuring that user pays price or more for change
    do {
        cout << "Please enter the amount you would like to pay: ";
        cin >> userAmount;
    } while (userAmount < totalPrice);

    if (userAmount > totalPrice)
    {
        cout << "Your change: $" << userAmount - totalPrice << endl;
    }
}

// Adds new users or updates user's records with their ID and passwords
void User:: updateRecords(int currentID, int newID, int currentPassword, int newPassword) {
    // Finding which array to update based on loyalty level and then finding empty place in respective array
    bool alreadyUpdated = false;

    // Puts record into regular membership records
    if (returnLoyalty() == 1)
    {
        for (int i = 0; i < 10; i ++)
        {
            if (prevRegularID[i] == currentID) // Finds place in array in previous place and updates ID into that spot
            {
                prevRegularID[i] = newID;
                prevRegularPasswords[i] = newPassword;
                alreadyUpdated = true;
                break; // Only does this once
            }
        }

        if (alreadyUpdated == false) // Runs conditional if the array hasn't been updated into a previous place (indicating new user)
        {
            for (int i = 0; i < 10; i ++)
            {
                if (prevRegularID[i] == 0) // Finds empty place in array and updates ID into that spot
                {
                    prevRegularID[i] = newID;
                    prevRegularPasswords[i] = newPassword;
                    alreadyUpdated = true;
                    break; // Only does this once
                }
            }
        }
    }
    else if (returnLoyalty() == 2) // Puts record into executive membership records
    {
        for (int i = 0; i < 10; i ++)
        {
            if (prevExecID[i] == currentID) // Finds place in array in previous place and updates ID into that spot
            {
                prevExecID[i] = newID;
                prevExecPasswords[i] = newPassword;
                alreadyUpdated = true;
                break; // Only does this once
            }
        }

        if (alreadyUpdated == false) // Runs conditional if the array hasn't been updated into a previous place (indicating new user)
        {
            for (int i = 0; i < 10; i ++)
            {
                if (prevExecID[i] == 0) // Finds empty place in array and updates ID into that spot
                {
                    prevExecID[i] = newID;
                    prevExecPasswords[i] = newPassword;
                    alreadyUpdated = true;
                    break; // Only does this once
                }
            }
        }
    }
}

// Validates if user entered right ID and password
bool User:: validateUser(int proposedID, int proposedPassword)
{
    bool validate = false;

    for (int i = 0; i < 10; i ++) // Loops through records to check if user has been registered
    {
        if (proposedID == prevRegularID[i] && proposedPassword == prevRegularPasswords[i])
        {
            validate = true;
        }
        else if (proposedID == prevExecID[i] && proposedPassword == prevExecPasswords[i])
        {
            validate = true;
        }
    }

    return validate;
}
