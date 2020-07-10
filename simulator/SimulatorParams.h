#pragma once

namespace simulator {

// SimulatorParams contains all parameters for Simulator
struct SimulatorParams {
  float r = 0.125f;
  float m = 0.006f;
  float kLen= 10000.f;
  float kBend = 0.005f;
  float kGlobal = 1.5f;
  // Contact force coefficient
  float kContact = 3250.f;
  float kDt = 0.003f;
  float kDn = 0.03f;
  float aSmall = 0.3f;
  float aLarge = 0.3f;
  // Time delta for each step (time resolution)
  float h = 0.001f;
  // Number of steps to run for each button click
  int steps = 100;
  // Gravity acceleration
  float gravity = 9.8f;
  // y coordinate of the ground
  float groundHeight = -5.f;
  // Ground fiction
  float groundFiction = 0.5f;

  static SimulatorParams Default() {
    SimulatorParams param;
    return param;
  }
};

}; // namespace simulator
