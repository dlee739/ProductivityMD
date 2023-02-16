/*!
 * this class is for temporary saving the data obtaining from calendar_task
 * Author: group 7
 */


#include "calendar_task.h"
using namespace std;
/*!
 * \brief calendar_task::calendar_task
 * \param currentTaskId
 * \param currentTaskStartTime
 * \param currentTaskEndTime
 * \param currentTaskTitle
 * \param currentTaskDesc
 * constructor
 */
calendar_task::calendar_task(std::string currentTaskId, std::string currentTaskStartTime, std::string currentTaskEndTime,
                             std::string currentTaskTitle, std::string currentTaskDesc) {
    // NOTE: this user id should be obtained by singleton obj for whole access
    taskId = currentTaskId;
    taskStartTime = currentTaskStartTime;
    taskEndTime = currentTaskEndTime;
    taskTitle = currentTaskTitle;
    taskDesc = currentTaskDesc;
}
/*!
 * \brief calendar_task::getTaskStartTime
 * \return the task start time in string 
 * this method is to get task start time of the calendar_task object
 */
string calendar_task::getTaskStartTime() {
    return taskStartTime;
}
/*!
 * \brief calendar_task::getTaskTitle
 * \return task title in string
 * this method is to get task title of the calendar_task object
 */
string calendar_task::getTaskTitle() {
    return taskTitle;
}
/*!
 * \brief calendar_task::getTaskEndTime
 * \return task end time in string
 * this method is to get task end time of the calendar_task object
 */
string calendar_task::getTaskEndTime() {
    return taskEndTime;
}
/*!
 * \brief calendar_task::getTaskDesc
 * \return task desc in string
 * this method is to get task description of the calendar_task object
 */
string calendar_task::getTaskDesc() {
    return taskDesc;
}

/*!
 * \brief calendar_task::getTaskDesc
 * \return task desc in string
 * this method is to get task id of the calendar_task object
 */
string calendar_task::getTaskId() {
    return taskId;
}

/*!
 * \brief calendar_task::setTaskDesc
 * \param newTaskDesc
 * \return void
 * this method is to set task description of the calendar_task object
 */
void calendar_task::setTaskDesc(string newTaskDesc) {
    taskDesc = newTaskDesc;
}
/*!
 * \brief calendar_task::setTaskTitle
 * \param newTaskTitle
 * this method is to set task title of the calendar_task object
 */
void calendar_task::setTaskTitle(string newTaskTitle) {
    taskTitle = newTaskTitle;
}
/*!
 * \brief calendar_task::setTaskStartTime
 * \param newStartTime
 * this method is to set task start time of the calendar_task object
 */
void calendar_task::setTaskStartTime(string newStartTime) {
    taskStartTime = newStartTime;
}
/*!
 * \brief calendar_task::setTaskEndTime
 * \param newTaskEndTime
 * this method is to set task end time of the calendar_task object
 */
void calendar_task::setTaskEndTime(string newTaskEndTime) {
    taskEndTime = newTaskEndTime;
}
