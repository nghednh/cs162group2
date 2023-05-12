#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <optional>
#include <algorithm>
#include <string>
#include "Structure.h"
#include "View.h"

namespace fs = std::filesystem;
using namespace fs;

Course* findCourseByFileName(SchoolYear* yearCur, int sm, string fileName);
void OfficialCourseToCSV(Course* courseCur);
bool updateCourseInfo(Course* courseCur, Course* courseTmp);
Course* findCourseByIDAndClass(string ID, string className, Semester sm);

// Input

void readListClass(const path& file_path, SchoolYear*& yearCur)
{
    Class* classCur = yearCur->classHead;

    for (const auto& entry : directory_iterator(file_path)) {
        string tmp = entry.path().filename().stem().string();
        if (tmp.size() > 9 && tmp.substr(tmp.size() - 9, 9) == "_password") continue;
        else
        {
            ifstream in;
            in.open(entry.path());

            if (classCur != NULL)
            {
                classCur->classNext = new Class;
                classCur = classCur->classNext;
            }
            else
            {
                yearCur->classHead = new Class;
                classCur = yearCur->classHead;
            }
            classCur->name = tmp;
            classCur->inSY = yearCur;
            Student* stuCur = classCur->stuHead;

            string header, line;              // xoa dong 1
            getline(in, header);

            while (!in.eof())
            {
                if (stuCur != NULL) {
                    stuCur->stuNext = new Student;
                    stuCur = stuCur->stuNext;
                }
                else {
                    classCur->stuHead = new Student;
                    stuCur = classCur->stuHead;
                }
                getline(in, stuCur->No, '\t');
                getline(in, stuCur->StuID, '\t');
                getline(in, stuCur->firstName, '\t');
                getline(in, stuCur->lastName, '\t');
                getline(in, stuCur->gender, '\t');
                getline(in, stuCur->dateOfBirth.day, '/');
                getline(in, stuCur->dateOfBirth.month, '/');
                getline(in, stuCur->dateOfBirth.year, '\t');
                getline(in, stuCur->socialID, '\t');
                getline(in, stuCur->curriculum, '\t');
                getline(in, stuCur->className, '\n');

                stuCur->inClass = classCur;
            }
            in.close();
        }
    }
}


Student* findStuInClass(string syTmp, string classTmp, string IDTmp, SchoolYear*& yearHead)
{
    SchoolYear* yearCur = yearHead;
    while (yearCur && yearCur->name != syTmp)
        yearCur = yearCur->yearNext;

    if (yearCur)
    {
        Class* classCur = yearCur->classHead;
        while (classCur && classCur->name != classTmp)
            classCur = classCur->classNext;

        if (classCur)
        {
            Student* stuCur = classCur->stuHead;
            while (stuCur && stuCur->StuID < IDTmp)
                stuCur = stuCur->stuNext;

            if (stuCur && stuCur->StuID == IDTmp)
                return stuCur;
        }
    }
    return nullptr;
}

void createCoursesFromList(SchoolYear*& sy, const path& file_path);


void createCoursesFromList(SchoolYear*& sy, const path& file_path) {

    ifstream fin(file_path);
    string s;
    getline(fin, s, ' ');
    string hk = s.substr(2, 1);

    getline(fin, s, '\n');

    getline(fin, s, '\n');  // header

    Course* tmp = sy->sm[stoi(hk) - 1].courseHead;

    while (!fin.eof()) {

        if (tmp == NULL)
        {
            sy->sm[stoi(hk) - 1].courseHead = new Course;
            tmp = sy->sm[stoi(hk) - 1].courseHead;
        }
        else
        {
            tmp->courseNext = new Course;
            tmp = tmp->courseNext;
        }

        getline(fin, tmp->ID, '\t');
        getline(fin, tmp->name, '\t');
        getline(fin, s, '\t');
        tmp->numCredit = stoi(s);
        getline(fin, tmp->teacherName, '\t');
        getline(fin, tmp->day, '\t');
        getline(fin, s, '\t');
        tmp->session = stoi(s);
        getline(fin, s, '\t');
        tmp->maxStudent = stoi(s);
        getline(fin, tmp->className, '\n');

        tmp->inSM = &(sy->sm[stoi(hk) - 1]);
        tmp->courseNext = NULL;

        // tao file
        path create_file = "Information/" + sy->name + "/Semester " + hk + '/' + tmp->ID + '_' + tmp->className + "_dsdkhp.txt";
        ofstream fout(create_file);

        fout << tmp->name << endl;
        fout << tmp->teacherName << endl;
        fout << tmp->numCredit << endl;
        fout << tmp->maxStudent << endl;
        fout << tmp->day << endl;
        fout << "S" << tmp->session << endl;
        fout << "SchoolYear Class   ID";
        fout.close();
    }
    fin.close();
    // xoa file dkhp
    remove(file_path);
}

void readScoreboardFile(const path& path, SchoolYear* yearCur, int sm)
{
    string tmp = path.filename().stem().string();
    Course* courseCur = findCourseByFileName(yearCur, sm, tmp);
    fstream in(path);
    if (courseCur == nullptr || !in.is_open()) return;
    string header;
    getline(in, header, '\n');
    getline(in, header, '\n');
    getline(in, header, '\n');
    getline(in, header, '\n');
    getline(in, header, '\n');

    StuInCourse* stuCur = courseCur->stuHead;

    while (stuCur)
    {
        getline(in, header, '\t');
        getline(in, header, '\t');
        getline(in, header, '\t');
        in >> stuCur->totalM;
        in.ignore(1, '\t');
        in >> stuCur->finalM;
        in.ignore(1, '\t');
        in >> stuCur->midM;
        in.ignore(1, '\t');
        in >> stuCur->otherM;

        stuCur = stuCur->stuNext;
    }
    in.close();
    return;
}


void readListCourse(const path& file_path, SchoolYear*& yearCur, SchoolYear*& yearHead, int i)
{
    Course* courseCur = yearCur->sm[i].courseHead;

    for (const auto& entry : directory_iterator(file_path)) {
        string tmp = entry.path().filename().stem().string();

 //       if (tmp == "dshp")
 //       {
 //           createCoursesFromList(yearCur, entry.path());
 //       }
        if (tmp == "Info")
        {
            ifstream in (entry.path());

            string header;
            getline(in, header, '\n');
            getline(in, header, '\t');
            getline(in, header, '\t');
            getline(in, yearCur->sm[i].start.day, '/');
            getline(in, yearCur->sm[i].start.month, '/');
            getline(in, yearCur->sm[i].start.year, '\t');
            getline(in, yearCur->sm[i].end.day, '/');
            getline(in, yearCur->sm[i].end.month, '/');
            getline(in, yearCur->sm[i].end.year, '\n');

            yearCur->sm[i].inSY = yearCur;
            yearCur->sm[i].num = i;
            yearCur->sm[i].syName = yearCur->name;

            in.close();
        }
        else if (tmp.substr(tmp.size() - 5, 5) == "_mark")
            readScoreboardFile(entry.path(), yearCur, i);
        else //if (tmp.size() > 5 && tmp.substr(tmp.size() - 5, 5) != "_mark")
        {
            ifstream in;
            in.open(entry.path());

            if (courseCur != NULL)
            {
                courseCur->courseNext = new Course;
                courseCur = courseCur->courseNext;
            }
            else
            {
                yearCur->sm[i].courseHead = new Course;
                courseCur = yearCur->sm[i].courseHead;
            }
            string className = "", ID = "", check = "", header, line; ;
            int j;

            for (j = 0; j < tmp.size() && tmp[j] != '_'; j++)
                ID += tmp[j];
            for (j += 1; j < tmp.size() && tmp[j] != '_'; j++)
                className += tmp[j];
            for (j += 1; j < tmp.size(); j++)
                check += tmp[j];

            getline(in, courseCur->name, '\n');
            getline(in, courseCur->teacherName, '\n');
            in >> courseCur->numCredit;
            in >> courseCur->maxStudent;
            in.ignore(1, '\n');
            getline(in, courseCur->day, '\n');
            getline(in, header, '\n');
            courseCur->session = stoi(header.substr(1, 1));
            // dang sua

            courseCur->ID = ID;
            courseCur->className = className;
            courseCur->inSM = &(yearCur->sm[i]);        // double linked
            StuInCourse* stuCur = courseCur->stuHead;

            // xoa dong 1
            getline(in, header, '\n');

            if (check != "dsdkhp")
                while (!in.eof())
                {
                    if (stuCur != NULL) {
                        stuCur->stuNext = new StuInCourse;
                        stuCur = stuCur->stuNext;
                    }
                    else {
                        courseCur->stuHead = new StuInCourse;
                        stuCur = courseCur->stuHead;
                    }

                    string syTmp, classTmp, IDTmp;
                    getline(in, syTmp, '\t');
                    getline(in, classTmp, '\t');
                    getline(in, IDTmp, '\n');

                    stuCur->courseID = ID;
                    stuCur->stuNext = nullptr;

                    Student* stuInClass = findStuInClass(syTmp, classTmp, IDTmp, yearHead);
                    stuCur->stuInClass = stuInClass;
                    stuCur->infoCourse = courseCur;

                    StuInCourse* pStuCourseCur = stuInClass->pStuCourseHead;

                    // reverselinked
                    if (pStuCourseCur == nullptr)
                    {
                        stuInClass->pStuCourseHead = stuCur;
                    }
                    else
                    {
                        while (pStuCourseCur->pStuCourseNext != nullptr)
                            pStuCourseCur = pStuCourseCur->pStuCourseNext;
                        pStuCourseCur->pStuCourseNext = stuCur;
                    }
                    stuCur->pStuCourseNext = nullptr;
                }
            in.close();
        }
    }
}
/*
read all information
log in:
find id in linked list  (view.cpp) (findStudentbyID(username, yearHead))
find password in filecheck passsword and username
*/
/*
bool checkPasswordInFile_01(string username, string password, SchoolYear* yearHead)
{
    SchoolYear* yearCur;
    Student* stuCur = findStudentByID(username, yearHead);
    if (stuCur == nullptr) return false;

    ifstream in("Information/" + yearCur->name + "/Class/" + stuCur->className + "_password.txt");
    if (!in.is_open()) return false;

    string user, pass;
    getline(in, user, '\t');
    getline(in, pass, '\n');
    
    while (!in.eof())
    {
        getline(in, user, '\t');
        getline(in, pass, '\n');

        if (user == username)
            if (pass == password) {
                in.close();
                return true;
            }
            else {
                in.close();
                return false;
            }
    }
    in.close();
    return false;
}
*/

