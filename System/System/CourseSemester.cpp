#pragma once
#include <string>
#include <iostream>
#include "Structure.h"

using namespace std;
/*
//Input a date (day-month-year)
void inputADate(Date& d){
    cin >> d.day >> d.month >> d.year;
}
//Create a semester
void createSemester(Semester& s){
    cin >> s.num;
    cout << "Input start date of this semester: ";
    inputADate(s.start);
    cout << "Input end date of this semester: ";
    inputADate(s.end);
}
//Tim nam hc theo so nam
SchoolYear* findSchoolYear(SchoolYear* sHead, string a){
    SchoolYear* cur = sHead;
    while(cur){
        if(cur->name == a)
            break;
        cur = cur->yearNext;
    }
    return cur;
}
//Xac dinh semester so may va thuoc nam nao
void addSemesterToSy(SchoolYear*& sHead, Semester& s, string nameSy){
    SchoolYear* tmp = findSchoolYear(sHead, nameSy);
    tmp->sm[s.num-1] = s;
    s.inSY = tmp;
    s.syName = tmp->name;
}
//Add a new student into a course by hand
bool Staff::addAStudentInCourse(Course*& a, Student* newStu){
    if(a->cntStudent == a->maxStudent)
        return false;
    if(a->stuHead == NULL){
        a->cntStudent += 1;
        a->stuHead = new StuInCourse;
        a->stuHead->stuInClass = newStu;
        if(newStu->pStuCourseHead == NULL)
            newStu->pStuCourseHead = a->stuHead;
        else{
            StuInCourse* tmp = newStu->pStuCourseHead;
            while(tmp){
                tmp = tmp->pStuCourseNext;
            }
            tmp = a->stuHead;
            tmp->pStuCourseNext = NULL;
        }
        InfoStu tmp;
        tmp.stuInClass = newStu;
        tmp.importStuToCourseCSV(a->ID);
        return true;
    }
    StuInCourse* cur = a->stuHead;
    while(cur)
        cur = cur->stuNext;
    cur->stuInClass = newStu;
    cur->stuNext = NULL;
    a->cntStudent += 1;
    if(newStu->pStuCourseHead == NULL)
        newStu->pStuCourseHead = cur;
    else{
        StuInCourse* tmp = newStu->pStuCourseHead;
        while(tmp){
            tmp = tmp->pStuCourseNext;
        }           // chay ra khoi linked list luon r :)))
        tmp = cur;
        tmp->pStuCourseNext = NULL;
    }
    return true;
}
//Input data of a course
void inputACourse(Course* a){
    cin >> a->ID;
    cin.ignore();
    getline(cin , a->name);
    getline(cin, a->teacherName);
    cin >> a->numCredit;
    cin >> a->day;
    cin >> a->session;
    cin >> a->maxStudent;
    cin >> a->className;
}
//Convert a string-type day into its certain number
int numPresentAsDay(string day){
    if(day == "MON")
        return 0;
    if(day == "TUE")
        return 1;
    if(day == "WED")
        return 2;
    if(day == "THU")
        return 3;
    if(day == "FRI")
        return 4;
    if(day == "SAT")
        return 5;
}
//Convert a int-type day into its certain string
string stringPresentAsDay(int n){
    if(n == 0)
        return "MON";
    if(n == 1)
        return "TUE";
    if(n == 2)
        return "WED";
    if(n == 3)
        return "THU";
    if(n == 4)
        return "FRI";
    if(n == 5)
        return "SAT";
}
//View all available sessions of a class in a week
void viewAvailableSession(Class* c){
    cout << "     MON   TUE   WED   THU   FRI   SAT   " << endl;
    for(int j = 0; j < 4; j++){
        cout << "S" << j+1 << "    ";
        for(int i = 0; i < 6; i++){
            if(c->courseSes[i][j])
                cout << "T" << "     ";
            else cout << "A" << "     "; 
        }
        cout << endl;
        if(j == 1)
            cout << "                  -" << "BREAK" << "-                  "<< endl;
    }
    cout << endl;
    cout << "A: Available session" << endl;
    cout << "T: Taken session";
    cout << endl;
}*/
//Choose a session of a class that a course will take 
/*void classAttendToCourse(Course* a, Class* c){
    //clear screen
    cout << "\033[2J\033[1;1H";

    //view all the sessions of the class
    viewAvailableSession(c);

    Class* cur = a->classHead;
    while(cur->classNext)
        cur = cur->classNext;
    cur->classNext = c;
    c->classNext = NULL;
    // Input day of week for this course occur
    string tmp;
    cin >> tmp;
    int d = numPresentAsDay(tmp);
    
    //Input the session
    int ses;
    cin >> ses; // Session 1 2 3 4
    
    //Mark this session has been taken
    c->courseSes[d][ses] = true;
    a->dayB[d].s[ses].cur_class = c;
    a->dayB[d].s[ses].isEmpty = false;
}*//*
//Add a course to a semester
void addCourse(Semester& s, Course* a){
    inputACourse(a);
    if(s.courseHead == nullptr){
        s.courseHead = a;
        return;
    }
    Course* courseCur = s.courseHead;
    while(courseCur->courseNext){
        courseCur = courseCur->courseNext;
    }
    courseCur->courseNext = a;
    courseCur = a;
    courseCur->courseNext = nullptr;
    ofstream ft(".\\Files\\DSHP\\dshp.txt", ofstream::app);
    ft << a->ID << ' ' << a->name << ' ' << a->numCredit << ' ' << a->teacherName << ' ' << a->day << ' ' << a->session << ' ' << a->maxStudent << ' ' << a->className << endl;

}
//Remove a student from a course
void removeStuFile(string courseclass, string courseid, string stuid) {
	ifstream fin(".\\Files\\DSHP\\"+courseid+"_"+courseclass+".txt");
	if (!fin) {
		cout << "Error" << endl;
		return;
	}

	string s;
	string s1 = "";
	ofstream ft(".\\Files\\DSHP\\tmp.txt");

	while (!fin.eof()) {
		for (int i = 0; i < 3; i++) {
			fin >> s;
			if (i == 0 && s.substr(4, 1) != "-") {
				fin.close();
				ft.close();

				s = ".\\Files\\DSHP\\" + courseid + "_" + courseclass + "_dsdkhp.txt";
				char* p = new char[s.length()+1];
				p[s.length()] = '\0';
				for (int i = 0; i < s.length(); i++) p[i] = s[i];
				
				remove(p);
				rename(".\\Files\\DSHP\\tmp.txt", p);
				delete[]p;
				return;
			}
			s1 += s + " ";
		}
		if (s != stuid) ft << s1.substr(0, s1.length() - 1) << endl;
		s1 = "";
	}
}
bool Staff::removeAStudentFromCourse(Course*& a, string ID){
    if(a->stuHead == NULL) 
        return false;
    StuInCourse* cur = a->stuHead;
    while(cur->stuNext){
        if(checkID(cur->stuNext->stuInClass->StuID, ID) == true){
            StuInCourse* tmp = cur->stuNext;
            cur->stuNext = cur->stuNext->stuNext;
            StuInCourse* tmpStu = cur->stuInClass->pStuCourseHead;
            while(tmpStu->stuNext != tmp){
                tmpStu = tmpStu->stuNext;
            }
            tmpStu->stuNext = tmpStu->stuNext->stuNext;
            delete tmp;
            a->cntStudent -= 1;
            removeStuFile(a->className, a->ID, ID);
            return true; //Thong bao xoa thanh cong.
        }
        cur = cur->stuNext;
    }
    return false; //Neu k co ID do thi bao hc sinh k tham gia khoa hoc.
}
//check whether the input ID is the same as the course's ID
bool checkID(string courseID, string tmpID){
    if(courseID.length() != tmpID.length())
        return false;
    for(int i = 0; i < courseID.length(); i++)
        if(courseID[i] != tmpID[i])
            return false;
    return true;
}
//Delete a course out of a semester by ID
bool Staff::deleteACourse(Course*& courseHead, string courseID){
    Course* cur = courseHead;
    if(cur == NULL)
        return false;
    if(checkID(courseHead->ID, courseID) == true){
        Course* tmp = courseHead;
        courseHead = courseHead->courseNext;
        delete tmp;
        return true;
    }
    while(cur->courseNext){
        if(checkID(cur->courseNext->ID, courseID) == true)
            break;
        cur = cur->courseNext;
    }
    if(cur->courseNext == NULL)
        return false;
    else{
        Course* tmp = cur->courseNext;
        cur->courseNext = cur->courseNext->courseNext;
        delete tmp;
        return true;
    }
}*/
//Student upgrade 14: check if a student is following a course or not
/*
StuInCourse* checkStuInCourse(Course* c, Student* stu){
    StuInCourse* curStu = c->stuHead;
    while(curStu){
        if(curStu->stuInClass->StuID == stu->StuID)
            return curStu;
        curStu = curStu->stuNext;
    }
    return NULL;
}
*//*
//View all the courses in a semester
void InfoStu::viewCourses(Semester s){
    Course* cur = s.courseHead;
    while(cur){
        if(checkStuInCourse(cur, stuInClass)){
            cout << "Your courses: ";
            cout << cur->name << '[' << cur->ID << ']';
            cout << endl;
        }
        cur = cur->courseNext;
    }
}

//find the final GPA of a student
float final_GPA(Semester sm, Student* s){
    float gpa = 0;
    Course* cur = sm.courseHead;
    while(cur){
        StuInCourse* tmp = checkStuInCourse(cur, s);
        if(tmp)
            gpa += tmp->totalM;
        cur = cur->courseNext;
    }
    gpa = (gpa*4)/10;
    return gpa;
}

//Update course's information
void viewOptions(){
    cout << "UPDATE COURSE'S INFORMATION." <<  endl;
    cout << endl; 
    cout << "Options: " << endl;
    cout << "1. Update ID." << endl;
    cout << "2. Update course name." << endl;
    cout << "3. Update teacher's name." << endl;
    cout << "4. Update number of credits." << endl;
    cout << "5. Update maximum students." << endl;
    cout << "6. Update session of course of a class (S1, S2, S3, S4 - MON...SAT)." << endl; 
    cout << "0. Stop updating and save" << endl;
} 
void viewCourseInfo(Course* course){
    cout << "Course: " << course->name << endl;
    cout << course->ID << "_" << course->className << endl;
    cout << "Teacher: " << course->teacherName << endl;
    cout << "Number of credits: ";
    cout << course->numCredit << endl;
    cout << "Maximum students: ";
    cout << course->maxStudent << endl;
    cout << "Time of occurence: " << course->day << ' ';
    switch(course->session){
        case 1:
        {
            cout << "7h30 - 9h30" << endl;
            break;
        }
        case 2:
        {
            cout << "9h30 - 11h30" << endl;
            break;
        }
        case 3:
        {
            cout << "13h30 - 15h30" << endl;
            break;
        }
        case 4:
        {
            cout << "15h30 - 17h30" << endl;
            break;
        }
    }
}

bool checkInfoCourse(Semester sm, string cID, string cName, string cCre, string cLec, string cDay, string cSes, string cMax, string cClass) {
    bool check = true;
    for (int i = 0; i < cMax.length(); i++) {
        if (cMax[i] - 48 < 0 || cMax[i] - 48 > 9) {
            cout << "Found a non-num character in maximum number of student which is an integer!" << endl;
            check = false;
        }
    }
    for (int i = 0; i < cCre.length(); i++) {
        if (cMax[i] - 48 < 0 || cMax[i] - 48 > 9) {
            cout << "Found a non-num character in number of credits which is an integer!" << endl;
            check = false;
        }
    }
    if (findCourseByIDAndClass(cID, cName, sm) != NULL) {
        cout << "This course has been already created in this semester!" << endl;
        check = false;
    }
    if (convertFloat(cMax) > 50) {
        cout << "The maximum student in a course is 50!" << endl;
        check = false;
    }
    if (cSes != "S1" || cSes != "S2" || cSes != "S3" || cSes != "S4") {
        cout << "There are only four sessions S1 -> S4!" << endl;
        check = false;
    }
    if (cDay != "MON" || cDay != "TUE" || cDay != "WED" || cDay != "THU" || cDay != "FRI" || cDay != "SAT") {
        cout << "Default day has been found!" << endl;
        check = false;
    }
    if (check == false) {
        cout << "Oops! There are some mistakes in the course's data as decribed above! Please check again!" << endl;
    }
    return check;
}

void updateCourseInfo(Course* course){
    viewOptions();
    int check = 10;
    while(check != 0){
        cin >> check;
        switch (check){
            case 1:
            {
                cout << "New course's ID: ";
                cin >> course->ID;
                break;
            }
            case 2:
            {
                cout << "New course's name: ";
                getline(cin, course->name);
                break;
            }
            case 3:
            {
                cout << "New teacher's name: ";
                getline(cin, course->teacherName);
                break;
            }
            case 4:
            {
                cout << "New number of credits: ";
                cin >> course->numCredit;
                break;
            }
            case 5:
            {
                cout << "New maximum students: ";
                cin >> course->maxStudent;
                if(course->maxStudent > 50){
                    cout << "The maximum student of a course can not be over 50. Please input again!" << endl;
                    cout << "New maximum students: ";
                    cin >> course->maxStudent;
                }
                break;
            }
            case 6:
            {
                cout << "New day and session (Day + num-th session): ";
                cin >> course->day >> course->session;
                break;
<<<<<<< HEAD
            }
            case 7:
            {
                cout << "New class name: ";
                cin >> course->className;
                break;
            }
=======
            }*/
