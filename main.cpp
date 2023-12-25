#include <iostream>
#include <string>

using namespace std;

struct Student {
   string Name;
   int Reg;
};

class Listnode {
public:
   Student st;
   Listnode *next;

   Listnode(Student s) {
       st = s;
       next = NULL;
   }
};

void insertStudent(Listnode** head, Student student) {
   Listnode* newNode = new Listnode(student);

   if (*head == nullptr) {
       *head = newNode;
       return;
   }

   Listnode* current = *head;
   while (current->next != nullptr) {
       current = current->next;
   }
   current->next = newNode;
}

Student getStudentInfo() {
   string name;
   int reg;

   cout << "Enter student name (or 'quit' to exit): ";
   getline(cin, name);

   if (name == "quit") {
       exit(0);
   }

   cout << "Enter student registration number: ";
   cin >> reg;

   return {name, reg};
}

void addStudentToList(Listnode* array[26]) {
   Student student = getStudentInfo();
   int index = tolower(student.Name[0]) - 'a';
   insertStudent(&array[index], student);
   cout << "Student added successfully!\n";
   cin.ignore();
}

int main() {
   Listnode* array[26] = {nullptr};

   while (true) {
       addStudentToList(array);
   }

   return 0;
}
