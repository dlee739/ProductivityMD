/*!
 * this class if for adding task form window pop-ip
 * Author: group 7
 */


#include "task_form.h"
#include "ui_task_form.h"


/*!
 * \brief task_form::task_form
 * constructor for task form window
 * \param parent
 */
task_form::task_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::task_form)
{
    ui->setupUi(this);
}
/*!
 * \brief task_form::~task_form
 * destructor
 */
task_form::~task_form()
{
    delete ui;
}
/*!
 * \brief task_form::on_buttonBox_accepted
 *  this fuction get the info that users typed, check if the input valid and insert to database.
 */
void task_form::on_buttonBox_accepted()
{
    //title description is here
    // getting user input

           QString title = ui->lineEdit_title->text();
           QString description = ui->lineEdit_description->toPlainText();

           QDateTimeEdit * start_time = ui->dateTimeEdit_startTime;
           QDateTimeEdit * end_time = ui->dateTimeEdit_endTime;
           ui->dateTimeEdit_startTime->setDisplayFormat("dd/MM/yyyy hh:mm:ss");
           ui->dateTimeEdit_endTime->setDisplayFormat("dd/MM/yyyy hh:mm:ss");
    //set date format


           //start time and end time string
           QDateTime dt_s = start_time->dateTime();
           QString start_str = dt_s.toString(ui->dateTimeEdit_startTime->displayFormat());

           QDateTime dt_e = end_time->dateTime();
           QString end_str = dt_e.toString(ui->dateTimeEdit_endTime->displayFormat());


           QMessageBox::information(this, "test", "This is a test message showing we are actually got the input that user typed! \n data already stored in database \n" + title+"\n"+description + "\n" + start_str + "\n" + end_str);


           if (title.trimmed()==""){
               QMessageBox::warning(this, "error", "title is empty or containing space only!");
           }
           else if(description.trimmed()==""){
                QMessageBox::warning(this, "error", "description is empty or containing space only!");
           }else if(dt_s >= dt_e){
               QMessageBox::warning(this, "error", "invalid time, end time must greater than start time!");
           }else{
               QMessageBox::information(this, "note", "task added!");

               // calling backend service to insert new task
               // this calendar obj and test id should be obtained from singleton obj
               std::string test_user_id = to_string(user::get_instance().get_id());
               calendar* new_calendar = new calendar(test_user_id);
               new_calendar->addCalendarTask(start_str.toStdString(), end_str.toStdString(), description.toStdString(), title.toStdString(), test_user_id);
               delete new_calendar;
           }
}

