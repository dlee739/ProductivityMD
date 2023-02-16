/*!
 * this class is for accessing the sqlite3 database 
 * Author: group 7
 */


#include "calendar.h"

using namespace std;
/*!
 * \brief calendar::calendar
 * \param userId
 * constructor
 */
calendar::calendar(string userId) {
    currentUserId = userId;
}


/*!
 * \brief calendar::calendar
 * destructor
 */
calendar::~calendar() {

}

/*!
 * \brief calendar::addCalendarTask
 * \param newTaskStartTime
 * \param newTaskEndTime
 * \param newTaskTitle
 * \param newTaskDesc
 * \param newTaskUserId
 * this method is to add calendar task that user inputs to the table 'calendar_task'
 */
void calendar::addCalendarTask(string newTaskStartTime, string newTaskEndTime, string newTaskTitle, string newTaskDesc, string newTaskUserId) {
    char *messaggeError = 0;
    string sql_insert = "insert into 'calendar_task' (taskStartTime, taskEndTime, taskTitle, taskDesc, taskUserId) "
                        "values ('" + newTaskStartTime + "', '" + newTaskEndTime  + "', '"
                        + newTaskTitle  + "', '"+ newTaskDesc  + "', '"
                        + newTaskUserId + "');";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_insert.c_str(), NULL, 0, &messaggeError);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Insertion operation done successfully\n");
    }
}

// Create a callback function
/*!
 * \brief callback
 * \param task_list
 * \param argc
 * \param argv
 * \param azColName
 * \return the status of database accessing
 * This function is a callback function for reading the rows of 'calendar_task' table
 */
static int callback(void *task_list, int argc, char **argv, char **azColName) {
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    string taskStartTime;
    string taskEndTime;
    string taskTitle;
    string taskDesc;
    string taskUserId;
    string taskId;
    // calendar_task' (taskStartTime, taskEndTime, taskTitle, taskDesc, taskUserId)
    for(int i = 0; i < argc; i++) {
        // Show column name, value, and newline
        if (strcmp(azColName[i], "taskStartTime") == 0) {
            taskStartTime = argv[i];
        }
        if (strcmp(azColName[i], "taskEndTime") == 0) {
            taskEndTime = argv[i];
        }
        if (strcmp(azColName[i], "taskTitle") == 0) {
            taskTitle = argv[i];
        }
        if (strcmp(azColName[i], "taskDesc") == 0) {
            taskDesc = argv[i];
        }
        if (strcmp(azColName[i], "taskId") == 0) {
            taskId = argv[i];
        }
    }
    calendar_task *task1 = new calendar_task(taskId, taskStartTime, taskEndTime, taskTitle, taskDesc);
    vector<calendar_task>* list = (vector<calendar_task>*) task_list;
    list->push_back(*task1);
    return 0;
}
/*!
 * \brief calendar::getTasksByIdAndStartingDate
 * \param userId
 * \param date
 * \return a vector of calendar_task obj that containing the data
 * this method is get a list of tasks by user id and starting date 
 */
vector<calendar_task> calendar::getTasksByIdAndStartingDate(string userId, string date) {
    char *messaggeError = 0;
    vector<calendar_task> result;
    string sql_select = "select * from 'calendar_task' where taskStartTime like '" +
            date + "%' and taskUserId='" + userId + "';";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_select.c_str(), callback, &result, &messaggeError);
    if(rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Selection operation done successfully\n");
    }
    return result;
}
/*!
 * \brief calendar::updateTaskStartTime
 * \param taskId
 * \param newStartTime
 * this method is to update the input task starting time
 */
void calendar::updateTaskStartTime(string taskId, string newStartTime) {
    char *messaggeError = 0;
    string sql_insert = "update 'calendar_task' set taskStartTime = '"+ newStartTime +"' where taskId = '" + taskId +"';";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_insert.c_str(), NULL, 0, &messaggeError);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Update operation for task starting time done successfully\n");
    }
}
/*!
 * \brief calendar::updateTaskEndTime
 * \param taskId
 * \param newEndTime
 * this method is to update the input task end time
 */
