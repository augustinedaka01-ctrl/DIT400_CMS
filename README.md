# Course Management System – DIT400 Assignment 1

## Project
Course Management System implemented in **C++** and **Java** (Pre-OOP).  
Uses **parallel arrays** for in-memory storage and text files for persistence.

---

## Group Members & Roles

| Name             | Registration Number | Program               | Role (Assignment)                                          |
|------------------|----------------------|-----------------------|------------------------------------------------------------|
| Augustine Daka   | 2410310       | Diploma in IT         | Member A — Authentication & File I/O Lead (C++ & user    |
| ALICE MULENGA     | 2410574       | Diploma in IT         | Member B — Course CRUD & Array Management Lead (C++)       |
| ALICE ZULU    | 2410639       | Diploma in IT         | Member C — Search/Update & Java Lead (Java translation)    |

---

## 1. System Description

This console-based Course Management System supports:
- User registration & login (credentials stored in `users.txt`).
- Course management: Add, Delete, Search (ID or title substring), Update, List.
- Data persistence via `users.txt` and `courses.txt`.
- Arrays only (no structs/classes in C++ version; Java version also uses arrays only).

---

## 2. File Formats

### users.txt
Format: `username,password` (one per line)

Example:
