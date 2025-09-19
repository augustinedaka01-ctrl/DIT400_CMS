# AI Prompt Documentation

## Course Management System – DIT 400 Assignment 1

This document records the prompts and responses used with ChatGPT to assist in the development of the **Course Management System** in **C++** and its conversion to **Java**.

---

## 1. Prompts Used

### Prompt 1 (Initial Guidance)
**Student Prompt:**  
*"Help us implement a Course Management System in C++ using arrays only, with user login/registration and course management features."*

**AI Response (Summary):**  
- Provided complete `main.cpp` program using arrays for `users` and `courses`.  
- Implemented login, registration, add, delete, search, update, list, and save/load to text files.  
- Warned about issues with mixing `cin >>` and `getline()` and suggested fixes.

**Accepted:** Full C++ code structure.  
**Rejected:** Use of vectors or classes (not allowed by assignment).

---

### Prompt 2 (Improvement & Robustness)
**Student Prompt:**  
*"Take us through the code step by step and fix issues like input handling, file creation if missing, and safe parsing."*

**AI Response (Summary):**  
- Added `trim()` helper and case-insensitive search.  
- Ensured `users.txt` and `courses.txt` are created if missing.  
- Wrapped `stoi()` in `try/catch` to prevent crashes.  
- Suggested consistent use of `getline()` instead of mixing with `cin`.

**Accepted:** All improvements.  
**Rejected:** Advanced validation such as regex for course ID (not required in spec).

---

### Prompt 3 (Conversion to Java)
**Student Prompt:**  
*"Convert the improved C++ version into Java. Keep arrays only (no ArrayList, no Map, no OOP classes beyond Main). Make sure it behaves the same and uses files."*

**AI Response (Summary):**  
- Delivered `Main.java` using `String[]` and `int[]` arrays.  
- Implemented login/registration, add/delete/search/update/list.  
- Used `BufferedReader` for console input.  
- Implemented case-insensitive search and safe parsing.  

**Accepted:** Full Java translation.  
**Rejected:** Suggestion to use ArrayList for scalability.

---

### Prompt 4 (Batch Files)
**Student Prompt:**  
*"Give us build.bat files for both C++ and Java that compile and run automatically."*

**AI Response (Summary):**  
- Provided `C++/build.bat` that compiles `main.cpp` and runs `cms_cpp.exe`.  
- Provided `Java/build.bat` that compiles `Main.java`, creates `cms_java.jar`, and runs it.  

**Accepted:** Both batch files.  
**Rejected:** Linux/Mac `build.sh` (not required for our environment).

---

### Prompt 5 (README Specification)
**Student Prompt:**  
*"Generate README.md according to the assignment instructions with group members, file formats, compilation instructions, and limitations."*

**AI Response (Summary):**  
- Produced assignment-style README with sections: Members, System Description, File Formats, Compilation, Scripts, Limitations, and Submission Checklist.  

**Accepted:** Entire structure, including group members table.  
**Rejected:** None.

---

## 2. AI Contributions Summary

The AI (ChatGPT) was used to:
- Generate the initial C++ program skeleton.
- Identify and fix input and file-handling bugs.
- Translate the program to Java while keeping array-only constraints.
- Produce build scripts (`build.bat`) for Windows.
- Generate assignment documentation (`README.md`, `ai_prompts.md`).

---

## 3. Human Contributions

- Students wrote initial draft code and tested edge cases.  
- Verified AI-generated code compiled and ran correctly.  
- Added real user accounts and course records for testing.  
- Edited documentation to include real member names, IDs, and submission details.  

---

## 4. Notes

- AI suggestions to use advanced data structures were rejected to comply with **pre-OOP / arrays only** requirement.  
- AI helped accelerate debugging, but final testing and validation were done by the student group.  
- This documentation ensures transparency in AI-assisted development.

---