>>>>>>> 1509760cc22cef013c779ef8e2a6ba208bafbef4
            /*case 7:
            {
                string tmp;
                cout << "The class's name you want to change its session: ";
                cin >> tmp;
                Class* cur = course->classHead;
                while(cur){
                    if(cur->name == tmp)
                        break;
                    cur = cur->classNext;
                }
                if(cur == NULL){
                    cout << "NO class's name found! " << endl;
                    break;
                }
                string old_day, new_day;
                int old_ses, new_ses;
                cout << "Please input your old session (Day + num-th session): ";
                cin >> old_day >> old_ses;
                cur->courseSes[numPresentAsDay(old_day)][old_ses] = false;
                
                //clear screen
                cout << "\033[2J\033[1;1H";
                viewAvailableSession(cur);
                cout << "Please input the new session you want to access to (Day + num-th session): ";
                cin >> new_day >> new_ses;
                cur->courseSes[numPresentAsDay(new_day)][new_ses] = true;
                break;
            }*//*
        }
    }
}
//Print out the schedule of a student
void viewSchedule(Semester sm, Student *s){
    string nameSes[4][7];
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 7; j++)
			nameSes[i][j] = "           ";
    Course* cur = sm.courseHead;
    while(cur){
        if(checkStuInCourse(cur, s)){
            nameSes[cur->session-1][numPresentAsDay(cur->day)] = cur->ID;
        }
        cur = cur->courseNext;
    }
	cout << "                                   < SCHEDULE >" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << " SES/DAY  |     MON    |    TUE    |    WED    |    THU    |    FRI    |    SAT    |" <<  endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    for(int i = 0; i < 4; i++){
        if(i == 2){
            cout << "                                      -BREAK-                     " << endl;
            cout << "------------------------------------------------------------------------------------" << endl;
        }
        cout << "Session " << i+1 << " : ";
        for(int j = 0; j < 6; j++)
            cout << string(11-((11-nameSes[i][j].length())/2)-nameSes[i][j].length(), ' ') << nameSes[i][j] << string((11-nameSes[i][j].length())/2, ' ') << '|';
        cout << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
    }
    cout << endl;
}

//additional function
//Convert a string into float type
float convertFloat(string s){
    float a = 0;
    if(s == "10")
        return 10;
    a += (s[0]-48); //first number
    int k = s.size();
    int tmp = 10;
    for(int i = 2; i < k; i++){//s[1] == ','
        a += (float)(s[i]-48)/tmp;
        tmp *= 10;
    }
    return a;
}

//Add students in a sorting way
void addAndSortByID(StuInCourse*& stuHead, StuInCourse* curStu){
    float a = convertFloat(curStu->stuInClass->StuID);
    StuInCourse* cur = stuHead;
    while(cur){
        float b = convertFloat(cur->stuInClass->StuID);
        if(a > b){ 
            curStu->stuNext = cur->stuNext->stuNext;
            cur->stuNext = curStu;
            return;
        }
        cur = cur->stuNext;
    }
    curStu->stuNext = stuHead;
    stuHead = curStu;
}
//Find and return a course by ID
Course* findCourseByIDAndClass(Semester sm, string inputID, string nameClass){
    Course* cur = sm.courseHead;
    while(cur){
        if(checkID(cur->ID, inputID) == true)
            if(cur->className == nameClass)
                return cur;
        cur  = cur->courseNext;
    }
    return NULL;
}
<<<<<<< HEAD
bool checkInfoCourse(Semester sm, string cID, string cName, string cCre, string cLec, string cDay, string cSes, string cMax, string cClass){
    bool check = true;
    for(int i = 0; i < cMax.length(); i++){
        if(cMax[i] - 48 < 0 || cMax[i] - 48 > 9){
            cout << "Found a non-num character in maximum number of student which is an integer!" << endl;
            check = false;
        }
    }
    for(int i = 0; i < cCre.length(); i++){
        if(cMax[i] - 48 < 0 || cMax[i] - 48 > 9){
            cout << "Found a non-num character in  number of credits which is an integer!" << endl;
            check = false;
        }
    }
    if(findCourseByIDAndClass(sm, cID, cClass) != NULL){
        cout << "This course has been already created in this semester!" << endl;
        check = false;
    }
    if(convertFloat(cMax) > 50){
        cout << "The maximum student in a course is 50!" << endl;
        check = false;
    }
    if(cSes != "S1" || cSes != "S2" || cSes != "S3" || cSes != "S4"){
        cout << "There are only four sessions S1 -> S4!" << endl;
        check = false;
    }
    if(cDay != "MON" || cDay != "TUE" || cDay != "WED" || cDay != "THU" || cDay != "FRI" || cDay != "SAT"){
        cout << "Default day has been found!" << endl;
        check = false;
    }
    if(check == false){
        cout << "Oops! There are some mistakes in the course's data as decribed above! Please check again!" << endl;
    }
    return check;
}
=======

*/
>>>>>>> 1509760cc22cef013c779ef8e2a6ba208bafbef4
