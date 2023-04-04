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
	string className;
	string password = dateOfBirth.day + dateOfBirth.month + dateOfBirth.year; //mac dinh
	string nganh;
	string lop;

	//node
	Student* stuNext = NULL;
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
	StuInCourse* stuHead = NULL;
	Course* courseNext = NULL;
};

struct Class {
	//detail
	string name;
	int numStu;

	//node
	Student* stuHead = NULL;
	Class* classNext = NULL;
};

struct Semester {
	//detail
	Date start;
	Date end;
	bool state = 0; //if 1 - accessible
	int num; //Semester 1 or 2 or 3?

	//node
	Course* courseHead = NULL;
};

struct SchoolYear {
	//detail
	string name; //ex: 2022-2023

	//node
	Class* classHead = NULL;
	SchoolYear* yearNext = NULL;

	//array
	Semester sm[3];
};

//May cai function nao lien quan den Student thi quang vao day
struct InfoStu {
	Student* stuInClass = NULL;
	InfoStu* InfoStuNext = NULL;

	//Main functions
	void viewScoreBoard(Course* course, int numSm); //24

	//Supplementary functions
	bool checkCourseName(Course* course, string s);
	void importStuToCourseCSV(SchoolYear* sy, string courseName, Student* stu);
	bool selectCourse(SchoolYear* sy, Student* stu, int numSm);
};

struct Staff {
	//elements
	string name;
	string ID; //username == ID
	string password;
	Staff* staffNext;

	//Main functions

	void exportCourseToCSV(Course* course); //19
	void importScoreboard(Course* course); //20
	void viewScoreboard(Course* course); //21
	void updateRes(Course* course); //22

	//Supplementary Functions
	void addStuFromDSDKHP(Course* course, Student* s);
	void createCourseFromCSV(SchoolYear* sy, int numSm);

	Class* findClass(SchoolYear*& sy, string nameClass);
	void addStuToClass(Class*& cl, Student*& stu);
	void createAllClassesFromCSV(SchoolYear*& sy, InfoStu*& info);
};