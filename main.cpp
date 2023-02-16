/*!
 * This is entrance class for running the entire program.
 */


#include "mainwindow.h"

#include <QApplication>
#include <calendar.h>
#include "loginui.h"
#include "Database.h"
using namespace std;
/*!
 * \brief entrance class
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginUI login;
    Database::get_instance(); // open database at beginning of application (singleton)

    QApplication::setQuitOnLastWindowClosed(false); // Disallow application to close itself upon closing QDialog Window

    login.show();

    // delete DB
     Database::deleteDB(); // delete memory allocated to database
    return a.exec();
}
