#include <iostream>


const char *fileread    = "number.in";
const char *filewrite   = "number.out";

bool more(const std::string& a, int sep) { // >

    // обрезать нули
    int i; // начало первой строки
    for (i = 0; i < sep && a[i] == '0'; ++i) {}
    int size_first = sep - i;

    int j; // начало втрой строки
    for (j = sep; j < a.size() && a[j] == '0'; ++j) {}
    int size_second = a.size() - j;

    if (size_first != size_second) {return size_first > size_second; }

    int k;
    for (k = i; k < size_first && a[k] == a[size_first + k]; ++k) {}

    if (k == size_first) { return false; }

    return a[k] > a[size_first + k];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::freopen(fileread, "r", stdin);
    std::freopen(filewrite, "w", stdout);

    std::string str;
    std::cin >> str;

    unsigned count = 0;

    for (int i = 1;  str[0] != '0' && i < str.size() - 1; ++i) {
        if (str[i] == '0') { continue; }
        if (more(str, i)) { break; }

//        std::cout << str.substr(0, i) << ' ' << str.substr(i, str.size()) << std::endl;
        count++;
    }

    std::cout << count;
}