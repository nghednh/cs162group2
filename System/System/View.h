#include "Structure.h"
void viewListClasses(SchoolYear* sYearHead);
void viewListCourses(Course* courseHead);
void viewListStudentsInCourse(Course* courseCur);
void viewListOfStudentInClass(Class* classCur);
Student* findStudentByID(string ID, SchoolYear* sYearHead);
bool checkPassword(Student* stuCur, string pass);
void changePassword(Student* stuCur, string newpass);