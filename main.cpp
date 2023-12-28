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

    // Function to add a student to the linked list
    void addStudent(string name, int reg) {
        StudentNode* newNode = new StudentNode{ name, reg, nullptr };
        newNode->next = studentList;
        studentList = newNode;
    }

    // Function to display students using merge sort
    void displayStudents() {
        // Implement merge sort to sort students by name
        // Display the sorted list
    }

    // Function to remove a student from the linked list
    void removeStudent(int reg) {
        StudentNode* current = studentList;
        StudentNode* prev = nullptr;

        while (current != nullptr && current->reg != reg) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Student not found." << endl;
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

    // Function to add a book to the binary search tree
    void addBook(string title, string author) {
        bookTree = insertBook(bookTree, title, author);
        cout << "Book added successfully." << endl;
    }

    // Recursive function to insert a book into the BST
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

    // Function to display books using inorder traversal
    void displayBooks(BookNode* root) {
        if (root != nullptr) {
            displayBooks(root->left);
            cout << "Title: " << root->title << ", Author: " << root->author << endl;
            displayBooks(root->right);
        }
    }

    // Function to delete a book from the binary search tree
    void deleteBook(string title) {
        bookTree = deleteBookNode(bookTree, title);
        cout << "Book deleted successfully." << endl;
    }

    // Recursive function to delete a book from the BST
    BookNode* deleteBookNode(BookNode* root, string title) {
        if (root == nullptr) {
            return root;
        }

        if (title < root->title) {
            root->left = deleteBookNode(root->left, title);
        } else if (title > root->title) {
            root->right = deleteBookNode(root->right, title);
        } else {
            // Node with only one child or no child
            if (root->left == nullptr) {
                BookNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BookNode* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children
            BookNode* temp = findMin(root->right);
            root->title = temp->title;
            root->author = temp->author;
            root->right = deleteBookNode(root->right, temp->title);
        }

        return root;
    }

    // Function to find the node with the minimum value in a BST
    BookNode* findMin(BookNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

// Function prototypes
void displayMenu();
void performOperation(LibraryManagementSystem& library, int choice);

int main() {
    LibraryManagementSystem library;

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 6) {
            performOperation(library, choice);
        } else if (choice != 0) {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    cout << "\nLibrary Management System Menu:\n";
    cout << "1. Add Student\n";
    cout << "2. Remove Student\n";
    cout << "3. Add Book\n";
    cout << "4. Delete Book\n";
    cout << "5. Display Students\n";
    cout << "6. Display Books\n";
    cout << "0. Exit\n";
}

void performOperation(LibraryManagementSystem& library, int choice) {
    switch (choice) {
        case 1: {
            string name;
            int reg;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter registration number: ";
            cin >> reg;
            library.addStudent(name, reg);
            break;
        }
        case 2: {
            int reg;
            cout << "Enter registration number of the student to remove: ";
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
        default:
            break;
    }
}
