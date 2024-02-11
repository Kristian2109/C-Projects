# Student Information in C++
The project imitates a student database

## Prerequisites:
  - Primitive datatypes, arrays, vectors, strings, classes and STL functions.

## Approach
  - First all students are loaded from the text file and stored in a vector.
  - The user can choose from the options and work with the data.
  - After the successful completion (quitting), the text file is overwritten with the new information.
  - Every incorrect input will be detected except the ID number and the discipline, as they aren't strictly specified.

## Functionalities

### 1. **Choose a specialty to visit**
    - You can choose only from the listed specialties.
    - You can exit the program, if you type **-1**.
  
### 2. **Supports up to 8 groups from a given specialty**

### 3. **Register a student** - the user should enter the following data: 
    - full student name with three names, every beginning with high letter. The format should be with exactly two spaces. Every other format wouldn't be registered
    - an unique ID number
    - the number of the disciplines and hence their names along the note for every discipline.

### 4. **Visualize the list with the students** from a group or all of them.
    - They can be sorted according to average grade or ID number.

### 5. **Change the data for a single student**
    - The user will be required to enter the ID number
    - It supports the folloing options:
      - delete student
      - add a discipline and hence a note for this
      - change note for an existing discipline

### 6. **Database**
    - The information for every specialty is stored in a distinct text file and overwritten after you quit the specialty.
