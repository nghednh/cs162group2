#include <iostream>
#include <string>
#include "login&menu.h"
#include "Input.h"
#include "View.h"

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
    Semester smCur;
    system("cls");
    string chose;
    UIlite();
    cout << "| User: " << username << endl;
    cout << "| 1.   Create a school year                                                         |" << '\n';
    cout << "| 2.   Create several classes for 1st-year students                                 |" << '\n';
    cout << "| 3.   Add students to class                                                        |" << '\n';
    cout << "| 4.   Create a semester                                                            |" << '\n';
    cout << "| 5.   Add a course to this semester                                                |" << '\n';
    cout << "| 6.   Update courses's information                                                 |" << '\n';
    cout << "| 6.   Add students to course                                                       |" << '\n';
    cout << "| 7.   Remove student from a course                                                 |" << '\n';
    cout << "| 8.   Delete a course                                                              |" << '\n';
    cout << "| 9.   Import scoreboard                                                            |" << '\n';
    cout << "| 10.  Update a student's result                                                    |" << '\n';
    cout << "| 11.  View                                                                         |" << '\n';
    cout << "| 12.  Log out                                                                      |" << '\n';
    cout << "| 13.  Exit                                                                         |\n";
    cout << "| Your choice: ";
    getline(cin, chose, '\n');

    string s;
    while (true)
    {
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
                        cout << "| Succeed. School year " << yearNow->name << " have been created!" << endl;
                    }
                    else cout << "| That school year already exists or last school year have't finished!" << endl;
                }
                else {
                    cout << "| Canceled" << endl;
                }
            }
            else cout << "| Input wrong" << endl;
            backmenuStaff(username, yearHead, "n");
        }
        else if (chose == "2") {
            string n;
            system("cls");
            UIlite();
            cout << "| Type 1 to create by keyboard or 2 to create by file or 3 to back to menu: ";
            getline(cin, n, '\n');
            if (n == "1") {
                system("cls");
                UIlite();
                cout << "| Please input Class's Name (Ex: 22CTT1): ";
                getline(cin, s, '\n');

                if (echo("Class " + s) == true)
                {
                    if (createClass(yearNow, s)) cout << "| Succeed." << endl;
                }
                else cout << "| Canceled" << endl;
                backmenuStaff(username, yearHead, "n");
            }
            else if (n == "2") {
                cout << "| Enter your file name (Ex: ListClass): ";
                getline(cin, s, '\n');
                if (echo(s) == true)
                {
                    cout << "| Is checking..." << endl;
                    if (importListClass_dslh("Import/" + s + ".txt", yearNow) == true)
                        cout << "| Done" << endl;
                    else cout << "| Can not open file or wrong school year in file." << endl;
                }
                else cout << "| Canceled" << endl;
                backmenuStaff(username, yearHead, "n");
            }
            else {
                backmenuStaff(username, yearHead, "1");
            }
        }
        else if (chose == "3") {
            string n;
            system("cls");
            UIlite();
            cout << "| Type 1 to add student by keyboard or 2 add by file or 3 to back to menu: ";
            getline(cin, n, '\n');
            if (n == "2") {
                findLastSYandSM(yearHead, yearNow, smNow);
                {
                    cout << "Please pass your file in import folder.";
                    if (echo("file class") == true)
                    {
                        cout << "Is checking..." << endl;
                        if (readStudentFromImportFile("Import", yearNow) == true)
                            cout << "Done" << endl;
                    }
                    else cout << "Canceled" << endl;
                }
                backmenuStaff(username, yearHead, "n");
            }
            else if (n == "1") {
                findLastSYandSM(yearHead, yearNow, smNow);

                string StuID, FirstName, LastName, Gender, dateofbirth, socialID, curriculum, cla;
                cout << "| Enter student's class: ";
                getline(cin, cla, '\n');
                Class* classCur = findClassInSchoolYear(yearNow, cla);
                if (classCur == nullptr)
                    cout << "| Not found " << cla << " in schoolyear " << yearNow->name << endl;
                else
                {
                    bool conti = true;
                    while (conti)
                    {
                        cout << "| Enter Student's ID: "; getline(cin, StuID, '\n');
                        cout << "| Enter Student's First Name: "; getline(cin, FirstName, '\n');
                        cout << "| Enter Student's Last Name: ";  getline(cin, LastName, '\n');
                        cout << "| Enter Student's Gender (Male/Female): ";     getline(cin, Gender, '\n');
                        cout << "| Enter Student's Date of Birth (Ex: 02/11/2004): "; getline(cin, dateofbirth, '\n');
                        cout << "| Enter Student's Social ID: "; getline(cin, socialID, '\n');
                        cout << "| Enter Student's Curriculum: "; getline(cin, curriculum, '\n');
                        // class already enter
                        if (checkInfoStu(StuID, FirstName, LastName, Gender, dateofbirth, socialID, cla) == true)
                        {
                            Student* newStu = new Student;
                            newStu->No = classCur->numStu;
                            newStu->StuID = StuID;
                            newStu->firstName = FirstName;
                            newStu->lastName = LastName;
                            newStu->gender = Gender;
                            newStu->dateOfBirth.day = dateofbirth[0];
                            newStu->dateOfBirth.day += dateofbirth[1];
                            newStu->dateOfBirth.month = dateofbirth[3];
                            newStu->dateOfBirth.month += dateofbirth[4];
                            newStu->dateOfBirth.year = dateofbirth[6];
                            newStu->dateOfBirth.year += dateofbirth[7];
                            newStu->dateOfBirth.year += dateofbirth[8];
                            newStu->dateOfBirth.year += dateofbirth[9];
                            newStu->socialID = socialID;
                            newStu->className = cla;
                            newStu->curriculum = curriculum;
                            if (addStudentToClass(yearNow, newStu) == false)
                                cout << "| Student with this ID already exists in class! " << StuID << endl;
                            else
                            {
                                addStudentToCSVFileClass(yearNow, newStu);
                                cout << "| Add succeed" << endl;
                            }
                        }
                        cout << "| +> Enter to continue add student to class " << classCur->name << endl;
                        cout << "| +> Or type in any key to return to menu\n";
                        getline(cin, s, '\n');
                        if (s != "") conti = false;
                    }
                }
                if (classCur)
                {
                    officialClass(classCur);
                    exportClassToCSVFile(classCur);
                }
                backmenuStaff(username, yearHead, "1");
            }
            else {
                backmenuStaff(username, yearHead, "1");
            }
        }
        else if (chose == "4") {
            system("cls");
            UIlite();
            findLastSYandSM(yearHead, yearNow, smNow);
            int tmp = smNow + 1;
            if (smNow == 2) cout << "| Already full semester at schoolyear " << yearNow->name;
            else {
                if (echo("semester " + to_string(tmp + 1) + " of schoolyear " + yearNow->name) == true)
                {
                    string end, start;
                    cout << "| Please enter the start date of semester " << tmp + 1 << " of school year " << yearNow->name << " : ";
                    getline(cin, start, '\n');
                    cout << "| Please enter the end date of semester " << tmp + 1 << " of school year " << yearNow->name << " : ";
                    getline(cin, end, '\n');
                    if (checkDate(start) == true && checkDate(end) == true)
                    {
                        Date endDate = createDate(end);
                        Date startDate = createDate(start);

                        if (createSemester(tmp, yearNow, startDate, endDate) == true)
                            cout << "| Succeed" << endl;
                        else cout << "| Failed" << endl;
                    }
                    else cout << "| Date input wrong" << endl;
                }
                else cout << "| Canceled" << endl;
            }
            backmenuStaff(username, yearHead, "n");
        }
        else if (chose == "5")
        {
            string n;
            system("cls");
            UIlite();
            cout << "| Type 1 to add course by keyboard or 2 to add by file or 3 to back to menu: ";
            getline(cin, n, '\n');
            if (n == "1") {
                bool conti = true;
                while (conti) {
                    findLastSYandSM(yearHead, yearNow, smNow);
                    if (smNow == -1) cout << "| Not have any semester in school year " << yearNow->name << endl;
                    else
                    {
                        if (addCourseToSemester(yearNow, smNow))
                            cout << "| Succeed" << endl;
                        else cout << "| Failed" << endl;
                    }
                    cout << "| +> Enter to continue\n";
                    cout << "| +> Or type in any key to return to menu\n";
                    getline(cin, s, '\n');
                    if (s != "") conti = false;
                }
                backmenuStaff(username, yearHead, "1");
            }
            else if (n == "2") {
                system("cls");
                UIlite();
                cout << "| Enter your file name (Ex: ListCourse): ";
                getline(cin, s, '\n');
                if (echo(s) == true)
                {
                    cout << "| Is checking..." << endl;
                    if (importListCourse_dshp("Import/" + s + ".txt", yearNow, smNow) == true)
                        cout << "| Done" << endl;
                    else cout << "| Can not open file or wrong schoolyear or semsester in file." << endl;
                }
                else cout << "| Canceled" << endl;
                backmenuStaff(username, yearHead, "n");
            }
        }
        else if (chose == "6") {
            system("cls");
            UIlite();
            Course* tmp;
            string s, ID, Name, Cre, Lec, Day, Ses, Max, Class;
            Semester smCur;

            cout << "| Enter course to upate information <ID_ClassName>: ";
            getline(cin, s, '\n');
            Course* cur = findCourseByFileNameInAllCourse(yearHead, smCur, s);
            if (cur != nullptr)
            {
                cout << "| Enter Course's ID: ";
                getline(cin, ID, '\n');
                cout << "| Enter Course's Name: ";
                getline(cin, Name, '\n');
                cout << "| Enter Course's number of credit: ";
                getline(cin, Cre, '\n');
                cout << "| Enter Course's Lecturer: ";
                getline(cin, Lec, '\n');
                cout << "| Enter Coures's day of perform (Ex: MON): ";
                getline(cin, Day, '\n');
                cout << "| Enter Course's session (S1 to S4): ";
                getline(cin, Ses, '\n');
                cout << "| Enter Course's Max number of student: ";
                getline(cin, Max, '\n');
                cout << "| Enter Course's ClassName: ";
                getline(cin, Class, '\n');

                if (checkInfoCourse(smCur, ID, Name, Cre, Lec, Day, Ses, Max, Class) == true)
                {
                    tmp = new Course;
                    tmp->ID = ID;
                    tmp->name = Name;
                    tmp->className = Class;
                    tmp->teacherName = Lec;
                    tmp->numCredit = stoi(Cre);
                    tmp->maxStudent = stoi(Max);
                    tmp->session = stoi(Ses.substr(1, 1));
                    tmp->day = Day;

                    if (updateCourseInfo(cur, tmp) == true)
                    {
                        cout << "| Succeed" << endl;
                    }
                    else cout << "| Already have " << tmp->ID << "_" << tmp->className << endl;
                }
                else
                    cout << "| Failed" << endl;

            }
            else cout << "| Could not fould " << s << "!"<<endl;
            backmenuStaff(username, yearHead, "n");
        }
        else if (chose == "8") {
            system("cls");
            UIlite();
            cout << "| Please enter Course <ID_ClassName>: ";
            getline(cin, s, '\n');
            Course* courseCur = findCourseByFileNameInAllCourse(yearHead, smCur, s);
            if (courseCur == nullptr || courseCur->inSM->num != smNow || courseCur->inSM->inSY->name != yearNow->name) cout << "| Could not find course " << s << " in current semester" << endl;
            else
            {
                if (deleteCourse(courseCur, yearNow, smNow) == true)
                    cout << "| Deleted" << endl;
                else cout << "| Failed." << endl;
            }
            backmenuStaff(username, yearHead, "n");
        }
        else if (chose == "9")
        {
            system("cls");
            UIlite();
            findLastSYandSM(yearHead, yearNow, smNow);
            if (yearNow != nullptr && smNow != -1)
            {
                cout << "| Please pass your file in Import folder.";
                if (echo("| scoreboard file") == true)
                {
                    cout << "| Is checking..." << endl;
                    if (importScoreboardFile("Import", yearNow, smNow) == true)
                        cout << "| Done" << endl;
                }
                else cout << "| Canceled" << endl;
            }
            else cout << "| Not have any semester or schoolyear" << endl;
            backmenuStaff(username, yearHead, "n");
        }
        else if (chose == "10")
        {
            system("cls");
            UIlite();
            bool conti = true;
            findLastSYandSM(yearHead, yearNow, smNow);
            string s;
            cout << "| Enter student's Course <ID_ClassName>: ";
            getline(cin, s, '\n');
            Course* courseCur = findCourseByFileNameInAllCourse(yearHead, smCur, s);
            if (courseCur == nullptr || courseCur->inSM->num != smNow || courseCur->inSM->inSY->name != yearNow->name) cout << "Could not find course " << s << " in current semester" << endl;
            else
            {
                if (checkFileMarkExist(courseCur) == true)
                {
                    cout << "| You are changing student result of course " << s << endl;
                    while (conti)
                    {
                        if (updateStudentResult(courseCur) == true)
                            cout << "| Updated" << endl;
                        else cout << "| Failed." << endl;

                        cout << "| +> Enter to continue changing student's result\n";
                        cout << "| +> Or type in any key to return to menu\n";
                        getline(cin, s, '\n');
                        if (s != "") conti = false;
                    }
                    backmenuStaff(username, yearHead, "1");
                }
                else cout << "| Course " << courseCur->ID << "_" << courseCur->className << " not have mark information" << endl;
            }
            backmenuStaff(username, yearHead, "n");
        }

        else if (chose=="13") {
            deleteAll(yearHead);
            cout << "| See you later!";
            exit(0);
        }
        else if (chose == "11") {
            system("cls");
            UIlite();
            string n;
            cout << "| Type in: \n";
            cout << "| 1. To view list classes\n";
            cout << "| 2. To view list courses\n";
            cout << "| 3. To view list of student in class\n";
            cout << "| 4. To view list of student in course\n| ";
            getline(cin, n, '\n');
            if (n == "1") {
                viewListClasses(yearHead, yearNow);
            }
            else if (n == "2") {
                viewListCourses(smCur.courseHead);
            }
            else if (n == "3") {
                viewListOfStudentInClass(yearHead->classHead);  
            }
            else if (n == "4") {
                viewListStudentsInCourse(smCur.courseHead);
            }
            backmenuStaff(username, yearHead, "n");
        }
        else {
            menuStaff(username, yearHead);
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
void backmenuStaff(string username, SchoolYear*& yearHead, string chose="n") {
    cout << "| Type in:                                                                          |\n";
    cout << "| 1. To return to menu                                                              |\n";
    cout << "| 2. To continue                                                                    |\n";
    cout << "| 3. To exit                                                                        |\n| ";
    if (chose == "n") {
        getline(cin, chose, '\n');
    }
    if (chose == "1") {
        menuStaff(username, yearHead);
    }
    else if (chose == "0") {
        exit(0);
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
    Semester cur;
    menuStaff("Nguyen Kim Khanh", yearHead);
    return 0;
}