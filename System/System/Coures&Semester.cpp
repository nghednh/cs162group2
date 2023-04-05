#pragma once
#include <string>
#include <iostream>
#include "Structure.h"

using namespace std;

void inputADate(Date d){
    cin >> d.day >> d.month >> d.year;
}
void createSemester(Semester s){
    cin >> s.num;
    inputADate(s.start);
    inputADate(s.end);
}
//Tim nam hc theo so nam
SchoolYear* findSchoolYear(SchoolYear* sHead, string a){
    SchoolYear* cur = sHead;
    while(cur){
        if(cur->name == a)
            break;
        cur = cur->yearNext;
    }
    return cur;
}
//Xac dinh semester so may va thuoc nam nao
void addSemesterToSy(SchoolYear* sHead, Semester s, string nameSy){
    SchoolYear* tmp = findSchoolYear(sHead, nameSy);
    tmp->sm[s.num-1] = s;
}

//Them 1 hc sinh vao course
bool Staff::addAStudentInCourse(Course* a, Student* newStu){
    if(a->cntStudent == a->maxStudent)
        return false;
    Student* cur = a->stuHead->stuInClass;
    while(cur)
        cur = cur->stuNext;
    cur->stuNext = newStu;
    cur = cur->stuNext;
    cur = nullptr;
    a->cntStudent += 1;
    return true;
}
void inputACourse(Course* a){
    cin >> a->ID;
    cin >> a->name;
    cin >> a->teacherName;
    cin >> a->numCredit;
    cin >> a->day;
    cin >> a->session;
}
void addCourse(Semester s, Course* a){
    inputACourse(a);
    Course* courseCur = s.courseHead;
    while(courseCur->courseNext){
        courseCur = courseCur->courseNext;
    }
    courseCur->courseNext = a;
    courseCur = a;
    courseCur->courseNext = nullptr;
}
bool Staff::removeAStudentFromCourse(Course* a, string ID){
    Student* cur = a->stuHead->stuInClass;
    while(cur->stuNext){
        if(cur->stuNext->StuID == ID){
            Student* tmp = cur->stuNext;
            cur->stuNext = cur->stuNext->stuNext;
            delete tmp;
            a->cntStudent -= 1;
            return true; //Thong bao xoa thanh cong.
        }
        cur = cur->stuNext;
    }
    return false; //Neu k co ID do thi bao hc sinh k tham gia khoa hoc.
}

bool Staff::deleteACourse(Course*& courseHead, string courseID){
    Course* cur = courseHead;
    while(cur->courseNext){
        if(cur->courseNext->ID == courseID)
            break;
        cur = cur->courseNext;
    }
    if(cur->courseNext == NULL)
        return false;
    else{
        Course* tmp = cur;
        cur->courseNext = cur->courseNext->courseNext;
        delete tmp;
    }
    return true;
}

//Student upgrade 14
bool checkStuInCourse(Course* c, Student* stu){
    StuInCourse* curStu = c->stuHead;
    while(curStu){
        if(curStu->stuInClass->StuID == stu->StuID)
            return true;
        curStu = curStu->stuNext;
    }
    return false;
}
void InfoStu::viewCourses(Semester s){
    Course* cur = s.courseHead;
    while(cur){
        if(checkStuInCourse(cur, stuInClass)){
            cout << "Your courses: ";
            cout << cur->name << '[' << cur->ID << ']';
            cout << endl;
        }
        cur = cur->courseNext;
    }
}
void viewOptions(){
    cout << "UPDATE COURSE'S INFORMATION." <<  endl;
    cout << endl; 
    cout << "Options: " << endl;
    cout << "1. Update ID." << endl;
    cout << "2. Update course name." << endl;
    cout << "3. Update class name." << endl;
    cout << "4. Update teacher's name." << endl;
    cout << "5. Update number of credits." << endl;
    cout << "6. Update maximum students." << endl;
    cout << "7. Update date of course taking place." << endl;
    cout << "8. Update session of course." << endl; 
    cout << "0. Stop updating and save" << endl;
} 
//Not done yet
void updateIDCourseL(Course* c){

}
void updateCourseInfo(Course* course){
    viewOptions();
    int check = 10;
    while(check != 0){
        cin >> check;
        switch (check){
            case 1: 
        }
    }
    
}