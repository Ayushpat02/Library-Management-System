// Ayush Patel 
// 12 PM CS 251
// library.cpp
// apate554@uic.edu
// Project 1: Library Management: This project has a library that stores books, which includes the following information: book title, isbn, and the status of the book in the library.
// library.cpp includes all the code that is outputting the library and the options to the user, and the code behind the scenes of how the library with the different functions are operating.
// You cannot use any libraries beyond the ones we have given below.
// You must use output streams, file streams, vectors, and strings.
// You are not allowed to use any other containers or objects.
// You may not use structs, pointers, or dynamic memory allocations.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function prototypes for all the glorious function decomposition
// Each function is a void function so that in the main, in the do while loop, the functions print out the necessary information.
// There are 3 parameters for all functions expect the loadLibrary and outputLibrary functions as the vecotr statusnum is to store the status number if the stauts is "Invalid State".
void printMenu();
void addItem(vector<string> &title, vector<string> &isbn, vector<string> &status);
void displayLibrary(vector<string> &title, vector<string> &isbn, vector<string> &status);
void clearLibrary(vector<string> &title, vector<string> &isbn, vector<string> &status);
void loadLibrary(vector<string> &title, vector<string> &isbn, vector<string> &status, vector<string> &statusnum);
void outputLibrary(vector<string> &title, vector<string> &isbn, vector<string> &status, vector<string> &statusnum);
void checkoutstats(vector<string> &title, vector<string> &isbn, vector<string> &status);
void searchlibrary(vector<string> &title, vector<string> &isbn, vector<string> &status);
void removelibrary(vector<string> &title, vector<string> &isbn, vector<string> &status);
void printinvalidentries(vector<string> &title, vector<string> &isbn, vector<string> &status);

// The main has the do while loop, where the conditions run at least once, and the if and else if statements were based off of the command the user gave.
// The functions for each option were called with the approiate parameters.
// All of the vectors were declared in main.
int main()
{
    string command;
    vector<string> bookTitleslib;
    vector<string> isbn;
    vector<string> status;
    vector<string> statusnum;


    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do 
    {
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        getline(cin, command);
        cout << endl;
        if (command == "A" || command == "a") {
            addItem(bookTitleslib, isbn, status);
        }
        else if (command == "C" || command == "c") {
            clearLibrary(bookTitleslib, isbn, status);
        }
        else if (command == "D" || command == "d") {
            displayLibrary(bookTitleslib, isbn, status);
        }
        else if (command == "I" || command == "i") {
            printinvalidentries(bookTitleslib, isbn, status);
        }
        else if (command == "L" || command == "l") {
            loadLibrary(bookTitleslib, isbn, status, statusnum);
        }
        else if (command == "O" || command == "o") {
            outputLibrary(bookTitleslib, isbn, status, statusnum);
        }
        else if (command == "P" || command == "p") {
            checkoutstats(bookTitleslib, isbn, status);
        }
        else if (command == "R" || command == "r") {
            removelibrary(bookTitleslib, isbn, status);
        }
        else if (command == "S" || command == "s") {
            searchlibrary(bookTitleslib, isbn, status);
        }
        

        cout << endl;
    } while (!(command == "x" || command == "X"));

    return 0;
}

// addItem function takes in 3 vectors, book title, ISBN, and status of book, and the user inputs the title and ISBN of the book.
// Since was the book was added, the status pushes back as "In Library".
// The title and ISBN vector pushes back the user input.
// The for loop is to see if the user input doesn't have any commas since it wasn't allowed, exiting the function.
void addItem(vector<string> &title, vector<string> &isbn, vector<string> &status) {
    string bookTitle, ISBN;
    cout << "What is the book title? " << endl;
    getline(cin, bookTitle);
    for (int i = 0; i < bookTitle.size(); i++) {
        if (bookTitle.at(i) == ',') {
            cout << "The book title cannot contain commas." << endl;
            return;
        }
    }
    cout << "What is the 13-digit ISBN (with hyphens)? " << ISBN << endl;
    getline(cin, ISBN);
    cout << "The Following Entry Was Added" << endl << "-----------------------------" << endl;
    cout << bookTitle << " --- " << ISBN << " --- In Library" << endl;
    title.push_back(bookTitle);
    isbn.push_back(ISBN);
    status.push_back("In Library");
}

