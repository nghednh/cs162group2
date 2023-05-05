#include <iostream>
#include <string>

using namespace std;
bool checkStudentpassword(string username, string password) {
    return true;
} /*=> cho cai ham cua ba vo, tai tui k chay duoc nen de vay*/
bool checkStaffpassword(string username, string password) {
    return  true;
}
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
    int role;
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
    cin >> role;
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
        if (checkStaffpassword(username, password)) {
            menuStaff(username);
        }
        else {
            system("cls");
            login(0);
        }
    }
    else if (role == 2) {
        if (checkStudentpassword(username, password)) {
            menuStudent(username);
        }
        else {
            // Wrong password, prompt user to try again
            system("cls");
            login(0);
        }
    }
}