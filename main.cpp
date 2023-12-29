#include <iostream>
#include <string>

using namespace std;

struct StudentNode {
    string name;
    int reg;
    StudentNode* next;
};

struct BookNode {
    string title;
    string author;
    BookNode* left;
    BookNode* right;
};

class LibraryManagementSystem {
public:
    StudentNode* studentList;
    BookNode* bookTree;

    LibraryManagementSystem() : studentList(nullptr), bookTree(nullptr) {}
    void addStudent(string name, int reg) {
        StudentNode* newNode = new StudentNode{name, reg, nullptr };
        newNode->next = studentList;
        studentList = newNode;
    }
void merge(StudentNode* &head, StudentNode* left, StudentNode* right) {
    StudentNode* temp = nullptr;
    StudentNode* current = nullptr;

    while (left != nullptr && right != nullptr) {
        if (left->name < right->name) {
            if (temp == nullptr) {
                temp = left;
                current = left;
            } else {
                current->next = left;
                current = left;
            }
            left = left->next;
        } else {
            if (temp == nullptr) {
                temp = right;
                current = right;
            } else {
                current->next = right;
                current = right;
            }
            right = right->next;
        }
    }

    if (left != nullptr) {
        current->next = left;
    }

    if (right != nullptr) {
        current->next = right;
    }

    head = temp;
}

void mergeSort(StudentNode* &head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    StudentNode* middle = head;
    StudentNode* fast = head->next;
    while(fast != nullptr && fast->next != nullptr) {
        middle = middle->next;
        fast = fast->next->next;
    }
    StudentNode* left = head;
    StudentNode* right = middle->next;
    middle->next = nullptr;

    mergeSort(left);
    mergeSort(right);

    merge(head, left, right);
}


void displayStudents() {

    mergeSort(studentList);
    StudentNode* current = studentList;
    while (current != nullptr) {
        cout << "Student ka Naam: " << current->name << ", Student Reg: " << current->reg << endl;
        current = current->next;
    }
}
void removeStudent(int reg) {
        StudentNode* current = studentList;
        StudentNode* prev = nullptr;
        while(current != nullptr && current->reg != reg) {
            prev = current;
            current = current->next;
        }
        if(current == nullptr) {
            cout << "Student doesnt exist." << endl;
            return;
        }
        if (prev == nullptr) {
            studentList = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        cout << "Student removed successfully." << endl;
    }
void addBook(string title, string author) {
        bookTree = insertBook(bookTree, title, author);
        cout << "Book added successfully." << endl;
    }

BookNode* insertBook(BookNode* root, string title, string author) {
        if (root == nullptr) {
            return new BookNode{ title, author, nullptr, nullptr };
        }
        if (title < root->title) {
            root->left = insertBook(root->left, title, author);
        } else if (title > root->title) {
            root->right = insertBook(root->right, title, author);
        }

        return root;
    }
void displayBooks(BookNode* root) {
        if (root != nullptr) {
            displayBooks(root->left);
            cout << "Title of book: " << root->title << ", Author of book: " << root->author << endl;
            displayBooks(root->right);
        }
    }

void deleteBook(string title) {
        bookTree = deleteBookNode(bookTree, title);
        cout << "Book deleted successfully." << endl;
    }

BookNode* deleteBookNode(BookNode* root, string title) {
        if (root == nullptr) {
            return root;
        }

        if (title < root->title) {
            root->left = deleteBookNode(root->left, title);
        } else if (title > root->title) {
            root->right = deleteBookNode(root->right, title);
        } else {

            if (root->left == nullptr) {
                BookNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BookNode* temp = root->left;
                delete root;
                return temp;
            }
            BookNode* temp = findMin(root->right);
            root->title = temp->title;
            root->author = temp->author;
            root->right = deleteBookNode(root->right, temp->title);
        }

        return root;
    }

BookNode* findMin(BookNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};
void assignBookToStudent(LibraryManagementSystem& library);
void returnBook(LibraryManagementSystem& library);
void displayMenu();
void performOperation(LibraryManagementSystem& library, int choice);
StudentNode* findStudentByReg(StudentNode* head, int reg) {
    StudentNode* current = head;
    while (current != nullptr) {
        if (current->reg == reg) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
BookNode* findBookByTitle(BookNode* root, string title) {
    if (root == nullptr) {
        return nullptr;
    }

    if (title < root->title) {
        return findBookByTitle(root->left, title);
    } else if (title > root->title) {
        return findBookByTitle(root->right, title);
    } else {
        return root; 
    }
}
void assignBookToStudent(LibraryManagementSystem& library) {
    int reg;
    cout << "Enter students reg num: ";
    cin >> reg;

    StudentNode* student = findStudentByReg(library.studentList, reg);

    if (student == nullptr) {
        cout << "Student was not found, Book cannot be assigned" << endl;
        return;
    }
    string title;
    cout << "Enter book title to assign: ";
    cin.ignore();
    getline(cin, title);

    BookNode* book = findBookByTitle(library.bookTree, title);

    if (book == nullptr) {
        cout << "Book was not found. Book cannot be assigned" << endl;
        return;
    }
    cout << "Book assigned successfully to " << student->name << "." << endl;
}
void returnBook(LibraryManagementSystem& library) {
    int reg;
    cout << "Enter student registration number: ";
    cin >> reg;

    StudentNode* student = findStudentByReg(library.studentList, reg);

    if (student == nullptr) {
        cout << "Student not found. Return failed." << endl;
        return;
    }

    string title;
    cout << "Enter book title to return: ";
    cin.ignore();
    getline(cin, title);

    BookNode* book = findBookByTitle(library.bookTree, title);

    if (book == nullptr) {
        cout << "Book not found. Return failed." << endl;
        return;
    }
    cout << "Book returned successfully by " << student->name << "." << endl;
}

void displayMenu();
void performOperation(LibraryManagementSystem& library, int choice);

int main() {
    LibraryManagementSystem library;

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 8) {
            performOperation(library, choice);
        } else if (choice != 0) {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    cout << "\n\t\t\t\t\t\t\033[1;36mGIKI LIBRARY MANAGEMENT SYSTEM:\033[0m\n"; 
    cout << "\n\t\t\t\t\t\t\033[1;36mBY AZHAR , ALI , HAMZA AND WADOOD\033[0m\n"; 
    cout << "\033[1;33m1. Add Student\n\033[0m";  
    cout << "\033[1;33m2. Remove Student\n\033[0m";  
    cout << "\033[1;33m4. Delete Book\n\033[0m";  
    cout << "\033[1;33m5. Display Students\n\033[0m"; 
    cout << "\033[1;33m6. Display Books\n\033[0m";  
    cout << "\033[1;33m7. Assign Book to Student\n\033[0m";  
    cout << "\033[1;33m8. Return Book\n\033[0m";  
    cout << "\033[1;33m0. Exit\n\033[0m";  
}



void performOperation(LibraryManagementSystem& library, int choice) {
    switch (choice) {
        case 1: {
            string name;
            int reg;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter their reg number: ";
            cin >> reg;
            library.addStudent(name, reg);
            break;
        }
        case 2: {
            int reg;
            cout << "The reg number of the student that has to be removed: ";
            cin >> reg;
            library.removeStudent(reg);
            break;
        }
        case 3: {
            string title, author;
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            library.addBook(title, author);
            break;
        }
        case 4: {
            string title;
            cout << "Enter the title of the book to delete: ";
            cin.ignore();
            getline(cin, title);
            library.deleteBook(title);
            break;
        }
        case 5: {
            cout << "\nStudents:\n";
            library.displayStudents();
            break;
        }
        case 6: {
            cout << "\nBooks:\n";
            library.displayBooks(library.bookTree);
            break;
        }
          case 7: {
            assignBookToStudent(library);
            break;
        }

        case 8: {
            returnBook(library);
            break;
        }
        default:
            break;
    }
}
