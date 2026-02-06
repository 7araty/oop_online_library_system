#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class User {
    private: 
        string regNo;
        string username;
        string pass;
    public:
        void signUp();        
        void signIn();
        
        

};

void User :: signUp() {
    cout<< "\nEnter Username: ";
    cin >> username;
    cout<< "Enter REGNO: ";
    cin >> regNo;
    cout<< "Enter Password: ";
    cin >> pass;
}
void User :: signIn(){
    cout<< "\nEnter REGNO: ";
    cin >> regNo;
    cout<< "Enter Password: ";
    cin >> pass;
};
class Book {
    public:
        string title;
        string author;
        int serial_No;
    public:
        void addBook();
        void removeBook(){};
        void searchBook(){};

};

void Book :: addBook() {
    cout << "Add a book" << endl;
    cout << "Enter book title: ";
    cin >> title;
    cout << "Enter author name: ";
    cin >> author;
    cout << "Enter Serial Number: ";
    cin >> serial_No;

}
class Library {};





int main(){
    cout << "\n==========ONLINE LEARNING MANAGEMENT SYSTEM==========" << endl;
    User user;
    int ch;
    cout << "\n1. Login\n2. Register\nChoose your option: ";
    cin >> ch;

    (ch == 1) ? user.signIn() : user.signUp();
    
    // User user;
    return 0;
}