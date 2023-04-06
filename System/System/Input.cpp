#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "Structure.h"
#include "View.h"

namespace fs = std::filesystem;
using namespace std;
using namespace fs;

struct User {
    string username;
    string password;
};

void processCSVFile(const path& file_path, Class* &classCur) {
    ifstream in;
    in.open(file_path);
    if (!in.is_open()) { 
        cout << "Cannot open file" << endl;
        return;
    }

    string header, line;              // xoa dong 1
    getline(in, header);
    
    if(!in.eof())
    {
        classCur->stuHead = new Student;
        Student* stuCur = classCur->stuHead;

        while (getline(in, line)) {
            if (stuCur->StuID != "")
            {
                stuCur->stuNext = new Student;
                stuCur = stuCur->stuNext;
            }
            stringstream ss(line);
            getline(ss, stuCur->StuID, ',');
            getline(ss, stuCur->firstName, ',');
            getline(ss, stuCur->lastName, ',');
            getline(ss, stuCur->gender, ',');
            getline(ss, stuCur->dateOfBirth.day, ',');
            getline(ss, stuCur->dateOfBirth.month, ',');
            getline(ss, stuCur->dateOfBirth.year, ',');
            getline(ss, stuCur->socialID, ',');
        }
    }
    in.close();
}

void read_files(const path& path, SchoolYear* &yearCur) {

    yearCur->classHead = new Class;
    Class* classCur = yearCur->classHead;

    for (const auto& entry : directory_iterator(path)) {
        if (entry.is_directory()) {                             // if is folder
            if (yearCur->name != "")
            {
                yearCur->yearNext = new SchoolYear;
                yearCur = yearCur->yearNext;
            }
            yearCur->name = entry.path().filename().string();
            read_files(entry.path(), yearCur);  // recursion
        }
        else {
            if (classCur->name != "")
            {
                classCur->classNext = new Class;
                classCur = classCur->classNext;
            }
            classCur->name = entry.path().filename().stem().string();     // filename (-.txt)
            processCSVFile(entry.path(), classCur);
        }
    }
}

int main() {
    SchoolYear* yearHead = NULL;
    yearHead = new SchoolYear;
    SchoolYear* yearCur = yearHead;

    path root_path("Student Information");
    read_files(root_path, yearCur);      // input all files in "Data"; 
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

  /*  path root_path = "Student Information";
    read_info(root_path, yearCur);      // input all files in "Data"; 
    
    if (findStudentByID("19127026", yearHead) != NULL)
        cout << findStudentByID("19127026", yearHead)->lastName << endl;
    else cout << "Could not found" << endl;*/
  

    return 0;
}

/*
 directory_iterator(path) : Hàm này nhận vào đường dẫn của một thư mục và trả về một iterator đại diện cho tất cả các tệp tin và thư mục trong thư mục đó.

entry.is_directory() : Hàm này kiểm tra xem một entry có phải là một thư mục hay không.

getline(file, header) và getline(ss, username, ',') : Hàm này đọc một dòng văn bản trong tệp tin.

read_files(path) : Hàm này nhận vào đường dẫn của một thư mục và đọc tất cả các tệp tin và thư mục trong đó bằng cách đệ quy gọi chính nó với đường dẫn của các thư mục con.

path root_path("Data") : Hàm này tạo một đối tượng path từ đường dẫn "Data".
*/