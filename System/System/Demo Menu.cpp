#include <iostream>
#include <string>
#include "login&menu.h"
#include "Input.h"

SchoolYear* yearNow;
int smNow;

using namespace std;
bool checkStudentPassword(string username, string password) {
    return true;
} /*=> cho cai ham cua ba vo, tai tui k chay duoc nen de vay*/
bool checkStaffPassword(string username, string password) {
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

bool echo(string source)
{
    cout << "| Are you sure want to add " << source << ". \n| Type 1 for YES or 0 for NO: ";
    string check;
    getline(cin, check, '\n');
    if (check == "1") return true;
    else return false;
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
            menuStaff(username, yearNow);
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

bool checkInputSchoolYear(string s)
{
    if (s.size() != 9) return false;
    if (s[4] != '-') return false;
    for (int i = 0; i < 9; i++)
        if (i != 4)
            if (!(s[i] <= '9' && s[i] >= '0')) return false;
    if (stoi(s.substr(5, 4))- stoi(s.substr(0, 4)) != 1) return false; 
    return true;
}

void menuStaff(string username, SchoolYear*& yearHead) {
    system("cls");
    string chose;
    UIlite();
    cout << "| User: " << username << endl;
    cout << "| 1.   Create a school year                                                         |" << '\n';
    cout << "| 2.   Create several classes for 1st-year students                                 |" << '\n';
    cout << "| 3.   Add students to class                                                        |" << '\n';
    cout << "| 4.   Create a semester                                                            |" << '\n';
    cout << "| 5.   Add a course to this semester                                                |" << '\n';
    cout << "| 6.   Add students to course                                                       |" << '\n';
    cout << "| 7.   Remove studentfrom a course                                                  |" << '\n';
    cout << "| 8.   Delete a course                                                              |" << '\n';
    cout << "| 9.   Import scoreboard                                                            |" << '\n';
    cout << "| 10.  Update a student's resul                                                     |" << '\n';
    cout << "| 11.  View                                                                         |" << '\n';
    cout << "| 12.  Log out                                                                      |" << '\n';
    cout << "| 13.  Exit                                                                         |\n";
    cout << "| Your choice: ";
    getline(cin, chose, '\n');

    string s;
    while (true)
    {
        if (chose == "13") {
            deleteAll(yearHead);
            cout << "| See you later!";
            exit(0);
        }
        if (chose == "12") {
            deleteAll(yearHead);
            login();
        }
        else if (chose == "1") {
            system("cls");
            UIlite();
            cout << "| Please input schoolyear's name (ex: 2022-2023): ";
            getline(cin, s, '\n');
            if (checkInputSchoolYear(s) == true)
            {
                if (echo("school year " + s) == true)
                {
                    if (createSchoolyear(yearNow, s, yearHead, smNow))
                    {
                        findLastSYandSM(yearHead, yearNow, smNow);
                        // chuyen qua year
                        cout << "| Succeed. School year " << yearNow->name <<" have been created!" << endl;
                    }
                    else cout << "| That school year already exists or last school year have't finished!" << endl;
                }
                else {
                    cout << "| Canceled" << endl;
                }
            }
            else cout << "| Input wrong" << endl;
            break;
        }
        else if(chose == "2") {
            cout << "Please input Class's Name (Ex: 22CTT1): ";
            getline(cin, s, '\n');
            
            if (echo("Class " + s) == true)
            {
                if (createClass(yearNow, s)) cout << "Succeed." << endl;
            }
            else cout << "Canceled" << endl;
        }
        else if (chose == "3")
        {
            cout << "Please pass your file in Import folder.";
           
            cout << "Enter your file name (Ex: ListClass): ";
            getline(cin, s, '\n');
            if (echo(s) == true)
            {
                cout << "Is checking..." << endl;
                if (importListClass_dslh("Import/" + s + ".txt", yearNow) == true)
                    cout << "Done" << endl;
                else cout << "Can not open file or wrong schoolyear in file." << endl;
            }
            else cout << "Canceled" << endl;
        }
        if (chose == "0")  {
        }
    }
    cout << "| Type 1 to back to menu or 0 to exit: ";
    getline(cin, chose, '\n');
    if (chose=="1") {
        menuStaff(username, yearHead);
    }
    else { 
        exit(0);
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
    SchoolYear* yearHead = NULL;
    SchoolYear* yearCur = yearHead;
    int semesterNow = -1;
    readInformation("Information", yearCur, yearHead);
    findLastSYandSM(yearHead, yearNow, smNow);
    menuStaff("Nguyen Kim Khanh", yearHead);
    return 0;
}