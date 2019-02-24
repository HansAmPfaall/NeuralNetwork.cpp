#pragma once
#include "./NeuralNetwork.h"
#include <cstdlib>

// _____________________________________________________________________________
NeuralNetwork::NeuralNetwork(int input, int hidden, int output)
    : input_hidden_w(hidden, input),
      hidden_output_w(output, hidden),
      bias_hidden_w(hidden, 1),
      bias_output_w(output, 1) {
  _input = input;
  _hidden = hidden;
  _output = output;

  learning_rate = 0.02;
}

// _____________________________________________________________________________
NeuralNetwork::~NeuralNetwork() {}

// _____________________________________________________________________________
std::vector<float> NeuralNetwork::calc(std::vector<float> input_array) {
  Matrix inputs(input_array.size(), 1, input_array);
  Matrix hidden = input_hidden_w * inputs;
  hidden += bias_hidden_w;
  hidden.sigmoid();

  Matrix output = hidden_output_w * hidden;
  output += bias_output_w;
  output.sigmoid();

  return output.toVector();
}

void NeuralNetwork::train(std::vector<float> input_array,
                          std::vector<float> target_array) {
  Matrix inputs(input_array.size(), 1, input_array);
  Matrix hidden = input_hidden_w * inputs;
  hidden += bias_hidden_w;
  hidden.sigmoid();

  Matrix outputs = hidden_output_w * hidden;
  outputs += bias_output_w;
  outputs.sigmoid();

  Matrix targets(target_array.size(), 1, target_array);

  Matrix output_errors = targets - outputs;

  Matrix gradients = outputs.d_sigmoid_r();

  gradients = gradients * output_errors;
  gradients.mult(learning_rate);

  Matrix hidden_t = hidden.t();

  Matrix weight_ho_deltas = gradients * hidden_t;

  hidden_output_w += weight_ho_deltas;

  bias_output_w += gradients;

  Matrix who_t = hidden_output_w.t();

  Matrix hidden_errors = who_t * output_errors;

  Matrix hidden_gradient = hidden.d_sigmoid_r();

  Matrix hidden_gradient_t = hidden_gradient.t();
  Matrix hidden_errors_t = hidden_errors.t();

  // hidden_gradient = hidden_gradient * hidden_errors;

  for (int i = 0; i < hidden_gradient._colNum * hidden_gradient._rowNum;
       i++) {
    hidden_gradient._storage[i] *= hidden_errors._storage[i];
  }

  hidden_gradient.mult(learning_rate);
  Matrix inputs_t = inputs.t();

  Matrix weight_ih_deltas = hidden_gradient * inputs_t;

  input_hidden_w += weight_ih_deltas;

  bias_hidden_w += hidden_gradient;
}
