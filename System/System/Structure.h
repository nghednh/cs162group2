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
	string curriculum;

	int accumCredits = 0;
	float accumScore = 0;

	//node
	Student* stuNext = NULL; //next of linkedlist
};

struct StuInCourse {
	//detail 
	float totalM;
	float finalM;
	float midM;
	float otherM;
	float GPA;

	//node 
	Student* stuInClass = NULL; //point to the node Student in a Class 
	StuInCourse* stuNext = NULL; //next of linkedlist
};

struct Class {
	//detail
	string name;
	int requiredCredits; //22TT1-165 tin chi de tot nghiep
	int numStu = 50;
	bool courseSes[6][4] = {}; //courses' sessions during days of week: empty session 0 and taken session 1

	//node
	Student* stuHead = NULL;
	Class* classNext = NULL;
};

struct Session{
	Class* cur_class = NULL;
	bool isEmpty = true;
};
struct Day{
	string name; //Mon - ... - Sat
	Session s[4];
};

struct Course {
	//detail
	string ID;
	string name;
	string className; //ex: 22TT, 22TT1
	string teacherName;
	int numCredit;
	int maxStudent = 50; //default 50
	int cntStudent;
	string date;
	int session;
	Day day[6]; //Mon - ... - Sat

	//node
	Class* classHead = NULL; //????
	StuInCourse* stuHead = NULL;
	Course* courseNext = NULL;
};

struct Semester {
	//detail
	Date start;
	Date end;
	bool state = 0; //if 1 - accessible
	int num;

	//node
	Course* courseHead = NULL;
};

struct SchoolYear {
	//detail
	string name; //ex: 2022-2023

	//node
	Class* classHead = NULL;
	Course* courseHead = NULL; 
	SchoolYear* yearNext = NULL;

	//array
	Semester sm[3];
};

//May cai function nao lien quan den Student thi quang vao day
struct InfoStu {
	Student* stuInClass = NULL;
	Class* infoClass = NULL;
	InfoStu* InfoStuNext = NULL;

	//Main functions
	void viewScoreBoard(SchoolYear* sy, int numSm); //24

	//Supplementary functions
	void viewCourses(Semester s); // View all the courses that the student participates in.
	bool checkCourseName(Course* course, string s);
	void importStuToCourseCSV(SchoolYear* sy, string courseName, Student* stu);
	bool selectCourse(SchoolYear* sy, Student* stu, int numSm);
};

struct Staff {
	//elements
	string ID; //username == ID
	string name;
	string password =  "10diemLy"; //mac dinh
	Staff* staffNext;

	//Main functions
	void exportCourseToCSV(Course* course); //19
	void importScoreboard(Course* course); //20
	void viewScoreboard(Course* course); //21
	void updateRes(Course* course); //22
	void viewScoreClass(SchoolYear* sy, int numSm, Class* cl); //24

	//Supplementary Functions
	void addStuFromDSDKHP(Course* course, Student* s);
	void createCourseFromCSV(SchoolYear* sy, int numSm);
	bool deleteACourse(Course*& courseHead, string courseID);
	bool addAStudentInCourse(Course* a, Student* newStu);
	bool removeAStudentFromCourse(Course* a, string ID);

	Class* findClass(SchoolYear*& sy, string nameClass);
	void addStuToClass(Class*& cl, Student*& stu);
	void createAllClassesFromCSV(SchoolYear*& sy, InfoStu*& info);
};
StuInCourse* checkStuInCourse(Course* c, Student* stu);