#include "Structure.h"

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
}
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
} 
void addCourseToSemester(Course* coursee, Semester* semesterr) {
    if (semesterr->courseHead == NULL) {
        semesterr->courseHead = coursee;
    }
    else {
        Course* cur = coursee;
        cur->courseNext = semesterr->courseHead;
        semesterr->courseHead = cur;
    }
} 
void addClassToSchoolYear(Class* classs, SchoolYear* schoolyearr) {
    if (!schoolyearr->classHead) {
        schoolyearr->classHead = classs;
    }
    else {
        Class* cur = classs;
        cur->classNext = schoolyearr->classHead;
        schoolyearr->classHead = cur;
    }
}
int biggerDate(Date left, Date right) {
    int lef = stoi(left.year) * 10000 + stoi(left.month) * 100 + stoi(left.day);
    int rig = stoi(right.year) * 10000 + stoi(right.month) * 100 + stoi(left.day);
    if (lef > rig) return 1;
    else if (lef == rig) return 0;
    else return -1;
}