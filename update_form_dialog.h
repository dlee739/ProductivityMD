#ifndef UPDATE_FORM_DIALOG_H
#define UPDATE_FORM_DIALOG_H

#include <QDialog>
#include <QVector>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <QDateTime>
#include <QMessageBox>
#include "calendar.h"
#include "user.h"

namespace Ui {
class update_form_dialog;
}

/*!
 * \brief The update_form_dialog class
 */
class update_form_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit update_form_dialog(QWidget *parent = nullptr, QVector<QString>* c = new QVector<QString>());
    ~update_form_dialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::update_form_dialog *ui;
    QVector<QString>* contents;
    QString taskId;
};

#endif // UPDATE_FORM_DIALOG_H
