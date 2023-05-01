#include <iostream>
#include "Structure.h"
void ChangePassword(Account*& account) {
	string pass;
	string newpass;
	cout << "Please enter the password: ";
	string newpass2;
	cin.get();
	while (true) {
		getline(cin, pass);
		if (pass.compare(account->password) == 0) {
			cout << "Please enter the new password: ";
			getline(cin, newpass);
			while (true) {
				cout << "Please enter the new password again: ";
				getline(cin, newpass2);
				if (newpass.compare(newpass2) == 0) {
					cout << "Your password have been changed";
					account->password = newpass;
					break;
				}
				else {
					cout << "Error, incorrectly new password!";
				}
			}
		}
		else {
			cout << "Wrong password";
		}
	}
}