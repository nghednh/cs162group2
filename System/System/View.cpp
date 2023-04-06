#include <stdlib.h>
#include <dirent.h>
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

void viewListStudentsInCourse(Course* courseCur)	// lop sinh hoat
{
	Student* stuCur = courseCur->stuHead->stuInClass;
	while (stuCur)
	{
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
		cout << stuCur->lastName << " " << stuCur->firstName << endl;
		stuCur = stuCur->stuNext;
	}
}

Student* findStudentByID(string ID, SchoolYear* sYearHead)
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
				else if (abs(stoi(stuCur->StuID) - id) < 1000)	// Name class ~ ID (22CTT1 ~ 22..)
				{
	//				while (stoi(stuCur->StuID) < id)		// stop if stuCur->StuID >= ID, Class sorted
	//					stuCur = stuCur->stuNext;

					while(stuCur)
					{
						if (stuCur->StuID == ID)
							return stuCur;
						stuCur = stuCur->stuNext;
					}
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

void viewStudentProfile(Student* stuCur)
{
	cout << "ID: " << stuCur->StuID << endl;
	cout << "First name: " << stuCur->firstName << endl;
	cout << "Last name: " << stuCur->lastName << endl;
	cout << "Gender: " << stuCur->gender << endl;
	cout << "Date of birth: " << stuCur->dateOfBirth.day << "/" << stuCur->dateOfBirth.month << "/" << stuCur->dateOfBirth.year << endl;
	cout << "Social ID: " << stuCur->socialID << endl;
//	cout << "Class name: " << stuCur->className << endl;
}