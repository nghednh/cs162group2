#include "Structure.h"
void viewListClasses(SchoolYear* sYearHead);
void viewListCourses(Course* courseHead);
void viewListStudentsInCourse(Course* courseCur);
void viewListOfStudentInClass(Class* classCur);
Student* findStudentByID(string ID, SchoolYear* sYearHead);
bool checkPassword(Student* stuCur, string pass);
void changePassword(Student* stuCur, string newpass);
void viewStudentProfile(Student* stuCur);
void viewListClasses2(SchoolYear* yhead, SchoolYear* ynow);

// view list of course of that semester
void viewCourseOfSemester(SchoolYear* yearCur, int smCur);

void viewListOfStudentInCourse(Course* courseCur);
Class* findClassInAll(SchoolYear* yearHead, string className);
void viewListOfStudentInClass2(Class* classCur);
void viewCourseOfStudent(Student* stuCur, int smCur, SchoolYear* yearCur);

/*
dshp -(create)-> CS162_22CTT1
->staff : dkhp -> staff+ student : add + remove CS162_22CTT1 => CS162_22CTT1_dsdkhp
staff: add+ remove
	*/