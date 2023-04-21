#include "Structure.h"

//Supplementary function
void trimS(string& s) { //to trim a string
	s = s.substr(0, s.length() - 1);
}

//19: Export a list of students in a course to a CSV file 
void Staff::exportCourseToCSV(Course* course) {
	ofstream ft(course->ID + "_dssv.txt");
	if (!ft) {
		cout << "Cannot open file named: " << course->ID + "_dssv.txt";
		return;
	}

	ft << "Course: " << course->name << endl;
	ft << "Credits: " << course->numCredit << endl;
	ft << "Lecturer: " << course->teacherName << endl << endl;
	ft << "No	Student ID	First name	Last name	Gender	Date of Birth	Social ID" << endl;

	StuInCourse* tmp = course->stuHead;
	while (tmp) {
		ft << tmp->stuInClass->No << "	" << tmp->stuInClass->StuID << "	" << tmp->stuInClass->firstName << "	" << tmp->stuInClass->lastName << "	" << tmp->stuInClass->gender << "	";
		ft << tmp->stuInClass->dateOfBirth.day << " " << tmp->stuInClass->dateOfBirth.month << " " << tmp->stuInClass->dateOfBirth.year << "	" << tmp->stuInClass->socialID << endl;
		tmp = tmp->stuNext;
	}
}

//20: Import the scoreboard of a course - create CSV file for teachers
void Staff::importScoreboard(Course* course) {
	ofstream ft(course->ID + "_mark.txt");

	ft << "No	Student ID	Student Full Name	Total	Final	Midterm	Other" << endl;

	StuInCourse* tmp = course->stuHead;
	while (tmp != NULL) {
		ft << tmp->stuInClass->No << "	" << tmp->stuInClass->StuID << "	" << tmp->stuInClass->firstName << " " << tmp->stuInClass->lastName << "	" << "	" << "	" << "	" << endl;
		tmp = tmp->stuNext;
	}
}

//21: View the scoreboard of a course
void Staff::viewScoreboard(Course* course) {
	cout << endl << string(85, '-') << endl;
	StuInCourse* s = course->stuHead;
	cout << "Course: " << course->name << endl;
	cout << "Credit: " << course->numCredit << endl;
	cout << "Lecturer: " << course->teacherName << endl;
	cout << "Student ID      First name      Last name      Total      Final      Mid      Other" << endl;
	while (s) {
		cout << s->stuInClass->StuID << "	" << s->stuInClass->firstName << string(16 - s->stuInClass->firstName.length(), ' ') << s->stuInClass->lastName << string(15 - s->stuInClass->lastName.length(), ' ');
		cout << s->totalM << string(10, ' ') << s->finalM << string(18 - to_string(s->finalM).length(), ' ') << s->midM << string(16 - to_string(s->midM).length(), ' ') << s->otherM << endl;
		s = s->stuNext;
	}
	cout << string(85, '-');
	cout << endl;
}

//22: Update a student's result.
void Staff::updateRes(Course* course) {
	ifstream fin(course->ID + "_mark.txt"); //Read file from "20"

	string s;
	float m;

	for (int i = 0; i < 10; i++) { //To ignore the title line
		fin >> s;
	}

	int cnt = 0;
	while (cnt < 24) {
		fin >> s; //No
		fin >> s; //ID

		StuInCourse* tmp = course->stuHead;
		while (tmp->stuInClass->StuID != s) {
			tmp = tmp->stuNext;
		}

		fin >> s; //First name
		fin >> s; //Last name;
		fin >> m;
		tmp->totalM = m;
		fin >> m;
		tmp->finalM = m;
		fin >> m;
		tmp->midM = m;
		fin >> m;
		tmp->otherM = m;
		if (tmp->totalM > 5) {
			tmp->stuInClass->accumCredits += course->numCredit;
			tmp->stuInClass->accumScore += tmp->finalM;
		}
		cnt++;
	}
}

//23: View the scoreboard of a class, including final marks of all courses in the semester, GPA in this semester, and the overall GPA.
StuInCourse* checkStuInCourse(Course* c, Student* stu) {
	StuInCourse* curStu = c->stuHead;
	while (curStu) {
		if (curStu->stuInClass->StuID == stu->StuID) return curStu;
		curStu = curStu->stuNext;
	}
	return NULL;
}

