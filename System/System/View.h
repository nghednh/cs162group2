#include "Structure.h"
void viewListClasses(SchoolYear* sYearHead);
void viewListCourses(Course* courseHead);
void viewListStudentsInCourse(Course* courseCur);
void viewListOfStudentInClass(Class* classCur);
Student* findStudentByID(string ID, SchoolYear* sYearHead);
bool checkPassword(Student* stuCur, string pass);
void changePassword(Student* stuCur, string newpass);
void viewStudentProfile(Student* stuCur);

// view list of course of that semester
void viewCourseOfSemester(SchoolYear* yearCur, int smCur);

void viewListOfStudentInCourse(Course* courseCur);

void viewListOfStudentInClass2(Class* classCur);