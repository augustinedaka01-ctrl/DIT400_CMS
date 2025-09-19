// main.cpp
// DIT400 — Course Management System (arrays + file I/O)
// No structs, classes, pointers, vectors, or maps — parallel arrays only.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

const int MAX_COURSES = 1000;
const string USERS_FILE = "users.txt";
const string COURSES_FILE = "courses.txt";

// Parallel arrays for courses
string courseIds[MAX_COURSES];
string titles[MAX_COURSES];
int creditHours[MAX_COURSES];
int courseCount = 0;

// Utility: trim (left + right)
string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// --- File I/O for courses ---
void loadCoursesFromFile() {
    courseCount = 0;
    ifstream fin(COURSES_FILE.c_str());
    if (!fin.is_open()) {
        // No file yet — treat as empty
        return;
    }
    string line;
    while (getline(fin, line) && courseCount < MAX_COURSES) {
        // Expected CSV: courseId,title,creditHours
        // title may contain commas in rare cases, but for assignment assume no commas in title.
        stringstream ss(line);
        string id, title, creditStr;

        if (!getline(ss, id, ',')) continue;
        if (!getline(ss, title, ',')) continue;
        if (!getline(ss, creditStr)) continue;

        id = trim(id);
        title = trim(title);
        creditStr = trim(creditStr);

        int cred = 0;
        try {
            cred = stoi(creditStr);
        } catch (...) {
            cred = 0;
        }

        courseIds[courseCount] = id;
        titles[courseCount] = title;
        creditHours[courseCount] = cred;
        courseCount++;
    }
    fin.close();
}

void saveCoursesToFile() {
    ofstream fout(COURSES_FILE.c_str(), ios::trunc);
    if (!fout.is_open()) {
        cout << "Error: could not open " << COURSES_FILE << " for writing.\n";
        return;
    }
    for (int i = 0; i < courseCount; ++i) {
        fout << courseIds[i] << "," << titles[i] << "," << creditHours[i] << "\n";
    }
    fout.close();
}

