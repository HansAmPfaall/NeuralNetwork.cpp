#pragma once
#include "./NeuralNetwork.h"
#include <cstdlib>

// _____________________________________________________________________________
NeuralNetwork::NeuralNetwork(int input, int hidden, int output, float lr = 0.1)
    : input_hidden_w(hidden, input),
      hidden_output_w(output, hidden),
      bias_hidden_w(hidden, 1),
      bias_output_w(output, 1) {
  _input = input;
  _hidden = hidden;
  _output = output;

  learning_rate = lr;
}

// _____________________________________________________________________________
NeuralNetwork::~NeuralNetwork() {}

// _____________________________________________________________________________
std::vector<float> NeuralNetwork::calc(std::vector<float> input_array) {
  Matrix inputs(input_array.size(), 1, input_array);
  Matrix hidden = input_hidden_w * inputs;
  // hidden += bias_hidden_w;
  hidden.sigmoid();

  Matrix output = hidden_output_w * hidden;
  // output += bias_output_w;
  output.sigmoid();

  return output.toVector();
}

void NeuralNetwork::trainN(std::vector<float> input_array,
                           std::vector<float> target_array) {
  // make Matrix from input and target
  Matrix inputs(input_array.size(), 1, input_array);
  Matrix targets(target_array.size(), 1, target_array);

  Matrix hidden = input_hidden_w * inputs;
  hidden.sigmoid();

  Matrix output = hidden_output_w * hidden;
  output.sigmoid();

  Matrix output_errors = targets - output;
  Matrix hidden_output_w_t = hidden_output_w.t();
  Matrix hidden_errors = hidden_output_w_t * output_errors;

  Matrix n_output = Matrix(output._rowNum, output._colNum, 1) - output;
  Matrix hidden_t = hidden.t();

  Matrix t1(output._colNum, output._rowNum, 0);
  for (int i = 0; i < output._rowNum * output._colNum; i++) {
    t1._storage[i] =
        output_errors._storage[i] * output._storage[i] * n_output._storage[i];
  }
  t1 = t1.mult(hidden_t);
  // Matrix test = ((output_errors * output * (n_output)) * hidden_t);
  t1.mult(learning_rate);
  hidden_output_w += t1;

  Matrix n_hidden = Matrix(hidden._rowNum, hidden._colNum, 1) - hidden;
  Matrix inputs_t = inputs.t();



  Matrix t2(hidden._colNum, hidden._rowNum, 0);
  for (int i = 0; i < hidden._rowNum * hidden._colNum; i++) {
    t1._storage[i] =
        hidden_errors._storage[i] * hidden._storage[i] * n_hidden._storage[i];
  }
  Matrix t2_t = t2.t();
  t2_t = t2_t.mult(inputs_t);
  // Matrix testo = ((hidden_errors * hidden * (n_hidden)) * inputs_t);
  t2_t.mult(learning_rate);
  input_hidden_w += t2_t;
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

  for (int i = 0; i < hidden_gradient._colNum * hidden_gradient._rowNum; i++) {
    hidden_gradient._storage[i] *= hidden_errors._storage[i];
  }

  hidden_gradient.mult(learning_rate);
  Matrix inputs_t = inputs.t();

  Matrix weight_ih_deltas = hidden_gradient * inputs_t;

  input_hidden_w += weight_ih_deltas;

  bias_hidden_w += hidden_gradient;
}
