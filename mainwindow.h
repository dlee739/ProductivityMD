/*!
 * this is header file for main Calendar dashboard
 * Author: group 7
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <QThread>
#include <iostream>
#include <calendar.h>
#include <QMessageBox>
#include <QVector>

#include "task_form.h"
#include "update_form_dialog.h"
#include "user.h"
#include "Database.h"
#include "todo_list.h"
#include "todo_form.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
 //   void on_pushButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void TableWidgetDisplay(const QDate &date);

    void on_newTodoButton_clicked();

    void on_completeTodoButton_clicked();

    void on_todolistWidget_itemChanged(QListWidgetItem *item);

    void closeEvent(QCloseEvent *event);

    void on_logoutButton_clicked();

    void on_search_button_clicked();

    void on_deleteButton_clicked();

    void on_updateButton_clicked();

    void on_addTaskButton_clicked();

    void quoteGen();

    void getQu(QNetworkReply*);

    void on_quoteButton_clicked();

private:
    Ui::MainWindow *ui;

    // Widgets

    // TODO LIST
    todo_list todo;
    void update_todo();
    QString myURL = "https://api.api-ninjas.com/v1/quotes?category=inspirational";
    QByteArray key = "/2BldEv5h6kJPBzq2ie/dw==wk7sjrfRgT1AYb91";
    QByteArray header = "X-Api-Key";
};
#endif // MAINWINDOW_H
