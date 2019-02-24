#include <chrono>
#include "./Matrix.h"
#include "./NeuralNetwork.cpp"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  // srand(0);
  NeuralNetwork nn(2, 8, 1);

  std::vector<std::vector<float> > v;

  v.push_back({1, 0});
  v.push_back({1, 1});
  v.push_back({0, 0});
  v.push_back({0, 1});

  std::vector<std::vector<float> > t;

  t.push_back({1});
  t.push_back({0});
  t.push_back({0});
  t.push_back({1});

  for (size_t i = 0; i < 400000; i++) {

    int randomIndex = rand() % v.size();
    nn.train(v[randomIndex], t[randomIndex]);
  }

  std::cout << nn.calc({0, 0})[0] << std::endl;
  std::cout << nn.calc({1, 1})[0] << std::endl;
  std::cout << nn.calc({1, 0})[0] << std::endl;
  std::cout << nn.calc({0, 1})[0] << std::endl;

  return 0;
}