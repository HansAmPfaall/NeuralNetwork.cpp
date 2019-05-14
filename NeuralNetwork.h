#pragma once
#include "./Matrix.h"

class NeuralNetwork {
 public:
  // Constructor.
  NeuralNetwork(int input, int hidden, int output, float lr);
  // Destructor.
  ~NeuralNetwork();

  std::vector<float> calc(std::vector<float> input_array);

  void train(std::vector<float> input_array, std::vector<float> target_array);

  void trainN(std::vector<float> input_array, std::vector<float> target_array);

  void mutate();

  float learning_rate;

  Matrix input_hidden_w;
  Matrix hidden_output_w;

  Matrix bias_hidden_w;
  Matrix bias_output_w;

 private:
  int _input;
  int _hidden;
  int _output;
};
