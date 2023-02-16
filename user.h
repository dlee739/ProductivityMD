/*!
 * ... text ...
 */

#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

/*!
 * \brief The user class
 * The user clas represents the user that is logged in
 * It is implemented as a singleton so that all parts of the application can access the user information of the logged in user
 * The user object created will store the username, first name, last name and the user id as attributes
 */
class user
{
private:
    friend class Authenticate;

    static user* _instance;  // a reference to the singleton user object
    string username;
    string firstname;
    string lastname;
    int user_id;

    user();
    void set_username(string username);
    void set_firstname(string fname);
    void set_lastname(string lname);
    void set_id(int userid);

public:
    ~user();
    static user& get_instance();
    static void delete_user();
    string get_username() const;
    string get_firstname() const;
    string get_lastname() const;
    int get_id() const;

};

#endif
