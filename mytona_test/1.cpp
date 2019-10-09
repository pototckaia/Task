#include <iostream>
#include <vector>

// Программа ждет ввода строки неограниченной длины.
// Затем программа ждет ввода символа.
// После чего она должна разбить первую строку в другие подстроки,
// используя второй параметр в виде разделителя и вывести на экран.

int main(int argc, char **argv) {
    std::string s;
    std::cin >> s;

    char del;
    std::cin >> del;

    std::vector<std::string> sub;

    unsigned long startOf = 0, posDel = s.find(del);
    while (posDel != std::string::npos) {
        sub.push_back(s.substr(startOf, posDel - startOf));
        startOf = posDel + 1;
        posDel = s.find(del, startOf);
    }
    sub.push_back(s.substr(startOf));

    std::cout << "size: " << sub.size() << std::endl;
    for (auto &e: sub) {
        std::cout << "'" << e << "'" << std::endl;
    }

    return 0;
}