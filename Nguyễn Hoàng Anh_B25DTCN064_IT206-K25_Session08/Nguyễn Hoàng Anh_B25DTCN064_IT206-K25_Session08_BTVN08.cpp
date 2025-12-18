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


void saveToFile(struct Student students[], int n, const char *filename) {
    // Buoc 1: Mo file o che do ghi (write mode)
    // "w" se tao file moi neu chua ton tai, hoac ghi de len file cu neu da ton tai
    FILE *fp = fopen(filename, "w");
    
    // Buoc 2: Kiem tra file co mo thanh cong khong
    // Neu fp == NULL nghia la khong the mo file (co the do quyen truy cap, duong dan sai, ...)
    if (fp == NULL) {
        printf("Khong the mo file de ghi!\n");
        return; // Thoat ham neu khong mo duoc file
    }
    
    // Buoc 3: Ghi tieu de bang vao file
    // Tieu de giup nguoi doc file de hieu cau truc du lieu
    fprintf(fp, "+------+----------------------+------+------+\n");
    fprintf(fp, "|  ID  |        Name          | Age  | GPA  |\n");
    fprintf(fp, "+------+----------------------+------+------+\n");
    
    // Buoc 4: Duyet qua tung sinh vien va ghi thong tin vao file
    // Vong lap chay tu 0 den n-1 de ghi tat ca sinh vien trong mang
    for (int i = 0; i < n; i++) {
        // Ghi thong tin cua sinh vien thu i vao file theo dinh dang b?ng
        fprintf(fp, "| %4d | %-20s | %4d | %4.2f |\n", 
                students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
    
    // Buoc 5: Ghi chan bang de hoan thien dinh dang
    fprintf(fp, "+------+----------------------+------+------+\n");
    
    // Buoc 6: Dong file de giai phong tai nguyen he thong
    // Luu y: Luon phai dong file sau khi su dung xong
    fclose(fp);
    printf("\nDa luu danh sach sinh vien vao file %s thanh cong!\n", filename);
}

int readFromFile(struct Student students[], int maxSize, const char *filename) {
    // Buoc 1: Mo file o che do doc (read mode)
    // "r" chi cho phep doc file, neu file khong ton tai se tra ve NULL
    FILE *fp = fopen(filename, "r");
    
    // Buoc 2: Kiem tra file co mo thanh cong khong
    if (fp == NULL) {
        printf("Khong the mo file %s de doc!\n", filename);
        printf("Kiem tra lai ten file hoac duong dan.\n");
        return -1; // Tra ve -1 de bao hieu co loi
    }
    
    // Buoc 3: Doc va bo qua dong tieu de bang (neu co)
    // Doc 3 dong dau tien (2 dong tieu de + 1 dong phan cach)
    char buffer[200];
    for (int i = 0; i < 3; i++) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL) {
            // Neu khong doc duoc thi co the file rong hoac sai dinh dang
            printf("File khong dung dinh dang hoac rong!\n");
            fclose(fp);
            return -1;
        }
    }
    
    // Buoc 4: Doc tung dong du lieu va phan tich
    int count = 0; // Dem so luong sinh vien da doc duoc
    
    // Doc cho den khi het file hoac mang day
    while (count < maxSize && fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Kiem tra neu dong la chan bang thi dung lai
        if (strstr(buffer, "+------") != NULL) {
            break; // Da den cuoi bang
        }
        
        // Phan tich dong du lieu theo dinh dang: | ID | Name | Age | GPA |
        // Su dung sscanf de doc cac truong tu chuoi buffer
        struct Student s;
        int result = sscanf(buffer, "| %d | %49[^|] | %d | %f |", 
                           &s.id, s.name, &s.age, &s.gpa);
        
        // Buoc 5: Kiem tra dinh dang du lieu co hop le khong
        // Neu doc duoc du 4 truong (id, name, age, gpa) thi hop le
        if (result == 4) {
            // Xoa khoang trang thua o dau va cuoi ten
            // Tim vi tri bat dau cua ten (bo qua khoang trang)
            int start = 0;
            while (s.name[start] == ' ' && s.name[start] != '\0') {
                start++;
            }
            // Tim vi tri ket thuc cua ten (bo qua khoang trang)
            int end = strlen(s.name) - 1;
            while (end >= 0 && s.name[end] == ' ') {
                s.name[end] = '\0';
                end--;
            }
            // Di chuyen ten ve dau chuoi neu co khoang trang o dau
            if (start > 0) {
                memmove(s.name, s.name + start, strlen(s.name) - start + 1);
            }
            
            // Luu sinh vien vao mang
            students[count] = s;
            count++;
        }
    }
    
    // Buoc 6: Dong file sau khi doc xong
    fclose(fp);
    
    // Buoc 7: Tra ve so luong sinh vien da doc duoc
    printf("Da doc duoc %d sinh vien tu file %s\n", count, filename);
    return count;
}


void createClassData(const char *filename, struct Student classData[], int n) {
    saveToFile(classData, n, filename);
}

int main() {
    printf("=== TAO DU LIEU GIA LAP CHO 3 LOP ===\n");
    
    struct Student classA[8] = {
        {101, "Nguyen Van An", 20, 3.85},
        {102, "Tran Thi Binh", 21, 2.75},
        {103, "Le Van Cuong", 19, 3.95},
        {104, "Pham Thi Dung", 22, 3.25},
        {105, "Hoang Van Em", 20, 2.50},
        {106, "Vu Thi Phuong", 21, 3.65},
        {107, "Dao Van Giang", 19, 4.00},
        {108, "Bui Thi Hoa", 20, 3.10}
    };
    createClassData("classA.txt", classA, 8);
    
    struct Student classB[7] = {
        {201, "Le Van Inh", 22, 2.90},
        {202, "Ngo Thi Kieu", 19, 3.80},
        {203, "Pham Van Long", 20, 3.45},
        {204, "Tran Thi Mai", 21, 2.85},
        {205, "Hoang Van Nam", 19, 3.70},
        {206, "Vu Thi Oanh", 20, 3.20},
        {207, "Dao Van Phuc", 22, 3.55}
    };
    createClassData("classB.txt", classB, 7);
    
    struct Student classC[9] = {
        {301, "Nguyen Thi Quynh", 19, 3.60},
        {302, "Tran Van Son", 21, 2.95},
        {303, "Le Thi Tam", 20, 3.30},
        {304, "Pham Van Uy", 22, 3.75},
        {305, "Hoang Thi Van", 19, 2.80},
        {306, "Vu Van Xuan", 20, 3.40},
        {307, "Dao Thi Yen", 21, 3.50},
        {308, "Bui Van Zung", 19, 2.70},
        {309, "Ngo Van Anh", 20, 3.90}
    };
    createClassData("classC.txt", classC, 9);
    
    printf("\nDa tao xong du lieu cho 3 lop: classA.txt, classB.txt, classC.txt\n");
    
    printf("\n=== DOC DU LIEU TU FILE ===\n");
    printf("Cac file co san: classA.txt, classB.txt, classC.txt\n");
    
    char filename[100];
    printf("Nhap ten file can doc: ");
    scanf("%s", filename);
    
    struct Student students[20];
    int n = readFromFile(students, 20, filename);
    

    if (n > 0) {
        printf("\n=== DANH SACH SINH VIEN TU FILE %s ===\n", filename);
        printStudentList(students, n);

    } else if (n == -1) {
        printf("Khong the doc du lieu tu file %s\n", filename);
        printf("Vui long kiem tra lai ten file.\n");
    } else {
        printf("File %s rong hoac khong co du lieu!\n", filename);
    }
    
    return 0;
}