// displayLibrary displays the title, ISBN, and the status of the book in the library, going through each line of the library with the book information using a for loop.
// If there were no books, then the output would let the user know there are no books to output. 
void displayLibrary(vector<string> &title, vector<string> &isbn, vector<string> &status) {
    cout << "Your Current Library" << endl << "--------------------" << endl;
    if (title.size() == 0) {
        cout << "The library has no books." << endl;
    } 
    else {
        for (size_t i = 0; i < title.size(); i++) {
            cout << title.at(i) << " --- " << isbn.at(i) << " --- " << status.at(i) << endl;
        }
    }
}

// clearLibrary uses the erase function to erase all of the book titles, ISBNS, and status in the library.
// The erase function starts from the beginning of the vector to the end of the vector.
void clearLibrary(vector<string> &title, vector<string> &isbn, vector<string> &status) {
    title.erase(title.begin(), title.begin()+title.size());
    isbn.erase(isbn.begin(), isbn.begin()+isbn.size());
    status.erase(status.begin(), status.begin()+status.size());
    cout << "Your library is now empty." << endl; 
}

// loadLibrary reads the filename from the user, uses a while loop to store all the information from the file to the vectors via string.
// the find function finds the strings from the file seperated by comma, so the first comma found means that the string before the comma is the title.
// the second comma via firstcomma + 1 is the ISBN, status is automatically the last part.
// There were strings for the title, ISBN, and status, where substr was used to capture the string between the commas.
// if condition was if there is a position for the first and second comma, then there was a title and ISBN in the file, but no status, hence status was given value based off of number.
// else if condition checked if there was only a title with no ISBN and status, hence they were given the default value.
// the vectors in the parameter pushed back the strings from the file.
// statusnum was used to store the number if the book has "Invalid State" for the outputLibrary function.
// if the input file didn't open, then the output pooped up.
// i was for the number of lines the vectors read in from the file.
void loadLibrary(vector<string> &title, vector<string> &isbn, vector<string> &status, vector<string> &statusnum) {
    string book;
    string isbns;
    string numrecord;
    string filename;
    string line;
    size_t startspace = 0; 
    int i = 0;
    cout << "What database to read from? ";
    getline(cin, filename);
    ifstream thefile(filename);
    cout << endl;
    if (!thefile) {
        cout << "Could not find the database file." << endl;
        return;
    }
    while (getline(thefile, line)) {
    int commafirst = line.find(',');
    int commasecond = line.find(',', commafirst + 1);
    
    if (commafirst != string::npos && commasecond != string::npos) {
        book = line.substr(0, commafirst);
        isbns = line.substr(commafirst + 2, commasecond - commafirst - 2);
        numrecord = line.substr(commasecond + 2);
        statusnum.push_back(numrecord);
        int statuss = stoi(numrecord); //used stoi to get the integer value of the stirng of the status.
        string record;
        if (statuss == 0) {
            numrecord = "In Library";
        } else if (statuss == 1) {
            numrecord = "Checked Out";
        } else if (statuss == 2) {
            numrecord = "On Loan";
        } else if (statuss == 3) {
            numrecord = "Unknown State";
        } else {
            record = to_string(statuss);
            numrecord = "Invalid State";
        }
        i++;
        title.push_back(book);
        isbn.push_back(isbns);
        status.push_back(numrecord);
    } else if (commafirst != string::npos && commasecond == string::npos) {
        book = line.substr(0, commafirst);
        isbns = line.substr(commafirst + 2);
        i++;
        title.push_back(book);
        isbn.push_back(isbns);
        status.push_back("In Library");
        statusnum.push_back("In Library");
    } else {
        book = line;
        i++;
        title.push_back(book);
        isbn.push_back("000-0-00-000000-0");
        status.push_back("In Library");
        statusnum.push_back("In Library");
    }
}   
    cout << "Read in " << i << " lines from the file." << endl;
}

