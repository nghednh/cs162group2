#include "Structure.h"

//Supplementary function
void trimS(string& s) { //to trim a string
	s = s.substr(0, s.length() - 1);
}

//19: Export a list of students in a course to a CSV file 
void Staff::exportCourseToCSV(Course* course) {
	ofstream ft(course->ID + "_dssv.txt");

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
	ofstream ft(course->ID + "_mark.txt");

	ft << "No, Student ID, Student Full Name, Total Mark, Final Mark, Midterm Mark, Other Mark" << endl;

	StuInCourse* tmp = course->stuHead;
	while (tmp != NULL) {
		ft << tmp->stuInClass->No << ", " << tmp->stuInClass->StuID << ", " << tmp->stuInClass->firstName << " " << tmp->stuInClass->lastName << ", " << ", " << ", " << ", " << endl;
		tmp = tmp->stuNext;
	}
}

//21: View the scoreboard of a course
void Staff::viewScoreboard(Course* course) {
	StuInCourse* s = course->stuHead;
	while (s) {
		cout << s->stuInClass->StuID << " " << s->stuInClass->firstName << " " << s->stuInClass->lastName << " " << s->totalM << " " << s->finalM << " " << s->midM << " " << s->otherM << endl;
		s = s->stuNext;
	}
}

//22: Update a student's result.
void Staff::updateRes(Course* course) {
	ifstream fin(course->ID + "_mark.txt"); //Read file from "20"

	string s;
	float m;

	for (int i = 0; i < 14; i++) { //To ignore the title line
		fin >> s;
	}

	while (!fin.eof()) {
		fin >> s; //No
		fin >> s; //ID
		trimS(s); //Trim ','
		StuInCourse* tmp = course->stuHead;
		while (tmp->stuInClass->StuID != s) {
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
void InfoStu::viewScoreBoard(Course* course, int numSm) {
	cout << "Scoreboard of " << stuInClass->firstName << " " << stuInClass->lastName << ": " << endl;
	while (course) {
		StuInCourse* tmp = course->stuHead;
		while (tmp && tmp->stuInClass != stuInClass) {
			tmp = tmp->stuNext;
		}
		if (tmp != NULL) cout << course->className << " " << tmp->totalM << " " << tmp->finalM << " " << tmp->midM << " " << tmp->otherM;
		course = course->courseNext;
	}
}

//Student can select Courses that are available for the semester
bool InfoStu::checkCourseName(Course* course, string s) { //check if the course ID entered is appropriate or not
	while (course != NULL) {
		if (s == course->ID) return 1;
		course = course->courseNext;

	}
	return 0;
}

void InfoStu::importStuToCourseCSV(SchoolYear* sy, string courseName, Student* stu) { //student register any course, his/her name will be exported to the CSV file
	ofstream ft(courseName + "_dsdkhp.txt", ofstream::app); //danh sach dang ky hoc phan
	ft << sy->name << " " << stu->className << " " << stu->StuID << endl;
}

bool InfoStu::selectCourse(SchoolYear* sy, Student* stu, int numSm) {
	if (numSm < 1 || numSm >3 || sy->sm[numSm - 1].state == 0) return 0;

	//Print out all courses for the student to choose
	Course* tmp = sy->sm[numSm - 1].courseHead;
	cout << "These are all courses available for Semester " << numSm << " " << sy->name << ": " << endl;

	while (tmp) {
		cout << "Name: " << tmp->name << endl << "ID: " << endl << tmp->ID << endl << "Credits: " << tmp->numCredit << endl << "Teacher: " << tmp->teacherName << endl;
		tmp = tmp->courseNext;
	}

	//Student chooses courses
	int cnt = 0; //max courses chosen are 4
	cout << endl << "Please select course(s)!" << endl;
	while (cnt < 5) {
		string s;
		cin >> s;
		if (checkCourseName(sy->sm[numSm - 1].courseHead, s)) {
			importStuToCourseCSV(sy, s, stu); // student id will be export to CSV file
			cnt++;
		}
		else cout << "Incorrect ID" << endl;
	}
	return 1;
}

//From DSDKHP (CSV) -> Add Student to a Course
void Staff::addStuFromDSDKHP(Course* course, Student* s) {
	StuInCourse* tmp = new StuInCourse();
	tmp->stuInClass = s;
	tmp->stuNext = course->stuHead;
	course->stuHead = tmp;
}

void Staff::createCourseFromCSV(SchoolYear* sy, int numSm) {
	Course* tmp = sy->sm[numSm - 1].courseHead;

	if (tmp == NULL) tmp = new Course();

	while (tmp != NULL) {
		ifstream fin(tmp->ID + "_dsdkhp.txt");
		string s;
		while (!fin.eof()) {
			fin >> s;
			SchoolYear* tmp1 = sy;
			while (tmp1->name != s) {
				tmp1 = tmp1->yearNext;
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
			addStuFromDSDKHP(tmp, tmp3);
			break;
		}
		break;
		tmp = tmp->courseNext;
	}
}

//Dang nhap
void username(Staff* staff, InfoStu* info, Staff*& user1, InfoStu*& user2) {
	string s1;
	string s2;

	cout << "Username: ";
	cin >> s1;
	cout << "Password: ";
	cin >> s2;

	//ID Student starts with number, ID Staff starts with char
	//ID Student
	if ('0' <= s1[0] && s1[0] <= '9') {
		while (info->stuInClass->StuID != s1) {
			info = info->InfoStuNext;
		}
		if (info == NULL || s2 != info->stuInClass->password) {
			cout << "Wrong username or password. Please enter again!";
			username(staff, info, user1, user2);
			return;
		}
		else user2 = info;
		return;
	}

	//ID Staff
	while (staff->ID != s1) {
		staff = staff->staffNext;
	}
	if (staff == NULL || s2 != staff->password) {
		cout << "Wrong username or password. Please enter again!";
		username(staff, info, user1, user2);
		return;
	}
	else user1 = staff;
	return;
}

//From CSV of All Students of The School -> Create Class
Class* Staff::findClass(SchoolYear*& sy, string nameClass) {
	Class* tmp = sy->classHead;

	if (sy->classHead == NULL) {
		sy->classHead = new Class();
		sy->classHead->name = nameClass;
		return sy->classHead;
	}

	while (tmp->name != nameClass) {
		tmp = tmp->classNext;
	}

	if (tmp == NULL) {
		tmp = new Class();
		tmp->name = nameClass;
	}
	return tmp;
}

void Staff::addStuToClass(Class*& cl, Student*& stu) {
	if (cl->stuHead == NULL) {
		cl->stuHead = stu;
		return;
	}

	Student* tmp = cl->stuHead;
	while (tmp) {
		tmp = tmp->stuNext;
	}
	tmp = stu;
}

void Staff::createAllClassesFromCSV(SchoolYear*& sy, InfoStu*& info) {
	ifstream fin("DSSV_Khoatuyen" + sy->name + ".txt");
	if (info == NULL) info = new InfoStu();

	//to ignore the title line
	int cnt = 0;
	string s;
	while (cnt < 15) {
		fin >> s;
		cnt++;
	}

	while (!fin.eof()) {
		Student* tmp = new Student();

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
		trimS(tmp->socialID);
		fin >> tmp->nganh;
		trimS(tmp->nganh);
		fin >> (tmp->lop);

		Class* tmpCl = findClass(sy, tmp->lop);
		addStuToClass(tmpCl, tmp);
		info->stuInClass = tmp;
		info = info->InfoStuNext;
	}
}

//From CSV of Staffs -> Create Staff
void createAllStaffsFromCSV(Staff*& staff) {
	fstream fin("Staff.txt");

	if (staff == NULL) staff = new Staff();
	Staff* tmp = staff;

	//ignore the title
	string s;
	for (int i = 0; i < 2; i++) {
		fin >> s;
	}

	while (!fin.eof()) {
		fin >> tmp->ID;
		trimS(tmp->ID);
		fin >> tmp->name;
		trimS(tmp->name);
		staff = staff->staffNext;
	}
}