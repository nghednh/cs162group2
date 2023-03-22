void viewListclasses(SchoolYear* sYearHead)
{
	Node* sYearCur = sYearHead;
	while (sYearCur != NULL)
	{
		Node* classCur = sYearCur->classHead;
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
	Node* courseCur = courseHead;
	while (courseCur != NULL)
	{
		cout << courseCur->name << endl;
		courseCur = courseCur->courseNext;
	}
}

void viewListStudentsInCourse(Course* courseCur);	// lop sinh hoat
{
	Node* stuCur = courseCur->stuHead;
	while (stuCur != NULL)
	{
		cout << stuCur->lastName << " " << stuCur->firstName << endl;
		stuCur = stuCur->stuNext;
	}
}