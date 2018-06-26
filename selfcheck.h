#ifndef SELFCHECK_H
#define SELFCHECK_H

// Including necessary files
#include "user.h"
#include "userinfo.h"

/* SelfCheck is a class for self-checkout
 * It is derived in a public fashion from the base class of User
*/
class SelfCheck : public User
{
public:
    // Linking constructor of SelfCheck to User class constructor to transfer existing records
    SelfCheck(userInfo regularID[10], userInfo execID[10], userInfo cashierRec[10], int enteredID, int enteredPassword, int enteredLoyalty) : User(regularID, execID, cashierRec, enteredID, enteredPassword, enteredLoyalty) {
    }

    void greeting(); // Overriding greeting of User base class

};

#endif // SELFCHECK_H
