#pragma once
#include <string>
#include <iostream>

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

struct Student {
	int No;
	int StuID;
	string firstName;
	string lastName;
	string gender;
	Date dateOfBirth;
	string socialID;
	string username;
	string password;
	Student* stuNext = NULL;
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
	Semester sm[3];
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
	int numCredit;
	int maxStudent = 50;
	int numStudent;
	Date d;
	Student* stuHead;

	//next node of course in a semester of a school year
	Course* courseNext;
};



