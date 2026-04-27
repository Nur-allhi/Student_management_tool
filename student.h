#ifndef STUDENT_H
#define STUDENT_H

#define MAX 100

struct Student {
    int id;
    char name[50];
    float marks;
};

// Extern allows multiple files to see the same global variables
extern struct Student students[MAX];
extern int count;

// Function Prototypes
void addStudent();
void viewStudents();
void searchStudent();
void editStudent();
void deleteStudent();
void sortStudents();
void capitalizeName(char *name);
void saveToFile();
void loadFromFile();

// Helper/Validation Prototypes
int getSafeInt(int allowBack);
float getSafeFloat();
int isValidName(char *name);

#endif