#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> a;
std::vector<int> b;
std::vector<std::vector<int>> plan;

void initialize() {
    int an, bn, ai, bj;

    std::cout << "Num of providers:\n";
    std::cin >> an;
    std::cout << "Enter " << an << " providers' values:\n";
    for (int i = 0; i < an; ++i) {
        std::cin >> ai;
        a.push_back(ai);
    }

    std::cout << "Num of customers:\n";
    std::cin >> bn;
    std::cout << "Enter " << bn << " customers' values:\n";
    for (int i = 0; i < bn; ++i) {
        std::cin >> bj;
        b.push_back(bj);
    }

    plan = std::vector<std::vector<int>>(a.size(), std::vector<int>(b.size()));
}

void calculate() {
    int min;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            if (b[j] == 0) continue;
            min = std::min(a[i], b[j]);
            plan[i][j] = min;
            a[i] -= min;
            b[j] -= min;
            if (a[i] == 0) break;
        }
    }
}

void printAnswer() {
    std::cout << "Basic plan:\n";
    for (int i = 0; i < plan.size(); ++i) {
        for (int j = 0; j < plan[0].size(); ++j) {
            std::cout << plan[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main()
{
    initialize();
    calculate();
    printAnswer();
}