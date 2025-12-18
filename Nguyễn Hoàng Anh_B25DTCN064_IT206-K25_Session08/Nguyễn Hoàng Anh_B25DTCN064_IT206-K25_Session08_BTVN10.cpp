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

// Ham luu danh sach sinh vien vao file
void saveToFile(struct Student students[], int n, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    
    fprintf(fp, "+------+----------------------+------+------+\n");
    fprintf(fp, "| ID   | Name                 | Age  | GPA  |\n");
    fprintf(fp, "+------+----------------------+------+------+\n");
    
    for (int i = 0; i < n; i++) {
        fprintf(fp, "| %4d | %-20s | %4d | %4.2f |\n", 
                students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
    
    fprintf(fp, "+------+----------------------+------+------+\n");
    fclose(fp);
    printf("\nDa luu danh sach sinh vien vao file %s thanh cong!\n", filename);
}

// Ham doc danh sach sinh vien tu file
int readFromFile(struct Student students[], int maxSize, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Khong the mo file %s de doc!\n", filename);
        return -1;
    }
    
    char buffer[200];
    for (int i = 0; i < 3; i++) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL) {
            printf("File khong dung dinh dang hoac rong!\n");
            fclose(fp);
            return -1;
        }
    }
    
    int count = 0;
    while (count < maxSize && fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "+------") != NULL) {
            break;
        }
        
        struct Student s;
        int result = sscanf(buffer, "| %d | %49[^|] | %d | %f |", 
                           &s.id, s.name, &s.age, &s.gpa);
        
        if (result == 4) {
            int start = 0;
            while (s.name[start] == ' ' && s.name[start] != '\0') {
                start++;
            }
            int end = strlen(s.name) - 1;
            while (end >= 0 && s.name[end] == ' ') {
                s.name[end] = '\0';
                end--;
            }
            if (start > 0) {
                memmove(s.name, s.name + start, strlen(s.name) - start + 1);
            }
            students[count] = s;
            count++;
        }
    }
    
    fclose(fp);
    printf("Da doc duoc %d sinh vien tu file %s\n", count, filename);
    return count;
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

void sortByGPA(struct Student students[], int n) {
    if (n <= 1) {
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Sap xep thanh cong\n");
}

void addStudent(struct Student students[], int *n) {
	if (*n >= MAX_STUDENTS) {
    	printf("Danh sach da day! Khong the them.\n");
    	return;
	}
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


void displayMenu() {
    printf("\n===== Student Manager =====\n");
    printf("1. Nhap sinh vien\n");
    printf("2. In danh sach\n");
    printf("3. Ghi file\n");
    printf("4. Doc file\n");
    printf("5. Tim kiem\n");
    printf("6. Sap xep\n");
    printf("7. Them sinh vien\n");
    printf("8. Xoa sinh vien\n");
    printf("0. Thoat\n");
    printf("===========================\n");
    printf("Chon chuc nang: ");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int n = 10;
    int choice;

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
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
            	addStudent(students, &n);
            	break;
                
            case 2:
                printf("\n=== DANH SACH SINH VIEN ===\n");
                printStudentList(students, n);
                break; 
                
            case 3:
                if (n == 0) {
                    printf("Danh sach rong! Khong co du lieu de ghi.\n");
                } else {
                    char filename[100];
                    printf("Nhap ten file: ");
                    scanf("%s", filename);
                    saveToFile(students, n, filename);
                }
                break;
                
			case 4:{
    			char filename[100];
    			printf("Nhap ten file: ");
    			scanf("%s", filename);

    			int readCount = readFromFile(students, MAX_STUDENTS, filename);
    			if (readCount > 0) {
        			n = readCount;
        			printf("Da doc thanh cong %d sinh vien.\n", n);
    			}
    			break;
    		}
                
            case 5:
    			searchStudentByID(students, n);
                break;
                
            case 6:
            	sortByGPA(students, n);
            	break;
                
            case 7:
                addStudent(students, &n);
                break;
            
            case 8:
            	deleteStudentByID(students, &n);
                break;
                
            case 0:
                printf("\nCam on ban da su dung chuong trinh!\n");
                break;
                
            default:
                printf("\nLua chon khong hop le! Vui long chon lai.\n");
        }
        
    } while (choice != 0);
    
    return 0;
}
