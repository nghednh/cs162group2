#include "Structure.h"
#include <iostream>
#include <string.h>
#include "Beginning.h"

using namespace std;

void inputDate(Date& datee) {
	cin >> datee.day >> datee.month >> datee.year;
}
void inputYear(SchoolYear*& year) {
    SchoolYear* cur = year = nullptr;
    int n;
    cin >> n;
    cin.get();
    while (n--) {
        if (!year) {
            year = new SchoolYear;
            cur = year;
        }
        else {
            cur->yearNext = new SchoolYear;
            cur = cur->yearNext;
        }
        getline(cin, cur->name);
        int numberClass;
        cin >> numberClass;
        while (numberClass--) {
            Class* tem = new Class;
            cin >> tem->name;
            tem->classNext = cur->classHead;
            cur->classHead = tem;
        }
    }
} // h�m n�y nh?p s? n�m r?i nh?p v�o t?ng n�m + c�c l?p trong n�m
void inputCourse(Course*& course) {
    Course* cur = course;
    int n;
    cin >> n;
    while (n--) {
        if (!course) {
            course = new Course;
            cur = course;
        }
        else {
            cur->courseNext = new Course;
            cur = cur->courseNext;
        }
        cin >> cur->ID;
        cin.get();
        getline(cin, cur->name);
        cin >> cur->numCredit >> cur->maxStudent >> cur->cntStudent;
        cin.get();
        getline(cin, cur->teacherName);
    }
} // h�m n�y nh?p s? course r?i nh?p v�o c�c course
void addCourseToSemester(Course* coursee, Semester* semesterr) {
    if (semesterr->courseHead == NULL) {
        semesterr->courseHead = coursee;
    }
    else {
        Course* cur = coursee;
        cur->courseNext = semesterr->courseHead;
        semesterr->courseHead = cur;
    }
} // h�m n�y th�m course v�o 1 semester
void addClassToSchoolYear(Class* classs, SchoolYear* schoolyearr) {
    if (!schoolyearr->classHead) {
        schoolyearr->classHead = classs;
    }
    else {
        Class* cur = classs;
        cur->classNext = schoolyearr->classHead;
        schoolyearr->classHead = cur;
    }
} // h�m n�y th�m class v�o 1 year