#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "product.h"

typedef struct {
    int id;
    int productId;
    char* productName;
    int quantity;
    int totalPrice;
    char* date;
} Transaction;

int loadTransactions(const char* filename, Transaction** transactions, int* capacity);
void saveTransactions(const char* filename, Transaction* transactions, int count);
void buyProduct(Product* products, int productCount, Transaction** transactions, int* transactionCount, int* transactionCapacity);
void displayTransactions(Transaction* transactions, int count);
void displayStatistics(Product* products, int productCount);
void freeTransactions(Transaction* transactions, int count);

#endif