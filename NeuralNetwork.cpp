#pragma once
#include "./NeuralNetwork.h"
#include <cstdlib>

// _____________________________________________________________________________
NeuralNetwork::NeuralNetwork(int input, int hidden, int output) {
  _input = input;
  _hidden = hidden;
  _output = output;

  Matrix input_hidden_w(hidden, input);
  Matrix hidden_output_w(output, hidden);

  Matrix bias_hidden_w(hidden, 1);
  Matrix bias_output_w(output, 1);

  learning_rate = 0.1;
}

// _____________________________________________________________________________
NeuralNetwork::~NeuralNetwork() {}

// _____________________________________________________________________________
std::vector<float> NeuralNetwork::calc(std::vector<float> input_array) {
  Matrix inputs(input_array.size(), 1, input_array);
  // Matrix hidden = input_hidden_w.mul(inputs);
  // input_hidden_w.print();

  return input_array;
}
