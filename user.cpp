#include <iostream>
#include "user.h"

using namespace std;

user::user() {}

user::~user() {}

user* user::_instance = NULL;
/*!
 * \brief method: get_instance()
 * \return the user object created
 */
user& user::get_instance() {
    if (_instance == NULL) { // if no user instance already, create one
        _instance = new user();
    }
    return *_instance; // return the user object
}

/*!
 * \brief method: delete_user
 * This method is called when the application is terminating to delete the user instance and free up memory to prevent memory leaks
  */
void user::delete_user() { // should be called when user terminates program
    cout << endl << "deleting instance" << endl;
    delete _instance; // delete object and free up memory
   _instance = NULL;
}

/*! \brief user::set_username
 *  \param username - the username of the logged in user
 * Method will set the username arttibute to be the username of the logged in user
 */
void user::set_username(string username){
    this->username = username;
}

/*! \brief user::set_firstname
 *  \param fname - the first name of the logged in user
 * Method will set the firstname arttibute to be the first name of the logged in user
 */
void user::set_firstname(string fname){
    this->firstname = fname;
}

/*! \brief user::set_lastname
 *  \param lname - the last name of the logged in user
 * Method will set the lastname arttibute to be the last name of the logged in user
 */
void user::set_lastname(string lname){
    this->lastname = lname;
}

/*! \brief user::set_id
 *  \param userid - the user id of the logged in user
 * Method will set the id arttibute to be the user id of the logged in user
 */
void user::set_id(int userid){
    this->user_id = userid;
}

/*!
 * \brief user::get_username
 * \return a string which is the username of the logged in user
 */
string user::get_username() const{
    return this->username;
}

/*!
 * \brief user::get_firstname
 * \return a string which is the first name of the logged in user
 */
string user::get_firstname() const{
    return this->firstname;
}

/*!
 * \brief user::get_lastname
 * \return a string which is the last name of the logged in user
 */
string user::get_lastname() const{
    return this->lastname;
}

/*!
 * \brief user::get_id
 * \return an int which is the user id of the logged in user
 */
int user::get_id() const{
    return this->user_id;
}

