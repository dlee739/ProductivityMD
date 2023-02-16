#include "todo_list_task.h"

/*!
 * \brief todo_list_task::getTitle
 * \return the title of the task in string
 * This method returns the task title
 */
const string &todo_list_task::getTitle() const
{
    return title;
}

/*!
 * \brief todo_list_task::setTitle
 * \param newTitle
 * This method sets the task title into a new title
 */
void todo_list_task::setTitle(const string &newTitle)
{
    title = newTitle;
}

/*!
 * \brief todo_list_task::getTaskId
 * \return the task id in int
 * This method returns the id of task
 */
int todo_list_task::getTaskId() const
{
    return taskId;
}

/*!
 * \brief todo_list_task::setTaskId
 * \param newTaskId
 * This method sets the task id to new task id
 */
void todo_list_task::setTaskId(int newTaskId)
{
    taskId = newTaskId;
}


/*!
 * \brief todo_list_task::todo_list_task
 * \param task_id
 * \param task_title
 * This is a constructor for todo_list_task
 */
todo_list_task::todo_list_task(int task_id, string task_title)
{
    // Initialization
    this->taskId = task_id;
    this->title = task_title;
}

// Destructor
todo_list_task::~todo_list_task() {

}
