#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <optional>
#include <algorithm>
#include "Structure.h"
namespace fs = std::filesystem;
using namespace fs;

Course* findCourseByFileName(SchoolYear* yearCur, int sm, string fileName);
void OfficialCourseToCSV(Course* courseCur);
bool updateCourseInfo(Course* courseCur, Course* courseTmp);
Course* findCourseByIDAndClass(string ID, string className, Semester sm);

// Input

bool checkInfoCourse(Semester sm, string cID, string cName, string cCre, string cLec, string cDay, string cSes, string cMax, string cClass);
void readListClass(const path& file_path, SchoolYear*& yearCur);
Student* findStuInClass(string syTmp, string classTmp, string IDTmp, SchoolYear*& yearHead);
void createCoursesFromList(SchoolYear*& sy, const path& file_path);
void readScoreboardFile(const path& path, SchoolYear* yearCur, int sm);
void readListCourse(const path& file_path, SchoolYear*& yearCur, SchoolYear*& yearHead, int i);
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

Student* findStudentByID(string ID, SchoolYear* sYearHead);

// check student's password
bool checkStudentPasswordInFile(string username, string password, SchoolYear* yearHead);
// check staff's password
bool checkStaffPasswordInFile(string username, string password);

bool changeStudentPasswordInFile(Student* stuCur, string newPass);

// phai chay ham checkPassword truoc, neu dung moi doi
bool changeStudentPasswordInFile(string user, string newPass);

void readInformation(const path& path, SchoolYear*& yearCur, SchoolYear*& yearHead);

void deleteAll(SchoolYear*& yearHead);

void sortStuInCourse_01(Course*& courseCur);

optional<path> findFileByName(const path& dir_path, const std::string& file_name);

void displayAll(SchoolYear* yearHead);

void saveChange(const path& file_path, Class*& classCur);
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



SchoolYear* findSchoolyear(SchoolYear* yearHead, string syName);

Class* findClassInSchoolYear(SchoolYear* yearCur, string className);

// truoc do can ham tim phai them semester may, schoolyear may, false if already create 3 sm in current schoolyear
// i from zero
bool createSemester(int i, SchoolYear* yearCur, Date start, Date end);

// schoolyear must create o cuoi
// cach su dung: goi ham
bool createSchoolyear(SchoolYear* yearCur, string schoolYear, SchoolYear*& yearHead, int smCur);
// da check
// i from 0
void findLastSYandSM(SchoolYear* yearHead, SchoolYear*& yearNow, int& semesterNow);
// chi thao tac tren last semester and last schoolyear
// class create o dau
// cach su dung: findLastSYandSm -> goi ham
bool createClass(SchoolYear* yearCur, string ClassName);
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

Class* findClassInSchoolYearByClassName(SchoolYear* yearCur, string className);
void addStu(Student*& stuCur, Student* stuNew);
// add vo dau, khi nao co danh sach chinh thuc thi sort + chinh No -> quang file
// pass vo (SY hien tai, newStu); add vo class ten newStu->className
// add in ordered
bool addStudentToClass(SchoolYear* yearCur, Student* newStu);
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

// courseTmp da check khong bi loi input
bool updateCourseInfo(Course* courseCur, Course* courseTmp);
bool removeStuInCourse(Course* courseCur, StuInCourse* stuCur);
// thieu
// can ham tim kiem check courseCur truoc va tim noi StuInClass cua newStu, da link stuinclass nhung chua link tu stuinclass sang
bool addStuInCourse(SchoolYear* yearCur, StuInCourse* newStu, Course* courseCur);
void sortStuInCourse(Course* courseCur);
void addStudentToCSVFileCourse(SchoolYear* yearCur, StuInCourse* newStu);
// chi khi ham tren == true thi moi thuc hien ham nay
void addStudentToCSVFileClass(SchoolYear* yearCur, Student* newStu);
// sort danh sach class chinh thuc + chinh No
void sortStuInClass(Class* classHead);
void officialClass(Class* classHead);

void exportClassToCSVFile(Class* classCur);

// cau 4. findyearCur (findLastSYandSM)-> readStudentFromImportFile -> officalCourse -> exportClassToCSVFile
// readStudentFromImportFile("Import", year hien tai)
bool readStudentFromImportFile(const path& path, SchoolYear* yearCur);

// viet chinh thuc nen viet het lai tu dau
// co the check so hoc sinh -> neu qua it -> ko phai danh sach chinh thuc
void exportClassToCSVFile(Class* classCur);
// export file nam trong folder export
bool exportListStudentInCourseCSV_mark(Course* courseCur);
bool exportListStudentInCourseCSV_dssv(Course* courseCur);
void readStudentFromImportFileToCourse(const path& path, SchoolYear* yearHead, int smCur);
Course* findCourseByFileName(SchoolYear* yearCur, int sm, string fileName);
// dung thay doi sau khi change courseInfo
void OfficialCourseToCSV(Course* courseCur);
// end: sort & ghi lai official file, doi ten
void endEnrollCourse(Course*& courseCur);
// list dslh -> tao class cho schoolyear
bool importListClass_dslh(const path& file_path, SchoolYear*& sy);
Course* findCourseByIDAndClass(string ID, string className, Semester sm);
// truoc do co ham kiem input
// sm from 0
bool createCourse(Course* newCourse, int sm, SchoolYear* yearCur);
// sm cur from 0
bool addCourseToSemester(SchoolYear*& yearCur, int smCur);
// file path la: Import/dshp.txt
bool importListCourse_dshp(const path& file_path, SchoolYear*& yearCur);
void outWrongCSVInput();
bool checkMark(string tmp, float& mark);
StuInCourse* findStuInCourse(string ID, string name, Course* courseCur);
// chuyen file tu import vao imformation
void passScoreboardFileFromImport(Course* courseCur);
// truong hop nhap sai, delete Class trong yearCur do, chi duoc dung ham beginning schoolyear
// tra ve false => ko co trong schoolyear, nhap sai ten
bool deleteClass(string className, SchoolYear* yearCur);
// cout << "you are change the course: courseCur->ID + courseCur->ClassName
bool updateStudentResult(Course* courseCur);
// chuyen tat ca cac file course cua hoc ky do thanh _dsdkhp
// pass vo "Information/" + sm->inSY->name + "/Semester " + to_string(sm->num + 1);

void beginStudentEnrollCourse(Semester* sm);
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

void viewStudentCourse(Student* stuHead, int sm, SchoolYear* yearCur);
// readStudentFromImportFile("Import", year hien tai)
// coi nhu dong bo giua 2 file danh sach va file diem
// co the dung de update file diem tu file
bool importScoreboardFile(const path& path, SchoolYear* yearCur, int sm);

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
