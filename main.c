#include <stdio.h>
#include <stdlib.h>
#include "product.h"
#include "transaction.h"
#include "utils.h"

int main() {
    int productCapacity = 20;
    Product* products = (Product*)malloc(productCapacity * sizeof(Product));
    if (products == NULL) {
        printf("Gagal alokasi memori untuk produk!\n");
        return 1;
    }

    int transactionCapacity = 50;
    Transaction* transactions = (Transaction*)malloc(transactionCapacity * sizeof(Transaction));
    if (transactions == NULL) {
        printf("Gagal alokasi memori untuk transaksi!\n");
        free(products);
        return 1;
    }

    int productCount = loadProducts("products.txt", &products, &productCapacity);
    int transactionCount = loadTransactions("transactions.txt", &transactions, &transactionCapacity);

    if (productCount == 0) {
        initializeDefaultProducts(&products, &productCount, &productCapacity);
        saveProducts("products.txt", products, productCount);
    }
    
    printf("Data berhasil dimuat!\n");
    printf("Produk: %d item\n", productCount);
    printf("Transaksi: %d item\n", transactionCount);

    int choice;
    int running = 1;
    
    while (running) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                // daftar produk
                clearScreen();
                displayProducts(products, productCount);
                pauseScreen();
                break;
                
            case 2:
                // beli produk 
                clearScreen();
                displayProducts(products, productCount);
                buyProduct(products, productCount, &transactions, &transactionCount, &transactionCapacity);
                
                // save data setelah transaksi
                saveProducts("products.txt", products, productCount);
                saveTransactions("transactions.txt", transactions, transactionCount);
                pauseScreen();
                break;
                
            case 3:
                // tambah stok 
                clearScreen();
                displayProducts(products, productCount);
                addStock(products, productCount);
                
                // save data setelah update stok
                saveProducts("products.txt", products, productCount);
                pauseScreen();
                break;
                
            case 4:
                // riwayat transaksi
                clearScreen();
                displayTransactions(transactions, transactionCount);
                pauseScreen();
                break;
                
            case 5:
                // statistik penjualan
                clearScreen();
                displayStatistics(products, productCount);
                pauseScreen();
                break;
                
            case 6:
                // keluar
                printf("\nTerima kasih telah berbelanja broo!\n");
                running = 0;
                break;
                
            default:
                printf("\nPilihan tidak valid!\n");
                pauseScreen();
                break;
        }
        
        clearScreen();
    }

    freeProducts(products, productCount);
    freeTransactions(transactions, transactionCount);
    free(products);
    free(transactions);
    
    return 0;
}