/*!
 * this class is for Main calendar dashboard UI
 * Author: group 7
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"

/*!
 * \brief MainWindow::MainWindow this is a constructor for main dashboard UI
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TableWidgetDisplay(QDate::currentDate());

    update_todo();// Todo
    quoteGen(); //quote gettter
}

/*!
 * \brief MainWindow::~MainWindow  --- destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief MainWindow::on_calendarWidget_clicked
 * this function will return the specific date when user clicking the Calendar
 * \param date
 */
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    const QDate date2 = date;
    QMessageBox::information(this, "test", "We store the date string below to return stored tasks related to that date: \n" + date2.toString("dd/MM/yyyy"));
   // get a list of the task by clicked date
    TableWidgetDisplay(date2);
}

/*!
 * \brief MainWindow::TableWidgetDisplay
 * this function will display calendar task by using table widget
 * \param date
 */
void MainWindow::TableWidgetDisplay(const QDate &date) {
    // first, render calendar_task from backend
    const QDate date2 = date;

    // NOTE: need to modify calendar obj!!
    calendar* new_calendar = new calendar(to_string(user::get_instance().get_id()));
    std::vector<calendar_task> task_list = new_calendar->getTasksByIdAndStartingDate(to_string(user::get_instance().get_id()),date2.toString("dd/MM/yyyy").toStdString());
    delete new_calendar;
    // set up table layout
    ui->tableWidget->setRowCount(task_list.size());
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setColumnWidth(3, 300);
    QStringList hLabels;
    hLabels << "Task Start Time" << "Task End Time" << "Title" << "Description";
    ui->tableWidget->setHorizontalHeaderLabels(hLabels);

    // display calendar task data on the table
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        QTableWidgetItem* item;
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            item = new QTableWidgetItem;
            if (j == 0) {
                item->setText(QString::fromStdString(task_list[i].getTaskStartTime()));
            } else if (j == 1) {
                item->setText(QString::fromStdString(task_list[i].getTaskEndTime()));
            } else if (j == 2) {
                item->setText(QString::fromStdString(task_list[i].getTaskTitle()));
            } else if (j == 3) {
                item->setText(QString::fromStdString(task_list[i].getTaskDesc()));
            }
            // for each column, set up the task id as whatsthis
            item->setWhatsThis(QString::fromStdString(task_list[i].getTaskId()));
            ui->tableWidget->setItem(i, j, item);
        }
        ui->tableWidget->setRowHeight(i, 50);
    }


    // set up table properity
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->setTextElideMode(Qt::ElideRight);
}

// TODO LIST
/*!
 * \brief MainWindow::update_todo
 * This method updates the todo list widget
 */
void MainWindow::update_todo() {
    ui->todolistWidget->clear(); // clear current list

    // Display all tasks in list
    cout << "list size: " << todo.getSize() << endl;
    for(int i = 0; i < todo.getSize(); i++){ // iterate through todo list object
        QString todo_task_title = QString::fromStdString(todo.get_title_at(i));
        QListWidgetItem *listItem = new QListWidgetItem(todo_task_title); // fetches the task title and makes a corresponding todo list item object
        listItem->setCheckState(Qt::Unchecked); // check state initially set to unchecked
        ui->todolistWidget->addItem(listItem); // add to list
    }

}

/*!
 * \brief MainWindow::on_newTodoButton_clicked
 * This method is an Event listener for create new todo task button. This method will display a todo form window.
 */
void MainWindow::on_newTodoButton_clicked()
{

    // Instantiates and displays a prompt window asking for required information in order to add it to the todo list
    todo_form todoForm;
    todoForm.setTodo(&todo);
    todoForm.setModal(true);
    todoForm.exec();

    update_todo(); // update list
}

/*!
 * \brief MainWindow::on_completeTodoButton_clicked
 * This method is an Event listener for complete todo task button which processes the task completions
 */
void MainWindow::on_completeTodoButton_clicked()
{
    if (ui->todolistWidget->count() != 0) { // list widget must have atleast one item
        for(int i = 0; i < ui->todolistWidget->count(); ++i) // iterate through the list and check for checked state tasks
        {
            QListWidgetItem* item = ui->todolistWidget->item(i);
            if (item->checkState() == Qt::Checked) { // if a task is checked
                todo.remove_task(item->text().toStdString()); // remove the task from todolist
            }
        }
        update_todo();
    }
}

