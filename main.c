#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Student {
    int id;
    char name[50];
    float marks;
};

struct Student students[MAX];
int count = 0;


void addStudent();
void capitalizeName(char *name);
void viewStudents();
void saveToFile();
void loadFromFile();

int main() {
    int choice;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Save to File\n");
        printf("4. Load from File\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: saveToFile(); break;
            case 4: loadFromFile(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addStudent() {
    if (count >= MAX) {
        printf("Student list is full!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &students[count].id);

    printf("Enter Name: ");
    getchar(); 
    fgets(students[count].name, sizeof(students[count].name), stdin);

    
    students[count].name[strcspn(students[count].name, "\n")] = 0;

   
    capitalizeName(students[count].name);

    printf("Enter Marks: ");
    scanf("%f", &students[count].marks);

    count++;
    printf("Student added successfully!\n");
}

void capitalizeName(char *name) {
    int i = 0;

   
    if (name[0] >= 'a' && name[0] <= 'z') {
        name[0] = name[0] - 32;
    }

    
    while (name[i] != '\0') {
        if (name[i] == ' ' && name[i + 1] >= 'a' && name[i + 1] <= 'z') {
            name[i + 1] = name[i + 1] - 32;
        }
        i++;
    }
}

void viewStudents() {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Marks: %.2f\n",
               students[i].id,
               students[i].name,
               students[i].marks);
    }
}

void saveToFile() {
    FILE *fp = fopen("students.txt", "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %f\n",
                students[i].id,
                students[i].name,
                students[i].marks);
    }

    fclose(fp);
    printf("Data saved to file successfully!\n");
}

void loadFromFile() {
    FILE *fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    count = 0;

    while (fscanf(fp, "%d %s %f",
                  &students[count].id,
                  students[count].name,
                  &students[count].marks) != EOF) {
        count++;
    }

    fclose(fp);
    printf("Data loaded from file successfully!\n");
}