// check student's password
bool checkStudentPasswordInFile(string username, string password, SchoolYear* yearHead)
{
    SchoolYear* yearCur;
    Student* stuCur = findStudentByID(username, yearHead);
    if (stuCur == NULL) return false;

    ifstream in("Information/" + stuCur->inClass->inSY->name + "/Class/" + stuCur->className + "_password.txt");
    if (!in.is_open()) return false;

    string user, pass;
    getline(in, user, '\t');
    getline(in, pass, '\n');

    while (!in.eof())
    {
        getline(in, user, '\t');
        getline(in, pass, '\n');

        if (user == username)
            if (pass == password) {
                in.close();
                return true;
            }
            else {
                in.close();
                return false;
            }
    }
    in.close();
    return false;
}

// check staff's password
bool checkStaffPasswordInFile(string username, string password)
{
    ifstream in("Information/Staff.txt");
    if (!in.is_open()) return false;

    string user, pass, name;
    getline(in, user, '\n');

    while (!in.eof())
    {
        getline(in, user, '\t');
        getline(in, user, '\t');
        getline(in, pass, '\n');

        if (user == username)
            if (pass == password) {
                in.close();
                return true;
            }
            else {
                in.close();
                return false;
            }
    }
    in.close();
    return false;
}

bool changeStudentPasswordInFile(Student* stuCur, string newPass)
{
    string inputFile = "Information/" + stuCur->inClass->inSY->name + "/Class/" + stuCur->className + "_password.txt";
    string copyFile = "Information/" + stuCur->inClass->inSY->name + "/Class/Temp_password.txt";
    ifstream in(inputFile);
    ofstream out(copyFile);
    if (!in.is_open() || !out.is_open()) return false;

    string username, password;

    getline(in, username, '\t');
    getline(in, password, '\n');
    out << username << '\t' << password;

    while (!in.eof())
    {
        getline(in, username, '\t');
        getline(in, password, '\n');
        out << '\n' << username << '\t';

        if (username == stuCur->StuID)
            out << newPass;
        else out << password;
    }
    in.close();
    out.close();

    remove(inputFile.c_str());
    rename(copyFile.c_str(), inputFile.c_str());
}

// phai chay ham checkPassword truoc, neu dung moi doi
bool changeStudentPasswordInFile(string user, string newPass)
{
    string inputFile = "Information/Staff.txt";
    string copyFile = "Information/Temp_password.txt";
    ifstream in(inputFile);
    ofstream out(copyFile);
    if (!in.is_open() || !out.is_open()) return false;

    string username, name, password;

    getline(in, username, '\t');
    getline(in, name, '\t');
    getline(in, password, '\n');
    out << username << '\t' << name << '\t' << password;

    while (!in.eof())
    {
        getline(in, username, '\t');
        getline(in, name, '\t');
        getline(in, password, '\n');
        out << '\n' << username << '\t' << name << '\t';

        if (username == user)
            out << newPass;
        else out << password;
    }
    in.close();
    out.close();

    remove(inputFile.c_str());
    rename(copyFile.c_str(), inputFile.c_str());
}

void readInformation(const path& path, SchoolYear*& yearCur, SchoolYear*& yearHead)
{
    for (const auto& entry : directory_iterator(path)) {
        string tmp = entry.path().filename().stem().string();
        string isSmt = tmp;

        if (tmp == "Class") {
            readListClass(entry.path(), yearCur);
        }
        else if (isSmt.size() == 10 && isSmt.substr(0, 8) == "Semester") {
            for (int i = 0; i < 3; i++)
                if (tmp == "Semester " + to_string(i + 1))
                {
                    readListCourse(entry.path(), yearCur, yearHead, i);
                    break;
                }
        }
        else if (tmp != "Staff")
        {
            if (yearHead == nullptr) {
                yearHead = new SchoolYear;
                yearCur = yearHead;
            }
            else {
                yearCur->yearNext = new SchoolYear;
                yearCur = yearCur->yearNext;
            }
            yearCur->name = tmp;
            readInformation(entry.path(), yearCur, yearHead);
        }
    }
}

void deleteAll(SchoolYear*& yearHead)
{
    while (yearHead)
    {
        while (yearHead->classHead)
        {
            Class* classTmp = yearHead->classHead;
            yearHead->classHead = yearHead->classHead->classNext;

            while (classTmp->stuHead)
            {
                Student* stuTmp = classTmp->stuHead;
                classTmp->stuHead = classTmp->stuHead->stuNext;
                delete stuTmp;
            }
            delete classTmp;
        }
        for (int i = 0; i < 3; i++)
        {
            while (yearHead->sm[i].courseHead)
            {
                Course* courseTmp = yearHead->sm[i].courseHead;
                yearHead->sm[i].courseHead = yearHead->sm[i].courseHead->courseNext;

                while (courseTmp->stuHead)
                {
                    StuInCourse* stuTmp = courseTmp->stuHead;
                    courseTmp->stuHead = courseTmp->stuHead->stuNext;
                    delete stuTmp;
                }
                delete courseTmp;
            }
        }
        SchoolYear* yearTmp = yearHead;
        yearHead = yearHead->yearNext;
        delete yearTmp;
    }
}

void sortStuInCourse_01(Course*& courseCur)
{
    bool sorted = false;
    StuInCourse* empty = new StuInCourse;
    empty->stuNext = courseCur->stuHead;

    while (!sorted)
    {
        sorted = true;

        StuInCourse* cur = courseCur->stuHead;
        StuInCourse* prev = empty;
        while (cur && cur->stuNext)
        {
            if (cur->stuInClass->StuID > cur->stuInClass->StuID)
            {
                StuInCourse* tmp = cur->stuNext;
                cur->stuNext = cur->stuNext->stuNext;
                tmp->stuNext = cur;
                prev->stuNext = tmp;

                sorted = false;
            }
            else cur = cur->stuNext;
        }
    }
    courseCur->stuHead = empty->stuNext;
}

optional<path> findFileByName(const path& dir_path, const std::string& file_name) {
    for (const auto& entry : directory_iterator(dir_path)) {
        if (entry.is_directory()) {
            auto result = findFileByName(entry.path(), file_name);
            if (result) {
                return result;
            }
        }
        else if (entry.path().filename().stem().string() == file_name) {
            return entry.path();
        }
    }
    // Không tìm thấy file, trả về một đối tượng optional<path> rỗng
    return nullopt;
}

void displayAll(SchoolYear* yearHead)
{
    while (yearHead)
    {
        cout << yearHead->name << endl;
        Class* classCur = yearHead->classHead;
        while (classCur)
        {
            cout << classCur->name << endl;
            //  viewListOfStudentInClass(classCur);
            classCur = classCur->classNext;
        }
        yearHead = yearHead->yearNext;
    }
}