// outputLibrary used a for loop to update the value of status from a string to a num.
// used statusnum vector if the status in the library was "Invalid State".
// made sure that the there were books in the library, hence, cheked if they weren't empty.
// for loop to print out each book info from the title, ISBN, and status vectors.
// closed the output file.
void outputLibrary(vector<string> &title, vector<string> &isbn, vector<string> &status, vector<string> &statusnum) {
    string filename;
    cout << "Where should the database output to? " << endl;
    getline(cin, filename);
    ofstream outfile(filename);
    for (size_t i = 0; i < title.size(); i++) {
        if (!title.empty() && !isbn.empty() && !status.empty()) {
            if (status.at(i) == "In Library") {
                status.at(i) = "0";
            }
            else if (status.at(i) == "Checked Out") {
                status.at(i) = "1";
            }
            else if (status.at(i) == "On Loan") {
                status.at(i) = "2";
            }
            else if (status.at(i) == "Unknown State") {
                status.at(i) = "3";
            }
            else if (status.at(i) == "Invalid State"){
                status.at(i) = statusnum.at(i);
            }
        }
    }
    for (size_t i = 0; i < title.size(); i++) {
         outfile << title.at(i) << ", " << isbn.at(i) << ", " << status.at(i) << endl;
    }
    outfile.close();
}

// checkoutstats checked the status for each book, and if it mathced depedning on the stautus, the amount of the status would be added.
// the stats of the type of status was then printed out.
void checkoutstats(vector<string> &title, vector<string> &isbn, vector<string> &status) {
    int totalbooks;
    totalbooks = title.size();
    int inlibrary = 0;
    int checkedout = 0;
    int onloan = 0;
    int unknown = 0;
    int other = 0;
    for (size_t i = 0; i < title.size(); i++) {
        if (status.at(i) == "In Library") {
            inlibrary++;
        }
        else if (status.at(i) == "Checked Out") {
            checkedout++;
        }
        else if (status.at(i) == "On Loan") {
            onloan++;
        }
        else if (status.at(i) == "Unknown State") {
            unknown++;
        }
        else if (status.at(i) == "Invalid State") {
            other++;
        }
    }
    cout << "Your Current Library's Stats" << endl << "----------------------------" << endl;
    cout << "Total Books: " << totalbooks << endl;
    cout << "   In Library: " << inlibrary << endl;
    cout << "   Checked Out: " << checkedout << endl;
    cout << "   On Loan: " << onloan << endl;
    cout << "   Unknown: " << unknown << endl;
    cout << "   Other: " << other << endl;

}

// searchlibrary takes the user choice if they want to search the library based off of title or ISBN.
// depending on the choice, the if statements received user input.
// if the search result matched the user input, then the book information printed out.
// used 2 counters to see if there was a match, which would print out the book information.
// used a reverse for loop to check the entries in the library from the back first in case the title or ISBN were the same in other entries in the library.
// else the match not found message appears.
void searchlibrary(vector<string> &title, vector<string> &isbn, vector<string> &status) {
    string book;
    string isbns;
    string choice;
    int counter1 = 0; 
    int counter2 = 0;
    cout << "Would you like to search by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, choice); 
    cout << endl;
    if ((choice == "1")) {
        cout << "Enter the book name: " << endl;
        getline(cin, book);
        cout << "The Following Are Your Search Results" << endl << "-------------------------------------" << endl;
    }
    else if ((choice == "2")) {
        cout << "Enter the book 13-digit ISBN (with dashes): " << endl; 
        getline(cin, isbns);
        cout << "The Following Are Your Search Results" << endl << "-------------------------------------" << endl;
    }
    else {
        cout << "Invalid search by choice option." << endl;
        return;
    }
    int index = -1;
    if (!title.empty()) {
    for (int i = title.size()-1; i >= 0; i--) {
        if (choice == "1") {
            if (book == title.at(i)) {
                index = i;
                counter1++;
                break;
            }
        }
        else if (choice == "2") {
            if (isbns == isbn.at(i)) {
                index = i;
                counter2++;
                break;
            }
        }
    }
    }
    if (counter1 == 1) {
        cout << title.at(index) << " --- " << isbn.at(index) << " --- " << status.at(index) << endl;
    }
    else if (counter2 == 1) {
        cout << title.at(index) << " --- " << isbn.at(index) << " --- " << status.at(index) << endl;
    }
    else {
        cout << "No matching entry found in the library." << endl;
    }
}

