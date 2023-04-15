#include "Structure.h"
#include "Course&Semester.h"

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
/*StuInCourse* checkStuInCourse(Course* c, Student* stu) {
	StuInCourse* curStu = c->stuHead;
	while (curStu) {
		if (curStu->stuInClass->StuID == stu->StuID) return curStu;
		curStu = curStu->stuNext;
	}
	return NULL;
}
*/
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
		if (tmpC == NULL) cout << "vl" << endl;
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
//function hoi muon xem diem o dau
void InfoStu::viewScoreBoard(SchoolYear* sy, int numSm) {
	cout << string(50, '*') << "THONG TIN TOM TAT" << string(50, '*') << endl << endl;
	cout << string(20, ' ') << "Thong tin chung" << string(20, ' ') << endl;
	cout << " Ma SV" << string(30, ' ') << stuInClass->StuID << endl;
	cout << " Ho ten SV" << string(26, ' ') << stuInClass->firstName << ' ' << stuInClass->lastName << endl;
	cout << " Tong TC tich luy" << string(19, ' ') << stuInClass->accumCredits << endl;
	cout << " Diem TB tich luy" << string(19, ' ') << stuInClass->accumScore / stuInClass->accumScore << endl;
	cout << " Du dieu kien tot nghiep" << string(12, ' ') << "NA" << endl;

	cout << string(45, '*') << "KET QUA CHI TIET TUNG HOC PHAN" << string(45, '*') << endl << endl;
	cout << "     Hoc Ky     " << "  Ma MH  " << string(15, ' ') << "Ten MH" << string(15, ' ') << " So TC " << "  Lop  " << " GK " << " Khac " << " CK " << " 10 " << endl;
	Course* course = sy->sm[numSm - 1].courseHead;
	if (course == NULL) cout << "True";
	while (course) {
		StuInCourse* tmp = course->stuHead;
		while (tmp && tmp->stuInClass != stuInClass) {
			tmp = tmp->stuNext;
		}
		if (tmp != NULL) {
			cout << "  HK" << numSm << " " << sy->name << "  ";
			cout << course->ID << string(4, ' ') << course->name << string(36 - course->name.length(), ' ');
			cout << "   " << course->numCredit << "   " << " " << stuInClass->className << " " << tmp->midM << "    " << tmp->otherM << "    " << tmp->finalM << "   " << tmp->totalM << endl;
		}
		course = course->courseNext;
	}
	cout << endl;
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

void Staff::createAllClassesFromCSV(SchoolYear*& sy, InfoStu*& info) {
	ifstream fin("DSSV_Khoatuyen" + sy->name + ".txt");
	if (!fin) {
		cout << "Cannot open file named: " << "DSSV_Khoatuyen" + sy->name + ".txt";
		return;
	}

	if (info == NULL) info = new InfoStu();
	InfoStu* tmpIn4 = info;

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
		Class* tmpCl = findClass(sy, tmp->className);
		addStuToClass(tmpCl, tmp);

		info->stuInClass = tmp;
		info->InfoStuNext = new InfoStu();
		info->infoClass = tmpCl;
		info = info->InfoStuNext;
		cout << cnt << endl;
		cnt++;
	}
	info = tmpIn4;
	fin.close();
}

int main() {
	SchoolYear* sy = new SchoolYear();
	sy->name = "2022-2023";
	Staff* staff = new Staff();
	InfoStu* info = new InfoStu();

	staff->createAllClassesFromCSV(sy, info);

	Class* cl = sy->classHead;
	while (cl) {
		Student* stu = cl->stuHead;
		while(stu)
		{
			cout << stu->firstName << endl;
			stu = stu->stuNext;
		}
		cl = cl->classNext;
	}

}
