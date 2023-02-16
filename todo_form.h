#ifndef TODO_FORM_H
#define TODO_FORM_H

#include <QDialog>
#include "todo_list.h"

namespace Ui {
class todo_form;
}

/*!
 * \brief The todo_form class
 */
class todo_form : public QDialog
{
    Q_OBJECT

public:
    explicit todo_form(QWidget *parent = nullptr);
    ~todo_form();

    void setTodo(todo_list *newTodo);

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::todo_form *ui;

    todo_list *todo;
};

#endif // TODO_FORM_H