// removelibrary does the same as searchlibrary except it erases the specific index of the book if the title or ISBN matched with the user input.
void removelibrary(vector<string> &title, vector<string> &isbn, vector<string> &status) {
    string book;
    string isbns;
    string choice;
    int counter1 = 0; 
    int counter2 = 0;
    cout << "Would you like remove by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, choice); 
    cout << endl;
    if ((choice == "1")) {
        cout << "Enter the book name: " << endl;
        getline(cin, book);
        cout << "The Following Entry Was Removed From The Library" << endl << "------------------------------------------------" << endl;
    }
    else if ((choice == "2")) {
        cout << "Enter the book 13-digit ISBN (with dashes): " << endl; 
        getline(cin, isbns);
        cout << "The Following Entry Was Removed From The Library" << endl << "------------------------------------------------" << endl;
    }
    else {
        cout << "Invalid remove by choice option." << endl;
        return;
    }
    int index = -1;
    if (!title.empty()) {
    for (int i = title.size()-1; i >= 0; i--) {
        if (choice == "1") {
            if (book == title.at(i)) {
                index = i;
                counter1++;
                break;
            }
        }
        else if (choice == "2") {
            if (isbns == isbn.at(i)) {
                index = i;
                counter2++;
                break;
            }
        }
    }
    }
    if (counter1 == 1) {
        cout << title.at(index) << " --- " << isbn.at(index) << " --- " << status.at(index) << endl;
        title.erase(title.begin()+index);
        isbn.erase(isbn.begin()+index);
        status.erase(status.begin()+index);
    }
    else if (counter2 == 1) {
        cout << title.at(index) << " --- " << isbn.at(index) << " --- " << status.at(index) << endl;
        title.erase(title.begin()+index);
        isbn.erase(isbn.begin()+index);
        status.erase(status.begin()+index);
    }
    else {
        cout << "No matching entry found in the library." << endl;
    }
}

// printinvalidentries checks all the invlid entries in the library.
// if there are no books, the message outputs.
// for loop to run through the following conditons: 
// if status at the book in the vector status is "Invalid State".
// else if the total number of digits in the ISBN doesn't equal 13 (used a for loop with an empty string, added the string with each ISBN string value, took out the hyphens to get the numbers only).
// else statement that check the 13 digit ISBN rule, where the first 12 digits is mutiplied every other time by 1, then 3.
// used a for loop using if the index is odd or even, and mutiplying the number by 1 if even, 3 if odd, kept the total by adding it, and then dividing by 10, and then subtracting 10 and the remainder. the number - '0' makes a string to an int.
// counter was used to see if an error occured, if it did, then the output message for no errors wouldn't output, else if counter wasn't updated, then the no invalid entries was outputted. 
void printinvalidentries(vector<string> &title, vector<string> &isbn, vector<string> &status) {
    cout << "The Following Library Entries Have Invalid Data" << endl << "-----------------------------------------------" << endl;
    string convert;
    vector<int> isbnnums;
    int isbnnum;
    int counter = 0;
    if (title.size() == 0) {
        cout << "The library has no books." << endl;
        counter++;
    }
    for (int i = 0; i < title.size(); i++) {
        string isbncopy = isbn.at(i);
        int total12 = 0;
        string result = "";
        for (size_t i = 0; i < isbncopy.length(); ++i) {
            if (isbncopy.at(i) != '-') {
                result += isbncopy.at(i);
            }
        }
        for (int k = 0; k < 12; k++) {
                if (k % 2 == 0) {
                    total12 += (result.at(k) - '0');
                }
                else if (k % 2 == 1) {
                    total12 += ((result.at(k) - '0')*3);
                }
            }
            total12 = total12 % 10;
            total12 = 10 - total12;
        if (status.at(i) == "Invalid State") {
            counter++;
            cout << title.at(i) << " --- " << isbn.at(i) << " --- " << status.at(i) << endl;
        }
        else if (result.length() != 13) {
            counter++;
            cout << title.at(i) << " --- " << isbn.at(i) << " --- " << status.at(i) << endl;
        }
        else if (total12 != (result.at(12) - '0')) {
                counter++;
                cout << title.at(i) << " --- " << isbn.at(i) << " --- " << status.at(i) << endl;
        }
    }
    if (counter == 0) {
        cout << "The library has no invalid entries." << endl;
    }
}

/// @brief print out the main menu of the management system
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}