#ifndef CASHIERCHECK_H
#define CASHIERCHECK_H

// Including necessary files
#include "user.h"
#include "userinfo.h"

/* CashierCheck is a class for cashier checkout
 * It is derived in a public fashion from the base class of User
*/
class CashierCheck : public User
{
public:
    // Linking constructor of SelfCheck to User class constructor to transfer existing records
    CashierCheck(userInfo regularID[10], userInfo execID[10], userInfo cashierRec[10], int enteredID, int enteredPassword, int enteredLoyalty) : User(regularID, execID, cashierRec, enteredID, enteredPassword, enteredLoyalty) {
    }

    void checkInfo(); // Allows user to check their own information
    void dataEntry(); // Asks user what they would like to do with the cashier
    void getLoyalty(); // Allows user to get a new loyalty and gets ID and other necessary details
    void greeting(); // Overriding greeting of User base class
    void summaryOfMembers(); // Outputs summary of all existing records.
    void updateInfo(); // Allows user to update their information
    bool validateCashier(int cashID, int cashPass); // Checks to make sure cashier is registered

};

#endif // CASHIERCHECK_H
