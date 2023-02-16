/*!
 * ... text ...
 */



#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#include <iostream>
#include <stdexcept>
#include "Database.h"
#include "sha512.h"
#include "user.h"

using namespace std;

/*!
 * \brief The Authenticate class
 */
class Authenticate 
{
private:

public:
	Authenticate();
    ~Authenticate();
    bool login_user(string username, string password);
    int register_user(string username, string password, string firstname, string lastname);
};

#endif
