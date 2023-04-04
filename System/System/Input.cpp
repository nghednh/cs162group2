#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using namespace std;
using namespace fs;

struct User {
    string username;
    string password;
};

void processCSVFile(const path& file_path) {
    ifstream file(file_path.c_str()); // mở file
    if (!file.good()) { // kiểm tra nếu không thể mở file
        cout << "Cannot open file" << endl;
        return;
    }

    string line;
    string username, password;

    while (getline(file, line)) {
        stringstream ss(line);

        getline(ss, username, ',');
        getline(ss, password, ',');

        User user = { username, password };
        cout << user.username << user.password << std::endl;
    }

    file.close();
}

void read_files(const path& path) {
    for (const auto& entry :directory_iterator(path)) {
        if (entry.is_directory()) {
            read_files(entry.path());
        }
        else {
            // Kiểm tra tệp tin có phải là tệp tin csv hay không
            if (entry.path().extension() == ".txt") {
                cout << entry.path() << endl;
                // Đọc và xử lý tệp tin csv
                processCSVFile(entry.path());
            }
        }
    }
}

int main() {
    path root_path("School Year 2022-2023");
    read_files(root_path);
    return 0;
}
