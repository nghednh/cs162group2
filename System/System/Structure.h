#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <optional>

using namespace std;

struct Date;
struct Class;
struct SchoolYear;
struct StuInCourse;
struct Student;
struct Semester;
struct Staff;
struct Semester;

struct Date {
	string day = "";
	string month = "";
	string year = "";
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
	string password = "123"; //mac dinh
	string curriculum;

	int accumCredits = 0;
	float accumScore = 0;

	//node
	Class* inClass = NULL;
	Student* stuNext = NULL; //next of linkedlist
	StuInCourse* pStuCourseHead = NULL;
};

struct Course;

struct StuInCourse {
	//detail 
	float totalM;
	float finalM;
	float midM;
	float otherM;
	float GPA;
	string courseID;
	Course* infoCourse = NULL;

	//node 
	Student* stuInClass = NULL; //point to the node Student in a Class 
	StuInCourse* stuNext = NULL; //next of linkedlist
	StuInCourse* pStuCourseNext = NULL; // that student in another Course
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
	SchoolYear* inSY = NULL;
};


struct Session {
	Class* cur_class = NULL;
	bool isEmpty = true;
};

struct Course {
	//detail
	string ID;
	string name;
	string className; //ex: 22TT, 22TT1
	string teacherName;
	int numCredit;
	int maxStudent; //default 50
	int cntStudent = 0;
	int session;
	string day;

	//node
	StuInCourse* stuHead = NULL;
	Course* courseNext = NULL;
	Semester* inSM = NULL;
};

struct Semester {
	//detail
	Date start;
	Date end;
	string syName;
//	string syName;
	bool state = 0; //if 1 - accessible
	int num;

	//node
	Course* courseHead = NULL;
	SchoolYear* inSY = NULL;
};

struct SchoolYear {
	//detail
	string name; //ex: 2022-2023

	//node
	Class* classHead = NULL;
	//	Course* courseHead = NULL; 
	SchoolYear* yearNext = NULL;

	//array
	Semester sm[3];
};

//May cai function nao lien quan den Student thi quang vao day
struct InfoStu {
	Student* stuInClass = NULL;
	Class* infoClass = NULL;
	InfoStu* InfoStuNext = NULL;
	SchoolYear* sy = NULL; //*

	//Main functions
	void viewScoreBoard(SchoolYear* sy, int numSm); //24

	//Supplementary functions
	void viewCourses(Semester s); // View all the courses that the student participates in.
	bool checkCourseName(Course*& course, string s);
	bool checkIfExist(Course*& c);
	void importStuToCourseCSV(string courseName);
	void countCredit(Course* c, int& cre, int& numCourse);
	bool addAndSortByID(Course*& c);
	void printListCourse(Course* c, int cre, int numCourse);
	void selectCourse();
};

struct Staff {
	//elements
	string ID; //username == ID
	string name;
	string password = "10diemLy"; //mac dinh
	Staff* staffNext = NULL;

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
	void createAllClassesFromCSV(SchoolYear*& sy, string syname, InfoStu*& info);
	void createAllCourse(SchoolYear* sy);
};

void inputADate(Date& d);
void createSemester(Semester& s);
SchoolYear* findSchoolYear(SchoolYear* sHead, int a);
void addSemesterToSy(SchoolYear* sHead, Semester s, int year);
bool addAStudentInCourse(Course* a, Student* newStu);
void inputACourse(Course* a);
void addCourse(Semester s, Course* a);
bool removeAStudentFromCourse(Course* a, int ID);

//Cap nhat lop tham gia vao khoa hoc (which day, which session)
void classAttendToCourse(Course* a, Class* c);

//Thay doi thong tin cua khoa hoc
void viewOptions();
void viewCourseInfo(Course* course);
void updateCourseInfo(Course* course);

//Ham phu - Additional functions
//In ra nhung tiet trong va nhung tiet da co lop
void viewAvailableSession(Class* c);
//Tinh GPA cuoi ki
float final_GPA(Semester sm, Student* s);

//Chuyen doi ngay trong tuan duoi dang so hoac chu
int numPresentAsDay(string day);
string stringPresentAsDay(int n);

//string_type -> float_type
float convertFloat(string s);
void addAndSortByID(StuInCourse*& stuHead, StuInCourse* curStu);
StuInCourse* checkStuInCourse(Course* c, Student* stu);
//compare the input ID with a course's ID
bool checkID(string courseID, string ID);
//Find and return a course by ID
Course* findCourseByID(Semester sm, string inputID);