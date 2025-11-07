#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    int copies;

public:
    // Constructor
    Book(string t, string a, string i, int c)
        : title(t), author(a), isbn(i), copies(c) {}

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    int getCopies() const { return copies; }

    // Setters
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setCopies(int c) { copies = c; }

    // Display
    void display() const {
        cout << left << setw(25) << title
             << setw(20) << author
             << setw(15) << isbn
             << setw(10) << copies << "\n";
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(const Book& book) {
        auto it = find_if(books.begin(), books.end(), [&](Book& b) {
            return b.getISBN() == book.getISBN();
        });

        if (it != books.end()) {
            cout << "Book with same ISBN exists. Updating details.\n";
            it->setTitle(book.getTitle());
            it->setAuthor(book.getAuthor());
            it->setCopies(book.getCopies());
        } else {
            books.push_back(book);
            cout << "Book added successfully.\n";
        }
    }

    void removeBook(const string& isbn) {
        auto it = remove_if(books.begin(), books.end(), [&](Book& b) {
            return b.getISBN() == isbn;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book removed successfully.\n";
        } else {
            cout << "No book found with that ISBN.\n";
        }
    }

    void searchByTitle(const string& title) {
        bool found = false;
        for (auto& b : books) {
            if (b.getTitle() == title) {
                b.display();
                found = true;
            }
        }
        if (!found)
            cout << "No book found with that title.\n";
    }

    void searchByAuthor(const string& author) {
        bool found = false;
        for (auto& b : books) {
            if (b.getAuthor() == author) {
                b.display();
                found = true;
            }
        }
        if (!found)
            cout << "No book found with that author.\n";
    }

    void searchByISBN(const string& isbn) {
        auto it = find_if(books.begin(), books.end(), [&](Book& b) {
            return b.getISBN() == isbn;
        });

        if (it != books.end())
            it->display();
        else
            cout << "No book found with that ISBN.\n";
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "Library is empty.\n";
            return;
        }

        sort(books.begin(), books.end(), [](Book& a, Book& b) {
            return a.getTitle() < b.getTitle();
        });

        cout << left << setw(25) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(10) << "Copies" << "\n";
        cout << string(70, '-') << "\n";

        for (auto& b : books) {
            b.display();
        }
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n====== Mini Library Management System ======\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book by ISBN\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by Author\n";
        cout << "5. Search Book by ISBN\n";
        cout << "6. Display All Books\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        string title, author, isbn;
        int copies;

        switch (choice) {
        case 1:
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            cout << "Enter Number of Copies: ";
            cin >> copies;
            lib.addBook(Book(title, author, isbn, copies));
            break;

        case 2:
            cout << "Enter ISBN to remove: ";
            getline(cin, isbn);
            lib.removeBook(isbn);
            break;

        case 3:
            cout << "Enter Title to search: ";
            getline(cin, title);
            lib.searchByTitle(title);
            break;

        case 4:
            cout << "Enter Author to search: ";
            getline(cin, author);
            lib.searchByAuthor(author);
            break;

        case 5:
            cout << "Enter ISBN to search: ";
            getline(cin, isbn);
            lib.searchByISBN(isbn);
            break;

        case 6:
            lib.displayBooks();
            break;

        case 7:
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
