#pragma once
#include "Structure.h"
bool checkStaffPassword(string, string);
bool checkStudentPassword(string, string);
void login(int firstlog, SchoolYear* &yearHead);
void menuStaff(string username, SchoolYear* yearHead);
void menuStudent(string usename, SchoolYear* yearHead, Student* stuCur);
void UI();
void UIlite();
void backmenuStaff(string username, SchoolYear*& yearHead, string chose);
void backmenuStudent(string username, SchoolYear*& yearHead, Student* stuCur, string chose);