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

void inputStudent(struct Student *s) {
    printf("Nhap ID: ");
    scanf("%d", &(*s).id);
    getchar();

    printf("Nhap ten: ");
    fgets((*s).name, sizeof((*s).name), stdin);
    (*s).name[strcspn((*s).name, "\n")] = '\0';

    printf("Nhap tuoi: ");
    scanf("%d", &(*s).age);

    printf("Nhap GPA: ");
    scanf("%f", &(*s).gpa);
}

void calculateAverageGPA(struct Student students[], int n) {
    float sum = 0.0;

    if (n == 0) {
        printf("Khong co sinh vien\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        sum += students[i].gpa;
    }

    printf("GPA trung binh: %.2f\n", sum / n);
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
    
    calculateAverageGPA(students, n);

    
    return 0;
}


