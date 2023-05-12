#include <stdlib.h>
#include "login&menu.h"
#include "Structure.h"

void viewListClasses(SchoolYear* sYearHead)
{
	system("cls");
	UIlite;
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
	system("cls");
	UIlite;
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
	system("cls");
	UIlite();
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
	system("cls");
	UIlite();
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
	system("cls");
	UIlite;
	if (classCur == NULL) return;
	Student* stuCur = classCur->stuHead;
	while (stuCur)
	{
		//		viewStudentProfile(stuCur);
		cout << stuCur->lastName << " " << stuCur->firstName << endl;
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