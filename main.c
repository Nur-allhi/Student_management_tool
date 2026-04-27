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


int getSafeInt();
void searchStudent();
void addStudent();
void capitalizeName(char *name);
void viewStudents();
void saveToFile();
void loadFromFile();
void deleteStudent();
void editStudent();

int main() {
    int choice;

    loadFromFile();

    while (1) {
        printf("\n--- Student Management System ---\n");
        
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Save to File\n");
        printf("4. Load from File\n");
        printf("5. Search Student by ID\n");
        printf("6. Edit Student\n");
        printf("7. Delete Student\n");  
        printf("8. Exit\n");
        printf("Enter choice: ");
        choice = getSafeInt();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: saveToFile(); break;
            case 4: loadFromFile(); break;
            case 5: searchStudent(); break;
            case 6: editStudent(); break;
            case 7: deleteStudent(); break;
            case 8: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

int getSafeInt() {
    char buffer[20];
    int value;
    int isValid = 0;

    while (!isValid) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
           
            buffer[strcspn(buffer, "\n")] = 0;

           
            if (strlen(buffer) == 0) {
                printf("Input cannot be empty. Try again: ");
                continue;
            }

            
            isValid = 1;
            for (int i = 0; i < strlen(buffer); i++) {
                if (buffer[i] < '0' || buffer[i] > '9') {
                    isValid = 0;
                    break;
                }
            }

            if (isValid) {
                value = atoi(buffer);
                return value;
            } else {
                printf("Invalid input! Please enter a number: ");
            }
        }
    }
    return 0;
}

int isValidName(char *name) {
    if (strlen(name) == 0) return 0; // Empty check

    for (int i = 0; i < strlen(name); i++) {
        // Allow letters (A-Z, a-z) and spaces
        if (!((name[i] >= 'a' && name[i] <= 'z') || 
              (name[i] >= 'A' && name[i] <= 'Z') || 
               name[i] == ' ')) {
            return 0; // Found a number or symbol
        }
    }
    return 1;
}

float getSafeFloat() {
    char buffer[20];
    float value;
    int isValid = 0;

    while (!isValid) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            buffer[strcspn(buffer, "\n")] = 0;

            if (strlen(buffer) == 0) {
                printf("Input cannot be empty. Try again: ");
                continue;
            }

            int dotCount = 0;
            isValid = 1;
            for (int i = 0; i < strlen(buffer); i++) {
                if (buffer[i] == '.') {
                    dotCount++;
                } else if (buffer[i] < '0' || buffer[i] > '9') {
                    isValid = 0;
                    break;
                }
            }

            // A valid float can have at most one decimal point
            if (isValid && dotCount <= 1) {
                value = atof(buffer); // Convert string to float
                return value;
            } else {
                printf("Invalid marks! Please enter a valid number (e.g., 85.5): ");
                isValid = 0; // Reset to keep looping
            }
        }
    }
    return 0.0f;
}


void addStudent() {
    if (count >= MAX) {
        printf("Student list is full!\n");
        return;
    }

    // 1. ID Validation (Already implemented)
    printf("Enter ID: ");
    int tempId = getSafeInt();
    if (tempId <= 0) {
        printf("Invalid ID. Cancelled.\n");
        return;
    }

    // 2. Name Validation (New Logic)
    char tempName[50];
    int nameOk = 0;
    while (!nameOk) {
        printf("Enter Name (Alphabets only): ");
        fgets(tempName, sizeof(tempName), stdin);
        tempName[strcspn(tempName, "\n")] = 0;

        if (isValidName(tempName)) {
            nameOk = 1;
        } else {
            printf("Invalid Name! Use only letters and spaces.\n");
        }
    }

    // 3. Marks Validation (Already implemented)
    printf("Enter Marks (0-100): ");
    float tempMarks = getSafeFloat();
    if (tempMarks < 0 || tempMarks > 100) {
        printf("Invalid Marks. Cancelled.\n");
        return;
    }

    // All checks passed -> Assign and Save
    students[count].id = tempId;
    strcpy(students[count].name, tempName);
    capitalizeName(students[count].name);
    students[count].marks = tempMarks;

    count++;
    printf("Student added successfully!\n");
    saveToFile(); 
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
        fprintf(fp, "%d|%s|%.2f\n",
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

    char line[100];
    count = 0;

    while (fgets(line, sizeof(line), fp) && count < MAX) {
        sscanf(line, "%d|%49[^|]|%f",
               &students[count].id,
               students[count].name,
               &students[count].marks);

        count++;
    }

    fclose(fp);
    printf("Data loaded from file successfully!\n");
}

void searchStudent() {
    if (count == 0) {
        printf("No students available.\n");
        return;
    }

    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\nStudent Found:\n");
            printf("ID: %d | Name: %s | Marks: %.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void editStudent() {
    if (count == 0) {
        printf("No students available to edit.\n");
        return;
    }

    int id, found = 0;
    printf("Enter Student ID to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Current Data - Name: %s, Marks: %.2f\n", students[i].name, students[i].marks);
            
            printf("Enter New Name: ");
            getchar();
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            capitalizeName(students[i].name);

            printf("Enter New Marks: ");
            scanf("%f", &students[i].marks);

            printf("Student record updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("Student ID %d not found.\n", id);
    saveToFile();

}

void deleteStudent() {
    if (count == 0) {
        printf("No students available to delete.\n");
        return;
    }

    int id, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            found = 1;
            
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            printf("Student deleted successfully!\n");
            break;
        }
    }

    if (!found) printf("Student ID %d not found.\n", id);
    saveToFile();
}