void Staff::viewScoreClass(SchoolYear* sy, int numSm, Class* cl) {
	Student* tmpS = cl->stuHead;
	float GPAsm = 0;
	int credits = 0;

	cout << "BANG DIEM TONG HOP HK" << numSm << endl;
	cout << "Curriculum: " << tmpS->curriculum << endl;
	cout << "Class: " << tmpS->className << endl << endl;

	while (tmpS) {
		cout << tmpS->No << ". " << tmpS->StuID << " - " << tmpS->firstName << " " << tmpS->lastName << endl;
		cout << "Accumulated credits: " << tmpS->accumCredits << "/" << cl->requiredCredits << endl;
		cout << "Accumulated GPA: " << tmpS->accumScore / tmpS->accumCredits << "/4.0" << endl << endl;

		Course* tmpC = sy->sm[numSm - 1].courseHead;
		while (tmpC) {
			StuInCourse* tmpSIC = checkStuInCourse(tmpC, tmpS);
			if (tmpSIC != NULL) {
				cout << tmpC->name << ": " << tmpSIC->finalM << endl;
				GPAsm += tmpSIC->totalM * tmpC->numCredit;
				credits += tmpC->numCredit;
			}
			tmpC = tmpC->courseNext;
		}
		cout << "GPA" << " HK" << numSm << ": " << GPAsm / float(credits) << endl << string(30, '-') << endl << endl;
		GPAsm = 0;
		credits = 0;
		tmpS = tmpS->stuNext;
	}
}

//24: View his/her scoreboard
void InfoStu::viewScoreBoard(SchoolYear* sy, int numSm) {
	cout << string(50, '-') << "THONG TIN TOM TAT" << string(50, '-') << endl << endl;
	cout << string(18, ' ') << "Thong tin chung" << string(45, ' ') << "Nhom hoc phan" << endl;

	cout << " Ma SV" << string(30, ' ') << stuInClass->StuID;
	cout << string(28 - stuInClass->StuID.length(), ' ') << "BBCS" << string(28, ' ') << "58" << endl;

	cout << " Ho ten SV" << string(26, ' ') << stuInClass->firstName << ' ' << stuInClass->lastName;
	cout << string(28 - (stuInClass->firstName + ' ' + stuInClass->lastName).length(), ' ') << "BBNCS" << string(27, ' ') << "26" << endl;

	cout << " Tong TC tich luy" << string(19, ' ') << stuInClass->accumCredits;
	cout << string(28 - to_string(stuInClass->accumCredits).length(), ' ') << "Math-Physics" << string(20, ' ') << "28" << endl;

	cout << " Diem TB tich luy" << string(19, ' ') << stuInClass->accumScore / stuInClass->accumCredits;
	cout << string(28 - to_string(stuInClass->accumScore).length(), ' ') << "TCCS" << string(28, ' ') << "36" << endl;

	cout << " Du dieu kien tot nghiep" << string(12, ' ') << "NA";
	cout << string(26, ' ') << "TN" << string(30, ' ') << "10" << endl << endl;

	cout << string(45, '-') << "KET QUA CHI TIET TUNG HOC PHAN" << string(45, '-') << endl << endl;

	cout << "    Hoc Ky    |" << "   Ma MH   |" << string(17, ' ') << "Ten MH" << string(15, ' ') << "| So TC |" << "  Lop  |" << " GK |" << " Khac |" << " CK |" << " 10 |" << "  ABC  " << endl;

	Course* course = sy->sm[numSm - 1].courseHead;
	while (course) {
		StuInCourse* tmp = course->stuHead;
		while (tmp && tmp->stuInClass != stuInClass) {
			tmp = tmp->stuNext;
		}
		if (tmp != NULL) {
			cout << " HK" << numSm << " " << sy->name << "|";
			cout << "   " << course->ID << string(8 - course->ID.length(), ' ') << "| " << course->name << string(37 - course->name.length(), ' ') << "|   ";
			cout << course->numCredit << "   | " << stuInClass->className << string(6 - stuInClass->className.length(), ' ') << "| " << tmp->midM << "| " << tmp->otherM << "    " << tmp->finalM << "   " << tmp->totalM << endl;
		}
		course = course->courseNext;
	}
	cout << endl;
}

//Student can select Courses that are available for the semester
bool InfoStu::checkCourseName(Course*& course, string s) { //check if the course ID entered is appropriate or not
	while (course != NULL) {
		if (s == course->ID) return 1;
		course = course->courseNext;
	}
	return 0;
}

