#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

const char *fileread = "swords.in";
const char *filewrite   = "swords.out";

int main() {
    std::ios::sync_with_stdio(false);
    std::freopen(fileread, "r", stdin);
    std::freopen(filewrite, "w", stdout);

    int n, k;
    std::cin >> n;
    std::cin >> k;
    std::vector<int> swords(n);
    std::vector<int> index_swords(n);
    std::vector<int> father(n, -1);

    for (int i = 0; i < n; ++i) {
        std::cin >> swords[i];
        index_swords[i] = i;
    }

    std::sort(index_swords.begin(), index_swords.end(),
            [&swords](std::size_t i1, std::size_t i2) { return swords[i1] > swords[i2]; } );

    int ac = index_swords[0];
    father[ac] = 0;
    bool error = false;

    for (int i = 1; i < n; i += 2) {
        int need_age = swords[ac] - k;
        if (swords[i] <= need_age) { father[i] = ac; }
        if (swords[i + 1] <=  need_age) { father[i] = }
    }



    for (int i = 0; i < n; ++i)
        std::cout << swords[i] << ' ' << swords[index_swords[i]] << std::endl;
}