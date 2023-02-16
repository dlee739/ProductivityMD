/*!
 * ... text ...
 */

#ifndef LOGINUI_H
#define LOGINUI_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <regex>
#include "Authenticate.h"
#include <QMessageBox>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginUI; }
QT_END_NAMESPACE
/*!
 * \brief The LoginUI class
 */
class LoginUI : public QMainWindow
{
    Q_OBJECT

public:
    LoginUI(QWidget *parent = nullptr);
    ~LoginUI();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::LoginUI *ui;
    QString username;
    QString password;
    bool validatePassword(std::string password);
};
#endif // LOGINUI_H
