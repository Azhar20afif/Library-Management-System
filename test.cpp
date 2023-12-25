#include <iostream>
#include <string>
using namespace std;

struct Book {
    string Title;
    string Author;
    int ISBN;
};

struct TreeNode {
    Book data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Book& book) : data(book), left(nullptr), right(nullptr) {}
};

class LibrarySystem {
private:
    static const int MAX_BOOKS = 100;
    Book* books;
    int numBooks;

    TreeNode* root; // Root of the Binary Search Tree

public:
    // Constructors and Destructor
    LibrarySystem() : books(new Book[MAX_BOOKS]), numBooks(0), root(nullptr) {}

    ~LibrarySystem() {
        delete[] books;
        deleteTree(root);
    }

    // Binary Search Tree Operations
    void insertBST(const Book& book);
    TreeNode* insertBSTRec(TreeNode* root, const Book& book);
    void deleteTree(TreeNode*& root);

    // Sorting Operations
    void merge(int left, int mid, int right);
    void mergeSort(int left, int right);

    // Book Management Operations
    void addBook();
    int searchBook(const string& title);
    void displayBookDetails(int index);

    // Display Operations
    void displayAllBooks();
};

// Binary Search Tree Operations
void LibrarySystem::insertBST(const Book& book) {
    root = insertBSTRec(root, book);
}

TreeNode* LibrarySystem::insertBSTRec(TreeNode* root, const Book& book) {
    if (root == nullptr) {
        return new TreeNode(book);
    }

    if (book.Title < root->data.Title) {
        root->left = insertBSTRec(root->left, book);
    } else {
        root->right = insertBSTRec(root->right, book);
    }

    return root;
}

void LibrarySystem::deleteTree(TreeNode*& root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

// Sorting Operations
void LibrarySystem::merge(int left, int mid, int right) {
    // Merge Sort Implementation
    // ...
}

void LibrarySystem::mergeSort(int left, int right) {
    // Merge Sort Implementation
    // ...
}

// Book Management Operations
void LibrarySystem::addBook() {
    if (numBooks < MAX_BOOKS) {
        cout << "Enter book title: ";
        cin >> books[numBooks].Title;
        cout << "Enter book author: ";
        cin >> books[numBooks].Author;
        cout << "Enter book ISBN: ";
        cin >> books[numBooks].ISBN;

        // Insert into BST
        insertBST(books[numBooks]);

        numBooks++;
    } else {
        cout << "Library is full, cannot add more books." << endl;
    }
}

int LibrarySystem::searchBook(const string& title) {
    int left = 0;
    int right = numBooks - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (books[mid].Title == title)
            return mid;

        if (books[mid].Title < title)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void LibrarySystem::displayBookDetails(int index) {
    if (index != -1) {
        cout << "Book found!\n";
        cout << "Title: " << books[index].Title << endl;
        cout << "Author: " << books[index].Author << endl;
        cout << "ISBN: " << books[index].ISBN << endl;
    } else {
        cout << "Book not found.\n";
    }
}

// Display all books in BST
void displayBST(TreeNode* root) {
    if (root != nullptr) {
        displayBST(root->left);
        cout << "Title: " << root->data.Title << ", Author: " << root->data.Author << ", ISBN: " << root->data.ISBN << endl;
        displayBST(root->right);
    }
}

void LibrarySystem::displayAllBooks() {
    cout << "Displaying all books in the library:\n";
    displayBST(root);
}

int main() {
    LibrarySystem librarySystem;

    // Add data of 5 books to the library
    for (int i = 0; i < 5; i++) {
        cout << "Enter data for book " << i + 1 << ":\n";
        librarySystem.addBook();
    }

    // Display all books in the library
    cout << "\nDisplaying all books in the library:\n";
    librarySystem.displayAllBooks();

    // Search for a book entered by the user
    string searchTitle;
    cout << "\nEnter the title of the book to search: ";
    cin >> searchTitle;

    int searchResult = librarySystem.searchBook(searchTitle);

    librarySystem.displayBookDetails(searchResult);

    return 0;

}