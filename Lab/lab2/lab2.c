// important line for debug purposes in Windows / Visual Studio
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// important line for debug purposes in Windows / Visual Studio
#include <crtdbg.h>

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

// Structure to store student data
typedef struct {
    int id;
    char* first_name;
    char* last_name;
    float* grades;
    int num_grades;
    float average_grade;
} Student;

// Function prototypes
Student* create_student(int id, const char* first_name, const char* last_name, float* grades, int num_grades);
float calculate_average(float* grades, int count);
void print_student(Student* student);
void free_student(Student* student);
int compare_students_by_average(const void* a, const void* b);
void sort_students_by_average(Student** students, int count);
Student** filter_passing_students(Student** students, int count, float passing_grade, int* num_passing);

int main() {
    // important line for debug purposes in Windows / Visual Studio
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Student** all_students = (Student**)malloc(MAX_STUDENTS * sizeof(Student*));
    int num_students = 0;
    Student** passing_students;
    int num_passing = 0;
    float passing_grade = 60.0;

    // Sample student data
    float grades1[] = { 85.5, 90.0, 78.5, 92.0 };
    float grades2[] = { 10.0, 10.0, 10.0, 10.0 };
    float grades3[] = { 92.5, 88.0, 76.0, 94.5 };
    float grades4[] = { 35.0, 42.5, 50.0, 48.0 };

    // Create student records
    all_students[num_students++] = create_student(1001, "John", "Doe", grades1, 4);
    all_students[num_students++] = create_student(1002, "Jane", "Smith", grades2, 4);
    all_students[num_students++] = create_student(1003, "Bob", "Johnson", grades3, 4);
    all_students[num_students++] = create_student(1004, "Alice", "Brown", grades4, 4);

    // Print all students
    printf("All Students:\n");
    printf("-------------\n");
    for (int i = 0; i < num_students; i++) {
        print_student(all_students[i]);
        printf("\n");
    }

    // Sort students by average grade
    sort_students_by_average(all_students, num_students);

    // Print sorted students
    printf("\nStudents Sorted by Average Grade:\n");
    printf("--------------------------------\n");
    for (int i = 0; i < num_students; i++) {
        print_student(all_students[i]);
        printf("\n");
    }

    // Filter passing students
    passing_students = filter_passing_students(all_students, num_students, passing_grade, &num_passing);

    // Free all students
    for (int i = 0; i < num_students; i++) {
        free_student(all_students[i]);
    }

    free(all_students);

    // Print passing students
    printf("\nPassing Students (>= %.1f):\n", passing_grade);
    printf("-------------------------\n");
    for (int i = 0; i < num_passing; i++) {
        print_student(passing_students[i]);
        printf("\n");
    }

    // Free passing students array
	for (int i = 0; i < num_passing; i++) {
		free_student(passing_students[i]);
	}
    free(passing_students);

    return 0;
}

// Function to create a student record
Student* create_student(int id, const char* first_name, const char* last_name, float* grades, int num_grades) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (student == NULL) {
        printf("Memory allocation failed for student!\n");
        return NULL;
    }

    student->id = id;

    // Allocate memory for first name
    student->first_name = (char*)malloc((strlen(first_name) + 1) * sizeof(char));
    if (student->first_name == NULL) {
        printf("Memory allocation failed for first name!\n");
        free(student);
        return NULL;
    }
    strcpy(student->first_name, first_name);

    // Allocate memory for last name
    student->last_name = (char*)malloc((strlen(last_name) + 1) * sizeof(char));
    if (student->last_name == NULL) {
        printf("Memory allocation failed for last name!\n");
        free(student->first_name);
        free(student);
        return NULL;
    }
    strcpy(student->last_name, last_name);

    // Allocate memory for grades
    student->grades = (float*)malloc(num_grades * sizeof(float));
    if (student->grades == NULL) {
        printf("Memory allocation failed for grades!\n");
        free(student->last_name);
        free(student->first_name);
        free(student);
        return NULL;
    }

    // Copy grades
    for (int i = 0; i < num_grades; i++) {
        student->grades[i] = grades[i];
    }

    student->num_grades = num_grades;
    student->average_grade = calculate_average(grades, num_grades);

    return student;
}

// Function to calculate average grade
float calculate_average(float* grades, int count) {
    if (count == 0) {
        return 0.0;
    }

    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += grades[i];
    }

    return sum / count;
}

// Function to print student information
void print_student(Student* student) {
    printf("ID: %d\n", student->id);
    printf("Name: %s %s\n", student->first_name, student->last_name);

    printf("Grades: ");
    for (int i = 0; i < student->num_grades; i++) {
        printf("%.1f ", student->grades[i]);
    }
    printf("\n");

    printf("Average: %.2f\n", student->average_grade);
}

// Function to free a student record
void free_student(Student* student) {
    if (student == NULL) {
        return;
    }

    free(student->first_name);
    free(student->last_name);
    free(student->grades);
    free(student);
}

// Function to compare students by average grade (for sorting)
int compare_students_by_average(const void* a, const void* b) {
    Student* student_a = *(Student**)a;
    Student* student_b = *(Student**)b;

    if (student_b->average_grade > student_a->average_grade) {
        return 1;
    }
    else if (student_b->average_grade < student_a->average_grade) {
        return -1;
    }
    else {
        return 0;
    }
}

// Function to sort students by average grade
void sort_students_by_average(Student** students, int count) {
    qsort(students, count, sizeof(Student*), compare_students_by_average);
}

// Function to filter passing students
Student** filter_passing_students(Student** students, int count, float passing_grade, int* num_passing) {
    // First pass: count passing students
    *num_passing = 0;
    for (int i = 0; i < count; i++) {
        if (students[i]->average_grade >= passing_grade) {
            (*num_passing)++;
        }
    }

    // Allocate memory for passing students
    Student** passing = (Student**)malloc(*num_passing * sizeof(Student*));
    if (passing == NULL) {
        printf("Memory allocation failed for passing students!\n");
        *num_passing = 0;
        return NULL;
    }

    // Second pass: store passing students
    int index = 0;
    for (int i = 0; i < count; i++) {
        if (students[i]->average_grade >= passing_grade) {
            passing[index] = create_student(students[i]->id, students[i]->first_name, students[i]->last_name, students[i]->grades, students[i]->num_grades);
            index++;
        }
    }

    return passing;
}

