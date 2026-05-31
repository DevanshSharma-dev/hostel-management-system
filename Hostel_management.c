#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define PASSWORD "dev123"

typedef struct {
    int id;
    char name[50];
    int room_no;
    int fees_paid;
} Student;

void admin_login();
void menu();
void add_student();
void update_student();
void delete_student();
void check_room_availability();
void generate_report();

int room_capacity = 50;

void admin_login() {
    char pass[20];
    printf("Enter Admin Password: ");
    scanf("%s", pass);

    if (strcmp(pass, PASSWORD) != 0) {
        printf("Incorrect Password. Access Denied.\n");
        exit(0);
    }
}

void add_student() {
    FILE *fp = fopen("students.dat", "ab");
    Student s;

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Room Number: ");
    scanf("%d", &s.room_no);
    printf("Fees Paid (1 for Yes / 0 for No): ");
    scanf("%d", &s.fees_paid);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student record added successfully!\n");
}

void update_student() {
    FILE *fp = fopen("students.dat", "rb+");
    Student s;
    int id, found = 0;

    printf("Enter Student ID to Update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            found = 1;
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Room Number: ");
            scanf("%d", &s.room_no);
            printf("Fees Paid (1 for Yes / 0 for No): ");
            scanf("%d", &s.fees_paid);

            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("Record updated successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Student ID not found.\n");

    fclose(fp);
}

void delete_student() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Student s;
    int id, found = 0;

    printf("Enter Student ID to Delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id != id) {
            fwrite(&s, sizeof(Student), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student record deleted.\n");
    else
        printf("Student ID not found.\n");
}

void check_room_availability() {
    FILE *fp = fopen("students.dat", "rb");
    Student s;
    int count = 0;

    while (fread(&s, sizeof(Student), 1, fp)) {
        count++;
    }
    fclose(fp);

    int available = room_capacity - count;
    printf("Total Rooms: %d\n", room_capacity);
    printf("Occupied Rooms: %d\n", count);
    printf("Available Rooms: %d\n", available);
}

void generate_report() {
    FILE *fp = fopen("students.dat", "rb");
    Student s;

    printf("\n--- Hostel Occupancy Report ---\n");
    printf("ID\tName\t\tRoom\tFees Paid\n");
    printf("-----------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%d\t%-15s\t%d\t%s\n", s.id, s.name, s.room_no, s.fees_paid ? "Yes" : "No");
    }
    fclose(fp);
}

void menu() {
    int choice;

    do {
        printf("\n--- Hostel Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. Check Room Availability\n");
        printf("5. Generate Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_student(); break;
            case 2: update_student(); break;
            case 3: delete_student(); break;
            case 4: check_room_availability(); break;
            case 5: generate_report(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid Choice.\n");
        }
    } while (choice != 6);
}

int main() {
    admin_login();
    menu();
    return 0;
}