#include "Structure.h"

void viewListclasses(SchoolYear* sYearHead)
{
	SchoolYear* sYearCur = sYearHead;
	while (sYearCur != NULL)
	{
		Class* classCur = sYearCur->classHead;
		while (classCur != NULL)
		{
			cout << classCur->name << endl;
			classCur = classCur->classNext;
		}
		sYearCur = sYearCur->sYearNext;
	}
}

void viewListCourses(Course* courseHead)
{
	Course* courseCur = courseHead;
	while (courseCur != NULL)
	{
		cout << courseCur->name << endl;
		courseCur = courseCur->courseNext;
	}
}

void viewListStudentsInCourse(Course* courseCur)	// lop sinh hoat
{
	Student* stuCur = courseCur->stuHead;
	while (stuCur != NULL)
	{
		cout << stuCur->lastName << " " << stuCur->firstName << endl;
		stuCur = stuCur->stuNext;
	}
}