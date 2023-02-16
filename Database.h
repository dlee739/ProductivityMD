/*!
 * ... text ...
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <QString>
#include <QStandardPaths>
#include <QApplication>
#include <sqlite3.h>
/*!
 * \brief The Database class
 */
class Database 
{
private:
    sqlite3* database_handle;
    static const Database* _instance;
    Database();

public:
    ~Database();
    static const Database& get_instance();  // const?
    sqlite3* get_db() const;
    static void deleteDB();

};

#endif
