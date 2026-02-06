#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;


string toLower(string data) {
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}

class User {
    private:
        string regID, auth, pass;
        string fRegID, fPass, fAuth;


    public:

        bool userPresent(string regID) {
            ifstream file("users.txt");
            

            while (getline(file, fRegID, '|') &&
                    getline(file, fPass, '|') &&
                    getline(file, fAuth)){

                    fAuth.erase(remove(fAuth.begin(), fAuth.end(), '\r'), fAuth.end());
                    fAuth.erase(remove(fAuth.begin(), fAuth.end(), '\n'), fAuth.end());

                if(fRegID == regID){
                    return true;
                }
                
            }
            return false;
        }
        void newUser(){                     
            

            cout << "Enter regID: ";
            cin >> regID;

            if(userPresent(regID)){
                cout<< "This user is already in the system"<< endl;
                return;
            }
            

            cout << "Enter Password: ";
            cin >> pass;

            cout << "Enter your position (admin/student): ";
            cin >> auth;

            ofstream file("users.txt", ios::app);

            file << regID << "|" << pass << "|" << auth << endl;

            
            file.close();
            cout << "\n*****Successful Registration*****\n";

        }

        string loginUser() {
            
            cout << "\nLogin here"<<endl;
            cout << "Enter Reg No: ";
            cin >> regID;

            cout << "Enter Password: ";
            cin >> pass; 
            

            ifstream file("users.txt");            
    
            while (getline(file, fRegID, '|') &&
                    getline(file, fPass, '|') &&
                    getline(file, fAuth)) {
                        

                    fAuth.erase(remove(fAuth.begin(), fAuth.end(), '\r'), fAuth.end());
                    fAuth.erase(remove(fAuth.begin(), fAuth.end(), '\n'), fAuth.end());
                if (regID == fRegID && pass == fPass){
                    cout << "Welcome Back " << regID << endl;
                    return fAuth + ":" + regID;
                }
                
                
            } 
            cout << "\n-----Sorry Missmatch detected-----\n" << endl;
            return "no position";  
        }

};
class Book {
    private:
        string title, fTitle; string borrower = "none";
        string author, fAuthor;
        string status = "available";
        int isbn, fIsbn;
        

    public:
        void addBook();
        void deleteBook();
        void updateBook();

        bool isbnExists(int checkIsbn) {
            ifstream file("books.txt");

            int fIsbn;
            string fTitle, fAuthor, status, borrower;

            while (file >> fIsbn) {
                file.ignore();
                getline(file, fTitle, '|');
                getline(file, fAuthor, '|');
                getline(file, status, '|');
                getline(file, borrower);

                if (fIsbn == checkIsbn) {
                    return true;
                }
            }

            return false;
        }


};

void Book :: addBook(){
    cout <<"\n-----ADD BOOK(S)-----"<< endl;
    cin.ignore(1000, '\n');
    cout << "Title: ";    
    getline(cin, title);
    title = toLower(title);
    cout << "Author: ";
    getline(cin, author);
    cout << "ISBN: ";
    cin >> isbn;

    if (isbnExists(isbn)) {
        cout << "\n A book with this ISBN already exists\n";
        return;
    
    }
    cout << "Status (available or borrowed): ";
    cin >> status;
    // cout << "Borrower(none)";
    // cin >> borrower;
    
    ofstream file("books.txt", ios::app);
    
    file << isbn << "|" << title << "|" << author << "|" << status << "|" << borrower << endl;


    file.close();
    cout<< "\n*****Success*****\n"<< endl;
}
void Book :: deleteBook(){
    cout <<"\n-----DELETE BOOK(S)-----"<<endl;
    int dIsbn;
    
    cout << "Enter the book's ISBN: ";
    cin >> dIsbn;

    ifstream file("books.txt");
    ofstream dummy("dummy.txt");

    string title, author, status, borrower;
    int fIsbn;

    bool found = false;
    while (file >> fIsbn){
        file.ignore();
        getline(file,title,'|');
        getline(file,author,'|');
        getline(file,status,'|');
        getline(file,borrower);
        if(fIsbn == dIsbn){
            found = true;
            continue;
        }
        
        dummy << fIsbn << "|" << title << "|" << author << "|" << status << "|" << borrower << endl;


    }
    file.close();
    dummy.close();

    remove("books.txt");
    rename("dummy.txt", "books.txt");

    if(found){
        cout << "Book deleted successfully";
    }
    else {
        cout << "Book not found"<< endl;
    }

    

}

