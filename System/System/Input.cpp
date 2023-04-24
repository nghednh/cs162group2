﻿#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include "Structure.h"
#include "View.h"

namespace fs = std::filesystem;
using namespace fs;

void readListClass(const path& file_path, SchoolYear* &yearCur) 
{
    Class* classCur = yearCur->classHead;

    for (const auto& entry : directory_iterator(file_path)) {
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
        string tmp = entry.path().filename().stem().string();
        classCur->name = tmp;
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
        }
        in.close();
    }  
}

Student* findStuInClass(string syTmp, string classTmp, string IDTmp, SchoolYear* &yearHead)
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

void createCoursesFromList(SchoolYear* &sy, const path& file_path);

void readListCourse(const path& file_path, SchoolYear*& yearCur, SchoolYear* &yearHead, int i)
{
    Course* courseCur = yearCur->sm[i].courseHead;

    for (const auto& entry : directory_iterator(file_path)) {
        string tmp = entry.path().filename().stem().string();

        if (tmp == "dshp")
        {
            createCoursesFromList(yearCur, entry.path());
        }
        else if (tmp.size() > 5 && tmp.substr(tmp.size() - 5, 5) != "_mark" && tmp.substr(tmp.size() - 5, 5) != "_dssv")
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
            int i;
            
            for (i = 0; i < tmp.size() && tmp[i] != '_'; i++)
                ID += tmp[i];
            for (i += 1; i < tmp.size() && tmp[i] != '_'; i++)
                className += tmp[i];

            getline(in, courseCur->name, '\n');
            getline(in, courseCur->teacherName, '\n');

            courseCur->ID = ID;
            courseCur->className = className;
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


void createCoursesFromList(SchoolYear* &sy, const path& file_path) {
   
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

        tmp->courseNext = NULL;
        
        // tao file
        path create_file = "Information/" + sy->name + "/Semester " + hk + '/' + tmp->ID + '_' + tmp->className + ".txt";
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

void sortStuInCourse(Course* &courseCur)
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
            viewListOfStudentInClass(classCur);
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

int main() {
    SchoolYear* yearHead = NULL;
    SchoolYear* yearCur = yearHead;
    readInformation("Information", yearCur, yearHead);

    Course* courseHead = yearHead->yearNext->yearNext->yearNext->sm[1].courseHead;

    /*
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
    */
    
    while (courseHead)
    {
        cout << courseHead->name << endl;
        courseHead = courseHead->courseNext;
    }

    deleteAll(yearHead);
    return 0;
}

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
