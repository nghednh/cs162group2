#pragma once
#include "Structure.h"

void chooseRole();
void login();
void viewProfile(Staff* staff);
void inputDate(Date& datee);
void inputYear(SchoolYear*& year);
void inputCourse(Course*& course);
void addClasstoSchoolYear();
void addClassToSchoolYear(Class* classs, SchoolYear* schoolyearr);
void addCourseToSemester(Course* coursee, Semester* semester);