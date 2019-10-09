

//Заполните случайными значениями два массива A и B.
// Выведите на экран сначала A потом B.
// Объедините A и B в массив C, отсортируйте его по возрастанию и выведите его на экран.
// Выведите максимальное, минимальное и среднее геометрическое значения из массива C.

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>


template<typename T>
void randomFill(std::vector<T> &v) {
    // We use static in order to instantiate the random engine
    // and the dis once only.
    // It may provoke some thread-safety issues.
    std::uniform_int_distribution<T> dis(
            std::numeric_limits<T>::min(),
            std::numeric_limits<T>::max());

    std::random_device seed;
    std::mt19937_64 gen(seed());

    std::generate(v.begin(), v.end(), [&dis, &gen]() { return dis(gen); });
}

template<typename T>
void printVector(std::vector<T> &v) {
    std::for_each(v.begin(), v.end(), [](auto x) { std::cout << x << " "; });
    std::cout << std::endl;
}


int main(int argc, char **argv) {
    unsigned long sizeA = 5, sizeB = 5;

    if (argc == 2) {
        sizeA = sizeB = std::stoul(argv[1]);
    } else if (argc == 3) {
        sizeA = std::stoul(argv[1]);
        sizeB = std::stoul(argv[2]);
    }

    std::vector<int> A(sizeA), B(sizeB), C;
    randomFill(A);
    randomFill(B);

    printVector(A);
    printVector(B);

    C.insert(C.end(), A.begin(), A.end());
    C.insert(C.end(), B.begin(), B.end());

    std::sort(C.begin(), C.end());
    printVector(C);

    std::cout << "Max: " << C.back()
              << " Min: " << C[0]
              << " Avg: " << std::accumulate(C.begin(), C.end(), 0) / C.size()
              << std::endl;

}