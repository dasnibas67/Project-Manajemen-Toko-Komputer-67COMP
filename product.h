#ifndef PRODUCT_H
#define PRODUCT_H

typedef enum {
    GPU,
    KEYBOARD,
    MOUSE,
    HEADSET,
    IEM,
    TWS,
    MICROPHONE,
    RAM,
    SSD
} ProductCategory;

typedef struct {
    int id;
    char* name;
    ProductCategory category;
    int price;
    int stock;
    int sold; 
} Product;

int loadProducts(const char* filename, Product** products, int* capacity);
void saveProducts(const char* filename, Product* products, int count);
void displayProducts(Product* products, int count);
void addStock(Product* products, int count);
const char* getCategoryName(ProductCategory cat);
void freeProducts(Product* products, int count);

#endif