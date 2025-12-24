#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// inisialisasi produk default jika file tidak ada
void initializeDefaultProducts(Product** products, int* count, int* capacity) {
    *count = 10;
    
    if (*count > *capacity) {
        *capacity = *count;
        Product* temp = (Product*)realloc(*products, (*capacity) * sizeof(Product));
        if (temp == NULL) {
            printf("Gagal alokasi memori!\n");
            exit(1);
        }
        *products = temp;
    }
    
    // Produk 1: GPU Flagship / High-End
    (*products)[0].id = 1;
    (*products)[0].name = strdup("ROG Astral GeForce RTX 5090 32GB GDDR7 OC Edition");
    (*products)[0].category = GPU;
    (*products)[0].price = 67999000;
    (*products)[0].stock = 5;
    (*products)[0].sold = 0;
    
    // Produk 2: GPU Mid-Range
    (*products)[1].id = 2;
    (*products)[1].name = strdup("ASUS Prime Radeon RX 9070 XT OC Edition 16GB GDDR6");
    (*products)[1].category = GPU;
    (*products)[1].price = 14599000;
    (*products)[1].stock = 10;
    (*products)[1].sold = 0;
    
    // Produk 3: Keyboard
    (*products)[2].id = 3;
    (*products)[2].name = strdup("Wooting 60HE+ Keyboard");
    (*products)[2].category = KEYBOARD;
    (*products)[2].price = 3999000;
    (*products)[2].stock = 8;
    (*products)[2].sold = 0;
    
    // Produk 4: Mouse
    (*products)[3].id = 4;
    (*products)[3].name = strdup("Logitech G PRO X SUPERLIGHT 2 Mouse");
    (*products)[3].category = MOUSE;
    (*products)[3].price = 2399000;
    (*products)[3].stock = 15;
    (*products)[3].sold = 0;
    
    // Produk 5: Headset
    (*products)[4].id = 5;
    (*products)[4].name = strdup("Logitech PRO X 2 LIGHTSPEED Headset");
    (*products)[4].category = HEADSET;
    (*products)[4].price = 3199000;
    (*products)[4].stock = 12;
    (*products)[4].sold = 0;
    
    // Produk 6: IEM
    (*products)[5].id = 6;
    (*products)[5].name = strdup("Moondrop Aria 2 IEM");
    (*products)[5].category = IEM;
    (*products)[5].price = 1499000;
    (*products)[5].stock = 20;
    (*products)[5].sold = 0;
    
    // Produk 7: TWS
    (*products)[6].id = 7;
    (*products)[6].name = strdup("Moondrop X Honkai Star Rail Robin TWS");
    (*products)[6].category = TWS;
    (*products)[6].price = 1999000;
    (*products)[6].stock = 18;
    (*products)[6].sold = 0;
    
    // Produk 8: Microphone
    (*products)[7].id = 8;
    (*products)[7].name = strdup("Behringer TM1 Complete Microphone");
    (*products)[7].category = MICROPHONE;
    (*products)[7].price = 2099000;
    (*products)[7].stock = 10;
    (*products)[7].sold = 0;
    
    // Produk 9: RAM
    (*products)[8].id = 9;
    (*products)[8].name = strdup("Corsair 32GB VENGEANCE RGB 2x16 DDR5 RAM");
    (*products)[8].category = RAM;
    (*products)[8].price = 3999000;
    (*products)[8].stock = 25;
    (*products)[8].sold = 0;
    
    // Produk 10: SSD
    (*products)[9].id = 10;
    (*products)[9].name = strdup("SAMSUNG 990 PRO 1TB NVMe M.2 SSD");
    (*products)[9].category = SSD;
    (*products)[9].price = 2799000;
    (*products)[9].stock = 30;
    (*products)[9].sold = 0;
    
    printf("Data produk default berhasil dibuat!\n");
}

// menu utama
void displayMenu() {
    printf("\n========================================\n");
    printf("   TOKO 67COMP GAMING - MENU UTAMA\n");
    printf("========================================\n");
    printf("1. Lihat Daftar Produk\n");
    printf("2. Beli Produk\n");
    printf("3. Tambah Stok Produk\n");
    printf("4. Lihat Riwayat Transaksi\n");
    printf("5. Lihat Statistik Penjualan\n");
    printf("6. Keluar\n");
    printf("========================================\n");
    printf("Pilih menu: ");
}

void clearScreen() {
    printf("\n\n");
}

void pauseScreen() {
    printf("\nTekan Enter untuk melanjutkan...");
    while(getchar() != '\n');
    getchar();
}