/*!
 * this is a header file for add task window
 * Author: group 7
 */


#ifndef TASK_FORM_H
#define TASK_FORM_H

#include <QDialog>
#include <calendar.h>
#include <QMessageBox>
#include "user.h"

/*!
 *
 */
namespace Ui {
class task_form;
}
/*!
 * \brief The task_form class
 */
class task_form : public QDialog
{
    Q_OBJECT

public:
    explicit task_form(QWidget *parent = nullptr);
    ~task_form();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::task_form *ui;
};

#endif // TASK_FORM_H
