#include "./viewer.h"

namespace UI {

void Viewer::launch() {
  igl::opengl::glfw::imgui::ImGuiMenu menu;
  viewer.plugins.push_back(&menu);

  double doubleVariable = 0.1;

  // TODO: Warning: this part is not complete and contains bugs.
  menu.callback_draw_viewer_menu = [&]() {
    // Draw parent menu content
    menu.draw_viewer_menu();

    // Add new group
    if (ImGui::CollapsingHeader("New Group", ImGuiTreeNodeFlags_DefaultOpen))
    {
      // Expose variable directly ...
      ImGui::InputDouble("double", &doubleVariable, 0, 0, "%.4f");

      // ... or using a custom callback
      static bool boolVariable = true;
      if (ImGui::Checkbox("bool", &boolVariable))
      {
        // do something
        std::cout << "boolVariable: " << std::boolalpha << boolVariable << std::endl;
      }

      // Expose an enumeration type
      enum Orientation { Up=0, Down, Left, Right };
      static Orientation dir = Up;
      ImGui::Combo("Direction", (int *)(&dir), "Up\0Down\0Left\0Right\0\0");

      // We can also use a std::vector<std::string> defined dynamically
      static int num_choices = 3;
      static std::vector<std::string> choices;
      static int idx_choice = 0;
      if (ImGui::InputInt("Num letters", &num_choices))
      {
        num_choices = std::max(1, std::min(26, num_choices));
      }
      if (num_choices != (int) choices.size())
      {
        choices.resize(num_choices);
        for (int i = 0; i < num_choices; ++i)
          choices[i] = std::string(1, 'A' + i);
        if (idx_choice >= num_choices)
          idx_choice = num_choices - 1;
      }
      ImGui::Combo("Letter", &idx_choice, choices);

      // Add a button
      if (ImGui::Button("Print Hello", ImVec2(-1,0)))
      {
        std::cout << "Hello\n";
      }
    }
  };
  viewer.launch();
}

void Viewer::plot(Eigen::MatrixXf points) {
  Eigen::MatrixXi E(points.rows() - 1, 2);
  for (int i = 0; i < points.rows() - 1; i++) {
    E(i, 0) = i;
    E(i, 1) = i + 1;
  }

  viewer.data().set_edges(points.cast<double>(),
      E, Eigen::RowVector3d(1, 1, 1));
}

} // namespace UI