void Book :: updateBook(){    
    cout<< "\n-----UPDATE BOOK-----"<< endl;
    int uIsbn;
    bool found = false;
    cout << "Enter the book's ISBN: ";
    cin >> uIsbn;

    ifstream file("books.txt");
    ofstream dummy("dummy.txt");
    string fTitle, fAuthor, status, borrower;
    int fIsbn;
    
    while (file >> fIsbn){
        file.ignore();
        getline(file,fTitle,'|');
        getline(file,fAuthor,'|');
        getline(file,status,'|');
        getline(file,borrower);
        if(fIsbn == uIsbn) {
            found = true;
            cout << "You are updating book :"<< fTitle <<endl;
            cout << "Enter new Title: ";
            cin.ignore();
            getline(cin, fTitle);
            cout << "Enter Author: ";
            getline(cin, fAuthor);
            cout << "Status (available or borrowed): ";
            cin >> status;
            cout << "Borrower: ";
            cin >> borrower;
            
        }
        dummy << fIsbn << "|" << fTitle << "|" << fAuthor << "|" << status << "|" << borrower << endl;

    }

    file.close();
    dummy.close();

    remove("books.txt");
    rename("dummy.txt", "books.txt");

    if(found){
        cout << "Update successfull" << endl;
    }
    else{
        cout << "Update failed!"<< endl;
    }
}
class Library {
    public:
        void libMenu();
        void borrowBook(string regID);
        void returnBook(string regID);
        void searchBook();
        void adminMenu();
        void studentMenu();
        void showAll();

        bool userBorrowed(string regID){
            ifstream file("books.txt");
            string line;

            while(getline(file, line)){
                if(line.find("|borrowed|" + regID) != string::npos){
                    return true;

                }
                
            }
            return false;
        }

        // void borrowBook(string regID){
        //     if(userBorrowed(regID)){
        //         cout << "You already borrowed a book"<< endl;
        //         return;
        //     }
        // }

        
};

void Library :: adminMenu(){
    cout<< "\n-----ADMIN MENU-----"<< endl;
    cout << "1. Add Book"<< endl;
    cout << "2. Update Book"<< endl;
    cout << "3. Delete Book"<< endl;
    cout << "4. Show All Books"<< endl;
    cout << "5. Exit"<< endl;
}

void Library :: studentMenu(){
    cout << "\n-----STUDENT MENU-----"<< endl;
    cout << "1. Borrow Book"<< endl;
    cout << "2. Return Book"<< endl;
    cout << "3. Search Book"<< endl;
    cout << "4. Show All Books"<< endl;
    cout << "5. Exit"<< endl;
}

void Library :: libMenu(){
    cout << "\n1. Borrow a Book" << endl;
    cout << "2. Return Book" << endl;
    cout << "3. Search Book" << endl;
    cout << "4. Exit" << endl;
}


void Library :: borrowBook(string regID){
    int bIsbn;
    bool found = false;
    cout << "\n-----BORROW BOOK-----"<< endl;
    cout << "Enter the book ISBN: ";
    cin >> bIsbn;

    // if(userBorrowed(regID)){
    //     cout << "You already borrowed a book"<< endl;
    //     return;
    // }

    ifstream file("books.txt");
    ofstream dummy("dummy.txt");

    int fIsbn;
    string fTitle, fAuthor, status, borrower;

    bool alreadyBorrowed =  false;

    while(file >> fIsbn){
        file.ignore();
        getline(file,fTitle,'|');
        getline(file,fAuthor,'|');
        getline(file,status,'|');
        getline(file,borrower);
        if(borrower == regID){
            alreadyBorrowed = true; 
        }

        if(fIsbn == bIsbn){
            found = true;
            if(status == "available" && !alreadyBorrowed){
                status = "borrowed";
                borrower = regID;
                cout << "Book Borrowed Successfully" << endl;
            } else if(status == "borrowed"){
                cout << "This book is already borrowed" << endl;
            } else if(alreadyBorrowed){
                cout << "You already borrowed a book" << endl;
            }
    }


    dummy << fIsbn << "|" << fTitle << "|" << fAuthor << "|" << status << "|" << borrower << endl;

}


    file.close();
    dummy.close();

    remove("books.txt");
    rename("dummy.txt", "books.txt");

    if(!found){
        cout << "Borrowing Failed!" << endl;
    }
    
}

