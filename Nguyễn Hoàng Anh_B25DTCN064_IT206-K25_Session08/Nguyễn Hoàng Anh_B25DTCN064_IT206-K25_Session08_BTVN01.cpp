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

int main() {
	int n = 3;
    struct Student students[3] = {
        {1, "Nguyen Van A", 20, 3.75},
        {2, "Tran Thi B", 21, 3.85},
        {3, "Le Van C", 19, 3.65}
    };
    
    printStudentList(students, n);
    
    return 0;
}


