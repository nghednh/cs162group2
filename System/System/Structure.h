#pragma once
#include <string>
using namespace std;
struct Date{
	int day;
	int month;
	int year;
};
struct Staff {
	string name;
	string username;
	string password;
	Staff* staffNext;
};
struct Class{
    string name;
    int numStu;
    Student* stuHead;
	Class* classNext;
};
struct SchoolYear{
    int year;
    Class* classHead;
    SchoolYear* sYearNext;
};
struct Semester{
	//Semester 1, 2 or 3?
    int num;
	//Start date and end date
    Date startDate, endDate;
    Course* courseHead;
};
struct Course {
	//detail of a course
	string ID;
	string name;
	string teacherName;
	int numberCredit;
	int maxStudent;
	Date d;

	//next node of course in a semester of a school year
	Course* courseNext = NULL;
};




