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


void searchStudentByID(struct Student students[], int n) {
    if (n == 0) {
        printf("Danh sach rong! Khong co sinh vien de tim.\n");
        return;
    }

    int searchID;
    printf("Nhap ID can tim: ");
    scanf("%d", &searchID);

    for (int i = 0; i < n; i++) {
        if (students[i].id == searchID) {
            printf("ID: %d\n", students[i].id);
            printf("Ten: %s\n", students[i].name);
            printf("Tuoi: %d\n", students[i].age);
            printf("GPA: %.2f\n", students[i].gpa);
            return;
        }
    }

    printf("Khong tim thay sinh vien co ID %d\n", searchID);
}

int main() {
    struct Student students[5];
    int n;
    
    printf("Nhap so luong sinh vien (toi da 5): ");
    scanf("%d", &n);
    
    if (n > 5) {
        n = 5;
        printf("So luong bi gioi han lai la 5 sinh vien.\n");
    }
    
    printf("\n=== NHAP THONG TIN SINH VIEN ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nSinh vien thu %d:\n", i + 1);
        inputStudent(&students[i]);
    }
    
    printf("\n=== DANH SACH SINH VIEN ===\n");
    printStudentList(students, n);
    
    searchStudentByID(students, n);
    
    return 0;
}