/*!
 * \brief MainWindow::on_todolistWidget_itemChanged
 * \param item
 * This method is an Event listener for each checkboxes in each todo task items
 */
void MainWindow::on_todolistWidget_itemChanged(QListWidgetItem *item)
{
    bool checked = item->checkState() == Qt::Checked;
    if (checked) { // strike out effect for checked items
        QFont f = item->font();
        f.setStrikeOut(true); // strike effect for the task title text whenever it is selected
        item->setFont(f);

    } else { // strike out effect removed for unchecked items
        QFont f = item->font();
        f.setStrikeOut(false); // undo the strike effect whenever it is deselected
        item->setFont(f);
    }
}


// Log out
/*!
 * \brief MainWindow::closeEvent
 * \param event
 * This method is an Event handler for exiting the program
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    Database::deleteDB(); // delete memory allocated to database
    user::delete_user();

    cout << "Closed by [x] button" << endl;

    exit(0);

}

/*!
 * \brief MainWindow::on_logoutButton_clicked
 * This method is an Event listener for logout button
 */
void MainWindow::on_logoutButton_clicked()
{
    // Delete instances
    Database::deleteDB();
    user::delete_user();

    this->close();

    cout << "Closed by logout button" << endl;

    exit(0);
}


/*!
 * \brief MainWindow::on_search_button_clicked
 * this function will search the keywords from title and desc edit
 * \param void
 */
void MainWindow::on_search_button_clicked()
{
    QString title = ui->search_title->text();
    QString desc = ui->search_desc->text();
    vector<calendar_task> result;
    if (title.trimmed() == "" && desc.trimmed() == ""){
        QMessageBox::warning(this, "error", "Title and Desc for searching are empty or containing space only!");
    } else {
        // check
        calendar* new_calendar = new calendar(to_string(user::get_instance().get_id()));
        if (title.trimmed() != "" && desc.trimmed() != "") {
            result = new_calendar->searchTaskByTitleAndDesc(to_string(user::get_instance().get_id()), title.toStdString(), desc.toStdString());
        } else if (title.trimmed() == "" && desc.trimmed() != "") {
            result = new_calendar->searchTaskByDesc(to_string(user::get_instance().get_id()), desc.toStdString());
        } else if (title.trimmed() != "" && desc.trimmed() == "") {
            result = new_calendar->searchTaskByTitle(to_string(user::get_instance().get_id()), title.toStdString());
        }
        delete new_calendar;
        ui->tableWidget->setRowCount(result.size());
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setColumnWidth(3, 300);
        QStringList hLabels;
        hLabels << "Task Start Time" << "Task End Time" << "Title" << "Description";
        ui->tableWidget->setHorizontalHeaderLabels(hLabels);

        // display calendar task data on the table
        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
            QTableWidgetItem* item;
            for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
                item = new QTableWidgetItem;
                if (j == 0) {
                    item->setText(QString::fromStdString(result[i].getTaskStartTime()));
                } else if (j == 1) {
                    item->setText(QString::fromStdString(result[i].getTaskEndTime()));
                } else if (j == 2) {
                    item->setText(QString::fromStdString(result[i].getTaskTitle()));
                } else if (j == 3) {
                    item->setText(QString::fromStdString(result[i].getTaskDesc()));
                }
                // for each column, set up the task id as whatsthis
                item->setWhatsThis(QString::fromStdString(result[i].getTaskId()));
                ui->tableWidget->setItem(i, j, item);
            }
            ui->tableWidget->setRowHeight(i, 50);
        }
        // set up table properity
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setSortingEnabled(true);
        ui->tableWidget->setTextElideMode(Qt::ElideRight);
    }
}


/*!
 * \brief MainWindow::on_deleteButton_clicked
 * this function will delete the selected row from table widget and database
 * \param void
 */
