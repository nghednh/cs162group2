#include "Structure.h"

void inputADate(Date d);
void createSemester(Semester s);
SchoolYear* findSchoolYear(SchoolYear* sHead, int a);
void addSemesterToSy(SchoolYear* sHead, Semester s, int year);
bool addAStudentInCourse(Course* a, Student* newStu);
void inputACourse(Course* a);
void addCourse(Semester s, Course* a);
bool removeAStudentFromCourse(Course* a, int ID);
float final_GPA(Semester sm, Student* s);