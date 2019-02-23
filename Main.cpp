#include <chrono>
#include "./Matrix.h"
#include "./NeuralNetwork.cpp"

int main(int argc, char const *argv[]) {
  NeuralNetwork nn(2, 4, 1);
  std::vector<float> v;
  v.push_back(1);
  v.push_back(3);
  v.push_back(3);
  v.push_back(7);
  nn.calc(v);
  // for (size_t j = 0; j < 10; j++) {
  //   auto start = std::chrono::system_clock::now();
  //   for (size_t i = 0; i < 10000; i++) {
  //     Matrix matrix(30, 80, 0);
  //     matrix.mult(matrix.t());
  //   }
  //   auto end = std::chrono::system_clock::now();
  //   auto elapsed = end - start;
  //   std::cout << elapsed.count() / 1000000000.0 << '\n';
  // }
  return 0;
}