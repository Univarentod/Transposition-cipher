#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

int setTransvector(int &row_num, int &colunm_num) {
    std::cout << "Intput your row number and colunm number:" << std::endl;
    fflush(stdin);
    scanf("%d%d", &row_num, &colunm_num);
    fflush(stdin);
    if (row_num < 1 || colunm_num < 1) return 0;
    return row_num*colunm_num;
}

std::vector<unsigned int> setKey(unsigned int colunm_num) {
    std::cout << "Input your key:" << std::endl;
    fflush(stdin);
    std::vector<unsigned int> buffer;
    buffer.resize(colunm_num, colunm_num);
    for (unsigned int i = 0, in = 0; i < colunm_num; i++) {
        scanf("%u", &in);
        if (in > colunm_num || in == 0) {
            std::cout << "Invalid input!" << std::endl;
            return std::vector<unsigned int>();
        }
        buffer[in-1] = i;
    }
    for (unsigned int i = 0; i < colunm_num; i++) {
        if (buffer[i] == colunm_num) {
            std::cout << "Invalid input!" << std::endl;
            return std::vector<unsigned int>();
        }
    }
    fflush(stdin);
    return buffer;
}

bool selectMode() {
    std::cout << std::endl << "If encrypt, input '1'. If decrypt, input '0':" << std::endl;
    fflush(stdin);
    unsigned int mode = 2;
    while (mode > 1) {
        if (!scanf("%u", &mode)) {
            fflush(stdin);
        }
    }
    fflush(stdin);
    return mode;
}

bool encrypt(std::vector<unsigned int> key, unsigned int row_num, unsigned int check_colunm_num, unsigned int length) {
    unsigned int colunm_num = key.size();
    if (colunm_num != check_colunm_num) {
        std::cout << "Something wrong happens" << std::endl;
    }
    std::cout << "Input your plaintext:" << std::endl;
    fflush(stdin);
    std::string plaintext;
    std::cin >> plaintext;
    if (plaintext.length() != length) {
        std::cout << "Invalid plaintext!" << std::endl;
        return false;
    }
    for (unsigned int i = 0; i < colunm_num; i++) {
        for (unsigned int j = 0, k = key[i]; j < row_num; j++) {
            std::cout << plaintext[colunm_num*j+k];
        }
    }
    return true;
}

std::vector<unsigned int> keyInverse(std::vector<unsigned int> key) {
    unsigned int colunm_num = key.size();
    std::vector<unsigned int> new_key;
    new_key.resize(colunm_num, 0);
    for (unsigned int i = 0; i < colunm_num; i++) {
        new_key[key[i]] = i;
    }
    return new_key;
}

bool decrypt(std::vector<unsigned int> key, unsigned int row_num, unsigned int check_colunm_num, unsigned int length) {
    unsigned int colunm_num = key.size();
    if (colunm_num != check_colunm_num) {
        std::cout << "Something wrong happens" << std::endl;
    }
    std::cout << "Input your ciphertext:" << std::endl;
    fflush(stdin);
    std::string ciphertext;
    std::cin >> ciphertext;
    if (ciphertext.length() != length) {
        std::cout << "Invalid ciphertext!" << std::endl;
        return false;
    }
    key = keyInverse(key);
    for (unsigned int i = 0; i < row_num; i++) {
        for (unsigned int j = 0; j < colunm_num; j++) {
            std::cout << ciphertext[row_num*key[j]+i];
        }
    }
    return true;
}

int main() {
    int row_num = 0, colunm_num = 0;
    unsigned int length = setTransvector(row_num, colunm_num);
    if (!length) {
        std::cout << "Invalid input!" << std::endl;
        system("pause");
        return 1;
    }
    std::vector<unsigned int> key;
    while (key.empty()) {
        key = setKey(colunm_num);
    }
    while (true) {
        if (selectMode()) {
            encrypt(key, row_num, colunm_num, length);
        } else {
            decrypt(key, row_num, colunm_num, length);
        }
    }
    return 0;
}
