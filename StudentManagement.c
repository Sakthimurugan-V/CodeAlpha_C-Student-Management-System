#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

// Structure for Student
struct Student {
    int id;
    char name[50];
    int age;
    char grade[5];
};

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

// Function to add a student
void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    getchar(); // clear buffer
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // remove newline
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Grade: ");
    scanf("%s", s.grade);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("✅ Student added successfully!\n");
}

// Function to display all students
void displayStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    struct Student s;
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("ID: %d | Name: %s | Age: %d | Grade: %s\n", s.id, s.name, s.age, s.grade);
    }

    fclose(fp);
}

// Function to search student by ID
void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    int id, found = 0;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    struct Student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("✅ Record Found!\n");
            printf("ID: %d | Name: %s | Age: %d | Grade: %s\n", s.id, s.name, s.age, s.grade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("❌ Student not found!\n");
    }

    fclose(fp);
}

// Function to update student record
void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    int id, found = 0;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    struct Student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Enter new Name: ");
            getchar();
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Grade: ");
            scanf("%s", s.grade);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("✅ Record updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("❌ Student not found!\n");
    }

    fclose(fp);
}

// Function to delete a student record
void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        printf("Error opening temp file!\n");
        fclose(fp);
        return;
    }

    int id, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    struct Student s;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;
            continue; // skip this record
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("✅ Record deleted successfully!\n");
    } else {
        printf("❌ Student not found!\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
