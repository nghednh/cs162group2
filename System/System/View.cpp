#include <stdlib.h>
#include "login&menu.h"
#include "Structure.h"



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