#include <iostream>
#include <vector>
#include <limits>
#include <cstddef>
#include <algorithm>

void initialize(std::vector<int>& vec, const int& size) {
    for (int i = 0; i < size; ++i) {
        int num = 0;
        std::cin >> num;
        vec[i] = num;
    }
}
void initialize(std::vector<std::vector<int>>& map) {
    const int x_size = (int)map.size();
    const int y_size = (int)map[0].size();
    
    for (int x = 0; x < x_size; ++x) {
        for (int y = 0; y < y_size; ++y) {
            // std::cout << "(" << x << "," << y << "): ";
            int num = 0;
            std::cin >> num;
            map[x][y] = num;
            // std::cout << "\n";
        }
    }
}

bool fin(const std::vector<int>& vec) {
    bool isEmpty = true;
    for (int x : vec) {
        if (x != 0) {
            isEmpty = false;
            break;
        }
    }
    return isEmpty;
}

std::vector<int> minimum_line(const std::vector<int>& compare, const std::vector<std::vector<int>>& map) {
    const int i_size = (int)map.size();
    const int j_size = (int)map[0].size();
    std::vector<int> answer(i_size, -1);
    
    for (int i = 0; i < i_size; ++i) {
        //если поставщик остался без товара - его не учитывать
        if (compare[i] == 0) continue;
        
        //нахождение первого минимума по цене перевозки
        int min_1 = std::numeric_limits<int>::max();
        std::pair<int, int> ind = {-1, -1};
        for (int j = 0; j < j_size; ++j) {
            if (map[i][j] < min_1) {
                min_1 = map[i][j];
                ind = {i, j};
            }
        }
        
        //нахождение второго минимума по цене перевозки
        int min_2 = std::numeric_limits<int>::max();
        for (int j = 0; j < j_size; ++j) {
            if (i == ind.first && j == ind.second) continue;
            if (map[i][j] >= min_1 && map[i][j] < min_2) {
                min_2 = map[i][j];
            }
        }
        
        answer[i] = min_2 - min_1;
    }
    
    return answer;
}

std::vector<int> minimum_row(const std::vector<int>& compare, const std::vector<std::vector<int>>& map, const std::vector<int>& _providers) {
    const int i_size = (int)map.size();
    const int j_size = (int)map[0].size();
    std::vector<int> answer(j_size, -1);
    
    for (int j = 0; j < j_size; ++j) {
        if (compare[j] == 0) continue;
        
        //нахождение первого минимума по цене перевозки
        int min_1 = std::numeric_limits<int>::max();
        std::pair<int, int> ind = {-1, -1};
        for (int i = 0; i < i_size; ++i) {
            if (_providers[i] == 0) continue;
            if (map[i][j] < min_1) {
                min_1 = map[i][j];
                ind = {i, j};
            }
        }
        
        //нахождение второго минимума по цене перевозки
        int min_2 = std::numeric_limits<int>::max();
        for (int i = 0; i < i_size; ++i) {
            if (_providers[i] == 0) continue;
            if (i == ind.first && j == ind.second) continue;
            if (map[i][j] >= min_1 && map[i][j] < min_2) {
                min_2 = map[i][j];
            }
        }
        
        answer[j] = min_2 - min_1;
    }
    
    return answer;
}

//Метод апроксимации Фогеля (на рядах)
std::vector<std::vector<int>> calculate(std::vector<int> _providers, std::vector<int> _customers, const std::vector<std::vector<int>>& _map) {
    std::vector<std::vector<int>> answer(_providers.size(), std::vector<int>(_customers.size()));
    const int x_size = (int)_map.size();
    const int y_size = (int)_map[0].size();
    
    while (fin(_providers) == false && fin(_customers) == false) {
        std::vector<int> row = minimum_row(_customers, _map, _providers);
        
        // ищем максимальную разницу в значениях потребностей (самую высокую потребность)
        int max_row = -1;
        int y_max = -1;
        for (int i = 0; i < y_size; ++i) {
            if (row[i] > max_row) {
                max_row = row[i];
                y_max = i;
            }
        }
        
        std::vector<int> vec_max{y_max};
        for (int i = 0; i < y_size; ++i) {
            if (y_max != i && row[i] == max_row) vec_max.push_back(i);
        }
        
        // ищем минимальную цену поставки
        int min_line = std::numeric_limits<int>::max();
        int x_min = -1;
        int y_min = -1;
        
        for (int ind : vec_max) {
            for (int i = 0; i < x_size; ++i) {
                if (answer[i][ind] != 0) continue;
                if (_providers[i] == 0) continue;
                if (_map[i][ind] < min_line) {
                    min_line = _map[i][ind];
                    x_min = i;
                    y_min = ind;
                }
            }
        }
        
        if (x_min != -1 && y_min != -1) {
            int add = std::min(_providers[x_min], _customers[y_min]);
            _providers[x_min] -= add;
            _customers[y_min] -= add;
            answer[x_min][y_min] = add;
        }
    };
    
    return answer;
}

int main() {
    constexpr int prov_cnt = 4;
    constexpr int custom_cnt = 5;
    
    std::vector<int> providers(prov_cnt);
    std::vector<int> customers(custom_cnt);
    
    std::vector<std::vector<int>> map(prov_cnt, std::vector<int>(custom_cnt));
    
    std::cout << "Providers: \n";
    initialize(providers, prov_cnt);
    
    std::cout << "Customers: \n";
    initialize(customers, custom_cnt);
    
    std::cout << "Map: \n";
    initialize(map);
    
    // Example: 
    // Providers: 100 300 180 320
    // Customers: 200 250 120 130 200
    // Map: 10 7 2 5 5 4 9 8 1 3 5 12 16 8 7 7 4 6 3 11
    
    std::vector<std::vector<int>> answer = calculate(providers, customers, map);
    
    return 0;
}