void InfoStu::importStuToCourseCSV(string courseName) { //student register any course, his/her name will be exported to the CSV file
	ofstream ft(courseName + "_dsdkhp.txt", ofstream::app); //danh sach dang ky hoc phan
	ft << sy->name << " " << stuInClass->className << " " << stuInClass->StuID << endl;
}

bool InfoStu::addAndSortByID(Course*& c, Student*& stu) {
	if (c->stuHead == NULL) {
		c->stuHead = new StuInCourse();
		c->stuHead->stuInClass = stu;
		return 1;
	}

	StuInCourse* sic = c->stuHead;
	StuInCourse* tmp = new StuInCourse();
	tmp->stuInClass = stu;
	while (sic->stuNext) {
		if (sic->stuNext->stuInClass->StuID == stu->StuID) return 0;
		if (sic->stuNext->stuInClass->StuID > stu->StuID) {
			tmp->stuNext = sic->stuNext;
			sic->stuNext = tmp;
			return 1;
		}
		sic = sic->stuNext;
	}
	if (sic->stuInClass->StuID != stu->StuID) {
		sic->stuNext = tmp;
		return 1;
	}
	return 0;
}

void InfoStu::printListCourse(Course* c, int cre, int numCourse) {
	cout << stuInClass->firstName << " " << stuInClass->lastName << " - " << stuInClass->StuID << string(30, ' ');
	cout << "Number of credits: " << cre << "/" << "24" << endl;
	cout << string(stuInClass->firstName.length() + stuInClass->lastName.length() + stuInClass->StuID.length() + 34, ' ');
	cout << "Number of courses: " << numCourse << "/" << "6" << endl << endl;

	cout << "ID" << string(9, ' ') << "Course" << string(30, ' ') << "Credits" << string(6, ' ') << "Lecturer" << string(8, ' ') << "Day    " << "Session    " << "Registered    " << "State" << endl;
	while (c->courseNext) {
		cout << c->ID << string(11 - c->ID.length(), ' ') << c->name << string(36 - c->name.length(), ' ') << "   " << c->numCredit << "      " << c->teacherName << string(19 - c->teacherName.length(), ' ') << c->day << string(8, ' ');
		cout << c->session << string(10, ' ') << c->cntStudent << "/" << c->maxStudent << " " << string(6, ' ');
		StuInCourse* sic = c->stuHead;
		while (sic != NULL) {
			if (sic->stuInClass->StuID == stuInClass->StuID) {
				cout << "Da chon";
				break;
			}
			sic = sic->stuNext;
		}
		cout << endl;
		c = c->courseNext;
	}
}

void InfoStu::selectCourse() {
	ifstream fin("dshp.txt");
	if (!fin) {
		cout << "Not time for registering course!" << endl;
		return;
	}

	//Print out all courses for the student to choose
	string s;
	fin >> s;
	cout << s << " "; //HK2
	string t = s;
	fin >> s;
	cout << s << endl; //2022-2023

	SchoolYear* tmpsy = sy;
	while (tmpsy->name != s) {
		tmpsy = tmpsy->yearNext;
	}

	Course* c = tmpsy->sm[stoi(s.substr(2, 1)) - 1].courseHead;
	Course* tmpC = c;

	int cre = 0;
	int numCourse = 0;
	printListCourse(c, cre, numCourse);
	while (cre < 16 && numCourse < 4) {
		cout << "Register: ";
		cin >> s;
		if (s == "0") return;
		if (checkCourseName(tmpC, s)) {
			if (tmpC->maxStudent == tmpC->cntStudent) cout << "No more slot!" << endl;
			else {
				if (addAndSortByID(tmpC, stuInClass)) {
					cre += tmpC->numCredit;
					numCourse++;
					tmpC->cntStudent++;
					importStuToCourseCSV(s);
					system("cls");
					printListCourse(c, cre, numCourse);
				}
				else cout << "Hoc phan " << tmpC->ID << " da duoc dang ky! " << endl;
			}
		}
		else cout << "Invalid ID!" << endl;
		tmpC = c;
	}
	fin.close();
}