void saveChange(const path& file_path, Class*& classCur)
{
    ofstream out;
    out.open(file_path);
    if (!out.is_open()) {
        cout << "Cannot open file" << endl;
        return;
    }

    // demo

    out.close();
}
/*
int main() {
    SchoolYear* yearHead = NULL;
    SchoolYear* yearCur = yearHead;
    readInformation("Information", yearCur, yearHead);

    Course* courseHead = yearHead->yearNext->yearNext->yearNext->sm[1].courseHead;

    while(courseHead)
    {
        cout << endl << courseHead->name << endl;
        viewListStudentsInCourse(courseHead);
        courseHead = courseHead->courseNext;
    }

    cout << endl << endl << "course of 19125029" << endl;
    StuInCourse* pCur = findStuInClass("2019-2020", "19CTT", "19125029", yearHead)->pStuCourseHead;
    while (pCur)
    {
        cout << pCur->courseID << endl;
        pCur = pCur->pStuCourseNext;
    }


    while (courseHead)
    {
        cout << courseHead->name << endl;
        courseHead = courseHead->courseNext;
    }

    deleteAll(yearHead);
    return 0;
}
*/
//    displayAll(yearHead);

/*    findStudentByID("19127027", yearHead)->password = "19127027";
    auto result = findFileByName("Student Information", "19CLC4");
    if (result) {
        cout << "Found file at: " << result->string() << std::endl;
    }
    else {
        cout << "File not found." << std::endl;
    }
*/
//saveChange(result->string(), yearHead->classHead);

/*
 directory_iterator(path) : Hàm này nhận vào đường dẫn của một thư mục và trả về một iterator đại diện cho tất cả các tệp tin và thư mục trong thư mục đó.

entry.is_directory() : Hàm này kiểm tra xem một entry có phải là một thư mục hay không.

getline(file, header) và getline(ss, username, ',') : Hàm này đọc một dòng văn bản trong tệp tin.

read_files(path) : Hàm này nhận vào đường dẫn của một thư mục và đọc tất cả các tệp tin và thư mục trong đó bằng cách đệ quy gọi chính nó với đường dẫn của các thư mục con.

path root_path("Data") : Hàm này tạo một đối tượng path từ đường dẫn "Data".
*/


/*

*/



// da check



SchoolYear* findSchoolyear(SchoolYear* yearHead, string syName)
{
    while (yearHead)
        if (yearHead->name == syName)
            return yearHead;
        else yearHead = yearHead->yearNext;

    return nullptr;
}

Class* findClassInSchoolYear(SchoolYear* yearCur, string className)
{
    Class* classCur = yearCur->classHead;
    while (classCur)
    {
        if (classCur->name == className)
            return classCur;
        else classCur = classCur->classNext;
    }
    return nullptr;
}

// truoc do can ham tim phai them semester may, schoolyear may, false if already create 3 sm in current schoolyear
// i from zero
bool createSemester(int i, SchoolYear* yearCur, Date start, Date end)
{
    yearCur->sm[i].start = start;
    yearCur->sm[i].end = end;
    yearCur->sm[i].num = i;
    yearCur->sm[i].inSY = yearCur;
    yearCur->sm[i].syName = yearCur->name;

    ofstream out("Information/" + yearCur->name + "/Semester " + to_string(i + 1) + "/Info.txt");
    if (!out.is_open()) return false;
    out << "Semester\tSchoolYear\tStart Date\tEnd Date" << endl;
    out << yearCur->sm[i].num + 1 << '\t' << yearCur->name << '\t';
    out << yearCur->sm[i].start.day << "/" << yearCur->sm[i].start.month << '/' << yearCur->sm[i].start.year << '\t';
    out << yearCur->sm[i].end.day << "/" << yearCur->sm[i].end.month << '/' << yearCur->sm[i].end.year; 
    out.close();
    return true;
}

// schoolyear must create o cuoi
// cach su dung: goi ham

Date createDate(string date)
{
    Date res;
    res.day = date[0];
    res.day += date[1];
    res.month = date[3];
    res.month += date[4];
    res.year = date[6];
    res.year += date[7];
    res.year += date[8];
    res.year += date[9];
    return res;
}

bool createSchoolyear(SchoolYear* yearCur, string schoolYear, SchoolYear*& yearHead, int smCur)      // file and link
{
    if (findSchoolyear(yearHead, schoolYear) != nullptr)
        return false;
    // chua tao du 2 semester cua hoc ki truoc
    if (smCur != 2) return false;

    create_directory("Information/" + schoolYear);
    create_directory("Information/" + schoolYear + "/Class");
    create_directory("Information/" + schoolYear + "/Semester 1");
    create_directory("Information/" + schoolYear + "/Semester 2");
    create_directory("Information/" + schoolYear + "/Semester 3");

    while (yearCur && yearCur->yearNext)
        yearCur = yearCur->yearNext;

    if (yearCur == nullptr) {
        yearHead = new SchoolYear;
        yearCur = yearHead;
    }
    else {
        yearCur->yearNext = new SchoolYear;
        yearCur = yearCur->yearNext;
    }
    yearCur->name = schoolYear;
    return true;
}

// da check
// i from 0
void findLastSYandSM(SchoolYear* yearHead, SchoolYear*& yearNow, int& semesterNow)
{
    while (yearHead && yearHead->yearNext)
        yearHead = yearHead->yearNext;

    yearNow = yearHead;
    semesterNow = -1;

    if (yearHead != nullptr)
    {
        for (int i = 0; i < 3; i++)
        {
            if (yearHead->sm[i].inSY != nullptr)
                semesterNow = i;
            else break;
        }
    }
}
// chi thao tac tren last semester and last schoolyear
// class create o dau
// cach su dung: findLastSYandSm -> goi ham
bool createClass(SchoolYear* yearCur, string ClassName)        // yearHead == yearCur (find last year & semester)
{
    if (yearCur == nullptr || findClassInSchoolYear(yearCur, ClassName) != nullptr)
    {   
        cout << "Already have class " << ClassName << endl;
        return false;
    }

    Class* classCur = yearCur->classHead;
    yearCur->classHead = new Class;
    yearCur->classHead->name = ClassName;
    yearCur->classHead->inSY = yearCur;
    yearCur->classHead->classNext = classCur;

    path class_path = "Information/" + yearCur->name + "/Class/" + ClassName + ".txt";
    ofstream out(class_path);
    out << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of Birth\tSocialID\tCurriculim\tClass";
    out.close();
    return true;
}
/*
dung ham create SchoolYear
dung ham create Class
int main()
{
    SchoolYear* yearHead = NULL;
    SchoolYear* yearCur = yearHead;
    int semesterNow = -1;
    readInformation("Information", yearCur, yearHead);      // yearCur de chay, yearHead de tim va danh dau
    bool createSYOK = createSchoolyear(yearHead, "2023-2024", yearHead);

    findLastSYandSM(yearHead, yearCur, semesterNow);
    createClass(yearCur, "23CTT1");

    deleteAll(yearHead);
    return 0;
}
*/

Class* findClassInSchoolYearByClassName(SchoolYear* yearCur, string className)
{
    Class* classCur = yearCur->classHead;

    while (classCur)
    {
        if (classCur->name == className)
            return classCur;
        else classCur = classCur->classNext;
    }
    return nullptr;
}

void addStu(Student*& stuCur, Student* stuNew) 
{
    Student* tmp = stuCur;
    stuCur = stuNew;
    stuCur->stuNext = tmp;
}
bool checkIfDateExist(string day, string month, string year) {
    int d = stoi(day);
    int m = stoi(month);
    int y = stoi(year);
    if (d > 31 || d <= 0)
        return false;
    if (m > 12 || m <= 0)
        return false;
    if (y < 0)
        return false;
    if (y % 4 == 0) {
        if (y % 100) {
            if (m == 2 && d > 28)
                return false;
            else if (m == 2 && d > 29)
                return false;
        }
    }
    return true;
}

bool checkDate (string dob) {
    if (dob.size() != 10 || dob[2] != '/' || dob[5] != '/')
        return false;

    for (int i = 0; i < 10; i++)
        if (i != 2 && i != 5)
            if (!(dob[i] <= '9' && dob[i] >= '0')) return false;
    string day = "";
    string month = "";
    string year = "";
    day += dob[0];  day += dob[1];
    month += dob[3];    month += dob[4];
    year += dob[6];     year += dob[7];     year += dob[8];     year += dob[9];

    return checkIfDateExist(day, month, year);
}

void displayWrong(string ID, string first, string last, string gender, string dob, string socID, string className)
{
    cout << "ID: " << ID << endl;
    cout << "First Name: " << first << endl;
    cout << "Last Name: " << last << endl;
    cout << "Gender: " << gender << endl;
    cout << "Date of birth: " << dob << endl;
    cout << "Social ID: " << socID << endl;
    cout << "Class Name: " << className << endl;
}

