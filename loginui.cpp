/*!
 * description: LoginUI class for displaying login and registration for users.
 * last modified: 11/7/2022
 */

#include "loginui.h"
#include "./ui_loginui.h"
#include "ui_loginui.h"

/*!
 * \brief LoginUI::LoginUI - LoginUI Constructor
 * \param parent - parent qt widget
 */
LoginUI::LoginUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginUI)
{
    ui->setupUi(this);
}

/*!
 * \brief LoginUI::~LoginUI - LoginUI destructor
 */
LoginUI::~LoginUI()
{
    delete ui;
}

/*!
 * \brief LoginUI::on_pushButton_clicked - function for when the Login Button is clicked
 */
void LoginUI::on_pushButton_clicked()
{
    // var setup for username and password
    username = ui->username->text();
    password = ui->password->text();

    if( username != "" && password != ""){ // username and password field not empty
        Authenticate* auth = new Authenticate();
        if ( auth->login_user(username.toStdString(), password.toStdString()) ){ // login success
            // hiding the login UI after user typed correct credentials
            this->hide();

            // trigger the main dashboard
            MainWindow *mw = new MainWindow(this);
            mw->show();
        }
        else { // login failed
            QMessageBox::warning(this,"Login", "Login failed");
        }
        delete auth;

    }
    else{ // either username or password field is empty
        QMessageBox::warning(this,"Login", "Cannot have empty username or password!");
        ui->password->setText("");
    }


}

/*!
 * \brief LoginUI::on_pushButton_2_clicked - function for when register button is clicked
 */
void LoginUI::on_pushButton_2_clicked()
{
    // var initialization
    string fname = ui->firstName->text().toStdString(); // firstname
    string lname = ui->lastName->text().toStdString(); // lastname
    string username = ui->newUsername->text().toStdString();
    string password = ui->newPassword->text().toStdString();
    string confirmPass = ui->confirmPassword->text().toStdString(); // enter password again to check if it matches
    if (fname == "" ){ // empty firstname field
        QMessageBox::warning(this,"Register", "You must enter your first name!");
    }
    else if (lname ==""){ // empty lastname field
        QMessageBox::warning(this,"Register", "You must enter your last name!");
    }
    else if (username == ""){ // empty username field
        QMessageBox::warning(this,"Register", "Username cannot be empty!");
    }
    else if (password =="" || password.length() < 8 || password.length() > 20){ // empty password field OR invalid password length (should be between 9 and 19 in length)
        QMessageBox::warning(this,"Register", "Password must be at least 8 characters long and less than 20 characters long!");
    }
    else if (!validatePassword(password)){ // empty password field
        QMessageBox::warning(this,"Register", "Password must contain at least one uppercase, one lowercase and one number");
    }
    else if (confirmPass != password){ // confirm password not matching initial password
        QMessageBox::warning(this,"Register", "Please make sure your passwords match");
    }
    else{ // every fields are entered correctly - proceed with registration
        Authenticate* registerer = new Authenticate(); // create new authenticate obj
        int result = registerer->register_user(username, password, fname, lname); // retrieve result of registration attempt
        if (result == 1){ // registration success
            QMessageBox::information(this,"Register", "Signed up successfully!"); // just for testing - please remove when integrating everything
            // bring up calendar UI
        }
        else if (result == 0){ // username already exists
            QMessageBox::warning(this,"Register", "Username taken,  please choose a different username");
        }
        else { // something went wrong with storing into sqlite3 db
            QMessageBox::warning(this,"Register", "Something went wrong.  Please contact support for help.");
        }
        ui->lastName->setText("");
        ui->firstName->setText("");
        ui->newUsername->setText("");
        ui->newPassword->setText("");
        ui->confirmPassword->setText("");
        delete registerer;
    }
}

// Log out
/*!
 * \brief LoginUI::closeEvent
 * \param event
 * This method is an Event handler for exiting the program
 */
void LoginUI::closeEvent(QCloseEvent *event)
{
    cout << "Closed by [x] button" << endl;

    exit(0);

}

/*!
 * \brief LoginUI::validatePassword - validates the given password
 * \param password - password to be validated
 * \return true if password is valid
 *         false otherwise
 * \author https://stackoverflow.com/questions/39709887/regex-specific-password-restrictions
 */
bool LoginUI::validatePassword(std::string password){
    bool upper_case = false; //saves the result if upper-case characters were found.
    bool lower_case = false; //same for lower-case
    bool number_case = false; //...

    // REGEX initialization
    std::regex upper_case_expression{ "[A-Z]+" }; //here is the very simple expression for upper_case search
    std::regex lower_case_expression{ "[a-z]+" }; //for lower-case
    std::regex number_expression{ "[0-9]+" }; //...

    upper_case = std::regex_search(password, upper_case_expression); //save the result, if the expression was found.
    lower_case = std::regex_search(password, lower_case_expression); //....
    number_case = std::regex_search(password, number_expression);

    //like: sum_of_positive_results = 1 + 0 + 1 (true/false as an integer)
    int sum_of_positive_results = 0;
    sum_of_positive_results = sum_of_positive_results+ upper_case + lower_case + number_case;

    if (sum_of_positive_results < 3){ //not enough booleans were true
        return false;
    }
    return true;
}