// --- File I/O for users ---
bool loadUsersCheckCredentials(const string &username, const string &password) {
    ifstream fin(USERS_FILE.c_str());
    if (!fin.is_open()) return false;

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string u, p;
        if (!getline(ss, u, ',')) continue;
        if (!getline(ss, p)) continue;
        if (trim(u) == username && trim(p) == password) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

bool userExists(const string &username) {
    ifstream fin(USERS_FILE.c_str());
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string u, p;
        if (!getline(ss, u, ',')) continue;
        if (trim(u) == username) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

bool registerUser(const string &username, const string &password) {
    if (username.empty() || password.empty()) return false;
    if (userExists(username)) return false;
    ofstream fout(USERS_FILE.c_str(), ios::app);
    if (!fout.is_open()) return false;
    fout << username << "," << password << "\n";
    fout.close();
    return true;
}

// --- Course operations ---
int findCourseIndexById(const string &id) {
    for (int i = 0; i < courseCount; ++i) {
        if (courseIds[i] == id) return i;
    }
    return -1;
}

void listAllCourses() {
    if (courseCount == 0) {
        cout << "No courses available.\n";
        return;
    }
    cout << "All courses (" << courseCount << "):\n";
    cout << "-------------------------------------------\n";
    cout << "CourseID\tTitle\t\tCreditHours\n";
    cout << "-------------------------------------------\n";
    for (int i = 0; i < courseCount; ++i) {
        cout << courseIds[i] << "\t" << titles[i] << "\t" << creditHours[i] << "\n";
    }
    cout << "-------------------------------------------\n";
}

void addCourse() {
    if (courseCount >= MAX_COURSES) {
        cout << "Cannot add more courses — storage full.\n";
        return;
    }
    string id, title;
    int cred;
    cout << "Enter course ID: ";
    cin >> ws;
    getline(cin, id);
    id = trim(id);
    if (id.empty()) {
        cout << "Course ID cannot be empty.\n";
        return;
    }
    if (findCourseIndexById(id) != -1) {
        cout << "A course with that ID already exists.\n";
        return;
    }
    cout << "Enter course title: ";
    getline(cin, title);
    title = trim(title);
    cout << "Enter credit hours (1-6): ";
    cin >> cred;
    if (cin.fail() || cred < 1 || cred > 6) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid credit hours. Must be 1-6.\n";
        return;
    }
    courseIds[courseCount] = id;
    titles[courseCount] = title;
    creditHours[courseCount] = cred;
    courseCount++;
    saveCoursesToFile();
    cout << "Course added successfully.\n";
}

void deleteCourse() {
    string id;
    cout << "Enter course ID to delete: ";
    cin >> ws;
    getline(cin, id);
    id = trim(id);
    int idx = findCourseIndexById(id);
    if (idx == -1) {
        cout << "Course ID not found.\n";
        return;
    }
    // Shift left to remove
    for (int i = idx; i < courseCount - 1; ++i) {
        courseIds[i] = courseIds[i + 1];
        titles[i] = titles[i + 1];
        creditHours[i] = creditHours[i + 1];
    }
    courseCount--;
    saveCoursesToFile();
    cout << "Course deleted successfully.\n";
}

void updateCourse() {
    string id;
    cout << "Enter course ID to update: ";
    cin >> ws;
    getline(cin, id);
    id = trim(id);
    int idx = findCourseIndexById(id);
    if (idx == -1) {
        cout << "Course ID not found.\n";
        return;
    }
    cout << "Current title: " << titles[idx] << "\n";
    cout << "Enter new title (leave blank to keep): ";
    string newTitle;
    getline(cin, newTitle);
    newTitle = trim(newTitle);
    if (!newTitle.empty()) titles[idx] = newTitle;

    cout << "Current credit hours: " << creditHours[idx] << "\n";
    cout << "Enter new credit hours (1-6) or 0 to keep: ";
    int newCred;
    cin >> newCred;
    if (!cin.fail()) {
        if (newCred >= 1 && newCred <= 6) creditHours[idx] = newCred;
        else if (newCred != 0) cout << "Invalid credit hours; keeping existing.\n";
    } else {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input; keeping existing credit hours.\n";
    }
    saveCoursesToFile();
    cout << "Course updated successfully.\n";
}

void searchCourse() {
    cout << "Search by: 1) Course ID  2) Title substring\nChoose (1 or 2): ";
    int choice;
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1) {
        string id;
        cout << "Enter course ID: ";
        getline(cin, id);
        id = trim(id);
        int idx = findCourseIndexById(id);
        if (idx == -1) cout << "Course not found.\n";
        else {
            cout << "Found: " << courseIds[idx] << " | " << titles[idx] << " | " << creditHours[idx] << "\n";
        }
    } else if (choice == 2) {
        string q;
        cout << "Enter title substring (case-insensitive): ";
        getline(cin, q);
        q = trim(q);
        if (q.empty()) {
            cout << "Empty query.\n";
            return;
        }
        // convert q to lowercase
        for (auto &c : q) c = tolower(c);
        bool any = false;
        for (int i = 0; i < courseCount; ++i) {
            string t = titles[i];
            string lowerT = t;
            for (auto &c : lowerT) c = tolower(c);
            if (lowerT.find(q) != string::npos) {
                cout << courseIds[i] << " | " << titles[i] << " | " << creditHours[i] << "\n";
                any = true;
            }
        }
        if (!any) cout << "No courses match that substring.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

// --- Authentication UI ---
bool performLogin() {
    cout << "=== Login ===\n";
    string username, password;
    cout << "Username: ";
    cin >> ws;
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    if (loadUsersCheckCredentials(trim(username), trim(password))) {
        cout << "Login successful. Welcome, " << username << "!\n";
        return true;
    } else {
        cout << "Invalid username/password.\n";
        return false;
    }
}

void performRegister() {
    cout << "=== Register ===\n";
    string username, password;
    cout << "Choose a username: ";
    cin >> ws;
    getline(cin, username);
    username = trim(username);
    if (username.empty()) {
        cout << "Username cannot be empty.\n";
        return;
    }
    if (userExists(username)) {
        cout << "Username already exists.\n";
        return;
    }
    cout << "Choose a password: ";
    getline(cin, password);
    password = trim(password);
    if (password.empty()) {
        cout << "Password cannot be empty.\n";
        return;
    }
    if (registerUser(username, password)) {
        cout << "Registration successful. You can now log in.\n";
    } else {
        cout << "Registration failed (could not write users file).\n";
    }
}

void showMainMenuAfterLogin() {
    while (true) {
        cout << "\n--- Course Management Menu ---\n";
        cout << "1. Add Course\n";
        cout << "2. Delete Course\n";
        cout << "3. Search Course\n";
        cout << "4. Update Course\n";
        cout << "5. List All Courses\n";
        cout << "6. Logout\n";
        cout << "7. Exit Program\n";
        cout << "Choose an option (1-7): ";
        int opt;
        cin >> opt;
        cin.ignore(10000, '\n');
        switch (opt) {
            case 1: addCourse(); break;
            case 2: deleteCourse(); break;
            case 3: searchCourse(); break;
            case 4: updateCourse(); break;
            case 5: listAllCourses(); break;
            case 6: cout << "Logging out...\n"; return;
            case 7: cout << "Exiting program...\n"; exit(0);
            default: cout << "Invalid option. Try again.\n"; break;
        }
    }
}

int main() {
    cout << "DIT400 — Course Management System (C++)\n";
    // Load courses on startup
    loadCoursesFromFile();

    while (true) {
        cout << "\n=== Welcome ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Choose (1-3): ";
        int choice;
        cin >> choice;
        cin.ignore(10000, '\n');
        if (choice == 1) {
            if (performLogin()) {
                showMainMenuAfterLogin();
            }
        } else if (choice == 2) {
            performRegister();
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
