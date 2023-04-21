#include "Structure.h"

void inputADate(Date d);
void createSemester(Semester s);
SchoolYear* findSchoolYear(SchoolYear* sHead, int a);
void addSemesterToSy(SchoolYear* sHead, Semester s, int year);
bool addAStudentInCourse(Course* a, Student* newStu);
void inputACourse(Course* a);
void addCourse(Semester& s, Course* a);
bool removeAStudentFromCourse(Course* a, int ID);

//Cap nhat lop tham gia vao khoa hoc (which day, which session)
void classAttendToCourse(Course* a, Class* c);

//Thay doi thong tin cua khoa hoc
void viewOptions();
void viewCourseInfo(Course* course);
void updateCourseInfo(Course* course);

//Ham phu - Additional functions
//In ra nhung tiet trong va nhung tiet da co lop
void viewAvailableSession(Class* c);
//Tinh GPA cuoi ki
float final_GPA(Semester sm, Student* s);

//Chuyen doi ngay trong tuan duoi dang so hoac chu
int numPresentAsDay(string day);
string stringPresentAsDay(int n);

//string_type -> float_type
float convertFloat(string s);
void addAndSortByID(StuInCourse*& stuHead, StuInCourse* curStu);
StuInCourse* checkStuInCourse(Course* c, Student* stu);