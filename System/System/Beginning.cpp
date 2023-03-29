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
