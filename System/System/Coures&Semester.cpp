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
        cur = cur->sYearNext;
    }
    return cur;
}
//Xac dinh semester so may va thuoc nam nao
void addSemesterToSy(SchoolYear* sHead, Semester s, string nameSy){
    SchoolYear* tmp = findSchoolYear(sHead, nameSy);
    tmp->sm[s.num-1] = s;
}

//Them 1 hc sinh vao course
bool addAStudentInCourse(Course* a, Student* newStu){
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
bool removeAStudentFromCourse(Course* a, string ID){
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

