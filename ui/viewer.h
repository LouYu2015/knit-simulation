#pragma once

#include <Eigen/Core>
#include <imgui/imgui.h>

#include <unordered_set>
#include <string>
#include <memory>

#include "./menu.h"
#include "../simulator/Simulator.h"

namespace UI {

class Menu;

class Viewer : igl::opengl::glfw::Viewer {
 public:
  Viewer() {}
  int launch(bool resizable = true, bool fullscreen = false,
    const std::string &name = "GRAIL Knit Simulator", int width = 0, int height = 0);
  void refresh();
  void loadYarn(std::string filename);
  void step() { _simulator.step(); }

  bool viewNext();
  bool viewPrev();
  int numStep() { return _simulator.numStep(); }

  // Number of samples for yarn cross-section (circle)
  int circleSamples = 8;
  // Number of samples for Catmull-Rom curve
  int curveSamples = 4;

  int currentStep = 0;

 private:
  std::unique_ptr<Menu> _menu;
  simulator::Simulator _simulator;
};

}  // namespace UI
