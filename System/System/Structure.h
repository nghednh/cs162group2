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
	string No;
	string StuID;
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
	string name; //ex: 2022-2023
    Class* classHead;
    SchoolYear* sYearNext;
	Semester sm[3];
};

struct Semester{
	Date start;
	Date end;
	bool state; //if 1 - accessible
	Course* courseHead;
};

struct Course {
	string ID;
	string name;
	string className;
	string teacherName;
	int numCredit;
	int maxStudent = 50;
	int numStudent;
	string day; //(MON / TUE / WED / THU / FRI / SAT)
	string session; //(S1(7:30), S2(09:30), S3(13:30), S4(15:30)
	Student* stuHead;
	Course* courseNext;
};