bool checkInfoStu(string ID, string first, string last, string gender, string dob, string socID, string className) {
    bool check = true;
    if (gender != "Male" && gender != "Female") {
        cout << "Invalid gender was found!" << endl;
        check = false;
    }
    if (dob.size() != 10 || dob[2] != '/' || dob[5] != '/')
    {
        cout << "Invalid date of birth" << endl;
        check = false;
    }

    for (int i = 0; i < 10; i++)
        if (i != 2 && i != 5)
            if (!(dob[i] <= '9' && dob[i] >= '0')) 
            {
                check = false;
            }
     

    string day = "";
    string month = "";
    string year = "";
    day += dob[0];  day += dob[1];
    month += dob[3];    month += dob[4];
    year += dob[6];     year += dob[7];     year += dob[8];     year += dob[9];
    if (checkIfDateExist(day, month, year) == false) {
        cout << "Found error in date of birth of the Student!" << endl;
        check = false;
    }

    for (int i = 0; i < first.length(); i++) {
        if (first[i] - 48 <= 9 && first[i] - 48 >= 0) {
            cout << "Found number in first name of student!" << endl;
            check = false;
            break;
        }
    }
    for (int i = 0; i < last.length(); i++) {
        if (last[i] - 48 <= 9 && last[i] - 48 >= 0) {
            cout << "Found number in last name of student!" << endl;
            check = false;
            break;
        }
    }
    return check;
}
// add vo dau, khi nao co danh sach chinh thuc thi sort + chinh No -> quang file
// pass vo (SY hien tai, newStu); add vo class ten newStu->className
// add in ordered
bool addStudentToClass(SchoolYear* yearCur, Student* newStu)      // yearCur ~ last schoolyear ~ your SchoolYear
{
    Class* classCur = findClassInSchoolYearByClassName(yearCur, newStu->className);
    if (classCur == nullptr) return false;

    Student* stuTmp = classCur->stuHead;
    if (stuTmp == nullptr || stuTmp->StuID > newStu->StuID)
    {
        classCur->stuHead = newStu;
        classCur->stuHead->stuNext = stuTmp;
    }
    else if (stuTmp->StuID == newStu->StuID)
        return false;
    else
    {
        while (stuTmp->stuNext && stuTmp->stuNext->StuID < newStu->StuID)
            stuTmp = stuTmp->stuNext;
        if (stuTmp->stuNext == nullptr)
        {
            stuTmp->stuNext = newStu;
        }
        else if (stuTmp->stuNext->StuID == newStu->StuID)
            return false;
        else
        {
            Student* stuPoint = stuTmp->stuNext;
            stuTmp->stuNext = newStu;
            newStu->stuNext = stuPoint;
        }
    }
    newStu->inClass = classCur;
    return true;
}
/*
cout << "Enter Course's ID: ";
getline(cin, courseTmp->ID, '\n');
cin.ignore(1, '\n');

cout << "Enter Course's name: ";
getline(cin, courseTmp->name, '\n');
cin.ignore(1, '\n');

cout << "Enter Course's className: ";
getline(cin, courseTmp->className, '\n');
cin.ignore(1, '\n');

cout << "Enter Course's teacherName: ";
getline(cin, courseTmp->teacherName, '\n');
cin.ignore(1, '\n');

cout << "Enter Course's credit: ";
cin >> courseCur->;
*/

bool updateCourseInfoInFile(Course* courseCur, Course* courseTmp)
{
    string copy = "Information/" + courseCur->inSM->inSY->name + "/Semester " + to_string(courseCur->inSM->num + 1) + '/' + courseCur->ID + '_' + courseCur->className + ".txt";
    string source = "Information/" + courseCur->inSM->inSY->name + "/Semester " + to_string(courseCur->inSM->num + 1) + '/' + courseTmp->ID + '_' + courseTmp->className + ".txt";
    ofstream out("Information/" + courseCur->inSM->inSY->name + "/Semester " + to_string(courseCur->inSM->num + 1) + '/' + courseCur->ID + "_" + courseCur->className + ".txt");
    if (!out.is_open()) return false;
    out << courseTmp->name << endl;
    out << courseTmp->teacherName << endl;
    out << courseTmp->numCredit << endl;
    out << courseTmp->maxStudent << endl;
    out << courseTmp->day << endl;
    out << "S" << courseTmp->session << endl;
    out << "SchoolYear\tClass\tID";
    StuInCourse* stuCur = courseCur->stuHead;
    while (stuCur)
    {
        out << endl;
        out << stuCur->stuInClass->inClass->inSY->name << '\t';
        out << stuCur->stuInClass->inClass->name << '\t';
        out << stuCur->stuInClass->StuID;
        stuCur = stuCur->stuNext;
    }
    out.close();
    rename(copy.c_str(), source.c_str());
}

// courseTmp da check khong bi loi input
bool updateCourseInfo(Course* courseCur, Course* courseTmp)
{
    // check CourseTmp update co bi trung course nao tru courseCur khong
    Course* check = findCourseByIDAndClass(courseTmp->ID, courseTmp->className, *(courseCur->inSM));
    if (!(check == nullptr || check == courseCur)) return false;

    updateCourseInfoInFile(courseCur, courseTmp);

    courseCur->ID = courseTmp->ID;
    courseCur->name = courseTmp->name;
    courseCur->className = courseTmp->className;
    courseCur->teacherName = courseTmp->teacherName;
    courseCur->numCredit = courseTmp->numCredit;
    courseCur->maxStudent = courseTmp->maxStudent;
    courseCur->session = courseTmp->session;
    courseCur->day = courseTmp->day;

    return true;
}

bool removeStuInCourse(Course* courseCur, StuInCourse* stuCur)
{
    Student* stuInClass = stuCur->stuInClass;
    if (stuInClass->pStuCourseHead == stuCur)
        stuInClass->pStuCourseHead = stuInClass->pStuCourseHead->pStuCourseNext;
    else
    {
        StuInCourse* stuHead = stuInClass->pStuCourseHead;
        while (stuHead->pStuCourseNext && stuHead->pStuCourseNext != stuCur)
            stuHead = stuHead->pStuCourseNext;
        if (stuHead->pStuCourseNext == nullptr) return false;
        else stuHead->pStuCourseNext = stuHead->pStuCourseNext->pStuCourseNext;
    }

    StuInCourse* stuCourse = courseCur->stuHead;
    if (stuCourse && stuCourse == stuCur) courseCur->stuHead = courseCur->stuHead->stuNext;
    else
    {
        while (stuCourse->stuNext && stuCourse->stuNext != stuCur)
            stuCourse = stuCourse->stuNext;
        if (stuCourse->stuNext == nullptr) return false;
        else stuCourse = stuCourse->stuNext;
    }
    delete stuCur;
    stuCur = nullptr;
}


// thieu
// can ham tim kiem check courseCur truoc va tim noi StuInClass cua newStu, da link stuinclass nhung chua link tu stuinclass sang
bool addStuInCourse(SchoolYear* yearCur, StuInCourse* newStu, Course* courseCur)      // yearCur ~ last schoolyear ~ your SchoolYear
{
    StuInCourse* stuCur = courseCur->stuHead;
    if (stuCur == nullptr || stuCur->stuInClass->StuID > newStu->stuInClass->StuID)
    {
        courseCur->stuHead = newStu;
        courseCur->stuHead->stuNext = stuCur;
    }
    else if (stuCur->stuInClass->StuID == newStu->stuInClass->StuID)
        return false;
    else
    {
        while (stuCur->stuNext && stuCur->stuNext->stuInClass->StuID < newStu->stuInClass->StuID)
            stuCur = stuCur->stuNext;
        if (stuCur->stuNext == nullptr)
        {
            stuCur->stuNext = newStu;
        }
        else if (stuCur->stuNext->stuInClass->StuID == newStu->stuInClass->StuID)
            return false;
        else
        {
            StuInCourse* stuPoint = stuCur->stuNext;
            stuCur->stuNext = newStu;
            newStu->stuNext = stuPoint;
        }
    }

    Student* stuInClass = newStu->stuInClass;
    StuInCourse* stuTmp = stuInClass->pStuCourseHead;
    stuInClass->pStuCourseHead = newStu;
    stuInClass->pStuCourseHead->pStuCourseNext = stuTmp;

    newStu->infoCourse = courseCur;
    return true;
}

void sortStuInCourse(Course* courseCur)
{
    if (courseCur->stuHead == nullptr || courseCur->stuHead->stuNext == nullptr) {
        return;
    }

    bool sorted = false;
    while (!sorted) {
        sorted = true;

        StuInCourse* tmp;
        StuInCourse* pre = nullptr;
        StuInCourse* cur = courseCur->stuHead;

        while (cur->stuNext != nullptr) {
            if (cur->stuInClass->StuID > cur->stuNext->stuInClass->StuID) {
                tmp = cur->stuNext;
                cur->stuNext = cur->stuNext->stuNext;
                tmp->stuNext = cur;
                if (cur == courseCur->stuHead) {
                    courseCur->stuHead = tmp;
                }
                else {
                    pre->stuNext = tmp;
                }
                pre = tmp;
                sorted = false;
            }
            else {
                pre = cur;
                cur = cur->stuNext;
            }
        }
    }
}

