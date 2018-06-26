#ifndef USER_H
#define USER_H

// Including libraries and files
#include <string>
#include "userinfo.h" // File containing structure

using namespace std;

// The User class is a base class for this whole program
class User {
private:
    int option; // Variable for user to select cashier or self-checkout options
    float totalPrice = 0; // Variable for the price

    /* The following arrays are used for product management.
     * Each index refers to the same product in all 3 arrays. */
    int itemsBought[10];  // Array for number of items bought
    string inventoryName[10] = {"Yogurt Parfait", "Bacon and Egg", "The Berloni Muffuleta", "Quattro Formaggio",
                                "Pappardelle Ragu", "Big Kahuna", "The Godfather", "Prosciutto",
                                "Smashed Avocado", "Macchiato"}; // Array for all product names
    float inventoryPrice[10] = {8, 14, 11, 10, 16, 17, 18, 18, 11, 3}; // Array for all prices
protected:
    int userID = 0; // Stores user's ID
    int password = 0; // Stores user's password
    int loyaltyType = 0; // Stores user's loyalty level (0 is not registered, 1 is regular loyalty, 2 is executive loyalty)
public:
    // Public variables to store regular and executive membership ID and passwords for use in all derived classes
    int prevRegularID[10];
    int prevRegularPasswords[10];
    int prevExecID[10];
    int prevExecPasswords[10];

    // Array to store ID and passwords for cashiers
    int cashierID[10];
    int cashierPassword[10];

    // Constructor to store past ID into user class for checking.
    User(userInfo regularID[10], userInfo execID[10], userInfo cashierRec[10], int enteredID, int enteredPassword, int enteredLoyalty) {
        for (int i = 0; i < 10; i ++){
            prevRegularID[i] = regularID[i].userID;
            prevRegularPasswords[i] = regularID[i].password;
            prevExecID[i] = execID[i].userID;
            prevExecPasswords[i] = execID[i].password;
            cashierID[i] = cashierRec[i].userID;
            cashierPassword[i] = cashierRec[i].password;
        }

        // Sets ID, password, loyalty level and email from given variables
        userID = enteredID;
        password = enteredPassword;
        loyaltyType = enteredLoyalty;
    }

    void buyItems(); // Function to state the number of items the user wishes to purchase
    void calculatePrice(); // Function to calculate the total price of all goods
    bool checkUniqueID (int proposedID); // Checks if proposed ID has already been used
    void getInfo(); // Asks whether user wants cashier or self-checkout
    void greeting(); // Initial greeting for user to welcome to cafe and gets ID and how user wants to checkout items
    void getUserCredentials(); // Gets id and password from user
    void purchaseSummary(); // Gives summary of all purchases and asks for money
    int returnID(); // Returns ID of user
    int returnLoyalty(); // Returns loyalty type of user
    int returnOption(); // Returns choice of user's pay (self or cashier)
    int returnPassword(); // Returns password of user
    void setID(int id); // Setting ID of user
    void setLoyalty(int level); // Setting loyalty of user
    void setPassword(int uPassword); // Setting password of user
    void updateRecords(int currentID, int newID, int currentPassword, int newPassword); // Updating regular and executive members records with new user
    bool validateUser(int proposedID, int proposedPassword); // Validates if user is registered with entered ID and password
};

#endif // USER_H
