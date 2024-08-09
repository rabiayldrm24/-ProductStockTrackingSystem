#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

// Product structure 
struct Product {
    int id;
    char name[50];
    char unit[50];
    int quantity;
};

// Read the product information from the file and add it to the product array
void readProductsFromFile(struct Product products[], int *productCount) {
    FILE *fp;
    char filename[] = "products.txt";
    char line[200];
    char *token;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }

    while (fgets(line, sizeof(line), fp) != NULL && *productCount < MAX_PRODUCTS) {
        token = strtok(line, ",");
        products[*productCount].id = atoi(token);
        token = strtok(NULL, ",");
        strcpy(products[*productCount].name, token);
        token = strtok(NULL, ",");
        strcpy(products[*productCount].unit, token);
        token = strtok(NULL, ",");
        products[*productCount].quantity = atoi(token);
        (*productCount)++;
    }

    fclose(fp);
}

// Show the menu
void displayMenu() {
    printf("\n--- Product Stock Tracking System ---\n");
    printf("1. Add a new product\n");
    printf("2. Update a product\n");
    printf("3. Search for product with name\n");
    printf("4. Increase quantity of a product\n");
    printf("5. Decrease quantity of a product\n");
    printf("6. List all products\n");
    printf("7. Exit / Quit the program\n");
    printf("-------------------------------------\n");
}

// Adding a new product
void addProduct(struct Product products[], int *productCount) {
    printf("Adding a new product...\n");

    // Check if there is space in the array
    if (*productCount >= MAX_PRODUCTS) {
        printf("Error: Maximum number of products reached. Cannot add new product.\n");
        return;
    }

    // Get new product information from the user
    struct Product newProduct;
    printf("Enter product ID: ");
    scanf("%d", &newProduct.id);
    printf("Enter product name: ");
    scanf("%s", newProduct.name);
    printf("Enter product unit: ");
    scanf("%s", newProduct.unit);
    printf("Enter product quantity: ");
    scanf("%d", &newProduct.quantity);

    // Add the new product to the array
    products[*productCount] = newProduct;
    (*productCount)++;

    printf("Product added successfully.\n");
}


// Updating a product
void updateProduct(struct Product products[], int productCount) {
    // The operations of receiving the product information to be updated from the user and updating the related product in the products series will be performed here
    printf("Updating a product...\n");

    // Check if there are products to update
    if (productCount == 0) {
        printf("Error: No products to update.\n");
        return;
    }

    // Get product ID to update from the user
    int idToUpdate;
    printf("Enter product ID to update: ");
    scanf("%d", &idToUpdate);

    // Search for the product with the given ID
    int indexToUpdate = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == idToUpdate) {
            indexToUpdate = i;
            break;
        } 
    }

    // Check if the product was found
    if (indexToUpdate == -1) {
        printf("Error: Product with ID %d not found.\n", idToUpdate);
        return;
    }

    // Get updated product information from the user
    //printf("Enter new product name: ");
    //scanf("%s", products[indexToUpdate].name);
    //printf("Enter new product unit: ");
    //scanf("%s", products[indexToUpdate].unit);
    //printf("Enter new product quantity: ");
    //scanf("%d", &products[indexToUpdate].quantity);

    //printf("Product updated successfully.\n");
    
    // Sub-menu for choosing the field to update
    int updateChoice;
    printf("Choose which field to update:\n");
    printf("1. Id\n");
    printf("2. Name\n");
    printf("3. Unit\n");
    printf("4. Quantity\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &updateChoice);

    // Update the selected field
    switch (updateChoice) {
        case 1:
            printf("Enter new id: ");
            scanf("%s", products[indexToUpdate].id);
            break;
        case 2:
            printf("Enter new name: ");
            scanf("%s", products[indexToUpdate].name);
            break;
        case 3:
            printf("Enter new unit: ");
            scanf("%d", &products[indexToUpdate].unit);
            break;
        case 4:
            printf("Enter new quantity: ");
            scanf("%d", &products[indexToUpdate].quantity);
            break;
        default:
            printf("Invalid choice. No field updated.\n");
            return;
    }

    printf("Product updated successfully.\n");
}

