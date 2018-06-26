// Including necessary files and libraries
#include "cashiercheck.h"
#include "user.h"

#include <iostream>
#include <string>

using namespace std;

// Outputs all customer information (ID, password, email)
void CashierCheck:: checkInfo()
{
   cout << "You have the following customer info: " << endl;
   cout << "Customer ID: " << User::returnID() << endl;
   cout << "Customer Password: " << User::returnPassword() << endl;
}

// Portal to enter data
void CashierCheck:: dataEntry() {
    // Variable for storing option and previous ID. Also storing cashier's id and password
    int dataOption;
    int currentID = User::returnID();
    int currentPassword = User::returnPassword();

    cout << "Welcome to the data entry home page! What would you like to update? " << endl;
    do
    {
        cout << "Option 1: Review your information (1)" << endl;
        cout << "Option 2: Update information (2)" << endl;
        cout << "Option 3: Sign up for loyalty (3)" << endl;
        cout << "Option 4: Quit (4)" << endl;

        cin >> dataOption;
    } while(dataOption != 1 && dataOption != 2 && dataOption != 3 && dataOption != 4); // Validating option set by user

    // Calls respective function based on option asked by user. Quit option will skip the following conditionals
    if (dataOption == 1) {
        checkInfo();
    }
    else if (dataOption == 2) {
        updateInfo();
        User:: updateRecords(currentID, User::returnID(), currentPassword, User::returnPassword());
    }
    else if (dataOption == 3) {
        getLoyalty();
        User:: updateRecords(currentID, User::returnID(), currentPassword, User:: returnPassword()); // Calls function update records with new member

    }

    summaryOfMembers(); // Calls function to get an information summary of all member
    greeting();

}

// Function to get a new account/loyalty
void CashierCheck:: getLoyalty()
{
    // Variables used in the function
    int loyaltyLevel;
    int newID;
    int newPassword;

    cout << "Here are the following options regarding loyalty levels: " << endl;
    cout << "Regular loyalty: 10% off on any purchase." << endl;
    cout << "Executive loyalty: 20% off on any purchase." << endl;

    // Outputs loyalty level of user
    cout << "Your current loyalty level is: ";
    if (User::returnLoyalty() == 0)
    {
        cout << "Not registered" << endl;
    }
    else if (User::returnLoyalty() == 1)
    {
        cout << "Regular loyalty" << endl;
    }
    else
    {
        cout << "Executive loyalty" << endl;
    }

    cout << "Please enter your new loyalty level." << endl;

    // Gets new loyalty level and validates function
    do {
        cout << "Option 1: Regular loyalty --- Please enter 1. " << endl;
        cout << "Option 2: Executive loyalty --- Please enter 2. " << endl;
        cin >> loyaltyLevel;
    } while (loyaltyLevel != 1 && loyaltyLevel != 2);

    User::setLoyalty(loyaltyLevel); // Setting loyalty in base class

    cout << "Your current user ID is: " << User::returnID() << endl;

    // Gets user's ID until it is unique from previously entered IDs
    do {
        cout << "Please enter your desired ID: ";
        cin >> newID;
    } while (newID == User::returnID() || checkUniqueID(newID) == false);

    User::setID(newID); // Setting ID in base class

    cout << "Your old password is: " << User::returnPassword() << endl;

    // Gets user's new password until it is unique from previously entered password
    do {
        cout << "Please enter your password: ";
        cin >> newPassword;
    } while (newPassword == User::returnPassword());

    User::setPassword(newPassword); // Setting password
}

// Function to greet user to cashier
void CashierCheck:: greeting()
{
    // Variables for storing options and cashier information
    int userOption;
    int tempCashierID;
    int tempCashierPassword;

    // Getting cashier login
    do
    {
        cout << "Please enter the cashier's ID: " << endl;
        cin >> tempCashierID;
        cout << "Please enter the cashier's password: " << endl;
        cin >> tempCashierPassword;
    } while (validateCashier(tempCashierID, tempCashierPassword) == false);

    cout << "Welcome to the cashier check in program! Please either input your selected food items or review your data. " << endl;

    do {
        cout << "Please enter 1 if you would like to buy your items, or 2 to review your customer data.";
        cin >> userOption;
    } while (userOption != 1 && userOption != 2); // Validates option

    // Calls function to view data or calls function to buy items based on userOption
    if (userOption == 2) {
       dataEntry();
    }
    else
    {
        User:: buyItems();
        User:: purchaseSummary();
    }
}

