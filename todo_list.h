#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Database.h"
#include "user.h"
#include "todo_list_task.h"

using namespace std;

/*!
 * \brief The todo_list class
 * Represents the list of to-do tasks
 * This class holds a vector storing all the to-do tasks for the logged in user
 */
class todo_list
{
private:
    int size;
    vector<todo_list_task> todo_tasks;
public:
    todo_list();
    ~todo_list();

    void insert(string new_task);
    void remove_task(string task);

    string get_title_at(int index);
    string search_by_taskId(int id);
    int search_by_taskTitle(string title);

    int getSize();
};

#endif // TODO_LIST_H
