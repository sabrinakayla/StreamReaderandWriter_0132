#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <vector>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    TokoElektronik() {
        etalase[0] = "Smart TV 4K";
        etalase[1] = "Kulkas Inverter";
        etalase[2] = "Air Conditioner (AC)";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            throw runtime_error("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};

const string FILE_GUDANG = "gudang.txt";

vector<string> bacaSemuaBarang() {
    vector<string> daftarBarang;
    ifstream fileInput(FILE_GUDANG);
    string barang;

    if (fileInput.is_open()) {
        while (getline(fileInput, barang)) {
            if (!barang.empty()) {
                daftarBarang.push_back(barang);
            }
        }
        fileInput.close();
    }
    return daftarBarang;
}

void tulisSemuaBarang(const vector<string>& daftarBarang) {
    ofstream fileOutput(FILE_GUDANG, ios::trunc);
    if (fileOutput.is_open()) {
        for (const auto& barang : daftarBarang) {
            fileOutput << barang << endl;
        }
        fileOutput.close();
    }
}

void tampilkanGudang() {
    vector<string> daftarBarang = bacaSemuaBarang();
    cout << "\n=== DAFTAR BARANG DI GUDANG ===" << endl;
    if (daftarBarang.empty()) {
        cout << "[Gudang Kosong / Belum ada data]" << endl;
    } else {
        for (size_t i = 0; i < daftarBarang.size(); ++i) {
            cout << i + 1 << ". " << daftarBarang[i] << endl;
        }
    }
    cout << "===============================" << endl;
}

void tambahBarang() {
    string barangBaru;
    cout << "Masukkan nama barang baru: ";
    cin.ignore();
    getline(cin, barangBaru);

    ofstream fileOutput(FILE_GUDANG, ios::app);
    if (fileOutput.is_open()) {
        fileOutput << barangBaru << endl;
        fileOutput.close();
        cout << "Sukses: Barang \"" << barangBaru << "\" berhasil ditambahkan ke gudang!\n";
    } else {
        cout << "Error: Gagal membuka file gudang.\n";
    }
}

void updateBarang() {
    tampilkanGudang();
    vector<string> daftarBarang = bacaSemuaBarang();
    if (daftarBarang.empty()) return;

    int nomor;
    cout << "Pilih nomor barang yang ingin diubah: ";
    cin >> nomor;

    if (nomor > 0 && nomor <= static_cast<int>(daftarBarang.size())) {
        string barangBaru;
        cout << "Masukkan nama baru untuk \"" << daftarBarang[nomor - 1] << "\": ";
        cin.ignore();
        getline(cin, barangBaru);

        daftarBarang[nomor - 1] = barangBaru;
        tulisSemuaBarang(daftarBarang);
        cout << "Sukses: Data barang berhasil diperbarui!\n";
    } else {
        cout << "Nomor tidak valid!\n";
    }
}

void hapusBarang() {
    tampilkanGudang();
    vector<string> daftarBarang = bacaSemuaBarang();
    if (daftarBarang.empty()) return;

    int nomor;
    cout << "Pilih nomor barang yang ingin dihapus: ";
    cin >> nomor;

    if (nomor > 0 && nomor <= static_cast<int>(daftarBarang.size())) {
        cout << "Sukses: Barang \"" << daftarBarang[nomor - 1] << "\" berhasil dihapus!\n";
        daftarBarang.erase(daftarBarang.begin() + (nomor - 1));
        tulisSemuaBarang(daftarBarang);
    } else {
        cout << "Nomor tidak valid!\n";
    }
}

void jalankanSimulasiEtalase(TokoElektronik& toko) {
    cout << "\n=== SIMULASI PENGUJIAN EXCEPTION HANDLING ===" << endl;

    cout << "[Skenario 1] Mengambil barang di rak indeks 1..." << endl;
    try {
        string produk = toko.ambilProduk(1);
        cout << "Hasil: Berhasil mengambil -> " << produk << "\n\n";
    }
    catch (const exception& e) {
        cout << "Hasil: Terjadi error -> " << e.what() << "\n\n";
    }

    cout << "[Skenario 2] Mengambil barang di rak indeks 5..." << endl;
    try {
        string produk = toko.ambilProduk(5);
        cout << "Hasil: Berhasil mengambil -> " << produk << "\n\n";
    }
    catch (const exception& e) {
        cout << "Hasil: Terjadi error -> " << e.what() << "\n\n";
    }
    cout << "=============================================" << endl;
}

int main() {
    TokoElektronik tokoGibran;
    int pilihan;

    do {
        tampilkanGudang();

        cout << "\n--- MENU MANAJEMEN TOKO \"GIBRAN JAYA\" ---" << endl;
        cout << "1. Tambah Barang Gudang (Create)" << endl;
        cout << "2. Ubah Barang Gudang (Update)" << endl;
        cout << "3. Hapus Barang Gudang (Delete)" << endl;
        cout << "4. Jalankan Simulasi Etalase (Exception Test)" << endl;
        cout << "5. Keluar Program" << endl;
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                updateBarang();
                break;
            case 3:
                hapusBarang();
                break;
            case 4:
                jalankanSimulasiEtalase(tokoGibran);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan sistem Toko Gibran Jaya." << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                break;
        }
        
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

    } while (pilihan != 5);

    return 0;
}