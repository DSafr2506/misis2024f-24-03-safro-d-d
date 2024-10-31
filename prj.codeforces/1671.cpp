#include <iostream>
#include <string>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::string s;
        std::cin >> s;
        bool ans = true;
        int n = s.length();

        for (int j = 0; j < n; ++j) {
            if ((j == 0 || s[j] != s[j - 1]) && (j == n - 1 || s[j] != s[j + 1])) {
                ans = false;
                break;
            }
        }

        std::cout << (ans ? "YES" : "NO") << std::endl;
    }
    return 0;
}