void addStudentToCSVFileCourse(SchoolYear* yearCur, StuInCourse* newStu)
{
    ofstream out("Information/" + yearCur->name + "/Semester " + to_string(newStu->infoCourse->inSM->num + 1) + "/" + newStu->infoCourse->ID + "_" + newStu->infoCourse->className + ".txt", ios::app);    // luu chinh sua -> viet o cuoi

    out.seekp(0, ios::end);
    out << endl;
    out << newStu->stuInClass->inClass->inSY->name << '\t';
    out << newStu->stuInClass->inClass->name << '\t';
    out << newStu->stuInClass->StuID;

    out.close();
}


// chi khi ham tren == true thi moi thuc hien ham nay
void addStudentToCSVFileClass(SchoolYear* yearCur, Student* newStu)
{
    ofstream out("Information/" + yearCur->name + "/Class/" + newStu->className + ".txt", ios::app);    // luu chinh sua -> viet o cuoi
    
    out.seekp(0, ios::end);
    out << endl;
    out << newStu->No << '\t';
    out << newStu->StuID << '\t';
    out << newStu->firstName << '\t';
    out << newStu->lastName << '\t';
    out << newStu->gender << '\t';
    out << newStu->dateOfBirth.day << '/' << newStu->dateOfBirth.month << '/' << newStu->dateOfBirth.year << '\t';
    out << newStu->socialID << '\t';
    out << newStu->curriculum << '\t';
    out << newStu->className;
       
    out.close();
}

// sort danh sach class chinh thuc + chinh No
void sortStuInClass(Class* classHead)
{
    if (classHead->stuHead == nullptr || classHead->stuHead->stuNext == nullptr) {
        return;
    }

    bool sorted = false;
    while (!sorted) {
        sorted = true;

        Student* tmp;
        Student* pre = nullptr;
        Student* cur = classHead->stuHead;

        while (cur->stuNext != nullptr) {
            if (cur->StuID > cur->stuNext->StuID) {
                tmp = cur->stuNext;
                cur->stuNext = cur->stuNext->stuNext;
                tmp->stuNext = cur;
                if (cur == classHead->stuHead) {
                    classHead->stuHead = tmp;
                }
                else {
                    pre->stuNext = tmp;
                }
                pre = tmp;
                sorted = false;
            }
            else {
                pre = cur;
                cur = cur->stuNext;
            }
        }
    }
}


void officialClass(Class* classHead)
{
    sortStuInClass(classHead);

    int No = 1;
    Student* stuCur = classHead->stuHead;
    while (stuCur)
    {
        stuCur->No = to_string(No++);
        stuCur = stuCur->stuNext;
    }
}

void exportClassToCSVFile(Class* classCur);/*
Semester createNextSemester(SchoolYear*& curSY) {
    int tmp = -1;
    Semester curSM;
    for (int i = 0; i < 2; i++) {
        if (curSY->sm[i].state == 1) {
            if (i != 2)
                tmp = i + 1;
        }
    }
    curSY->sm[tmp - 1].state = 0;
    if (tmp != -1) {
        curSY->sm[tmp].state = 1;
        curSY->sm[tmp].num = tmp + 1;
        cout << "Please enter the start date of semester " << tmp + 1 << " of school year " << curSY->name << " : ";
        inputADate(curSY->sm[tmp].start);
        cout << "Please enter the end date of semester " << tmp + 1 << " of school year " << curSY->name << " : ";
        inputADate(curSY->sm[tmp].end);
        curSM = curSY->sm[tmp];
        curSM.inSY = curSY;
    }
    else {
        SchoolYear* nextSY = new SchoolYear;
        string tmpStr = "";
        int year = 0;
        for (int i = curSY->name.length() - 5; i < curSY->name.length(); i++) {
            year *= 10;
            year += (curSY->name[i] - 48);
        }
        tmpStr += to_string(year);
        tmpStr += "-";
        tmpStr += to_string(year + 1);
        nextSY->name = tmpStr;
        nextSY->sm[0].state = 1;
        cout << "Please enter the start date of semester " << 1 << " of school year " << nextSY->name << " : ";
        inputADate(nextSY->sm[0].start);
        cout << "Please enter the end date of semester " << 1 << " of school year " << nextSY->name << " : ";
        inputADate(nextSY->sm[0].end);
        curSY->yearNext = nextSY;
        curSM = nextSY->sm[0];
        curSM.inSY = nextSY;
    }
    return curSM;
}
*/
Student* createStudent(string No, string StuID, string FirstName, string LastName, string Gender, string dateofbirth, string socialID, Class* classCur, string curriculum)
{
    Student* stuCur = new Student;
    stuCur->No = classCur->numStu;
    stuCur->StuID = StuID;
    stuCur->firstName = FirstName;
    stuCur->lastName = LastName;
    stuCur->gender = Gender;
    stuCur->dateOfBirth.day = dateofbirth[0];
    stuCur->dateOfBirth.day += dateofbirth[1];
    stuCur->dateOfBirth.month = dateofbirth[3];
    stuCur->dateOfBirth.month += dateofbirth[4];
    stuCur->dateOfBirth.year = dateofbirth[6];
    stuCur->dateOfBirth.year += dateofbirth[7];
    stuCur->dateOfBirth.year += dateofbirth[8];
    stuCur->dateOfBirth.year += dateofbirth[9];
    stuCur->socialID = socialID;
    stuCur->className = classCur->name;
    stuCur->curriculum = curriculum;
    return stuCur;
}

// cau 4. findyearCur (findLastSYandSM)-> readStudentFromImportFile -> officalCourse -> exportClassToCSVFile
// readStudentFromImportFile("Import", year hien tai)
bool readStudentFromImportFile(const path& path, SchoolYear* yearCur)
{
    for (const auto& entry : directory_iterator(path)) {
 
        string tmp = entry.path().filename().stem().string();
        Class* classCur = findClassInSchoolYear(yearCur, tmp);
        if (classCur == nullptr)
            cout << "Don't have Class " << tmp << endl;
        else 
        {
            fstream in(entry.path());
            string header;
            getline(in, header, '\n');

            while (!in.eof())
            {
                bool check = true;
                string No, StuID, FirstName, LastName, Gender, dateofbirth, socialID, curriculum, cla;
                Student* stuCur = new Student;

                getline(in, No, '\t');
                getline(in, StuID, '\t');
                getline(in, FirstName, '\t');
                getline(in, LastName, '\t');
                getline(in, Gender, '\t');
                getline(in, dateofbirth, '\t');
                getline(in, socialID, '\t');
                getline(in, curriculum, '\t');
                getline(in, cla, '\n');

                if (checkInfoStu(StuID, FirstName, LastName, Gender, dateofbirth, socialID, cla) == true)
                {
                    Student* stuCur = createStudent(No, StuID, FirstName, LastName, Gender, dateofbirth, socialID, classCur, curriculum);
                    if (tmp == stuCur->className)
                    {
                        if (addStudentToClass(yearCur, stuCur))
                            addStudentToCSVFileClass(yearCur, stuCur);
                        else
                        {
                            cout << "Already have student with same ID." << endl;
                            check = false;
                        }
                    }
                    else
                    {
                        cout << "Wrong class." << endl;
                        check = false;
                    }
                }
                else check = false;

                if (check == false)
                    displayWrong(StuID, FirstName, LastName, Gender, dateofbirth, socialID, cla);
            }
            in.close();

            officialClass(classCur);
            exportClassToCSVFile(classCur);

            remove(entry.path());
        }
    }
    return true;
}


// viet chinh thuc nen viet het lai tu dau
// co the check so hoc sinh -> neu qua it -> ko phai danh sach chinh thuc
void exportClassToCSVFile(Class* classCur)
{
    ofstream out ("Information/" + classCur->inSY->name + "/Class/" + classCur->name + ".txt", ios::trunc);
    out << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of birth\tSocial ID\tCurriculum\tClass";
    
    Student* stuCur = classCur->stuHead;
    while (stuCur)
    {
        out << endl;
        out << stuCur->No << '\t';
        out << stuCur->StuID << '\t';
        out << stuCur->firstName << '\t';
        out << stuCur->lastName << '\t';
        out << stuCur->gender << '\t';
        out << stuCur->dateOfBirth.day << '/' << stuCur->dateOfBirth.month << '/' << stuCur->dateOfBirth.year << '\t';
        out << stuCur->socialID << '\t';
        out << stuCur->curriculum << '\t';
        out << stuCur->className;
        
        stuCur = stuCur->stuNext;
    }
    out.close();
}