void calendar::updateTaskEndTime(string taskId, string newEndTime) {
    char *messaggeError = 0;
    string sql_insert = "update 'calendar_task' set taskEndTime = '"+ newEndTime +"' where taskId = '" + taskId +"';";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_insert.c_str(), NULL, 0, &messaggeError);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Update operation for task End time done successfully\n");
    }
}
/*!
 * \brief calendar::updateTaskTitle
 * \param taskId
 * \param newTaskTitle
 * this method is to update task title 
 */
void calendar::updateTaskTitle(string taskId, string newTaskTitle) {
    char *messaggeError = 0;
    string sql_insert = "update 'calendar_task' set taskTitle = '"+ newTaskTitle +"' where taskId = '" + taskId +"';";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_insert.c_str(), NULL, 0, &messaggeError);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Update operation for task title done successfully\n");
    }
}
/*!
 * \brief calendar::updateTaskDesc
 * \param taskId
 * \param newTaskDesc
 * this method is to update task descritption
 */
void calendar::updateTaskDesc(std::string taskId, std::string newTaskDesc) {
    char *messaggeError = 0;
    string sql_insert = "update 'calendar_task' set taskDesc = '"+ newTaskDesc +"' where taskId = '" + taskId +"';";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_insert.c_str(), NULL, 0, &messaggeError);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Update operation for task desc done successfully\n");
    }
}

/*!
 * \brief calendar::deleteTaskById
 * \param taskId
 * this method is to delete a calendar task by its taskId
 */
void calendar::deleteTaskById(std::string taskId) {
     char *messaggeError = 0;
     string sql_delete = "delete from 'calendar_task' where taskId= '" + taskId +"';";
     int rc = sqlite3_exec(Database::get_instance().get_db(), sql_delete.c_str(), NULL, 0, &messaggeError);
     if( rc != SQLITE_OK ) {
         fprintf(stderr, "SQL error: %s\n", messaggeError);
         sqlite3_free(messaggeError);
     } else {
         fprintf(stdout, "Delete operation for task desc done successfully\n");
     }
}

/*!
 * \brief calendar::searchTaskByTitleAndDesc
 * \param userId
 * \param title
 * \param desc
 * this method is to search tasks by given desc and title
 */
std::vector<calendar_task> calendar::searchTaskByTitleAndDesc(std::string userId, std::string title, std::string desc) {
    char *messaggeError = 0;
    vector<calendar_task> result;
    string sql_select = "select * from 'calendar_task' where taskTitle like '%" +
            title + "%' and taskDesc like '%" +
            desc + "%' and  taskUserId='" + userId + "';";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_select.c_str(), callback, &result, &messaggeError);
    if(rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Search by Title and Desc operation done successfully\n");
    }
    return result;
}

/*!
 * \brief calendar::searchTaskByTitle
 * \param userId
 * \param title
 * this method is to search tasks by given title
 */
std::vector<calendar_task> calendar::searchTaskByTitle(std::string userId, std::string title) {
    char *messaggeError = 0;
    vector<calendar_task> result;
    string sql_select = "select * from 'calendar_task' where taskTitle like '%" +
            title + "%' and  taskUserId='" + userId + "';";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_select.c_str(), callback, &result, &messaggeError);
    if(rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Search by Title operation done successfully\n");
    }
    return result;
}

/*!
 * \brief calendar::searchTaskByDesc
 * \param userId
 * \param desc
 * this method is to search tasks by given desc
 */
std::vector<calendar_task> calendar::searchTaskByDesc(std::string userId, std::string desc) {
    char *messaggeError = 0;
    vector<calendar_task> result;
    string sql_select = "select * from 'calendar_task' where taskDesc like '%" +
            desc + "%' and  taskUserId='" + userId + "';";
    int rc = sqlite3_exec(Database::get_instance().get_db(), sql_select.c_str(), callback, &result, &messaggeError);
    if(rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", messaggeError);
        sqlite3_free(messaggeError);
    } else {
        fprintf(stdout, "Search by Desc operation done successfully\n");
    }
    return result;
}
