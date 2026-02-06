# Online Library Management System – GitHub README

## Project Description

This is a console-based Online Library Management System developed in C++ using Object-Oriented Programming (OOP) principles. The system allows users to register and login, manage books, and perform library operations like borrowing and returning. Admins have special privileges to add, update, delete, and view books. The project ensures validation rules such as preventing duplicate ISBNs and duplicate users.

## Features

* User registration and login (admin/student roles)
* Add, update, delete, and view books (admin only)
* Borrow and return books (students)
* Search books by title
* Data persistence using text files (users.txt, books.txt)
* Validations: duplicate ISBN, duplicate user, one book per user at a time

## How to Compile and Run on Windows

1. Open Command Prompt in the project folder:

   ```
   C:\Users\Administrator\Desktop\OnlineLMS>
   ```
2. Compile the program using g++:

   ```
   g++ main.cpp -o home
   ```
3. Run the program:

   ```
   .\home
   ```
4. Make sure the following files are in the same directory:

   * `users.txt`
   * `books.txt`

The application will display login/registration options, followed by role-specific menus.

## Screenshots Steps

1. **Login/Register Menu**

   * Prompt to login or register a new user
   * 

2. **Admin Menu**

   * Options to add, update, delete, and view books

3. **Student Menu**

   * Options to borrow, return, search, and view books

4. **Borrow/Return Operation**

   * Successful borrowing or returning messages
   * Prevent duplicate borrowing

5. **Book Search**

   * Displays book details including status and borrower

---

**Note:** Screenshots can be captured using Windows Snipping Tool or Print Screen and added to the repository for reference.
