#include <iostream>
#include <vector>
#include <fstream>

unsigned month[13] = {31, 28, 31,
                 30, 31, 30,
                 31, 31, 30,
                 31, 30, 31};

unsigned bust[6][3] = {{0, 1, 2},
                 {0, 2, 1},
                 {1, 0, 2},
                 {1, 2, 0},
                 {2, 0, 1},
                 {2, 1, 0}
};

const char *fileread    = "chronicle.in";
const char *filewrite   = "chronicle.out";

bool check_data(unsigned dd, unsigned mm, unsigned yy) {
    if ((mm < 1 || mm >= 13) || (yy > 100)) {
        return false;
    }

    if (mm == 2) {
        unsigned yy_ = yy + 2000;
        if (yy == 0) {
            yy_ = 2100;
        }
        if ((yy_ % 4 == 0 && yy_ % 100 != 0) || yy_ % 400 == 0) { // Високосный
            if (dd > 29 || dd < 1) {
                return false;
            } else {
                return true;
            }
        } else { // невисокосный
            if (dd > 28 || dd < 1) {
                return false;
            } else {
                return true;
            }
        }
    }

    unsigned max_data = month[mm - 1];
    if (dd > max_data || dd < 1) {
        return false;
    } else {
        return true;
    }
}


void suc_print(unsigned day, unsigned month, unsigned year) {
    std::string str_d = (day < 10) ? "0" : "";
    std::string str_m = (month < 10) ? "0" : "";
    std::string str_y = (year < 10) ? "0" : "";
    std::cout << str_d << day << "/" << str_m << month << "/" << str_y << year << std::endl;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::freopen("chronicle.in", "r", stdin);
    std::freopen("chronicle.out", "w", stdout);

    unsigned data[3];
    char sep;
    std::cin >> data[0];
    std::cin >> sep;
    std::cin >> data[1];
    std::cin >> sep;
    std::cin >> data[2];

    bool is_valid = false;
    for (auto &e: bust) {
        if ((data[e[0]] == data[e[1]] && e[0] > e[1]) ||
            (data[e[1]] == data[e[2]] && e[1] > e[2]) ||
            (data[e[0]] == data[e[2]] && e[0] > e[2])
            ) {
            continue;
        }
        if (check_data(data[e[0]], data[e[1]], data[e[2]]) ) {
            is_valid = true;
            suc_print(data[e[0]], data[e[1]], data[e[2]]);
        }
    }

    if (!is_valid) {
        std::cout << "No such date" << std::endl;
    }



}