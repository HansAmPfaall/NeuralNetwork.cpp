#include <chrono>
#include "./Matrix.h"

int main(int argc, char const *argv[]) {
  std::cout << "Start Constructor" << std::endl;
  {
    Matrix t(400, 200, 0);
    for (int i = 0; i < t._colNum * t._rowNum; i++) {
      assert(0 == t._storage[i]);
    }
  }
  std::cout << "Constructor Succesfull" << std::endl;
  std::cout << std::endl;

  std::cout << "Start second Constructor" << std::endl;
  {
    std::vector<float> v;
    for (int i = 0; i < 200 * 400; i++) {
      v.push_back(i);
    }
    Matrix t(400, 200, v);
    for (int i = 0; i < t._colNum * t._rowNum; i++) {
      assert(i == t._storage[i]);
    }
  }
  std::cout << "second Constructor Succesfull" << std::endl;
  std::cout << std::endl;

  std::cout << "Start Matrixmultiplikation" << std::endl;
  {
    std::vector<float> v1;
    std::vector<float> v2;
    for (int i = 0; i < 2 * 3; i++) {
      v1.push_back(i);
      v2.push_back((5 * 5) - i);
    }
    Matrix a(2, 3, v1);
    Matrix b(3, 2, v2);
    Matrix c = a * b;
    std::vector<float> v3{65, 62, 272, 260};
    for (int i = 0; i < 2 * 2; i++) {
      assert(c._storage[i] == v3[i]);
    }
  }
  std::cout << "Matrixmultiplikation Succesfull" << std::endl;
  std::cout << std::endl;


    std::cout << "Start Matrixsubtraction" << std::endl;
  {
    std::vector<float> v1;
    std::vector<float> v2;
    for (int i = 0; i < 20 * 20; i++) {
      v1.push_back(i);
      v2.push_back(i);
    }
    Matrix a(20, 20, v1);
    Matrix b(20, 20, v2);
    Matrix c = a - b;
    std::vector<float> v3{0, 0, 0, 0};
    for (int i = 0; i < 2 * 2; i++) {
      assert(c._storage[i] == v3[i]);
    }
  }
  std::cout << "Matrixsubtraction Succesfull" << std::endl;
  std::cout << std::endl;

  std::cout << "ALL TESTS SUCCESFULL" << std::endl;

  // auto start = std::chrono::system_clock::now();
  // auto end = std::chrono::system_clock::now();
  // auto elapsed = end - start;
  // std::cout << elapsed.count() / 1000000000.0 << '\n';
  return 0;
}