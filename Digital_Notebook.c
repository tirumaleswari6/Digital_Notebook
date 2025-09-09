#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "notes.dat"
#define MAX_TITLE 50
#define MAX_CONTENT 500

struct Note {
    char title[MAX_TITLE];
    char content[MAX_CONTENT];
};

void addNote() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    struct Note n;
    getchar(); // clear input buffer

    printf("\nEnter Note Title: ");
    fgets(n.title, MAX_TITLE, stdin);
    n.title[strcspn(n.title, "\n")] = '\0';

    printf("Enter Note Content: ");
    fgets(n.content, MAX_CONTENT, stdin);
    n.content[strcspn(n.content, "\n")] = '\0';

    fwrite(&n, sizeof(n), 1, fp);
    fclose(fp);

    printf("Note added successfully!\n");
}

void viewNotes() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No notes found.\n");
        return;
    }

    struct Note n;
    int index = 1;

    printf("\n==== All Notes ====\n\n");
    while (fread(&n, sizeof(n), 1, fp)) {
        printf("[%d] %s\n", index++, n.title);
        printf("    %s\n\n", n.content);
    }
    fclose(fp);
}

void searchNote() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No notes found.\n");
        return;
    }

    struct Note n;
    char keyword[MAX_TITLE];
    int found = 0;

    getchar(); // clear buffer
    printf("\nEnter keyword to search: ");
    fgets(keyword, MAX_TITLE, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    printf("\n==== Search Results ====\n\n");
    while (fread(&n, sizeof(n), 1, fp)) {
        if (strstr(n.title, keyword) || strstr(n.content, keyword)) {
            printf("Title: %s\nContent: %s\n\n", n.title, n.content);
            found = 1;
        }
    }

    if (!found) printf("No notes matched '%s'.\n", keyword);

    fclose(fp);
}

void editNote() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        printf("No notes found.\n");
        return;
    }

    struct Note n;
    int index, count = 0;

    printf("\nEnter note number to edit: ");
    scanf("%d", &index);

    // Count total notes
    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / sizeof(n);

    if (index < 1 || index > count) {
        printf("Invalid note number!\n");
        fclose(fp);
        return;
    }

    getchar(); // clear buffer
    fseek(fp, (index - 1) * sizeof(n), SEEK_SET);

    printf("\nEnter new title: ");
    fgets(n.title, MAX_TITLE, stdin);
    n.title[strcspn(n.title, "\n")] = '\0';

    printf("Enter new content: ");
    fgets(n.content, MAX_CONTENT, stdin);
    n.content[strcspn(n.content, "\n")] = '\0';

    fwrite(&n, sizeof(n), 1, fp);
    fclose(fp);

    printf("Note updated successfully!\n");
}

void deleteNote() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp;
    if (!fp) {
        printf("No notes found.\n");
        return;
    }

    struct Note n;
    int index, count = 0, current = 1;

    printf("\nEnter note number to delete: ");
    scanf("%d", &index);

    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / sizeof(n);
    rewind(fp);

    if (index < 1 || index > count) {
        printf("Invalid note number!\n");
        fclose(fp);
        return;
    }

    temp = fopen("temp.dat", "wb");

    while (fread(&n, sizeof(n), 1, fp)) {
        if (current != index) {
            fwrite(&n, sizeof(n), 1, temp);
        }
        current++;
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    printf("Note deleted successfully!\n");
}

void deleteAllNotes() {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (!fp) {
        printf("Error clearing notes.\n");
        return;
    }
    fclose(fp);
    printf("All notes deleted successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Digital Notebook =====\n");
        printf("1. Add Note\n");
        printf("2. View Notes\n");
        printf("3. Search Note\n");
        printf("4. Edit Note\n");
        printf("5. Delete Note\n");
        printf("6. Delete All Notes\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addNote(); break;
            case 2: viewNotes(); break;
            case 3: searchNote(); break;
            case 4: editNote(); break;
            case 5: deleteNote(); break;
            case 6: deleteAllNotes(); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