// export file nam trong folder export
bool exportListStudentInCourseCSV_mark(Course* courseCur)
{
    path file_path = "Export/" + courseCur->ID + '_' + courseCur->className + "_mark.txt";
    ofstream out(file_path);
    if (!out.is_open()) return false;
    int i = 1;

    out << "Course: " << courseCur->name;
    out << endl << "ID: " << courseCur->ID;
    out << endl << "Class name: " << courseCur->className;
    out << endl << "Teacher name: " << courseCur->teacherName << endl;
    out << "No\tStudent ID\tStudent Full Name";

    StuInCourse* stuCur = courseCur->stuHead;
    while (stuCur)
    {
        out << endl << i++ << '\t';
        out << stuCur->stuInClass->StuID << '\t';
        out << stuCur->stuInClass->firstName << ' ' << stuCur->stuInClass->lastName;
        stuCur = stuCur->stuNext;
    }

    out.close();
    return true;
}

bool exportListStudentInCourseCSV_dssv(Course* courseCur)
{
    path file_path = "Export/" + courseCur->ID + '_' + courseCur->className + "_dssv.txt";
    ofstream out(file_path);
    if (!out.is_open()) return false;
    int i = 1;

    out << "Course: " << courseCur->name;
    out << endl << "ID: " << courseCur->ID;
    out << endl << "Class name: " << courseCur->className;
    out << endl << "Teacher name: " << courseCur->teacherName << endl;
    out << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of birth\tSocial ID\tCurriculum\tClass";

    StuInCourse* stuCur = courseCur->stuHead;
    while (stuCur)
    {
        out << endl << i++ << '\t';
        out << stuCur->stuInClass->StuID << '\t';
        out << stuCur->stuInClass->firstName << '\t';
        out << stuCur->stuInClass->lastName << '\t';
        out << stuCur->stuInClass->gender << '\t';
        out << stuCur->stuInClass->dateOfBirth.day << '/' << stuCur->stuInClass->dateOfBirth.month << '/' << stuCur->stuInClass->dateOfBirth.year << '\t';
        out << stuCur->stuInClass->socialID << '\t';
        out << stuCur->stuInClass->curriculum << '\t';
        out << stuCur->stuInClass->className;

        stuCur = stuCur->stuNext;
    }

    out.close();
    return true;
}

void readStudentFromImportFileToCourse(const path& path, SchoolYear* yearHead, int smCur)    // smCur from 0
{
    for (const auto& entry : directory_iterator(path)) {
        ifstream in;
        in.open(entry.path());
        string tmp = entry.path().filename().stem().string() + "_mark";
        Course* courseCur = findCourseByFileName(yearHead, smCur, tmp);

        if (courseCur == nullptr) return;
        string header;

        getline(in, courseCur->name, '\n');
        getline(in, courseCur->teacherName, '\n');
        in >> courseCur->numCredit;
        in >> courseCur->maxStudent;
        in.ignore(1, '\n');
        getline(in, courseCur->day, '\n');
        getline(in, header, '\n');
        courseCur->session = stoi(header.substr(1, 1));
        // dang sua

        // xoa dong 1
        getline(in, header, '\n');
        while (!in.eof())
        {
            StuInCourse* stuTmp = new StuInCourse;
            string syTmp, classTmp, IDTmp;
            getline(in, syTmp, '\t');
            getline(in, classTmp, '\t');
            getline(in, IDTmp, '\n');

            Student* stuInClass = findStuInClass(syTmp, classTmp, IDTmp, yearHead);
            stuTmp->stuInClass = stuInClass;
            stuTmp->infoCourse = courseCur;

            // check thong tin

            if (addStuInCourse(yearHead, stuTmp, courseCur))
                addStudentToCSVFileCourse(yearHead, stuTmp);
        }
        in.close();

        OfficialCourseToCSV(courseCur);
    }
}

bool isInt(string a)
{
    for (int i = 0; i < a.size(); i++)
        if (!(a[i] >= '0' && a[i] <= '9'))
            return false;
    return true;
}

bool checkInfoCourse(Semester sm, string cID, string cName, string cCre, string cLec, string cDay, string cSes, string cMax, string cClass) {
    bool check = true;
    cout << "Is checking " << cID << "_" << cClass << "..." << endl;
    if (!isInt(cCre) || !isInt(cMax))
    {
        cout << "Found a non-num character in number of credits or number max which is an integer!" << endl;
        check == false;
    }

 //   if (findCourseByIDAndClass(cID, cClass, sm) != NULL) {
 //       cout << cID << "_" << cClass << " has been already created in this semester!" << endl;
 //       check = false;
 //   }
    if (cSes != "S1" && cSes != "S2" && cSes != "S3" && cSes != "S4") {
        cout << "There are only four sessions S1 -> S4!" << endl;
        check = false;
    }
    if (cDay != "MON" && cDay != "TUE" && cDay != "WED" && cDay != "THU" && cDay != "FRI" && cDay != "SAT") {
        cout << "Default day has not been found!" << endl;
        check = false;
    }
    if (check == false) {
        cout << "Oops! There are some mistakes in the course's data as decribed above! Please check again!" << endl;
    }
    return check;
}

Course* findCourseByFileName(SchoolYear* yearCur, int sm, string fileName)
{
    if (!(fileName.size() > 4 && fileName.substr(fileName.size() - 5, 5) == "_mark")) return nullptr;

    Course* courseCur = yearCur->sm[sm].courseHead;
    string courseID = "", className = "";
    for (int i = 0; i < size(fileName); i++)
    {
        if (fileName[i] != '_')
            courseID += fileName[i];
        else
        {
            for (++i; fileName[i] != '_'; i++)
                className += fileName[i];
            break;
        }
    }

    while (courseCur)
    {
        if (courseCur->ID == courseID && courseCur->className == className)
            return courseCur;
        courseCur = courseCur->courseNext;
    }
    return nullptr;
}

Course* findCourseByFileNameInAllCourse(SchoolYear* yearHead, Semester &smCur, string fileName)
{
    string courseID = "", className = "";
    for (int i = 0; i < size(fileName); i++)
    {
        if (fileName[i] != '_')
            courseID += fileName[i];
        else
        {
            for (++i; i < size(fileName) && fileName[i] != '_'; i++)
                className += fileName[i];
            break;
        }
    }
    while (yearHead)
    {
        for (int sm = 0; sm < 3; sm++)
        {
            Course* courseCur = yearHead->sm[sm].courseHead;
            while (courseCur)
            {
                if (courseCur->ID == courseID && courseCur->className == className)
                {
                    smCur = yearHead->sm[sm];
                    return courseCur;
                }
                courseCur = courseCur->courseNext;
            }
        }
        yearHead = yearHead->yearNext;
    }
    return nullptr;
}

// dung thay doi sau khi change courseInfo
void OfficialCourseToCSV(Course* courseCur)
{
    sortStuInCourse(courseCur);

    path create_file = "Information/" + courseCur->inSM->inSY->name + "/Semester " + to_string(courseCur->inSM->num + 1) + '/' + courseCur->ID + '_' + courseCur->className + ".txt";
    ofstream fout(create_file, ios::trunc);

    fout << courseCur->name << "\n";
    fout << courseCur->teacherName << "\n";
    fout << courseCur->numCredit << "\n";
    fout << courseCur->maxStudent << "\n";
    fout << courseCur->day << "\n";
    fout << "S" << courseCur->session << "\n";
    fout << "SchoolYear\tClass\tID";

    StuInCourse* stuHead = courseCur->stuHead;
   
    while (stuHead)
    {
        fout << endl;
        fout << stuHead->stuInClass->inClass->inSY->name << '\t';
        fout << stuHead->stuInClass->inClass->name << '\t';
        fout << stuHead->stuInClass->StuID;

        stuHead = stuHead->stuNext;
    }
}

