#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

void printStudentList(struct Student students[], int n) {
    if (n == 0) {
        printf("Danh sach sinh vien rong!\n");
        return;
    }

    printf("+------+----------------------+------+------+\n");
    printf("|  ID  |        Name          | Age  | GPA  |\n");
    printf("+------+----------------------+------+------+\n");

    for (int i = 0; i < n; i++) {
        printf("| %4d | %-20s | %4d | %4.2f |\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    printf("+------+----------------------+------+------+\n");
}


void sortByGPA(struct Student students[], int n) {
    if (n <= 1) {
        return;
    }
    
    // Bubble Sort: sap xep theo GPA giam dan
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    struct Student students[10];
    int n = 10;

    struct Student testStudents[10] = {
        {1, "Nguyen Van An", 20, 3.85},
        {2, "Tran Thi Binh", 21, 2.75},
        {3, "Le Van Cuong", 19, 3.95},
        {4, "Pham Thi Dung", 22, 3.25},
        {5, "Hoang Van Em", 20, 2.50},
        {6, "Vu Thi Phuong", 21, 3.65},
        {7, "Dao Van Giang", 19, 4.00},
        {8, "Bui Thi Hoa", 20, 3.10},
        {9, "Le Van Inh", 22, 2.90},
        {10, "Ngo Thi Kieu", 19, 3.80}
    };

    for (int i = 0; i < n; i++) {
        students[i] = testStudents[i];
    }

    printf("\n=== DANH SACH SINH VIEN ===\n");
    printStudentList(students, n);


    printf("\nSAP XEP THEO GPA (GIAM DAN)\n");
    sortByGPA(students, n);

    printf("\n=== DANH SACH SINH VIEN SAU KHI SAP XEP ===\n");
    printStudentList(students, n);
    
    return 0;
}


