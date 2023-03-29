#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Date {
	string day;
	string month;
	string year;
};

struct Student {
	//detail
	string No;
	string StuID;
	string firstName;
	string lastName;
	string gender;
	Date dateOfBirth;
	string socialID;
	string username;
	string password;
	string className;

	//node
	Student* stuNext = NULL;

	//function still bug
	//void viewScoreBoard(SchoolYear* sy, Student* p, int numSm);
	//bool selectCourse(SchoolYear* sy, Student* stu, int numSm);
};

struct StuInCourse {
	//detail 
	float totalM;
	float finalM;
	float midM;
	float otherM;

	//node 
	Student* stuInClass = NULL; //point to the node Student in a Class 
	StuInCourse* stuNext = NULL; //next of linkedlist
};

struct Course {
	//detail
	string ID;
	string name;
	string className;
	string teacherName;
	int numCredit;
	int maxStudent = 50;
	int cntStudent;
	Date d;
	string day; //(MON / TUE / WED / THU / FRI / SAT)
	int session; //(S1(7:30), S2(09:30), S3(13:30), S4(15:30)

	//node
	StuInCourse* stuHead;
	Course* courseNext;
};

struct Class {
	//detail
	string name;
	int numStu;

	//node
	Student* stuHead;
	Class* classNext;
};

struct Semester {
	//detail
	Date start;
	Date end;
	bool state; //if 1 - accessible
	int num; //Semester 1 or 2 or 3?

	//node
	Course* courseHead;
};

struct SchoolYear {
	//detail
	string name; //ex: 2022-2023

	//node
	Class* classHead;
	SchoolYear* sYearNext;

	//array
	Semester sm[3];
};

struct Staff {
	//elements
	string name;
	string username;
	string password;
	Staff* staffNext;

	//functions
	void importStuFromCSV(Class* c);
	void createCourseFromCSV(SchoolYear* sy, int numSm);
	void exportListStuToCSV(Course* course);
	void importScoreboard(Course* course);
	void viewScoreboard(Course* course);
	void updateRes(Course* course);
};