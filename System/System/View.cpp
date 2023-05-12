#include <stdlib.h>
#include "Structure.h"

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
	cout << "No\tStudent ID\tFirst Name\tLast Name\tGender\tDate of birth\tSocial ID\tCurriculum\tClass";
	while (stuCur)
	{
		cout << endl;
		cout << stuCur->No << '\t';
		cout << stuCur->StuID << '\t';
		cout << stuCur->firstName << '\t';
		cout << stuCur->lastName << '\t';
		cout << stuCur->gender << '\t';
		cout << stuCur->dateOfBirth.day << '/' << stuCur->dateOfBirth.month << '/' << stuCur->dateOfBirth.year << '\t';
		cout << stuCur->socialID << '\t';
		cout << stuCur->curriculum << '\t';
		cout << stuCur->className;

		stuCur = stuCur->stuNext;
	}
}

void viewCourseOfSemester(SchoolYear* yearCur, int smCur)
{
	cout << "This is list of course of semester " << smCur + 1 << "in School year " << yearCur->name << endl;
	Course* courseCur = yearCur->sm[smCur].courseHead;
	while (courseCur)
	{
		cout << courseCur->name << " < " << courseCur->ID << "_" << courseCur->className << " > " << endl;
		courseCur = courseCur->courseNext;
	}
}
// view list of student in course
void viewListOfStudentInCourse(Course* courseCur)
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
				if (classCur->stuHead != NULL && stuCur &&  abs(stoi(stuCur->StuID) - stoi(ID)) < 1000)	// Name class ~ ID (22CTT1 ~ 22..)
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
