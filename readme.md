# Student Management System (v2.0)

A robust, crash-proof CLI application built in C for managing student records. This version focuses on **Data Integrity** and **User Experience**, featuring a comprehensive validation layer and dynamic navigation.

## 🚀 Key Features

- **Bulletproof Input Validation**: Custom protectors (`getSafeInt`, `getSafeFloat`) prevent infinite loops and crashes from non-numeric input.
- **Business Logic Filters**: 
  - Prevents duplicate Student IDs.
  - Validates names (alphabetic characters only).
  - Restricts marks to a logical range (0-100).
- **Professional UI**: Tabular data display with aligned columns for easy reading.
- **Advanced Sorting**: Organize records by **ID (Ascending)** or **Performance/Marks (Descending)** using the Bubble Sort algorithm.
- **Safe Navigation**: "Early Exit" logic allowed in all menus—press `0` to cancel any operation and return to the main menu.
- **Persistent Storage**: Automatic data synchronization with `students.txt`.

## 🛠️ Technical Implementation

- **Language**: C
- **Data Structure**: Array of Structs
- **Algorithm**: Bubble Sort (swapping full struct units to maintain data integrity)
- **File I/O**: Formatted file handling for long-term storage.

## 📋 How to Run

1. Clone the repository.
2. Compile using GCC:
   ```bash
   gcc main.c -o student_system