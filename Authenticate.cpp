/*!
 * description: Authenticate class deals with the registration and login of user into the system
 * last modified: 11/7/2022
 */

#include "Authenticate.h"

/*!
 * \brief Authenticate::Authenticate - Authenticate constructor
 */
Authenticate::Authenticate(){}

/*!
 * \brief Authenticate::~Authenticate - Authenticate destructor
 */
Authenticate::~Authenticate(){}

// Login function
/*!
 * \brief Authenticate::login_user - Login function for authenticate object, used for verifying login of users.
 * \param username - username of user
 * \param password - password of user
 * \return - true if login is successful,
 *           false otherwise.
 */
bool Authenticate::login_user(string username, string password)
{
    const string query_user = "SELECT * FROM user WHERE username = \'" + username + "\';";
    sqlite3_stmt* statement;
    sqlite3_prepare_v2(Database::get_instance().get_db(), query_user.c_str(), -1, &statement, 0); // Converts sql query into byte-code program - necessary to execute an SQL statement

    string db_username, db_hashed_password, db_fname, db_lname; // username and password inside the db
    int db_id;
    int status = sqlite3_step(statement);
    if (status == SQLITE_DONE){ // username does not exist (no rows returned)
        return false;
    }
    else { // username exists - checking if passwords match 
        db_username = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1))); // username column needs to be in position 1
        db_hashed_password = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2))); // hashed password column need to be in position 2 
        db_fname = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
        db_lname = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
        db_id = sqlite3_column_int(statement, 0);
        string hashed_result = sha512(password);
        if (hashed_result != db_hashed_password) { // password does not match
            sqlite3_finalize(statement);
            return false;
        }

        // NEED TO CREATE USER OBJECT
        user::get_instance();
        user::get_instance().set_id(db_id);
        user::get_instance().set_username(db_username);
        user::get_instance().set_firstname(db_fname);
        user::get_instance().set_lastname(db_lname);

        // DEBUG
        cout << user::get_instance().get_firstname() << " " << user::get_instance().get_lastname() << " (User ID: " << user::get_instance().get_id() << ")" << endl;
        cout << "Username: " << user::get_instance().get_username() << endl;

        sqlite3_finalize(statement);
        return true;
    }
    return true;
}

/*!
 * \brief Authenticate::register_user - Register function for authenticate object used for registering new user.
 * \param username - username of user
 * \param password - password of user
 * \param firstname - firstname of user
 * \param lastname - lastname of user
 * \return - 0 if username already exists in database,
 *           1 if registration is successful,
 *           -1 if insertion failed with sqlite3.
 */
int Authenticate::register_user(string username, string password, string firstname, string lastname)
{
    const string query_user = "SELECT * FROM user WHERE username = \'" + username + "\';";
    sqlite3_stmt* statement;
    sqlite3_prepare_v2(Database::get_instance().get_db(), query_user.c_str(), -1, &statement, 0); // Converts sql query into byte-code program - necessary to execute an SQL statement

    int status = sqlite3_step(statement);
    if (status != SQLITE_DONE){ // username already exists in database
        cout << "User exists: "<< status << endl;
        return 0;
    }
    sqlite3_finalize(statement);

    string hashed_password = sha512(password); // hash password using sha512 algorithm
    const string query_insert_user = "INSERT INTO user (username, hashedPassword, firstname, lastname) VALUES (\'" + username + "\', \'" + hashed_password + "\', \'" + firstname + "\', \'" + lastname + "\');";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(Database::get_instance().get_db(), query_insert_user.c_str(), -1, &stmt, 0); // Converts sql query into byte-code program - necessary to execute an SQL statement
    status = sqlite3_step(stmt);
    if (status != SQLITE_DONE){ // something went wrong with inserting
        cout << "Something went wrong with inserting, status: "<< status << endl;
        return -1;
    }
    sqlite3_finalize(stmt);
    return 1; // register success
}