void MainWindow::on_deleteButton_clicked()
{
    QTableWidgetItem* item = ui->tableWidget->currentItem();
    if (item == NULL) {
        // check if user has selected an item in table widget
        QMessageBox::information(this, "Error", "You haven't selected any row! ");
    } else {
        // get task id
         QString taskId = item->whatsThis();
         // delete task by its id
         calendar* new_calendar = new calendar(to_string(user::get_instance().get_id()));
         new_calendar->deleteTaskById(taskId.toStdString());
         QMessageBox::information(this, "Success", "Item deleted successfully. Please select the date you want to check for reloading.");
         // re-display the data
         QDate currentSelectedDate = ui->calendarWidget->selectedDate();
         TableWidgetDisplay(currentSelectedDate);

          // release pointer
         delete new_calendar;
    }
}


/*!
 * \brief MainWindow::on_updateButton_clicked
 * this function will update the selected row with by calling a pop up dialog
 * \param void
 */
void MainWindow::on_updateButton_clicked()
{
    QTableWidgetItem* item = ui->tableWidget->currentItem();
    if (item == NULL) {
        // check if user has selected an item in table widget
        QMessageBox::information(this, "Error", "You haven't selected any row! ");
    } else {
        // get task id
         QString taskId = item->whatsThis();
         // get row contents vector
         int row = ui->tableWidget->currentRow();
         QVector<QString>* row_contents = new QVector<QString>();
         for (int i = 0; i < ui->tableWidget->columnCount(); i++) {
             row_contents->push_back(ui->tableWidget->item(row, i)->text());
         }
         row_contents->push_back(taskId);

         // pop update form
         update_form_dialog* update_form = new update_form_dialog(this, row_contents);
         update_form->setModal(true);
         update_form->exec();

         // refresh table by the selected date
         QString dateToUpdate = row_contents->at(0);
         QDate currentSelectedDate = ui->calendarWidget->selectedDate();
         TableWidgetDisplay(currentSelectedDate);

         // release pointer
         delete update_form;
    }
}

/*!
 * \brief MainWindow::on_pushButton_clicked
 * this function pop-up a Qdialog for adding task window when button cliecked
 * \param void
 */
void MainWindow::on_addTaskButton_clicked()
{
    task_form* taskForm = new task_form(this);
    taskForm->setModal(true);
    taskForm->exec();

    // display task list of current date
    TableWidgetDisplay(QDate::currentDate());

    // set default selected date on calander widget to current date
    ui->calendarWidget->setSelectedDate(QDate::currentDate());

    // release pointer
    delete taskForm;
}

/*!
 * \brief MainWindow::quoteGen
 * this function sends a request to a quote API to recieve a randomly gernerated quote
 */
void MainWindow::quoteGen()
{
    QNetworkAccessManager *quote = new QNetworkAccessManager(this);
    connect(quote, &QNetworkAccessManager::finished, this, &MainWindow::getQu);
    const QUrl url = QUrl(myURL);
    QNetworkRequest request(url);
    request.setRawHeader(header, key);
    quote->get(request);
    connect(quote, &QNetworkAccessManager::finished, quote, &QNetworkAccessManager::deleteLater);
}
/*!
 * \brief MainWindow::on_quoteButton_clicked
 * calls the quoteGen function when the quote button is clicked
 */
void MainWindow::on_quoteButton_clicked()
{
    quoteGen();
}

/*!
 * \brief MainWindow::getQu
 * retrieves and parses the string from the network request and displays the quote on the api in a viewable display
 * \param reply
 */
void MainWindow::getQu(QNetworkReply *reply){

    QString q = QString::fromUtf8(reply->readLine());
    QStringList data = q.split(": ");
    QStringList quote = data.value(1).split(", ");
    QStringList author = data.value(2).split(", ");
    QStringList authorS = author.value(0).split('"');
    QString backUpQ = "Develop success from failures. Discouragement and failure are two of the surest stepping stones to success.";
    QString backUPA = "-Dale Carnegie";
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCodeV.toInt()==200){
        if(authorS.value(1) == ""){
            ui->quoteFrame->setText(quote.value(0)+"\n - Unknown");
        }
        else{
            ui->quoteFrame->setText(quote.value(0)+'"'+"\n - "+authorS.value(1));
        }
    }
    else{
        ui->quoteFrame->setText('"'+backUpQ+'"'+"\n"+backUPA);
    }
    reply->deleteLater();
}

