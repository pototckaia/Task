#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//Напишите программу которая открывает файл "input.txt" и удаляет в ней все пробелы и числа

int main(int argc, char **argv) {
    std::string fileName = "input.txt";
    std::string tmpFileName = "__tmp.txt";
    std::fstream ifile(fileName, std::fstream::in);
    std::fstream tmp(tmpFileName, std::fstream::out | std::fstream::trunc | std::fstream::in);
    std::vector<char> buffer(1024, '\0');

    do {
        ifile.read(buffer.data(), buffer.size());
        long sizeBuffer = ifile.gcount();
        for (std::size_t i = 0; i < sizeBuffer; ++i) {
            if (!std::isdigit(buffer[i]) && buffer[i] != ' ')
                tmp << buffer[i];
        }
    } while (ifile.gcount());
    ifile.close();

    tmp.seekg(0, std::fstream::beg);
    ifile.open(fileName, std::ofstream::out | std::ofstream::trunc);
    do {
        tmp.read(buffer.data(), buffer.size());
        long sizeBuffer = tmp.gcount();
        for (std::size_t i = 0; i < sizeBuffer; ++i) {
            ifile << buffer[i];
        }
    } while (tmp.gcount());
    tmp.close();
    ifile.close();
    std::remove(tmpFileName.c_str());
}