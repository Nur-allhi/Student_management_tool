# Student Management System (C CLI)

✅ **FEATURES COMPLETED**
1. **Core System Architecture**
   * Menu-driven navigation with continuous loop.
   * Integrated auto-loading of data on program startup.
2. **Data Model**
   * `struct Student` containing ID (int), Name (char array), and Marks (float).
   * Global array storage with a fixed `MAX` capacity.
3. **Record Management (CRUD)**
   * **Add**: Supports full names with spaces and automatic capitalization.
   * **View**: Formatted display of all records.
   * **Search**: Linear search by Student ID.
   * **Edit**: Modify name and marks for an existing ID.
   * **Delete**: Removes records using array-shifting logic.
4. **File Persistence (TEXT FORMAT)**
   * **Auto-Save**: Updates `students.txt` immediately after any Add, Edit, or Delete operation.
   * **Format**: `id|name|marks` parsing using `sscanf`.
5. **Stability Fixes**
   * Input buffer clearing with `getchar()`.
   * Handling newline characters from `fgets`.

🚧 **CURRENT LIMITATIONS**
* Fixed size array (MAX = 100).
* No duplicate ID prevention yet.
* Basic input validation (weak handling of non-numeric inputs).

🧠 **CONCEPTS APPLIED**
* **Array Shifting**: Moving elements to maintain order after deletion.
* **Struct-based Modeling**: Real-world entity representation.
* **File I/O**: Automated read/write operations for persistence.
* **String Manipulation**: Custom capitalization logic and delimiter-based parsing.

💻 **HOW TO RUN**
1. **Compile**: `gcc main.c -o app`
2. **Run**: `./app`