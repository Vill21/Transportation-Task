#include <iostream>
#include <vector>

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
      std::cout << "(" << x << "," << y << "): ";
      int num = 0;
      std::cin >> num;
      map[x][y] = num;
      std::cout << "\n";
    }
  }
}
std::vector<std::vector<int>> calculate(std::vector<int> _providers, std::vector<int> _customers, const std::vector<std::vector<int>>& _map) {
  std::vector<std::vector<int>> answer(_providers.size(), std::vector<int>(_customers.size()));
  const int x_size = (int)_map.size();
  const int y_size = (int)_map[0].size();
  int current_min = INT_MAX;
  int min_post = NULL;
  int min_potr = NULL;
  int potrebnost = 1;

  while (potrebnost != 0) {
    for (int i = 0; i < x_size; ++i) {
      if(_providers[i] != 0)
      for (int j = 0; j < y_size; ++j) {
        if(_customers[j] != 0)
        if (_map[i][j] < current_min) {
          current_min = _map[i][j];
          min_post = i;
          min_potr = j;
        }
      }
    }
    if (_providers[min_post] <= _customers[min_potr]) {
      answer[min_post][min_potr] = _providers[min_post];
      _customers[min_potr] -= _providers[min_post];
      _providers[min_post] = 0;
      current_min = INT_MAX;
    }
    else {
      answer[min_post][min_potr] = _customers[min_potr];
      _providers[min_post] -= _customers[min_potr];
      _customers[min_potr] = 0;
      current_min = INT_MAX;
    }
    potrebnost = 0;
    for (int i : _customers) {
      potrebnost += i;
    }
  }
  return answer;
}

int main() {
  const int prov_cnt = 4;
  const int custom_cnt = 5;

  std::vector<int> providers(prov_cnt);
  std::vector<int> customers(custom_cnt);

  std::vector<std::vector<int>> map(prov_cnt, std::vector<int>(custom_cnt));

  std::cout << "Providers: \n";
  initialize(providers, prov_cnt);

  std::cout << "Customers: \n";
  initialize(customers, custom_cnt);

  std::cout << "Map: \n";
  initialize(map);

  // std::vector<int> ans_line = minimum_line(providers, map);
  // std::vector<int> ans_row = minimum_row(customers, map, providers);

  // Providers: 100 300 180 320
  // Customers: 200 250 120 130 200
  // Map: 10 7 2 5 5 4 9 8 1 3 5 12 16 8 7 7 4 6 3 11

    std::vector<std::vector<int>> answer = calculate(providers, customers, map);

  return 0;
}