// end: sort & ghi lai official file, doi ten
void endEnrollCourse(Course* &courseCur)
{
    if (courseCur->stuHead == nullptr || courseCur->stuHead->stuNext == nullptr) {
        return;
    }

    bool sorted = false;
    while (!sorted) {
        sorted = true;

        StuInCourse* tmp;
        StuInCourse* pre = nullptr;
        StuInCourse* cur = courseCur->stuHead;

        while (cur->stuNext != nullptr) {
            if (cur->stuInClass->StuID > cur->stuNext->stuInClass->StuID) {
                tmp = cur->stuNext;
                cur->stuNext = cur->stuNext->stuNext;
                tmp->stuNext = cur;
                if (cur == courseCur->stuHead) {
                    courseCur->stuHead = tmp;
                }
                else {
                    pre->stuNext = tmp;
                }
                pre = tmp;
                sorted = false;
            }
            else {
                pre = cur;
                cur = cur->stuNext;
            }
        }
    }
    string output_file = "Information/" + courseCur->inSM->inSY->name + "/Semester " + to_string(courseCur->inSM->num + 1) + '/' + courseCur->ID + '_' + courseCur->className + "_dsdkhp.txt";
    string name = "Information/" + courseCur->inSM->inSY->name + "/Semester " + to_string(courseCur->inSM->num + 1) + '/' + courseCur->ID + '_' + courseCur->className + ".txt";

    ofstream out(output_file);
    out << courseCur->name << '\n';
    out << courseCur->teacherName << '\n';
    out << "SchoolYear\tClass\tID";
    StuInCourse* stuCur = courseCur->stuHead;
    
    while (stuCur)
    {
        out << endl << stuCur->stuInClass->inClass->inSY->name << '\t';
        out << stuCur->stuInClass->className << '\t';
        out << stuCur->stuInClass->StuID;

        stuCur = stuCur->stuNext;
    }
    rename(output_file.c_str(), name.c_str());
}

// list dslh -> tao class cho schoolyear
bool importListClass_dslh(const path& file_path, SchoolYear*& sy)
{
    ifstream fin(file_path);
    if (!fin.is_open()) return false;
    string s;
    getline(fin, s, '\n');

    // file csv sai schoolYear
    if (s != sy->name) return false;
    getline(fin, s, '\n');  // header
    Class* tmp = sy->classHead;

    while (!fin.eof()) {
        getline(fin, s, '\n');
        createClass(sy, s);
    }
    fin.close();
    // xoa file dkhp
    remove(file_path);
    return true;
}

Course* findCourseByIDAndClass(string ID, string className, Semester sm)
{
    Course* courseCur = sm.courseHead;
    while (courseCur)
    {
        if (courseCur->ID == ID && courseCur->className == className)
            return courseCur;
        courseCur = courseCur->courseNext;
    }
    return nullptr;
}

// truoc do co ham kiem input
// sm from 0
bool createCourse(Course* newCourse, int sm, SchoolYear* yearCur)
{
    if (findCourseByIDAndClass(newCourse->ID, newCourse->className, yearCur->sm[sm]) != nullptr) return false;     // da tao r
    Course* courseTmp = yearCur->sm[sm].courseHead;
    yearCur->sm[sm].courseHead = newCourse;
    newCourse->courseNext = courseTmp;
    newCourse->inSM = &(yearCur->sm[sm]);

    // createFile
    path create_file = "Information/" + yearCur->name + "/Semester " + to_string(sm + 1) + '/' + newCourse->ID + '_' + newCourse->className + ".txt";
    ofstream fout(create_file);

    fout << newCourse->name << endl;
    fout << newCourse->teacherName << endl;
    fout << newCourse->numCredit << endl;
    fout << newCourse->maxStudent << endl;
    fout << newCourse->day << endl;
    fout << "S" << newCourse->session << endl;
    fout << "SchoolYear Class   ID";
    fout.close();
    return true;
}

// sm cur from 0
bool addCourseToSemester(SchoolYear*& yearCur, int smCur)
{
    Course* tmp;
    string s, ID, Name, Cre, Lec, Day, Ses, Max, Class;

    cout << "Enter Course's ID: ";
    getline(cin, ID, '\n');
    cout << "Enter Course's Name: ";
    getline(cin, Name, '\n');
    cout << "Enter Course's number of credit: ";
    getline(cin, Cre, '\n');
    cout << "Enter Course's Lecturer: ";
    getline(cin, Lec, '\n');
    cout << "Enter Coures's day of perform (Ex: MON): ";
    getline(cin, Day, '\n');
    cout << "Enter Course's session (S1 to S4): ";
    getline(cin, Ses, '\n');
    cout << "Enter Course's Max number of student: ";
    getline(cin, Max, '\n');
    cout << "Enter Course's ClassName: ";
    getline(cin, Class, '\n');

        // check thong tin
    if (findClassInSchoolYear(yearCur, Class) != nullptr)
    {
        if (checkInfoCourse(yearCur->sm[smCur], ID, Name, Cre, Lec, Day, Ses, Max, Class) == true)
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
            return createCourse(tmp, smCur, yearCur);
        }
        return false;
    }
    else {
        cout << "Could not find Class " << Class << " in Schoolyear " << endl;
        return false;
    }
}


// file path la: Import/dshp.txt
bool importListCourse_dshp(const path& file_path, SchoolYear*& yearCur, int smCur)
{
    ifstream fin(file_path);
    if (!fin.is_open()) return false;
    string s;
    getline(fin, s, ' ');
    string hk = s.substr(2, 1);
    if (hk != "1" && hk != "2" && hk != "3") return false;

    if (stoi(hk) - 1 != smCur) return false;
    getline(fin, s, '\n');
    if (s != yearCur->name) return false;

    getline(fin, s, '\n');  // header

    Course* tmp = new Course;

    while (!fin.eof()) {
        string s, ID, Name, Cre, Lec, Day, Ses, Max, Class;
        getline(fin, ID, '\t');
        getline(fin, Name, '\t');
        getline(fin, Cre, '\t');
        getline(fin, Lec, '\t');
        getline(fin, Day, '\t');
        getline(fin, Ses, '\t');
        getline(fin, Max, '\t');
        getline(fin, Class, '\n');

        if (findClassInSchoolYear(yearCur, Class) != nullptr)
        {
            if (checkInfoCourse(yearCur->sm[stoi(hk)-1], ID, Name, Cre, Lec, Day, Ses, Max, Class) == true)
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
                if (createCourse(tmp, smCur, yearCur))
                    cout << "Created " << tmp->ID << "_" << tmp->className << endl;
            }
        }
        else {
            cout << "Could not find Class " << Class << " in Schoolyear " << endl;
        }
    }
    fin.close();
    // xoa file dkhp
    remove(file_path);
    return true;
}

void outWrongCSVInput()
{
    return;
}

bool checkMark(string tmp, float& mark)
{
    int t = 0;
    if (tmp.size() > 4) return false;
    for (int i = 0; i < tmp.size(); i++)
    {
        if (tmp[i] == '.' && i != 0 && i != tmp.size() - 1)
        {
            t++;
            if (t != 1) return false;
        }
        else if (!(tmp[i] <= '9' && tmp[i] >= '0')) return false;
    }
    mark = stof(tmp);
    return (mark <= 10.0);
}

StuInCourse* findStuInCourse(string ID, string name, Course* courseCur)
{
    StuInCourse* stuCur = courseCur->stuHead;

    while (stuCur)
    {
        if (stuCur->stuInClass->StuID == ID)
            if (stuCur->stuInClass->firstName + ' ' + stuCur->stuInClass->lastName == name)
                return stuCur;
            else return nullptr;
        stuCur = stuCur->stuNext;
    }
    return nullptr;
}

// chuyen file tu import vao imformation
void passScoreboardFileFromImport(Course* courseCur)
{
    ofstream out("Information/" + courseCur->inSM->inSY->name + "/Semester " + to_string(courseCur->inSM->num + 1) + '/' + courseCur->ID + "_" + courseCur->className + "_mark.txt");

    int i = 1;

    out << "Course: " << courseCur->name << endl;
    out << "ID: " << courseCur->ID << endl;
    out << "Class name: " << courseCur->className << endl;
    out << "Teacher name: " << courseCur->teacherName << endl;
    out << "No\tStudent ID\tStudent Full Name\tTotal\tFinal\tMidterm\tOther";

    StuInCourse* stuCur = courseCur->stuHead;
    while (stuCur)
    {
        out << endl << i++ << '\t';
        out << stuCur->stuInClass->StuID << '\t';
        out << stuCur->stuInClass->firstName << ' ' << stuCur->stuInClass->lastName << '\t';
        out << stuCur->totalM << '\t' << stuCur->finalM << '\t' << stuCur->midM << '\t' << stuCur->otherM;

        stuCur = stuCur->stuNext;
    }
    out.close();
}

// truong hop nhap sai, delete Class trong yearCur do, chi duoc dung ham beginning schoolyear
// tra ve false => ko co trong schoolyear, nhap sai ten
bool deleteClass(string className, SchoolYear* yearCur)
{
    Class* classCur = yearCur->classHead;
    if (classCur && classCur->name == className)
    {
        yearCur->classHead = yearCur->classHead->classNext;
        delete classCur;
        return true;
    }
    
    while (classCur && classCur->classNext)
    {
        if (classCur->classNext->name == className)
        {
            Class* classTmp = classCur->classNext;
            classCur->classNext = classCur->classNext->classNext;
            delete classTmp;
            return true;
        }
        classCur = classCur->classNext;
    }
    return false;
}

