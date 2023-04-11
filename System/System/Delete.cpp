#include "Structure.h"
#include "Delete.h"
void deleteClass(Class*& classs) {
	Class *cur = classs;
	while (cur) {
		classs = classs->classNext;
		delete cur;
		cur = classs;
	}
}
void deleteSchoolYear(SchoolYear*& year) {
	SchoolYear* cur = year;
	while (cur) {
		year = year->yearNext;
		delete cur;
		cur = year;
	}
}
void deleteCourse(Course*& coursee) {
	Course* cur = coursee;
	while (cur) {
		coursee = coursee->courseNext;
		delete cur;
		cur = coursee;
	}
}
void deleteStudent(Student*& stu) {
	Student*& cur = stu;
	while (cur) {
		stu = stu->stuNext;
		delete cur;
		cur = stu;
	}
}