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


int getSafeInt(int allowBack);
void searchStudent();
void addStudent();
void capitalizeName(char *name);
void sortStudents();
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
        printf("8. Sort Students\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        choice = getSafeInt(0);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: saveToFile(); break;
            case 4: loadFromFile(); break;
            case 5: searchStudent(); break;
            case 6: editStudent(); break;
            case 7: deleteStudent(); break;
            case 8: sortStudents(); break;
            case 9: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

int getSafeInt(int allowBack) {
    char buffer[20];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            buffer[strcspn(buffer, "\n")] = 0;

            if (strlen(buffer) == 0) continue;

            // Check if user wants to go back
            if (allowBack && (strcmp(buffer, "0") == 0)) {
                return -1; // We use -1 as a special 'Back' signal
            }

            // Standard digit validation
            int isValid = 1;
            for (int i = 0; i < strlen(buffer); i++) {
                if (buffer[i] < '0' || buffer[i] > '9') {
                    isValid = 0;
                    break;
                }
            }

            if (isValid) return atoi(buffer);
            printf("Invalid input! (Enter '0' to cancel): ");
        }
    }
}

int isValidName(char *name) {
    if (strlen(name) == 0) return 0; 

    for (int i = 0; i < strlen(name); i++) {
        
        if (!((name[i] >= 'a' && name[i] <= 'z') || 
              (name[i] >= 'A' && name[i] <= 'Z') || 
               name[i] == ' ')) {
            return 0; 
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

           
            if (isValid && dotCount <= 1) {
                value = atof(buffer); 
                return value;
            } else {
                printf("Invalid marks! Please enter a valid number (e.g., 85.5): ");
                isValid = 0; 
            }
        }
    }
    return 0.0f;
}


void addStudent() {

    printf("Enter ID (or 0 to go back): ");
    int tempId = getSafeInt(1); // 1 means we allow the 'back' option
    
    if (tempId == -1) {
        printf("Returning to main menu...\n");
        return; 
    }

    if (count >= MAX) {
        printf("Student list is full!\n");
        return;
    }

    if (tempId <= 0) {
        printf("Invalid ID. Cancelled.\n");
        return;
    }

    
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

    
    printf("Enter Marks (0-100): ");
    float tempMarks = getSafeFloat();
    if (tempMarks < 0 || tempMarks > 100) {
        printf("Invalid Marks. Cancelled.\n");
        return;
    }

    
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

void sortStudents() {
    if (count < 2) {
        printf("Not enough students to sort.\n");
        return;
    }

    printf("\nSort by:\n1. ID (Ascending)\n2. Marks (Descending)\nEnter choice: ");
    int sortChoice = getSafeInt(1);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int swapNeeded = 0;

            if (sortChoice == 1) {
                if (students[j].id > students[j + 1].id) swapNeeded = 1;
            } else if (sortChoice == 2) {
                if (students[j].marks < students[j + 1].marks) swapNeeded = 1;
            }

            if (swapNeeded) {
                // Swapping the entire struct
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Students sorted successfully! (View list to see changes)\n");
    // We don't auto-save here unless you want the file permanently reordered
}

void viewStudents() {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\n------------------------------------------------------------\n");
    printf("%-10s | %-30s | %-10s\n", "ID", "Name", "Marks");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d | %-30s | %-10.2f\n", 
               students[i].id, 
               students[i].name, 
               students[i].marks);
    }
    printf("------------------------------------------------------------\n");
    printf("Total Students: %d\n", count);
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
        printf("No students to edit.\n");
        return;
    }

    printf("Enter Student ID to edit (or 0 to go back): ");
    int id = getSafeInt(1); // Enable 'back' logic

    if (id == -1) {
        printf("Returning to main menu...\n");
        return;
    }

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student ID %d not found.\n", id);
        return;
    }

    printf("\nEditing Student: %s (ID: %d)\n", students[index].name, students[index].id);

    // 1. Edit Name
    char tempName[50];
    printf("Enter new name (or '0' to keep current: %s): ", students[index].name);
    fgets(tempName, sizeof(tempName), stdin);
    tempName[strcspn(tempName, "\n")] = 0;

    if (strcmp(tempName, "0") != 0 && strlen(tempName) > 0) {
        if (isValidName(tempName)) {
            strcpy(students[index].name, tempName);
            capitalizeName(students[index].name);
        } else {
            printf("Invalid name format. Name not updated.\n");
        }
    }

    // 2. Edit Marks
    printf("Enter new marks (or -1 to keep current: %.2f): ", students[index].marks);
    float tempMarks = getSafeFloat();

    if (tempMarks != -1) {
        if (tempMarks >= 0 && tempMarks <= 100) {
            students[index].marks = tempMarks;
        } else {
            printf("Invalid marks range. Marks not updated.\n");
        }
    }

    printf("Record updated successfully!\n");
    saveToFile();
}

void deleteStudent() {
    if (count == 0) {
        printf("No students available to delete.\n");
        return;
    }

    printf("Enter Student ID to delete: ");
    int id = getSafeInt(1); // 1 means we allow the 'back' option
    int found = -1;

    // Find the index
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Show what is about to be deleted
        printf("\nFound: ID: %d | Name: %s\n", students[found].id, students[found].name);
        printf("Are you sure you want to delete this record? (y/n): ");
        
        char confirm;
        scanf(" %c", &confirm); // Note the space before %c to skip any leftover newline
        getchar(); // Clean the buffer

        if (confirm == 'y' || confirm == 'Y') {
            for (int j = found; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            printf("Student deleted successfully!\n");
            saveToFile();
        } else {
            printf("Deletion cancelled.\n");
        }
    } else {
        printf("Student ID %d not found.\n", id);
    }
}