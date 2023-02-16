/*!
 * description: Database class storing the sqlite3 database
 * last modified: 11/7/2022
 */

#include "Database.h"

using namespace std;

/*!
 * \brief Database::Database - Database constructor
 */
Database::Database() {
    QString dbPath = QCoreApplication::applicationDirPath() + "/prodMS.db"; // initialize path for database
    string str = dbPath.toStdString();
    int open_result = sqlite3_open(str.c_str(), &database_handle); // open sqlite3
    if (open_result != SQLITE_OK) {
        throw ("Database failed to open."); // throw an error if database could not be opened or created
    }
    cout << "DB connection opened" << endl;

    string createTableQuery = "CREATE TABLE IF NOT EXISTS user (userId INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(20) NOT NULL, hashedPassword VARCHAR(300) NOT NULL, firstname VARCHAR(20) NOT NULL, lastname VARCHAR(20) NOT NULL);";
    char* err;
    int status1 = sqlite3_exec(database_handle, createTableQuery.c_str(), NULL, 0, &err);
    if (status1 != SQLITE_OK) {
        cout << "Creation Error for table user!" << endl;
                // need to return a signal to front end to terminate program
     } else {
        cout << "Table user created successfully." << endl;
      }

    string create_calendar_table_sql = "create table if not exists 'calendar_task' (taskStartTime TEXT NOT NULL, "
            "taskEndTime TEXT NOT NULL, taskTitle TEXT NOT NULL, taskDesc TEXT, taskUserId INTEGER, "
            "taskId INTEGER PRIMARY KEY AUTOINCREMENT, FOREIGN KEY(taskUserId) REFERENCES user(userId));";
    status1 = sqlite3_exec(database_handle, create_calendar_table_sql.c_str(), NULL, 0, &err);
    if (status1 != SQLITE_OK) {
        cout << "Creation Error for table calendar_task!" << endl;
                // need to return a signal to front end to terminate program
    } else {
        cout << "Table calendar_task created successfully." << endl;
    }

    string create_todo_list_sql = "CREATE TABLE IF NOT EXISTS todo_task (todoId INTEGER PRIMARY KEY AUTOINCREMENT, todoUserId INTEGER, todoTitle TEXT NOT NULL, FOREIGN KEY(todoUserId) REFERENCES user(userId) );";
    status1 = sqlite3_exec(database_handle, create_todo_list_sql.c_str(), NULL, 0, &err);
    if (status1 != SQLITE_OK) {
        cout << "Creation Error for table todo_task!" << endl;
                // need to return a signal to front end to terminate program
    } else {
        cout << "Table todo_task created successfully." << endl;
    }

    sqlite3_free(err);

}

/*!
 * \brief Database::~Database - Database destructor
 */
Database::~Database() {
    sqlite3_close(database_handle); // need to close the connection to database when logger is destroyed to ensure no data loss
    cout << "Database Connection Closed." << endl;
}

const Database* Database::_instance = NULL;
/*!
 * \brief Database::get_instance - Returns the database instance
 * \return const Database& - instance
 */
const Database& Database::get_instance() {
    if (_instance == NULL) { // if no instance already in the Database, create one
        _instance = new Database();
    }
    return *_instance;
}

/*!
 * \brief Database::get_db - fetches the database_handle
 * \return sqlite3*  - database handle
 */
sqlite3* Database::get_db() const{
    return database_handle;
}

/*!
 * \brief Database::deleteDB - deletes an existing instance of a database
 */
void Database::deleteDB(){
   delete _instance; // delete object and free up memory
   _instance = NULL; // so GetInstance will still work.
}
