#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 100

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

void addStudent(struct Student students[], int *n) {
    struct Student newStudent;
    inputStudent(&newStudent);

    for (int i = 0; i < *n; i++) {
        if (students[i].id == newStudent.id) {
            printf("ID %d da ton tai! Khong the them sinh vien.\n", newStudent.id);
            return;
        }
    }

    students[*n] = newStudent;
    (*n)++;

    printf("Da them sinh vien co ID %d thanh cong!\n", newStudent.id);
}

void deleteStudentByID(struct Student students[], int *n) {
    if (*n == 0) {
        printf("Danh sach rong! Khong co sinh vien nao de xoa.\n");
        return;
    }

    int deleteID;
    printf("Nhap ID can xoa: ");
    scanf("%d", &deleteID);

    int pos = -1;
    for (int i = 0; i < *n; i++) {
        if (students[i].id == deleteID) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Khong tim thay sinh vien co ID %d!\n", deleteID);
        return;
    }

    for (int i = pos; i < *n - 1; i++) {
        students[i] = students[i + 1];
    }

    (*n)--;

    printf("Da xoa sinh vien co ID %d thanh cong!\n", deleteID);
}

int main() {
    struct Student students[MAX_STUDENTS];
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

    printStudentList(students, n);


    printf("\n=== THEM SINH VIEN MOI ===\n");
	addStudent(students, &n);
	
    printStudentList(students, n);
    
    
    printf("\n=== XOA SINH VIEN ===\n");
    deleteStudentByID(students, &n);
        
    printStudentList(students, n);
    
    return 0;
}


