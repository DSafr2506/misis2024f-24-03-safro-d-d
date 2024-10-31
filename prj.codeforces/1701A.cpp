#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::vector<std::vector<int>> a(2, std::vector<int>(2));
        
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                std::cin >> a[i][j];
            }
        }
        
        int cnt = a[0][0] + a[0][1] + a[1][0] + a[1][1];
        
        if (cnt == 0) {
            std::cout << 0 << std::endl;
        } else if (cnt == 4) {
            std::cout << 2 << std::endl;
        } else {
            std::cout << 1 << std::endl;
        }
    }

    return 0;
}
