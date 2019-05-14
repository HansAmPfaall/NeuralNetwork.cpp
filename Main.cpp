#include <chrono>
#include "./Matrix.h"
#include "./NeuralNetwork.cpp"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  // srand(0);
  NeuralNetwork nn(4, 16, 2, 0.2);

  std::vector<std::vector<float> > v;

  v.push_back({0, 0, 0, 0});
  v.push_back({0, 0, 0, 1});
  v.push_back({0, 0, 1, 0});
  v.push_back({0, 0, 1, 1});
  v.push_back({0, 1, 0, 0});
  v.push_back({0, 1, 0, 1});
  v.push_back({0, 1, 1, 0});
  v.push_back({0, 1, 1, 1});
  v.push_back({1 ,0, 0, 0});
  v.push_back({1 ,0, 0, 1});
  v.push_back({1 ,0, 1, 0});
  v.push_back({1 ,0, 1, 1});
  v.push_back({1 ,1, 0, 0});
  v.push_back({1 ,1, 0, 1});
  v.push_back({1 ,1, 1, 0});
  v.push_back({1 ,1, 1, 1});

  std::vector<std::vector<float> > t;

  t.push_back({0, 1});
  t.push_back({1, 0});
  t.push_back({1, 0});
  t.push_back({0, 1});
  t.push_back({0, 1});
  t.push_back({1, 0});
  t.push_back({1, 0});
  t.push_back({0, 1});
  t.push_back({0, 1});
  t.push_back({1, 0});
  t.push_back({1, 0});
  t.push_back({0, 1});
  t.push_back({0, 1});
  t.push_back({1, 0});
  t.push_back({1, 0});
  t.push_back({0, 1});


  for (size_t i = 0; i < 10000000; i++) {
    int ri = rand() % v.size();
    nn.trainN(v[ri], t[ri]);
    // std::cout << v[ri][0] << v[ri][1] << t[ri][0] << std::endl;
  }

  std::vector<float> output;
  for (size_t i = 0; i < v.size(); i++) {
    output = nn.calc(v[i]);
    std::cout << output[0] << " != " << t[i][0] << std::endl;
  }

  return 0;
}