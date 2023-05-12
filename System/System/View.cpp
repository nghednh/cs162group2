#include <stdlib.h>
#include "Structure.h"
#include "login&menu.h"

void viewListClasses2(SchoolYear* yhead, SchoolYear* ynow)
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
	cout << "| Type in: \n";
	cout << "| 1. To view the year after this year \n";
	cout << "| 2. To view the year before this year \n| ";
	string m;
	getline(cin, m, '\n');
	if (m == "1") {
		if (ynow->yearNext) {
			viewListClasses2(yhead, ynow->yearNext);
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

void viewListClasses(SchoolYear* sYearHead)
{
	SchoolYear* sYearCur = sYearHead;
	while (sYearCur)
	{
		Class* classCur = sYearCur->classHead;
		while (classCur)
		{
			cout << classCur->name << endl;
			classCur = classCur->classNext;
		}
		sYearCur = sYearCur->yearNext;
	}
}

void viewListCourses(Course* courseHead)
{
	Course* courseCur = courseHead;
	while (courseCur)
	{
		cout << courseCur->name << endl;
		courseCur = courseCur->courseNext;
	}
}

void viewStudentProfile(Student* stuCur);

void viewStudentProfile(Student* stuCur)
{
	cout << "ID: " << stuCur->StuID << endl;
	cout << "First name: " << stuCur->firstName << endl;
	cout << "Last name: " << stuCur->lastName << endl;
	cout << "Gender: " << stuCur->gender << endl;
	cout << "Date of birth: " << stuCur->dateOfBirth.day << "/" << stuCur->dateOfBirth.month << "/" << stuCur->dateOfBirth.year << endl;
	cout << "Social ID: " << stuCur->socialID << endl;
	cout << "Curriculum: " << stuCur->curriculum << endl;
	//	cout << "Class name: " << stuCur->className << endl;
}

void viewListStudentsInCourse(Course* courseCur)	// lop sinh hoat
{
	Student* stuCur = courseCur->stuHead->stuInClass;
	while (stuCur)
	{
//		viewStudentProfile(stuCur);
		cout << stuCur->lastName << " " << stuCur->firstName << endl;
		stuCur = stuCur->stuNext;
	}
}

void viewCourseOfStudent(Student* stuCur, int smCur, SchoolYear* yearCur)
{
	cout << endl << "This is list of your course in semester " << smCur + 1 << "in School year " << yearCur->name << endl << endl;
	Course* courseCur = yearCur->sm[smCur].courseHead;
	while (courseCur)
	{
		if (courseCur->inSM->inSY == yearCur && courseCur->inSM->num == smCur)
		{
			cout << courseCur->name << "\t < " << courseCur->ID << "_" << courseCur->className << " > " << endl;
		}
		courseCur = courseCur->courseNext;
	}
	cout << endl;
}

void viewListOfStudentInClass(Class* classCur)
{
	if (classCur == NULL) return;
	Student* stuCur = classCur->stuHead;
	while (stuCur)
	{
//		viewStudentProfile(stuCur);
		cout << stuCur->lastName << " " << stuCur->firstName << endl;
		stuCur = stuCur->stuNext;
	}
}
// view list of course of that semester
void viewListOfStudentInClass2(Class* classCur)
{
	Student* stuCur = classCur->stuHead;
	cout << endl << "No" << string(6, ' ') << "Student ID" << string(6, ' ') << "First Name" << string(3, ' ') << "Last Name" << string(4, ' ') << "Gender" << string(4, ' ');
	cout << "Date of birth" << string(4, ' ') << "Social ID" << string(7, ' ') << "Curriculum" << string(10, ' ') << "Class" << endl;

	while (stuCur)
	{
		cout << stuCur->No << string(8 - (stuCur->No).length(), ' ');
		cout << stuCur->StuID << string(8, ' ');
		cout << stuCur->firstName << string(14 - stuCur->firstName.length(), ' ');
		cout << stuCur->lastName << string(11 - stuCur->lastName.length(), ' ');
		if (stuCur->gender == "Female") cout << "Female" << string(5, ' ');
		else cout << " Male " << string(5, ' ');
		cout << stuCur->dateOfBirth.day << '/' << stuCur->dateOfBirth.month << '/' << stuCur->dateOfBirth.year << string(7, ' ');
		cout << stuCur->socialID << string(3, ' ');
		cout << stuCur->curriculum << string(24 - stuCur->curriculum.length(), ' ');
		cout << stuCur->className << endl;

		stuCur = stuCur->stuNext;
	}
	cout << endl;
}

Class* findClassInAll(SchoolYear* yearHead, string className)
{
	while (yearHead)
	{
		Class* classCur = yearHead->classHead;
		while (classCur)
		{
			if (classCur->name == className)
				return classCur;
			classCur = classCur->classNext;
		}
		yearHead = yearHead->yearNext;
	}
	return nullptr;
}

void viewCourseOfSemester(SchoolYear* yearCur, int smCur)
{
	cout << endl << "This is list of course of semester " << smCur + 1 << "in School year " << yearCur->name << endl << endl;
	Course* courseCur = yearCur->sm[smCur].courseHead;
	while (courseCur)
	{
		cout << courseCur->name << "\t < " << courseCur->ID << "_" << courseCur->className << " > " << endl;
		courseCur = courseCur->courseNext;
	}
	cout << endl;
}
// view list of student in course
/*void viewListOfStudentInCourse(Course* courseCur)
{
	int i = 1;
	cout << "Course: " << courseCur->name;
	cout << endl << "ID: " << courseCur->ID;
	cout << endl << "Class name: " << courseCur->className;
	cout << endl << "Teacher name: " << courseCur->teacherName << endl;
	cout << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of birth\tSocial ID\tCurriculum\tClass";

	StuInCourse* stuCur = courseCur->stuHead;
	while (stuCur)
	{
		cout << endl << i++ << '\t';
		cout << stuCur->stuInClass->StuID << '\t';
		cout << stuCur->stuInClass->firstName << '\t' << '\t';
		cout << stuCur->stuInClass->lastName << '\t' << '\t';
		cout << stuCur->stuInClass->gender << '\t';
		cout << stuCur->stuInClass->dateOfBirth.day << '/' << stuCur->stuInClass->dateOfBirth.month << '/' << stuCur->stuInClass->dateOfBirth.year << '\t';
		cout << stuCur->stuInClass->socialID << '\t';
		cout << stuCur->stuInClass->curriculum << " ";
		cout << stuCur->stuInClass->className;

		stuCur = stuCur->stuNext;
	}
}*/
void viewListOfStudentInCourse(Course* courseCur)
{
	int i = 1;
	cout << endl << "Course:   " << courseCur->name;
	cout << endl << "ID:       " << courseCur->ID;
	cout << endl << "Class:    " << courseCur->className;
	cout << endl << "Lecturer: " << courseCur->teacherName << endl;
	cout << "No  " << "Student ID   " << "First Name   " << "Last Name   " << "Gender  " << "Date of birth   " << "Social ID       " << "Curriculum        " << "Class" << endl;

	StuInCourse* stuCur = courseCur->stuHead;
	while (stuCur)
	{
		cout << i++ << string(4 - to_string(i).length(), ' ');
		cout << stuCur->stuInClass->StuID << string(7, ' ');
		cout << stuCur->stuInClass->firstName << string(12 - stuCur->stuInClass->firstName.length(), ' ');
		cout << stuCur->stuInClass->lastName << string(10 - stuCur->stuInClass->lastName.length(), ' ');
		if (stuCur->stuInClass->gender == "Female") cout << "Female   ";
		else cout << " Male    ";
		cout << stuCur->stuInClass->dateOfBirth.day << '/' << stuCur->stuInClass->dateOfBirth.month << '/' << stuCur->stuInClass->dateOfBirth.year << string(6, ' ');
		cout << stuCur->stuInClass->socialID << string(2, ' ');
		cout << stuCur->stuInClass->curriculum << string(23 - stuCur->stuInClass->curriculum.length(), ' ');
		cout << stuCur->stuInClass->className << endl;

		stuCur = stuCur->stuNext;
	}
	cout << endl;
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
				if (classCur->stuHead != NULL && stuCur) // &&  abs(stoi(stuCur->StuID) - stoi(ID)) < 1000)	// Name class ~ ID (22CTT1 ~ 22..)
				{
					while (stuCur)// && stuCur->StuID)// < ID)		// stop if stuCur->StuID >= ID, Class sorted
						if (stuCur && stuCur->StuID == ID)
							return stuCur;
						else stuCur = stuCur->stuNext;
				}
				classCur = classCur->classNext;
			}
		}
		sYearCur = sYearCur->yearNext;
	}
	return NULL;
}
bool checkPassword(Student* stuCur, string pass)
{
	if (stuCur->password == pass)
		return true;
	else return false;
}

void changePassword(Student* stuCur, string newpass)
{
	stuCur->password = newpass;
}