// cout << "you are change the course: courseCur->ID + courseCur->ClassName
bool updateStudentResult(Course* courseCur) {
    if (courseCur->stuHead) return false;
    string header, ID, name, totalTmp, finalTmp, midTmp, otherTmp;
    float total, final, mid, other;

    cout << "Enter student ID: ";
    getline(cin, ID, '\n');
    cout << "Enter student full name: ";
    getline(cin, name, '\n');
    cout << "Enter Total Mark: ";
    getline(cin, totalTmp, '\n');
    cout << "Enter Final Mark: ";
    getline(cin, finalTmp, '\n');
    cout << "Enter Midterm Mark: ";
    getline(cin, midTmp, '\n');
    cout << "Enter Other Mark: ";
    getline(cin, otherTmp, '\n');

    StuInCourse* stuCur = findStuInCourse(ID, name, courseCur);
    if (stuCur != nullptr)
    {
        if (checkMark(totalTmp, total) && checkMark(finalTmp, final) && checkMark(midTmp, mid) && checkMark(otherTmp, other))
        {
            stuCur->totalM = total;
            stuCur->finalM = final;
            stuCur->midM = mid;
            stuCur->otherM = other;

            // chuyen file vao information
            passScoreboardFileFromImport(courseCur);
        }
    }
    // xu ly have wrong data
    return true;
}

// chuyen tat ca cac file course cua hoc ky do thanh _dsdkhp
// pass vo "Information/" + sm->inSY->name + "/Semester " + to_string(sm->num + 1);

void beginStudentEnrollCourse(Semester* sm)
{
    path path = "Information/" + sm->inSY->name + "/Semester " + to_string(sm->num + 1);
    for (const auto& entry : directory_iterator(path)) {
        string tmp = "Information/" + sm->inSY->name + "/Semester " + to_string(sm->num + 1) + '/' + entry.path().filename().stem().string();
        string inputFile = tmp + ".txt";
        string copyFile = tmp + "_dsdkhp.txt";

        if (entry.path().filename().stem().string() != "Info")
            rename(inputFile.c_str(), copyFile.c_str());
    }
}

/*
void beginStudentEnrollCourse(Semester* sm)
{
    path path = "Information/" + sm->inSY->name + "/Semester " + to_string(sm->num + 1);
    for (const auto& entry : directory_iterator(path)) {
        string tmp = entry.path().filename().stem().string();
        string inputFile = tmp + ".txt";
        string copyFile = tmp + "_dsdkhp.txt";

        if (tmp != "Info")
            rename(copyFile.c_str(), inputFile.c_str());
    }
}
*/

void viewStudentCourse(Student* stuHead, int sm, SchoolYear* yearCur)
{
    StuInCourse* stuCur = stuHead->pStuCourseHead;
    while (stuCur)
    {
        if (stuCur->infoCourse->inSM->num == sm && stuCur->infoCourse->inSM->inSY == yearCur)
            cout << stuCur->infoCourse->name << " < " << stuCur->infoCourse->ID << '_' << stuCur->infoCourse->className << " > " << endl;
        stuCur = stuCur->pStuCourseNext;
    }
}

// readStudentFromImportFile("Import", year hien tai)
// coi nhu dong bo giua 2 file danh sach va file diem
// co the dung de update file diem tu file
bool importScoreboardFile(const path& path, SchoolYear* yearCur, int sm)
{
    for (const auto& entry : directory_iterator(path)) {
        string tmp = entry.path().filename().stem().string();   // tmp = CS612_22CTT1_mark;
        Course* courseCur = findCourseByFileName(yearCur, sm, tmp);
        fstream in(entry.path());
        if (courseCur == nullptr || !in.is_open()) return false;
        string header, ID, name, totalTmp, finalTmp, midTmp, otherTmp;
        float total, final, mid, other;
        getline(in, header, '\n');
        getline(in, header, '\n');
        getline(in, header, '\n');
        getline(in, header, '\n');
        getline(in, header, '\n');

        while (!in.eof())
        {
            getline(in, header, '\t');
            getline(in, ID, '\t');
            getline(in, name, '\t');
            getline(in, totalTmp, '\t');
            getline(in, finalTmp, '\t');
            getline(in, midTmp, '\t');
            getline(in, otherTmp, '\n');

            StuInCourse* stuCur = findStuInCourse(ID, name, courseCur);
            if (stuCur != nullptr)
            {
                if (checkMark(totalTmp, total) && checkMark(finalTmp, final) && checkMark(midTmp, mid) && checkMark(otherTmp, other))
                {
                    stuCur->totalM = total;
                    stuCur->finalM = final;
                    stuCur->midM = mid;
                    stuCur->otherM = other;
                }
            }
            // xu ly have wrong data
        }
        // chuyen file vao information
        passScoreboardFileFromImport(courseCur);

        in.close();
        remove(entry.path());
    }
    return true;
}


// delete trong linked list va delete trong file

// create Schoolyear, check if it exist
/*
int main()
{
    SchoolYear* yearHead = NULL;
    SchoolYear* yearCur = yearHead;
    int semesterNow = -1;
    readInformation("Information", yearCur, yearHead);      // yearCur de chay, yearHead de tim va danh dau
 
    yearCur = yearHead->yearNext->yearNext->yearNext;

//    beginStudentEnrollCourse(&(yearCur->sm[1]));

    deleteAll(yearHead);
    return 0;
}
*/
/*
dung ham add Class by file dslh.txt
importListClass_dslh("Import/dslh.txt", yearCur);

*/

/*
dung ham add stu to class from csv file
    readStudentFromImportFile("Import", yearCur);
*/

/*
dung ham add stu to class
    if (createClass(yearCur, "23CTT1"))
        cout << "Create duoc" << endl;
    else cout << "create loi" << endl;

    Student* newStu = new Student;
    newStu->No = "3";
    newStu->StuID = "22125001";
    newStu->firstName = "Nguyen Mia";
    newStu->lastName = "Khanh";
    newStu->gender = "Female";
    newStu->dateOfBirth.day = "02";
    newStu->dateOfBirth.month = "11";
    newStu->dateOfBirth.year = "2004";
    newStu->socialID = "35271423";
    newStu->className = "23CTT1";
    newStu->curriculum = "IT";

    if(addStudentToClass(yearCur, newStu))
        addStudentToCSVFileClass(yearCur, newStu);
    else cout << "Loi" << endl;

//    importListCourse_dshp("Import/dshp.txt", yearHead->yearNext->yearNext->yearNext);

    // check man hinh console
    Class* classCur = findClassInSchoolYearByClassName(yearCur, "23CTT1");
    Student* stuCur = findClassInSchoolYearByClassName(yearCur, "23CTT1")->stuHead;
    while (stuCur)
    {
        cout << stuCur->StuID << '\t' << stuCur->firstName << endl;
        stuCur = stuCur->stuNext;
    }

    // khi log out thi dung ham nay
    officialClass(classCur);
    exportClassToCSVFile(classCur);

*/

/*
add student to export official class
 if (addStudentToClass(yearHead, stuCur)) addStudentToCSVFileClass(yearHead, stuCur);

    officialClass(yearHead->classHead);
    exportClassToCSVFile(yearHead, yearHead->classHead);
*/

/*
   readStudentFromTMP("Import", yearHead);

    Student* stuNow = yearHead->classHead->stuHead;
    while (stuNow) {
        cout << stuNow->StuID << ", " << stuNow->lastName << ", " << stuNow->firstName << endl;
        stuNow = stuNow->stuNext;
    }
    */

/*
    
    if (exportListStudentInCourseCSV(yearHead->yearNext->yearNext->yearNext->sm[0].courseHead)) cout << "ok";
    else cout << "not ok";

*/

//    importScoreboardFile("Import", yearHead->yearNext->yearNext->yearNext, 0);

//    findLastSYandSM(yearHead, yearCur, semesterNow);
//    officialClass(yearHead->classHead);
//    exportClassToCSVFile(yearHead, yearHead->classHead);

/*
Student* stuCur = findStudentByID("22125006", yearHead);
    if (changePasswordInFile(stuCur, "da chuyen doi ok")) cout << "dung";
    else cout << "sai rui";
    */

/*
    dshp ->dang ky hoc phan
    Course* courseCur = yearHead->yearNext->yearNext->yearNext->sm[1].courseHead;
    while (courseCur)
    {
        cout << courseCur->name << " " << courseCur->className << endl;
        courseCur = courseCur->courseNext;
    }
    */

/*
   readInformation("Information", yearCur, yearHead);      // yearCur de chay, yearHead de tim va danh dau

    importListCourse_dshp("Import/dshp.txt", yearHead->yearNext->yearNext->yearNext);
*/
