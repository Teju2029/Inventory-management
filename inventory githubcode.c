#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure for item
struct Item {
    int id;
    char name[50];
    int stock;
    float price;
};

struct Item inventory[MAX];
int count = 0;

/* Function to save data to file */
void saveToFile() {
    FILE *fp = fopen("inventory.txt", "w");
    int i;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %.2f\n",
                inventory[i].id,
                inventory[i].name,
                inventory[i].stock,
                inventory[i].price);
    }

    fclose(fp);
}

/* Function to load data from file */
void loadFromFile() {
    FILE *fp = fopen("inventory.txt", "r");

    if (fp == NULL)
        return;

    while (fscanf(fp, "%d %s %d %f",
                  &inventory[count].id,
                   inventory[count].name,
                  &inventory[count].stock,
                  &inventory[count].price) != EOF) {
        count++;
    }

    fclose(fp);
}

/* 1) Add Item */
void addItem() {
    printf("\nEnter Item ID: ");
    scanf("%d", &inventory[count].id);

    printf("Enter Item Name: ");
    scanf("%s", inventory[count].name);

    printf("Enter Stock Quantity: ");
    scanf("%d", &inventory[count].stock);

    printf("Enter Price: ");
    scanf("%f", &inventory[count].price);

    count++;
    saveToFile();

    printf("Item Added Successfully!\n");
}

/* 2) Update Stock */
void updateStock() {
    int id, qty, found = 0;
    int i;

    printf("\nEnter Item ID to update: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            printf("Enter quantity to add: ");
            scanf("%d", &qty);

            inventory[i].stock += qty;
            saveToFile();

            printf("Stock Updated Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Item not found!\n");
}

/* 3) Generate Bill for Sold Products */
void generateBill() {
    int id, qty, found = 0;
    int i;
    float total = 0;

    printf("\nEnter Item ID sold: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            printf("Enter quantity sold: ");
            scanf("%d", &qty);

            if (qty > inventory[i].stock) {
                printf("Not enough stock!\n");
                return;
            }

            inventory[i].stock -= qty;
            total = qty * inventory[i].price;

            saveToFile();

            printf("\n----- BILL -----\n");
            printf("Item: %s\n", inventory[i].name);
            printf("Quantity: %d\n", qty);
            printf("Price: %.2f\n", inventory[i].price);
            printf("Total Amount: %.2f\n", total);
            printf("----------------\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Item not found!\n");
}

int main() {
    int choice;

    loadFromFile();

    while (1) {
        printf("\n--- Inventory Management ---\n");
        printf("1. Add Item\n");
        printf("2. Update Stock\n");
        printf("3. Bill for Sold Product\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                updateStock();
                break;
            case 3:
                generateBill();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}