// Decrypt a product by name
void searchProductByName(struct Product products[], int productCount) {
    // The operations of getting the product name to be searched from the user and finding and displaying the related products in the products array will be performed here
    printf("Searching for a product by name...\n");
    
    // Check if there are products to search
    if (productCount == 0) {
        printf("Error: No products available to search.\n");
        return;
    }

    // Get the name of the product to search
    char searchName[50];
    printf("Enter the name of the product to search: ");
    scanf("%s", searchName);

    // Search for products with the given name
    int found = 0;
    printf("\n--- Search Results ---\n");
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, searchName) == 0) {
            printf("ID: %d, Name: %s, Unit: %s, Quantity: %d\n", products[i].id, products[i].name, products[i].unit, products[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No products found with the name '%s'.\n", searchName);
    }
    printf("----------------------\n");

}

// Increasing the amount of a product
void increaseProductQuantity(struct Product products[], int productCount) {
    // The process of getting the ID of the product to be increased from the user and increasing the amount of the corresponding product will be performed here
    printf("Increasing quantity of a product...\n");


    // Check if there are products to update
    if (productCount == 0) {
        printf("Error: No products available to update quantity.\n");
        return;
    }

    // Get the ID of the product to update quantity
    int updateID;
    printf("Enter the ID of the product to increase quantity: ");
    scanf("%d", &updateID);

    // Find the product with the given ID
    int foundIndex = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == updateID) {
            foundIndex = i;
            break;
        }
    }

    // Check if the product with the given ID exists
    if (foundIndex == -1) {
        printf("Error: Product with ID %d not found.\n", updateID);
        return;
    }

    // Get the quantity to increase
    int increaseQuantity;
    printf("Enter the quantity to increase: ");
    scanf("%d", &increaseQuantity);

    // Increase the quantity of the product
    products[foundIndex].quantity += increaseQuantity;

    printf("Quantity of product with ID %d increased by %d. New quantity of %s: %d\n", 
            updateID, increaseQuantity, products[foundIndex].name, products[foundIndex].quantity);
}

// Reducing the amount of a product
void decreaseProductQuantity(struct Product products[], int productCount) {
    // The process of getting the ID of the product to be reduced from the user and reducing the amount of the corresponding product will be performed here
    printf("Decreasing quantity of a product...\n");


    // Check if there are products to update
    if (productCount == 0) {
        printf("Error: No products available to update quantity.\n");
        return;
    }

    // Get the ID of the product to update quantity
    int updateID;
    printf("Enter the ID of the product to decrease quantity: ");
    scanf("%d", &updateID);

    // Find the product with the given ID
    int foundIndex = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == updateID) {
            foundIndex = i;
            break;
        }
    }

    // Check if the product with the given ID exists
    if (foundIndex == -1) {
        printf("Error: Product with ID %d not found.\n", updateID);
        return;
    }

    // Get the quantity to decrease
    int decreaseQuantity;
    printf("Enter the quantity to decrease: ");
    scanf("%d", &decreaseQuantity);

    // Check if the requested decrease quantity is greater than the current quantity
    if (decreaseQuantity > products[foundIndex].quantity) {
        printf("Error: Cannot decrease quantity by %d, as current quantity is %d.\n", decreaseQuantity, products[foundIndex].quantity);
        return;
    }

    // Decrease the quantity of the product
    products[foundIndex].quantity -= decreaseQuantity;

    printf("Quantity of product with ID %d decreased by %d. New quantity of %s: %d\n", 
            updateID, decreaseQuantity, products[foundIndex].name, products[foundIndex].quantity);
}



// Listing all products
void listAllProducts(struct Product products[], int productCount) {
    printf("\n--- List of All Products ---\n");
    for (int i = 0; i < productCount; ++i) {
        printf("ID: %d, Name: %s, Unit: %s, Quantity: %d\n", products[i].id, products[i].name, products[i].unit, products[i].quantity);
    }
    printf("---------------------------\n");
}

int main() {
    struct Product products[MAX_PRODUCTS];
    int num_products = 0;

    // Reading products from file
    readProductsFromFile(products, &num_products);

    int choice;
    do {
        displayMenu(); // Print the menu here
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(products, &num_products);
                break;
            case 2:
                updateProduct(products, num_products);
                break;
            case 3:
                searchProductByName(products, num_products);
                break;
            case 4:
                increaseProductQuantity(products, num_products);
                break;
            case 5:
                decreaseProductQuantity(products, num_products);
                break;
            case 6:
                listAllProducts(products, num_products);
                break;
            case 7:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

        printf("\n"); // Add a new line after each option
    } while (1);

    return 0;
}
