#include "todo_form.h"
#include "ui_todo_form.h"

/*!
 * \brief todo_form::todo_form
 * \param parent
 * This is a constructor for todo_form
 */
todo_form::todo_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::todo_form)
{
    ui->setupUi(this);
}

/*!
 * \brief todo_form::~todo_form
 * Destructor
 */
todo_form::~todo_form()
{
    delete ui;
}

/*!
 * \brief todo_form::on_confirmButton_clicked
 * This is an Event listener for confirm button
 */
void todo_form::on_confirmButton_clicked()
{
    if (!(ui->todoLineEdit->text().isEmpty())) { // add a new task only if its textfield is not empty
        todo->insert(ui->todoLineEdit->text().toStdString()); // insert to todo list
        close(); // close current prompt window (todo_form)

        // on_cancelTodoButton_clicked(); // reset button states
    }
}

/*!
 * \brief todo_form::on_cancelButton_clicked
 * This is an event listener for cancel button
 */
void todo_form::on_cancelButton_clicked()
{
    // Close dialog
    close();
}

/*!
 * \brief todo_form::setTodo
 * \param list
 * This method is a Setter for todo_list object
 */
void todo_form::setTodo(todo_list *list)
{
    todo = list;
}