//From DSHP -> create all Course nodes
void Staff::createAllCourse(SchoolYear* sy) {
	ifstream fin("dshp.txt");
	if (!fin) {
		cout << "Cannot open file" << endl;
		return;
	}

	string s;
	fin >> s;
	string hk = s.substr(2, 1);

	fin >> s;
	while (sy->name != s) sy = sy->yearNext;

	for (int i = 0; i < 7; i++) {
		fin >> s;
	}

	Course*& course = sy->sm[stoi(hk) - 1].courseHead;
	if (course == NULL) course = new Course();
	Course* tmp = course;
	int cnt = 0;

	while (!fin.eof()) {
		//ID
		fin >> tmp->ID;
		if (tmp->ID.length() < 2) return;

		//Name
		fin >> tmp->name;
		fin >> s;
		while (s[0] > '9') {
			tmp->name += ' ' + s;
			fin >> s;
		}

		//Credits
		tmp->numCredit = stoi(s);

		//Teacher name
		fin >> tmp->teacherName;
		fin >> s;
		while (s[0] > '9') {
			if (s[0] == 'S' && s[1] < '9') break;
			tmp->teacherName += ' ' + s;
			fin >> s;
		}

		//session
		tmp->day = s;

		//day
		fin >> s;
		tmp->session = stoi(s);

		//max
		fin >> s;
		tmp->maxStudent = stoi(s);

		tmp->courseNext = new Course();
		tmp = tmp->courseNext;
	}
	tmp = NULL;
	fin.close();
}

//From DSDKHP -> Add Student to a Course
void Staff::addStuFromDSDKHP(Course* course, Student* s) {
	StuInCourse* tmp = new StuInCourse();
	tmp->stuInClass = s;
	tmp->stuNext = course->stuHead;
	course->stuHead = tmp;
}

void Staff::createCourseFromCSV(SchoolYear* sy, int numSm) {
	Course*& course = sy->sm[numSm - 1].courseHead;

	if (course == NULL) course = new Course();
	Course* tmp = course;

	while (tmp) {
		ifstream fin(tmp->ID + "_dsdkhp.txt");
		string s;
		int cnt = 0;
		while (cnt < 24) {
			//find stuInClass
			//findYear
			fin >> s;
			SchoolYear* tmp1 = sy;
			while (tmp1->name != s) {
				tmp1 = tmp1->yearNext;
			}

			//findClass
			fin >> s;
			Class* tmp2 = sy->classHead;
			while (tmp2->name != s) {
				tmp2 = tmp2->classNext;
			}

			//findStudent
			fin >> s;
			Student* tmp3 = tmp2->stuHead;
			while (tmp3->StuID != s) {
				tmp3 = tmp3->stuNext;
			}
			addStuFromDSDKHP(tmp, tmp3);
			cnt++;

		}
		tmp = tmp->courseNext;
	}
}

//Dang nhap
void username(Staff* staff, InfoStu* info, Staff* user1, InfoStu* user2) {
	string s1;
	string s2;
	Staff* tmps = staff;
	InfoStu* tmpi = info;
	cout << "Username: ";
	cin >> s1;
	cout << "Password: ";
	cin >> s2;

	//ID Student starts with number, ID Staff starts with char
	//ID Student
	if ('0' <= s1[0] && s1[0] <= '9') {
		if (info == NULL) {
			system("cls");
			cout << "Not time for student!" << endl;
			return;
		}
		while (info->InfoStuNext->InfoStuNext && info->stuInClass->StuID != s1) {
			cout << info->stuInClass->StuID << endl;
			info = info->InfoStuNext;
		}
		if (info == NULL || s2 != info->stuInClass->password) {
			//system("cls");
			cout << "Wrong username or password. Please enter again!" << endl;
			username(tmps, tmpi, user1, user2);
			return;
		}
		system("cls");
		cout << "You are using system for Student" << endl;
		user2 = info;
		return;
	}

	//ID Staff
	while (staff && staff->ID != s1) {
		staff = staff->staffNext;
	}
	if (staff == NULL || s2 != staff->password) {
		system("cls");
		cout << "Wrong username or password. Please enter again!" << endl;
		username(tmps, tmpi, user1, user2);
		return;
	}
	system("cls");
	cout << "You are using system for Staff" << endl;
	user1 = staff;
	return;
}

//From CSV of All Students of The School -> Create Class
Class* Staff::findClass(SchoolYear*& sy, string nameClass) {
	if (sy->classHead == NULL) {
		sy->classHead = new Class();
		sy->classHead->name = nameClass;
		return sy->classHead;
	}

	Class* tmp = sy->classHead;
	while (tmp->name != nameClass && tmp->classNext) {
		tmp = tmp->classNext;
	}
	if (tmp->name == nameClass) return tmp;
	tmp->classNext = new Class();
	tmp->classNext->name = nameClass;
	return tmp->classNext;
}

