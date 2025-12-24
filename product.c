#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

const char* getCategoryName(ProductCategory cat) {
    switch(cat) {
        case GPU: return "GPU";
        case KEYBOARD: return "Keyboard";
        case MOUSE: return "Mouse";
        case HEADSET: return "Headset";
        case IEM: return "IEM";
        case TWS: return "TWS";
        case MICROPHONE: return "Microphone";
        case RAM: return "RAM";
        case SSD: return "SSD";
        default: return "Unknown";
    }
}

int loadProducts(const char* filename, Product** products, int* capacity) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File tidak ditemukan, membuat data default...\n");
        return 0;
    }
    
    char buffer[256];
    int count = 0;
    
    while (fgets(buffer, sizeof(buffer), file) != NULL && count < *capacity) {
        buffer[strcspn(buffer, "\n")] = 0;
        
        char* token = strtok(buffer, "|");
        if (token != NULL) {
            (*products)[count].id = atoi(token);
            
            token = strtok(NULL, "|");
            if (token != NULL) {
                (*products)[count].name = strdup(token);
            }
            
            token = strtok(NULL, "|");
            (*products)[count].category = (token != NULL) ? atoi(token) : 0;
            
            token = strtok(NULL, "|");
            (*products)[count].price = (token != NULL) ? atoi(token) : 0;
            
            token = strtok(NULL, "|");
            (*products)[count].stock = (token != NULL) ? atoi(token) : 0;
            
            token = strtok(NULL, "|");
            (*products)[count].sold = (token != NULL) ? atoi(token) : 0;
            
            count++;
        }
    }
    
    fclose(file);
    return count;
}

void saveProducts(const char* filename, Product* products, int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Gagal menyimpan file!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%d|%d|%d|%d\n",
                products[i].id,
                products[i].name,
                products[i].category,
                products[i].price,
                products[i].stock,
                products[i].sold);
    }
    
    fclose(file);
}

// tampilan semua produk
void displayProducts(Product* products, int count) {
    printf("\n========== DAFTAR PRODUK TOKO 67COMP GAMING ==========\n");
    printf("%-4s %-50s %-12s %-15s %-8s\n", "ID", "Nama Produk", "Kategori", "Harga", "Stok");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-4d %-50s %-12s Rp%-13d %-8d\n",
               products[i].id,
               products[i].name,
               getCategoryName(products[i].category),
               products[i].price,
               products[i].stock);
    }
    printf("\n");
}

// tambah stok produk 
void addStock(Product* products, int count) {
    int id, tambahan;
    
    printf("\nMasukkan ID produk: ");
    if (scanf("%d", &id) != 1) {
        printf("Input ID harus berupa angka!\n");
        while (getchar() != '\n');
        return;
    }
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            printf("Produk: %s\n", products[i].name);
            printf("Stok saat ini: %d\n", products[i].stock);
            printf("Tambah stok: ");
            
            if (scanf("%d", &tambahan) != 1) {
                printf("Input stok harus berupa angka!\n");
                while (getchar() != '\n');
                return;
            }
            
            if (tambahan <= 0) {
                printf("Jumlah stok harus lebih dari 0!\n");
                return;
            }
            
            products[i].stock += tambahan;
            printf("Stok berhasil ditambahkan! Stok baru: %d\n",
                   products[i].stock);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Produk dengan ID %d tidak ditemukan!\n", id);
    }
}

void freeProducts(Product* products, int count) {
    for (int i = 0; i < count; i++) {
        free(products[i].name);
    }
}