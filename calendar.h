/*!
 *
 * Author: Author: group 7
 */

#ifndef CALENDAR_H
#define CALENDAR_H
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <sqlite3.h>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include "Database.h"
#include "calendar_task.h"
/*!
 * \brief The calendar class
 */
class calendar {
private:
    std::string currentUserId;

public:
    calendar(std::string userId);
    ~calendar();
    void addCalendarTask(std::string newTaskStartTime, std::string newTaskEndTime,
                         std::string newTaskTitle, std::string newTaskDesc, std::string newTaskUserId);
    std::vector<calendar_task> getTasksByIdAndStartingDate(std::string userId, std::string date);
    std::vector<calendar_task> searchTaskByTitleAndDesc(std::string userId, std::string title, std::string desc);
    std::vector<calendar_task> searchTaskByTitle(std::string userId, std::string title);
    std::vector<calendar_task> searchTaskByDesc(std::string userId, std::string desc);

    // boolean addMultipleCalendarTasks(vector<calendar_task> list);
    void updateTaskStartTime(std::string taskId, std::string newStartTime);
    void updateTaskEndTime(std::string taskId, std::string newEndTime);
    void updateTaskTitle(std::string taskId, std::string newTaskTitle);
    void updateTaskDesc(std::string taskId, std::string newTaskDesc);
    void deleteTaskById(std::string taskId); 

};


#endif
