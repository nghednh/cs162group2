#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <optional>
#include "Structure.h"
#include "View.h"

namespace fs = std::filesystem;
using namespace fs;

Course* findCourseByFileName(SchoolYear* yearCur, int sm, string fileName);

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
    yearCur->sm[i].inSY = yearCur;

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
            int num = i;

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
            string className = "", ID = "";
            int j;

            for (j = 0; j < tmp.size() && tmp[j] != '_'; j++)
                ID += tmp[j];
            for (j += 1; j < tmp.size() && tmp[j] != '_'; j++)
                className += tmp[j];

            getline(in, courseCur->name, '\n');
            getline(in, courseCur->teacherName, '\n');

            courseCur->ID = ID;
            courseCur->className = className;
            courseCur->inSM = &(yearCur->sm[i]);        // double linked
            StuInCourse* stuCur = courseCur->stuHead;

            string header, line;              // xoa dong 1
            getline(in, header);

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
find password in file 
check passsword and username
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
bool checkPasswordInFile(string username, string password, SchoolYear* yearHead)
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


bool changePasswordInFile(Student* stuCur, string newPass)
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
        else {
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

// schoolyear must create o cuoi
// cach su dung: goi ham
bool createSchoolyear(SchoolYear* yearCur, string schoolYear, SchoolYear*& yearHead)      // file and link
{
    if (findSchoolyear(yearHead, schoolYear) != nullptr)
        return false;

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
            if (yearHead->sm[i].state == 1)
                semesterNow == i;
            else break;
        }
    }
}
// chi thao tac tren last semester and last schoolyear
// class create o dau
// cach su dung: findLastSYandSm -> goi ham
bool createClass(SchoolYear* yearCur, string ClassName)        // yearHead == yearCur (find last year & semester)
{
    if (yearCur == nullptr || findClassInSchoolYear(yearCur, ClassName) != nullptr) return false;

    Class* classCur = yearCur->classHead;
    yearCur->classHead = new Class;
    yearCur->classHead->name = ClassName;
    yearCur->classHead->classNext = classCur;

    path class_path = "Information/" + yearCur->name + "/Class/" + ClassName + ".txt";
    ofstream out(class_path);
    out << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of Birth\tSocialID\tCurriculim\tClass";
    out.close();
    return true;
}
/*
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

// add vo dau, khi nao co danh sach chinh thuc thi sort + chinh No -> quang file
// pass vo (SY hien tai, newStu); add vo class ten newStu->className
bool addStudentToClass(SchoolYear* yearCur, Student* newStu)      // yearCur ~ last schoolyear ~ your SchoolYear
{
    Class* classCur = findClassInSchoolYearByClassName(yearCur, newStu->className);
    if (classCur == nullptr) return false;

    Student* stuTmp = classCur->stuHead;
    classCur->stuHead = newStu;
    classCur->stuHead->stuNext = stuTmp;
    return true;
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


// cau 4. findyearCur (findLastSYandSM)-> readStudentFromImportFile -> officalCourse -> exportClassToCSVFile
// readStudentFromImportFile("Import", year hien tai)
void readStudentFromImportFile(const path& path, SchoolYear* yearCur)
{
    for (const auto& entry : directory_iterator(path)) {
 
        fstream in (entry.path());
        string header;
        getline(in, header, '\n');
        while (!in.eof())
        {
            Student* stuCur = new Student;
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

            if (addStudentToClass(yearCur, stuCur))
                addStudentToCSVFileClass(yearCur, stuCur);
        }    
        in.close();
        remove(entry.path());
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

// viet chinh thuc nen viet het lai tu dau
// co the check so hoc sinh -> neu qua it -> ko phai danh sach chinh thuc
void exportClassToCSVFile(SchoolYear* yearCur, Class* classCur)
{
    ofstream out ("Information/" + yearCur->name + "/Class/" + classCur->name + ".txt", ios::trunc);
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
        out << stuCur->stuInClass->firstName << ' ' << stuCur->stuInClass->lastName << '\t';
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

Course* findCourseByFileName(SchoolYear* yearCur, int sm, string fileName)
{
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

// file path la: Import/dshp.txt
bool importListCourse_dshp(const path& file_path, SchoolYear*& sy)
{
    ifstream fin(file_path);
    if (!fin.is_open()) return false;
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
        fout << "SchoolYear Class   ID";
        fout.close();
    }
    fin.close();
    // xoa file dkhp
    remove(file_path);
    return true;
}

// readStudentFromImportFile("Import", year hien tai)
// coi nhu dong bo giua 2 file danh sach va file diem
bool importScoreboardFile(const path& path, SchoolYear* yearCur, int sm)
{
    for (const auto& entry : directory_iterator(path)) {
        string tmp = entry.path().filename().stem().string();
        Course* courseCur = findCourseByFileName(yearCur, sm, tmp);
        fstream in(entry.path());
        if (courseCur == nullptr || !in.is_open()) return false;
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
   
        ofstream out("Information/" + yearCur->name + "/Semester " + to_string(sm + 1) + '/' + tmp + ".txt");
        in.seekg(0, ios::beg);
        out << in.rdbuf();
        out.close();
        in.close();
        remove(entry.path());
    }
    return true;
}

// delete trong linked list va delete trong file

// create Schoolyear, check if it exist
int main()
{
    SchoolYear* yearHead = NULL;
    SchoolYear* yearCur = yearHead;
    int semesterNow = -1;
    readInformation("Information", yearCur, yearHead);      // yearCur de chay, yearHead de tim va danh dau

    importListCourse_dshp("Import/dshp.txt", yearHead->yearNext->yearNext->yearNext);


    deleteAll(yearHead);
    return 0;
}

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