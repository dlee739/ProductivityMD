#ifndef TODO_LIST_TASK_H
#define TODO_LIST_TASK_H

#include <iostream>
#include <string>

using namespace std;

/*!
 * \brief The todo_list_task class
 */
class todo_list_task
{
private:
    int taskId;
    string title;
public:
    todo_list_task(int task_id, string task_title);
    ~todo_list_task();

    const string &getTitle() const;
    void setTitle(const string &newTitle);
    int getTaskId() const;
    void setTaskId(int newTaskId);
};

#endif // TODO_LIST_TASK_H