// Gives summary of all members
void CashierCheck:: summaryOfMembers() {
    cout << "Here are the following records of all users in the cafe. For privacy, no passwords will be displayed." << endl;

    // Sorting arrays via bubble sort
    for (int i = 0; i < 10; i ++)
    {
        for (int j = 0; j < 9; j ++)
        {
            if (prevRegularID[j + 1] < prevRegularID[j])
            {
                int tempID = prevRegularID[j];
                //string tempEmail = prevRegEmails[j];

                prevRegularID[j] = prevRegularID[j + 1];
                //prevRegEmails[j] = prevRegEmails[j + 1];

                prevRegularID[j + 1] = tempID;
                //prevRegEmails[j + 1] = tempEmail;
            }

            if (prevExecID[j + 1] < prevExecID[j])
            {
                int tempID = prevExecID[j];
                //string tempEmail = prevExecEmails[j];

                prevExecID[j] = prevExecID[j + 1];
                //prevExecEmails[j] = prevExecEmails[j + 1];

                prevExecID[j + 1] = tempID;
                //prevExecEmails[j + 1] = tempEmail;
            }
        }
    }

    // Outputs regular members ID
    cout << "Regular membership members: " << endl;
    for (int i = 0; i < 10; i ++)
    {
        cout << "ID of Member " << i + 1 <<": " << prevRegularID[i] << endl;
    }

    // Outputs executive members ID and email
    cout << "Executive membership members: " << endl;
    for (int i = 0; i < 10; i ++)
    {
        cout << "ID of Member " << i + 1 <<": " << prevExecID[i] << endl;
    }
}

// Function to update previous information with new information
void CashierCheck:: updateInfo()
{
    // Variable to store user's option
    char userOption;

    cout << "You can now update your customer information: " << endl;

    // Asks if user wants to update ID
    do {
        cout << "Your old user ID is: " << User::returnID() << endl;
        cout << "Would you like to change your ID (y/n)? " << endl;
        cin >> userOption;
    } while (userOption != 'y' && userOption != 'n');

    // If the user wants to update the ID, it will make sure that there are no ID that are identical to the one entered
    if (userOption == 'y')
    {
        int newUserID;

        do {
           cout << "Please enter your new user ID: ";
           cin >> newUserID;
        } while (newUserID == User::returnID() || checkUniqueID(newUserID) == false); // Makes sure that entered ID is not identical to the previous and makes sure that ID is not identical to other IDs

        User::setID(newUserID); // Sets new ID
    }

    userOption = ' '; // Clearing user option for use in another case

    // Asks user if they would like to change the password and validates option
    do {
        cout << "Your old password: " << User::returnPassword() << endl;
        cout << "Would you like to change your password (y/n)?" << endl;
        cin >> userOption;
    } while (userOption != 'y' && userOption != 'n');

    // Changes password and validates if password is unique
    if (userOption == 'y') {
        int newPassword;

        do {
            cout << "Please enter your new password: ";
            cin >> newPassword;
        } while (newPassword == User::returnPassword()); // Makes sure that entered password is not identical to the previous password

        User::setPassword(newPassword); // Sets new password
    }

}

// Function to ensure that cashier is registered. Returns true if registered, and false if not registered
bool CashierCheck:: validateCashier(int cashID, int cashPass)
{
    bool validate = false;

    for (int i = 0; i < 10; i ++) // Loops through records to check if cashier has been registered
    {
        if (cashID == cashierID[i] && cashPass == cashierPassword[i])
        {
            validate = true;
        }
    }

    return validate;
}
