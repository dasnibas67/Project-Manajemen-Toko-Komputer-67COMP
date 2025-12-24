#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "transaction.h"

// load transaksi dari file
int loadTransactions(const char* filename, Transaction** transactions, int* capacity) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    
    char buffer[256];
    int count = 0;
    
    while (fgets(buffer, sizeof(buffer), file) != NULL && count < *capacity) {
        buffer[strcspn(buffer, "\n")] = 0;
        
        char* token = strtok(buffer, "|");
        if (token != NULL) {
            (*transactions)[count].id = atoi(token);
            
            token = strtok(NULL, "|");
            (*transactions)[count].productId = (token != NULL) ? atoi(token) : 0;
            
            token = strtok(NULL, "|");
            if (token != NULL) {
                (*transactions)[count].productName = strdup(token);
            }
            
            token = strtok(NULL, "|");
            (*transactions)[count].quantity = (token != NULL) ? atoi(token) : 0;
            
            token = strtok(NULL, "|");
            (*transactions)[count].totalPrice = (token != NULL) ? atoi(token) : 0;
            
            token = strtok(NULL, "|");
            if (token != NULL) {
                (*transactions)[count].date = strdup(token);
            }
            
            count++;
        }
    }
    
    fclose(file);
    return count;
}

// simpan transaksi ke file
void saveTransactions(const char* filename, Transaction* transactions, int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Gagal menyimpan transaksi!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%d|%s|%d|%d|%s\n",
                transactions[i].id,
                transactions[i].productId,
                transactions[i].productName,
                transactions[i].quantity,
                transactions[i].totalPrice,
                transactions[i].date);
    }
    
    fclose(file);
}

void buyProduct(Product* products, int productCount, Transaction** transactions, int* transactionCount, int* transactionCapacity) {
    int id, qty;
    
    printf("\nMasukkan ID produk yang ingin dibeli: ");
    scanf("%d", &id);
    
    int found = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Produk tidak ditemukan!\n");
        return;
    }
    
    printf("Produk: %s (Stok: %d)\n", products[found].name, products[found].stock);
    printf("Masukkan jumlah: ");
    scanf("%d", &qty);
    
    if (qty > products[found].stock) {
        printf("Stok tidak cukup!\n");
        return;
    }
    
    if (qty <= 0) {
        printf("Jumlah tidak valid!\n");
        return;
    }
    
    // update stok dan sold 
    products[found].stock -= qty;
    products[found].sold += qty;

    products[found].sold |= (1 << 0);
    
    // tambah transaksi baru
    if (*transactionCount >= *transactionCapacity) {
        *transactionCapacity *= 2;
        Transaction* temp = (Transaction*)realloc(*transactions, (*transactionCapacity) * sizeof(Transaction));
        if (temp == NULL) {
            printf("Gagal alokasi memori!\n");
            return;
        }
        *transactions = temp;
    }
    
    // waktu sekarang
    time_t now = time(NULL);
    char* dateStr = (char*)malloc(20 * sizeof(char));
    strftime(dateStr, 20, "%Y-%m-%d %H:%M", localtime(&now));
    
    int newId = (*transactionCount > 0) ? (*transactions)[*transactionCount - 1].id + 1 : 1;
    
    (*transactions)[*transactionCount].id = newId;
    (*transactions)[*transactionCount].productId = products[found].id;
    (*transactions)[*transactionCount].productName = strdup(products[found].name);
    (*transactions)[*transactionCount].quantity = qty;
    (*transactions)[*transactionCount].totalPrice = products[found].price * qty;
    (*transactions)[*transactionCount].date = dateStr;
    
    (*transactionCount)++;
    
    printf("\n=== TRANSAKSI BERHASIL ===\n");
    printf("Produk: %s\n", products[found].name);
    printf("Jumlah: %d\n", qty);
    printf("Total: Rp%d\n", products[found].price * qty);
    printf("==========================\n\n");
}

// riwayat transaksi
void displayTransactions(Transaction* transactions, int count) {
    if (count == 0) {
        printf("\nBelum ada transaksi.\n\n");
        return;
    }
    printf("\n========== RIWAYAT TRANSAKSI ==========\n");
    printf("%-4s %-60s %-8s %-20s %-22s\n",
           "ID", "Produk", "Qty", "Total", "Tanggal");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-4d %-60.60s %-8d Rp%-18d %-22s\n",
               transactions[i].id,
               transactions[i].productName,
               transactions[i].quantity,
               transactions[i].totalPrice,
               transactions[i].date);
    }
    printf("\n");
}

// statistik penjualan
void displayStatistics(Product* products, int productCount) {
    printf("\n=== STATISTIK PENJUALAN ===\n");
    
    int totalRevenue = 0;
    int totalSold = 0;
    
    for (int i = 0; i < productCount; i++) {
        int everSold = (products[i].sold & (1 << 0)) ? 1 : 0;
        
        if (everSold) {
            int soldQty = products[i].sold;
            int revenue = soldQty * products[i].price;
            totalRevenue += revenue;
            totalSold += soldQty;
            
            printf("- %s: %d unit terjual (Rp%d)\n", 
                   products[i].name, soldQty, revenue);
        }
    }
    
    printf("\nTotal Unit Terjual: %d\n", totalSold);
    printf("Total Pendapatan: Rp%d\n", totalRevenue);
    printf("===========================\n\n");
}

void freeTransactions(Transaction* transactions, int count) {
    for (int i = 0; i < count; i++) {
        free(transactions[i].productName);
        free(transactions[i].date);
    }
}