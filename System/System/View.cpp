#include <stdlib.h>
#include "login&menu.h"
#include "Structure.h"
#include "View.h"
void viewListClasses2(SchoolYear* yhead,SchoolYear* ynow)
{
	system("cls");
	UIlite();
	cout << "| List of classes in: " << ynow->name << endl;
	SchoolYear* sYearCur = ynow;
	while (sYearCur)
	{
		Class* classCur = sYearCur->classHead;
		while (classCur)
		{
			cout <<"|  " <<classCur->name << endl;
			classCur = classCur->classNext;
		}
		sYearCur = sYearCur->yearNext;
	}
	cout << "| Type in: \n";
	cout << "| 1. To view the year after this year \n";
	cout << "| 2. To view the year before this year \n| ";
	string m;
	getline(cin, m, '\n');
	if (m == "1") {
		if (ynow->yearNext) {
			viewListClasses2(yhead,ynow->yearNext);
		}
		else {
			cout << "| The year after this year doesn't exist!\n";
		}
	}
	if (m == "2") {
		
		if (yhead == ynow) {
			cout << "| The year before this year doesn't exist!\n";
		}
		else {
			SchoolYear* ycur = yhead;
			if (ycur->yearNext == ynow) {
				viewListClasses2(yhead, ycur);
			}
			while (ycur->yearNext != ynow) {
				ycur = ycur->yearNext;
				if (ycur->yearNext == ynow) {
					viewListClasses2(yhead, ycur);
				}
			}
		}
	}
	else {
		return;
	}
}
void viewListClasses1(SchoolYear* ynow)
{
	system("cls");
	UIlite();
	cout << "| List of classes in: " << ynow->name << endl;
	SchoolYear* sYearCur = ynow;
	while (sYearCur)
	{
		Class* classCur = sYearCur->classHead;
		while (classCur)
		{
			cout << "|  " << classCur->name << endl;
			classCur = classCur->classNext;
		}
		sYearCur = sYearCur->yearNext;
	}

}

void viewListCourses2(Course* chead, Course* cnow)
{
	system("cls");
	UIlite();
	cout << "| List of courses: " << endl;
	Course* courseCur = chead;
	while (courseCur)
	{
		cout <<"|  " << courseCur->name << endl;
		courseCur = courseCur->courseNext;
	}
	cout << "| Type in: \n";
	cout << "| 1. To view the course after this course \n";
	cout << "| 2. To view the course before this course \n| ";
	string m;
	getline(cin, m, '\n');
	if (m == "1") {
		if (cnow->courseNext) {
			viewListCourses2(chead, cnow->courseNext);
		}
		else {
			cout << "| The year after this year doesn't exist!\n";
		}
	}
	if (m == "2") {

		if (chead == cnow) {
			cout << "| The year before this year doesn't exist!\n";
		}
		else {
			Course* cur = chead;
			if (cur->courseNext == cnow) {
				viewListCourses2(chead, cur);
			}
			while (cur->courseNext != cnow) {
				cur = cur->courseNext;
				if (cur->courseNext == cnow) {
					viewListCourses2(chead, cur);
				}
			}
		}
	}
	else {
		return;
	}
}

void viewStudentProfile(Student* stuCur)
{
	system("cls");
	UIlite();
	cout << "|  ID: " << stuCur->StuID << endl;
	cout << "|  First name: " << stuCur->firstName << endl;
	cout << "|  Last name: " << stuCur->lastName << endl;
	cout << "|  Gender: " << stuCur->gender << endl;
	cout << "|  Date of birth: " << stuCur->dateOfBirth.day << "/" << stuCur->dateOfBirth.month << "/" << stuCur->dateOfBirth.year << endl;
	cout << "|  Social ID: " << stuCur->socialID << endl;
	cout << "|  Curriculum: " << stuCur->curriculum << endl;
	//	cout << "Class name: " << stuCur->className << endl;
}

void viewListStudentsInCourse(Course* courseCur)	// lop sinh hoat
{
	system("cls");
	UIlite();
	Student* stuCur = courseCur->stuHead->stuInClass;
	while (stuCur)
	{
		//		viewStudentProfile(stuCur);
		cout <<"|  " << stuCur->lastName << " " << stuCur->firstName << endl;
		stuCur = stuCur->stuNext;
	}
}

void viewListOfStudentInClass(Class* classCur)
{
	system("cls");
	UIlite();
	cout << "| List of student in class " << classCur->name << ": \n";
	if (classCur == NULL) return;
	Student* stuCur = classCur->stuHead;
	while (stuCur)
	{
		//		viewStudentProfile(stuCur);
		cout <<"|  " << stuCur->lastName << " " << stuCur->firstName << endl;
		stuCur = stuCur->stuNext;
	}
}

Student* findStudentByID_01(string ID, SchoolYear* sYearHead)
{
	int id = stoi(ID);
	SchoolYear* sYearCur = sYearHead;
	while (sYearCur)
	{
		if (sYearCur->name[2] == ID[0] && sYearCur->name[3] == ID[1])	// 2022-2023 ~ 2212...
		{
			Class* classCur = sYearCur->classHead;
			while (classCur)
			{
				Student* stuCur = classCur->stuHead;
				if (classCur->stuHead == NULL) classCur = classCur;
				else if (stuCur && abs(stoi(stuCur->StuID) - id) < 1000)	// Name class ~ ID (22CTT1 ~ 22..)
				{
					while (stoi(stuCur->StuID) < id)		// stop if stuCur->StuID >= ID, Class sorted
						stuCur = stuCur->stuNext;

					if (stuCur->StuID == ID)
					{
						return stuCur;
					}
				}
				classCur = classCur->classNext;
			}
		}
		sYearCur = sYearCur->yearNext;
	}
	return NULL;
}

Student* findStudentByID(string ID, SchoolYear* sYearHead)
{
	SchoolYear* sYearCur = sYearHead;
	while (sYearCur)
	{
		if (sYearCur->name[2] == ID[0] && sYearCur->name[3] == ID[1])	// 2022-2023 ~ 2212...
		{
			Class* classCur = sYearCur->classHead;
			while (classCur)
			{
				Student* stuCur = classCur->stuHead;
				if (classCur->stuHead != NULL && stuCur && abs(stoi(stuCur->StuID) - stoi(ID)) < 1000)	// Name class ~ ID (22CTT1 ~ 22..)
				{
					while (stuCur && stuCur->StuID < ID)		// stop if stuCur->StuID >= ID, Class sorted
						stuCur = stuCur->stuNext;

					if (stuCur && stuCur->StuID == ID)
						return stuCur;

				}
				classCur = classCur->classNext;
			}
		}
		sYearCur = sYearCur->yearNext;
	}
	return NULL;
}