void Library :: returnBook (string regID){   
    cout << "\n-----RETURN BOOK-----"<< endl;
    int rIsbn;
    bool found = false;
    cout << "Enter the book ISBN: ";
    cin >> rIsbn;

    ifstream file("books.txt");
    ofstream dummy("dummy.txt");

    int fIsbn;
    string fTitle, fAuthor, status, borrower;

    while(file >> fIsbn){
        file.ignore();
        getline(file,fTitle,'|');
        getline(file,fAuthor,'|');
        getline(file,status,'|');
        getline(file,borrower);
        if(fIsbn == rIsbn && borrower == regID){
            found = true;
            status = "available";
            borrower = "none";
            cout << "\nBook returned successfully\n"<< endl;
            
        }
        
        dummy << fIsbn << "|" << fTitle << "|" << fAuthor << "|" << status << "|" << borrower << endl;

    }


    file.close();
    dummy.close();

    remove("books.txt");
    rename("dummy.txt", "books.txt");

    if(!found){
        cout << "Return Failed!" << endl;
    }
}
void Library :: searchBook(){
    string sTitle;    
    bool found = false;
    cout << "\n-----SEARCH BOOK-----"<< endl;
    cout << "Enter the book Title: ";
    cin.ignore();
    getline(cin, sTitle);

    ifstream file("books.txt");
    sTitle = toLower(sTitle);
    int fIsbn;
    string fTitle, fAuthor, status, borrower;

    while(file >> fIsbn){
        
        getline(file,fTitle,'|');
        getline(file,fAuthor,'|');
        getline(file,status,'|');
        getline(file,borrower);
        if(fTitle == sTitle){
            found = true;
            cout << "\n-----AVAILABLE BOOK(S)-----"<< endl;
            cout << "Title: " << fTitle << endl;
            cout << "Author: " << fAuthor << endl;
            cout << "ISBN: " << fIsbn << endl;
            cout << "Status: " << status << endl;
            cout << "Borrower: " << borrower << endl;

            
        }
        
    }

    file.close();

    if(!found){
        cout << "Book Not Found!" << endl;
    }
}

void Library :: showAll(){

    ifstream file("books.txt");

    string line;
    int isbn;
    string fTitle, fAuthor, status, borrower;

    cout << "\n-----ALL BOOKS-----\n" << endl;

    while (getline(file, line)) {

        stringstream ss(line);

        string sIsbn;

        getline(ss, sIsbn, '|');
        getline(ss, fTitle, '|');
        getline(ss, fAuthor, '|');
        getline(ss, status, '|');
        getline(ss, borrower);

        isbn = stoi(sIsbn);

        cout << "ISBN: " << isbn << endl;
        cout << "Title: " << fTitle << endl;
        cout << "Author: " << fAuthor << endl;
        cout << "Status: " << status << endl;
        cout << "Borrower: " << borrower << endl;
        cout << "----------------------" << endl;
    }

    file.close();
}


int main(){
    User student;
    Library lib;
    Book b;

    cout << "\n==========ONLINE LIBRARY MANAGEMENT SYSTEM==========" << endl;
    User user;
    int ch;
    cout << "\n1. Login\n2. Register\nChoose your option: ";
    cin >> ch;

    if (ch == 2) {
        student.newUser();
    }
    string res = student.loginUser();
    if(res == "no position") return 0;

    string auth = res.substr(0, res.find(":"));
    string regID = res.substr(res.find(":") + 1);
    
    if (auth == "admin") {
    
        int num;
        
            do {
                lib.adminMenu();
                cout<< "\nEnter your choice: ";
                cin >> num;

                
                switch(num){
                    case 1: b.addBook(); break;
                    case 2: b.updateBook(); break;
                    case 3: b.deleteBook(); break;
                    case 4: lib.showAll(); break;
                }
            } while(num != 5);
        
    } else if (auth == "student"){
        int num;
        do {
                lib.studentMenu();
                cout<< "\nEnter your choice: ";
                cin >> num;

                switch(num){
                    case 1: lib.borrowBook(regID); break;
                    case 2: lib.returnBook(regID); break;
                    case 3: lib.searchBook(); break;
                    case 4: lib.showAll(); break;
                
                }

            } while(num != 5);        
       
    } else {
        cout<<"Your are not Authorized"<< endl;
    }
    
    // User user;
    return 0;
}