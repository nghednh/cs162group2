#include <iostream>
#include <string>

using namespace std;
bool checkStudentPassword(string username, string password) {
    return true;
} /*=> cho cai ham cua ba vo, tai tui k chay duoc nen de vay*/
bool checkStaffPassword(string username, string password) {
    return  true;
}
void menuStudent(string username);
void menuStaff(string username);
void UI() {
    cout << " ___________________________________________________________________________________ " << endl;
    cout << "|" << string(83, ' ') << "|" << endl;
    cout << "|  <-  -> || courses.ctda.hcmus.edu.vn                                              |" << endl;
    cout << "|___________________________________________________________________________________|" << endl;
    cout << "|" << string(83, ' ') << "|" << endl;
    cout << "|    										    |	" << endl;
    cout << "|				    fit@hcmus					    |	" << endl;
    cout << "|            _______________________________________________________                |" << endl;
    cout << "|										    |" << endl;
}
void UIlite() {
    cout << " ___________________________________________________________________________________ " << endl;
    cout << "|" << string(83, ' ') << "|" << endl;
    cout << "|  <-  -> || courses.ctda.hcmus.edu.vn                                              |" << endl;
    cout << "|___________________________________________________________________________________|" << endl;
}
void login(int firstlog = 1) {
    system("cls");
    string rol;
    UI();
    if (!firstlog) {
        cout << "| Wrong password or username or role                                                |\n";
        cout << "| Enter your role again:                                                            |\n";
        cout << "| 1. Staff                                                                          |\n";
        cout << "| 2. Student                                                                        |\n";
        cout << "| 3. Exit                                                                           |\n";
    }
    else {
        cout << "| Enter your role again:                                                            |\n";
        cout << "| 1. Staff                                                                          |\n";
        cout << "| 2. Student                                                                        |\n";
        cout << "| 3. Exit                                                                           |\n";
    }
    cout << "| Choose: ";
    cin >> rol;
    int role = stoi(rol);
    if (role != 3 && role != 2 && role != 1) {
        login(0);
    }
    if (role == 3) {
        system("cls");
        UI();
        cout << "| See you later!                                                                    |\n";
        // Exit the program
        return;
    }
    system("cls");
    string username, password;
    UI();
    cout << "| Enter your username: ";
    cin >> username;
    cout << "| Enter your password: ";
    cin >> password;
    if (role == 1) {
        if (checkStaffPassword(username, password)) {
            menuStaff(username);
        }
        else {
            system("cls");
            login(0);
        }
    }
    else if (role == 2) {
        if (checkStudentPassword(username, password)) {
            menuStudent(username);
        }
        else {
            // Wrong password, prompt user to try again
            system("cls");
            login(0);
        }
    }
}
void menuStaff(string username) {
    system("cls");
    string chose;
    UIlite();
    cout << "| User: " << username << endl;
    cout << "| 0.   Log out.                                                                    |\n";
    cout << "| 1. View the current account.                                                   |" << '\n';
    cout << "| 2. To change the password.                                                        |" << '\n';
    cout << "| 3. To view student.                                                               |" << '\n';
    cout << "| 4. To add school year.                                                            |" << '\n';
    cout << "| 5. To add semester.                                                               |" << '\n';
    cout << "| 6. To update course information.                                                  |" << '\n';
    cout << "| 7. To delete course by ID.                                                        |" << '\n';
    cout << "| 8. To input course into CSV files.                                                |" << '\n';
    cout << "| 9. To get info of the scoreboard from CSV files.                                  |" << '\n';
    cout << "| 10. To view scoreboard.                                                           |" << '\n';
    cout << "| 11. To update scoreboard info.                                                    |" << '\n';
    cout << "| 12. To view list of classes.                                                      |" << '\n';
    cout << "| 13. To view list of courses.                                                      |" << '\n';
    cout << "| 14. To import first year students from CSV files.                                 |" << '\n';
    cout << "| Your choice: ";
    cin >> chose;
    int choose = stoi(chose);

    switch (choose)
    {
    case 0: {
    }
    case 1: {
    }
    case 2: {
    }
    case 3: {
    }
    case 4: {
    }
    case 5: {
    }
    case 6: {
    }
    case 7: {
    }
    case 8: {
    }
    case 9: {
    }
    case 10: {
    }
    case 11: {
    }
    case 12: {
    }
    case 13: {
    }
    case 14: {
    }
    }
}
void menuStudent(string username) {
    system("cls");
    UIlite();
    cout << "| User: " << username << '\n';
    cout << "| 0. To log out.                                                                    |" << '\n';
    cout << "| 1. To view the current account.                                                   |" << '\n';
    cout << "| 2. To change the password.                                                        |" << '\n';
    cout << "| 3. To enroll in a course.                                                         |" << '\n';
    cout << "| 4. To remove enrolled course.                                                     |" << '\n';
    cout << "| 5. To view enrolled courses.                                                      |" << '\n';
    cout << "| 6. To view scoreboard.                                                            |" << '\n';
    string chose;
    cout << "| Your choice: ";
    cin >> chose;
    int choose = stoi(chose);
    switch (choose)
    {
    case 0: {
    }
    case 1: {
    }
    case 2: {
    }
    case 3: {
    }
    case 4: {
    }
    case 5: {
    }
    case 6: {
    }
    case 7: {
    }
    case 8: {
    }
    case 9: {
    }
    case 10: {
    }
    case 11: {
    }
    case 12: {
    }
    case 13: {
    }
    case 14: {
    }
    }
}
void inputInt(int* i) {
    cout << "Input: ";
    cin >> *i;
    if (cin.fail()) {
        cout << "Invalid input. Please input again!";
        cin.clear();
        cin.ignore(100, '\n');
        inputInt(i);
    }
}

int main() {
    login();
}