void Staff::addStuToClass(Class*& cl, Student*& stu) {
	if (cl->stuHead == NULL) {
		cl->stuHead = stu;
		return;
	}

	Student* tmp = cl->stuHead;
	while (tmp->stuNext) {
		tmp = tmp->stuNext;
	}
	tmp->stuNext = stu;
}

void Staff::createAllClassesFromCSV(SchoolYear*& sy, string syname, InfoStu*& info) {
	ifstream fin("DSSV_Khoatuyen" + syname + ".txt");
	if (!fin) {
		cout << "Cannot open file named: " << "DSSV_Khoatuyen" + syname + ".txt";
		return;
	}

	//check and create new SchoolYear
	SchoolYear* tmpSy = NULL;

	if (sy == NULL) {
		sy = new SchoolYear();
		sy->name = syname;
		tmpSy = sy;
	}

	else if (sy != NULL) {
		tmpSy = sy;
		while (tmpSy->yearNext && tmpSy->name != syname) {
			tmpSy = tmpSy->yearNext;
		}
		if (tmpSy->name != syname) {
			tmpSy->yearNext = new SchoolYear();
			tmpSy = tmpSy->yearNext;
			tmpSy->name = syname;
		}
	}

	//check InfoStu
	InfoStu* tmpIn4 = NULL;
	if (info != NULL) {
		tmpIn4 = info;
		while (info != NULL) {
			if (info->InfoStuNext == NULL) break;
			info = info->InfoStuNext;
		}
	}
	else {
		info = new InfoStu();
		tmpIn4 = info;
	}

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
		fin >> tmp->StuID;
		fin >> tmp->firstName;
		fin >> tmp->lastName;
		fin >> tmp->gender;
		fin >> s;
		tmp->dateOfBirth.day = s.substr(0, 2);
		tmp->dateOfBirth.month = s.substr(3, 2);
		tmp->dateOfBirth.year = s.substr(6, 4);
		fin >> tmp->socialID;
		fin >> tmp->curriculum;
		fin >> tmp->className;
		Class* tmpCl = findClass(tmpSy, tmp->className);
		addStuToClass(tmpCl, tmp);

		info->stuInClass = tmp;
		info->InfoStuNext = new InfoStu();
		info->infoClass = tmpCl;
		info->sy = sy;
		info = info->InfoStuNext;
	}
	info = NULL;
	info = tmpIn4;
	fin.close();
}

//From CSV of Staff -> Create Staff
void createAllStaffsFromCSV(Staff*& staff) {
	fstream fin("Staff.txt");

	if (!fin) {
		cout << "Cannot open file named " << "Staff.txt" << endl;
		return;
	}

	if (staff == NULL) staff = new Staff();
	Staff* tmp = staff;

	//ignore the title
	string s;
	for (int i = 0; i < 2; i++) {
		fin >> s;
	}

	while (!fin.eof()) {
		fin >> tmp->ID;
		fin >> tmp->name;
		fin >> s;
		tmp->name = tmp->name + ' ' + s;
		tmp->staffNext = new Staff();
		tmp = tmp->staffNext;
	}
	tmp = NULL;
	fin.close();
}

int main() {
	//create headnode of InfoStu, Staff, SchoolYear
	InfoStu* info = NULL;
	Staff* staff = NULL;
	SchoolYear* sy = NULL;

	//create all Staff, Class, Student from CSV
	createAllStaffsFromCSV(staff);
	staff->createAllClassesFromCSV(sy, "2022-2023", info);
	staff->createAllClassesFromCSV(sy, "2021-2022", info);
	staff->createAllClassesFromCSV(sy, "2019-2020", info);

	//username 
	Staff* user1 = NULL;
	InfoStu* user2 = NULL;
	//username(staff, info, user1, user2);

	//staff function
	staff->createAllCourse(sy);
	//info->selectCourse();

	//delete 
	while (sy) {
		SchoolYear* tmps = sy;
		Class* tmpc = sy->classHead;
		/*while (tmpc) {
			cout << tmpc->name << endl;
			tmpc = tmpc->classNext;
		}*/
		sy = sy->yearNext;
		delete tmps;
	}
	while (info) {
		//cout << info->stuInClass->lastName << endl;
		InfoStu* tmpi = info;
		info = info->InfoStuNext;
		delete tmpi;
	}
	while (staff) {
		Staff* tmps = staff;
		staff = staff->staffNext;
		delete (tmps);
	}
}