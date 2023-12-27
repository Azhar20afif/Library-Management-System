#include <iostream>
#include <string>

using namespace std;

// Node for linked list
struct StudentNode {
    string name;
    int reg;
    StudentNode* next;
};

// Node for binary search tree
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

public:
    LibraryManagementSystem() : studentList(nullptr), bookTree(nullptr) {}

    // Function to add a student to the linked list
    void addStudent(string name, int reg) {
        StudentNode* newNode = new StudentNode{ name, reg, nullptr };
        // Add at the beginning of the list for simplicity
        newNode->next = studentList;
        studentList = newNode;
    }

    // Function to display students using merge sort
    // (Merge sort implementation not included for brevity)
    void displayStudents() {
        // Implement merge sort to sort students by name
        // Display the sorted list
    }

    // Function to remove a student from the linked list
    void removeStudent(int reg) {
        // Implement code to remove a student by registration number
    }

    // Function to add a book to the binary search tree
    void addBook(string title, string author) {
        bookTree = insertBook(bookTree, title, author);
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
    }

    // Recursive function to delete a book from the BST
    BookNode* deleteBookNode(BookNode* root, string title) {
        // Implement code to delete a book by title
        return root;
    }

    // Other functions like checkOutBook and returnBook can be added as needed
};

int main() {
    LibraryManagementSystem library;

    // Adding students
    library.addStudent("John Doe", 123);
    library.addStudent("Alice Smith", 456);
    library.addStudent("Bob Johnson", 789);

    // Displaying students
    cout << "Students:" << endl;
    library.displayStudents();

    // Adding books
    library.addBook("Introduction to Programming", "Jane Doe");
    library.addBook("Data Structures and Algorithms", "Bob Smith");
    library.addBook("Database Management", "Alice Johnson");

    // Displaying books
// Displaying books
cout << "\nBooks:" << endl;
   library.displayBooks(library.bookTree);


    // Removing a student
    library.removeStudent(456);

    // Deleting a book
    library.deleteBook("Data Structures and Algorithms");

    // Displaying updated students and books
    cout << "\nUpdated Students:" << endl;
    library.displayStudents();

    cout << "\nUpdated Books:" << endl;
    library.displayBooks(library.bookTree);

    return 0;
}
