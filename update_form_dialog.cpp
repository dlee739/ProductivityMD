#include "update_form_dialog.h"
#include "ui_update_form_dialog.h"


/*!
 * \brief update_form_dialog::update_form_dialog
 * constructor for update form dialog from main window
 * \param parent
 */
update_form_dialog::update_form_dialog(QWidget *parent, QVector<QString>* content_vec) :
    QDialog(parent),
    ui(new Ui::update_form_dialog)
{
    ui->setupUi(this);

    // read row contents vector
    contents = content_vec;
    QString startTime, endTime, title, desc;
    for (int i = 0; i < contents->size(); i++) {
        if (i == 0) {
            startTime = contents->at(i);
        }
        if (i == 1) {
            endTime = contents->at(i);
        }
        if (i == 2) {
            title = contents->at(i);
        }
        if (i == 3) {
            desc = contents->at(i);
        }
    }

    taskId = contents->last();


    ui->start_update->setDateTime(QDateTime::fromString(startTime, "dd/MM/yyyy hh:mm:ss"));
    ui->end_update->setDateTime(QDateTime::fromString(endTime, "dd/MM/yyyy hh:mm:ss"));
    ui->start_update->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->end_update->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->title_update->setText(title);
    ui->desc_update->setText(desc);
}

/*!
 * \brief update_form_dialog::~update_form_dialog
 * destructor
 */
update_form_dialog::~update_form_dialog()
{
    delete ui;
}

/*!
 * \brief update_form_dialog::on_buttonBox_accepted
 * this function is to handle the submit button. when user's input is valid, the function will update the current selected task.
 * \param void
 */
void update_form_dialog::on_buttonBox_accepted()
{
    QString title_update = ui->title_update->text();
    QString desc_update = ui->desc_update->text();


    QDateTimeEdit * start_time = ui->start_update;
    QDateTimeEdit * end_time = ui->end_update;
    //set date format
    ui->start_update->setDisplayFormat("dd/MM/yyyy hh:mm:ss");
    ui->end_update->setDisplayFormat("dd/MM/yyyy hh:mm:ss");

    //start time and end time string
    QDateTime dt_s = start_time->dateTime();
    QString start_str = dt_s.toString(ui->start_update->displayFormat());

    QDateTime dt_e = end_time->dateTime();
    QString end_str = dt_e.toString(ui->end_update->displayFormat());
    if (title_update.trimmed()==""){
        QMessageBox::warning(this, "error", "title is empty or containing space only!");
    }
    else if(desc_update.trimmed()==""){
         QMessageBox::warning(this, "error", "description is empty or containing space only!");
    }else if(dt_s >= dt_e){
        QMessageBox::warning(this, "error", "invalid time, end time must greater than start time!");
    }else{
        QMessageBox::information(this, "note", "task updated!");
        // here you can add insert stuff
        // this calendar obj and test id should be obtained from singleton obj
        std::string test_user_id = to_string(user::get_instance().get_id());
        calendar* new_calendar = new calendar(test_user_id);
        // update task
        new_calendar->updateTaskStartTime(this->taskId.toStdString(), start_str.toStdString());
        new_calendar->updateTaskEndTime(this->taskId.toStdString(), end_str.toStdString());
        new_calendar->updateTaskTitle(this->taskId.toStdString(), title_update.toStdString());
        new_calendar->updateTaskDesc(this->taskId.toStdString(), desc_update.toStdString());
        delete new_calendar;
    }
    this->close();
}

/*!
 * \brief update_form_dialog::on_buttonBox_rejected
 * this function is to handle the close button. when user clicks it, it will close the dialog
 * \param void
 */
void update_form_dialog::on_buttonBox_rejected()
{
    this->close();
}

