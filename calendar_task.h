/*!
 * ... text ...
 */

#ifndef CALENDAR_TASK_H
#define CALENDAR_TASK_H
#include <string>
/*!
 * \brief The calendar_task class
 */
class calendar_task {
private:
    std::string taskDesc;
    std::string taskTitle;
    std::string taskId;
    std::string taskStartTime;
    std::string taskEndTime;

public:
    calendar_task(std::string currentTaskId, std::string currentTaskStartTime, std::string currentTaskEndTime,
                  std::string currentTaskTitle, std::string currentTaskDesc);
    std::string getTaskDesc();
    std::string getTaskTitle();
    std::string getTaskId();
    std::string getTaskStartTime();
    std::string getTaskEndTime();

    void setTaskDesc(std::string newTaskDesc);
    void setTaskTitle(std::string newTaskTitle);
    void setTaskStartTime(std::string newStartTime);
    void setTaskEndTime(std::string newTaskEndTime);
};


#endif
