#include "structure.h"

//SIPPLEMENTARY FUNCTIONS
//to trim a string
void trimS(string& s) { 
	s = s.substr(0, s.length() - 1);
}

//check if the course ID entered is appropriate or not
bool trueOrFalse(Course* course, string s) { 
	while (course) {
		if (s == course->ID) return 1;
		course = course->courseNext;
	}
	return 0;
}

//student register any course, his/her name will be exported to the CSV file
void importStuToCourseCSV(SchoolYear* sy, string name, Student* stu) { 
	ofstream ft(name + "_dsdkhp.txt", ofstream::app); //danh sach dang ky hoc phan
	ft << sy->name << " " << stu->stuClass->name << " " << stu->StuID << endl;
}

//Add Student to a Course
void addStuToCourse(Course* course, Student* s) { 
	StuInCourse* tmp = new StuInCourse();
	tmp->stuInClass = s;
	tmp->stuNext = course->stuHead;
	course->stuHead = tmp;
}

//MAIN FUNCTIONS
//19: Export a list of students in a course to a CSV file
void Staff::exportListStuToCSV(Course* course) {
	ofstream ft(course->ID + ".txt");

	ft << "Course: " << course->name << endl;
	ft << "Teacher: " << course->teacherName << endl;
	ft << "No, Student ID, First name, Last name, Gender, Date of Birth, Social ID" << endl;

	StuInCourse* tmp = course->stuHead;
	while (tmp) {
		ft << tmp->stuInClass->No << ", " << tmp->stuInClass->StuID << ", " << tmp->stuInClass->firstName << ", " << tmp->stuInClass->lastName << ", " << tmp->stuInClass->gender << ", ";
		ft << tmp->stuInClass->dateOfBirth.day << "/" << tmp->stuInClass->dateOfBirth.month << "/" << tmp->stuInClass->dateOfBirth.year << ", " << tmp->stuInClass->socialID << endl;
		tmp = tmp->stuNext;
	}
}

//20: Import the scoreboard of a course - create CSV file for teachers
void Staff::importScoreboard(Course* course) {
	ofstream ft(course->ID + "mark.txt");

	ft << "Course: " << course->name << endl;
	ft << "Teacher: " << course->teacherName << endl;
	ft << "No, Student ID, Student Full Name, Total Mark, Final Mark, Midterm Mark, Other Mark" << endl;

	StuInCourse* tmp = course->stuHead;
	while (tmp) {
		ft << tmp->stuInClass->No << ", " << tmp->stuInClass->StuID << ", " << tmp->stuInClass->firstName << " " << tmp->stuInClass->lastName << ", " << ", " << ", " << ", " << endl;
		tmp = tmp->stuNext;
	}
}

//21: View the scoreboard of a course
void Staff::viewScoreboard(StuInCourse* s) {
	while (s) {
		cout << s->stuInClass->StuID << " " << s->stuInClass->firstName << " " << s->stuInClass->lastName << " " << s->totalM << " " << s->finalM << " " << s->midM << " " << s->otherM << endl;
		s = s->stuNext;
	}
}

//22: Update a student's result.
void Staff::updateRes(Course* course) {
	ifstream fin(course->ID + "mark.txt"); //Read file from 20

	int cnt = 0;
	string s;
	float m;

	while (cnt < 14) { //To ignore the title line
		fin >> s;
		cnt++;
	}

	while (!fin.eof()) {
		fin >> s; //No
		fin >> s; //ID
		trimS(s); //Trim ','
		StuInCourse* tmp = course->stuHead;
		while (tmp->stuInClass->socialID != s) {
			tmp = tmp->stuNext;
		}
		fin >> s; //First name
		fin >> s; //Last name
		fin >> m;
		tmp->totalM = m;
		fin >> s;
		fin >> m;
		tmp->finalM = m;
		fin >> s; //','
		fin >> m;
		tmp->midM = m;
		fin >> s; //','
		fin >> m;
		tmp->otherM = m;
	}
}

//24: View his/her scoreboard
void Student::viewScoreBoard(SchoolYear* sy, Student* s, int numSm) {
	Course* tmp = sy->sm[numSm].courseHead;
	cout << "Scoreboard of " << s->firstName << " " << s->lastName << ": " << endl;
	while (tmp) {
		StuInCourse* tmp1 = tmp->stuHead;
		while (tmp1 && tmp1->stuInClass != s) {
			tmp1 = tmp1->stuNext;
		}
		if (tmp1 != NULL) cout << tmp->name << " " << tmp1->totalM << " " << tmp1->finalM << " " << tmp1->midM << " " << tmp1->otherM;
		tmp = tmp->courseNext;
	}
}

//From DSSV -> Add Student 
void importStuFromCSV(Student*& p) {
	ifstream fin("demo.txt");

	if (p == NULL) p = new Student();
	Student* tmp = p;

	int cnt = 0;
	string s;
	while (cnt < 13) { //to ignore the title line
		fin >> s;
		cnt++;
	}

	while (!fin.eof()) {
		if (tmp->stuNext == NULL) {
			Student* node = new Student();
			tmp->stuNext = node;
			tmp = node;
		}
		fin >> tmp->No;
		trimS(tmp->No);
		fin >> tmp->StuID;
		trimS(tmp->StuID);
		fin >> tmp->firstName;
		trimS(tmp->firstName);
		fin >> tmp->lastName;
		trimS(tmp->lastName);
		fin >> tmp->gender;
		trimS(tmp->gender);
		fin >> tmp->dateOfBirth.day;
		fin >> tmp->dateOfBirth.month;
		fin >> tmp->dateOfBirth.year;
		trimS(tmp->dateOfBirth.year);
		fin >> tmp->socialID;
	}
}

//Student can select Courses that are available for the semester
bool Student::selectCourse(SchoolYear* sy, Student* stu, int numSm) {
	if (numSm < 1 || numSm >3 || sy->sm[numSm].state == 0) return 0;

	//Print out all courses for the student to choose
	Course* tmp = sy->sm[numSm].courseHead;
	cout << "These are all courses available for Semester " << numSm << " " << sy->name << ": " << endl;

	while (tmp) {
		cout << tmp->name << " " << tmp->ID << " " << tmp->numCredit << " " << tmp->teacherName << endl;
		tmp = tmp->courseNext;
	}

	//Student chooses courses
	int cnt = 0; //max courses chosen are 4
	cout << "Please select course(s)!" << endl;
	while (cnt < 5) {
		string s;
		cin >> s;
		if (trueOrFalse(sy->sm[numSm].courseHead, s)) {
			importStuToCourseCSV(sy, s, stu); // student id will be export to CSV file
			cnt++;
		}
		else cout << "Incorrect ID";
	}
	return 1;
}

//From DSDKHP -> Add Student to a Course
void createCourseFromCSV(SchoolYear* sy, int numSm) {
	Course* tmp = sy->sm[numSm].courseHead;

	while (tmp) {
		ifstream fin(tmp->ID + "_dsdkhp.txt");
		string s;
		while (!fin.eof()) {
			fin >> s;
			SchoolYear* tmp1 = sy;
			while (tmp1->name != s) {
				tmp1 = tmp1->sYearNext;
			}

			fin >> s;
			Class* tmp2 = sy->classHead;
			while (tmp2->name != s) {
				tmp2 = tmp2->classNext;
			}

			fin >> s;
			Student* tmp3 = tmp2->stuHead;
			while (tmp3->StuID != s) {
				tmp3 = tmp3->stuNext;
			}

			addStuToCourse(tmp, tmp3);
			tmp = tmp->courseNext;
		}
	}
}