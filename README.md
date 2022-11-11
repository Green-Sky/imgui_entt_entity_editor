# imgui_entt_entity_editor
A drop-in, single-file entity editor for EnTT, with ImGui as graphical backend.
Originally developed for [MushMachine](https://github.com/MadeOfJelly/MushMachine).

[demo-code](https://github.com/Green-Sky/imgui_entt_entity_editor_demo) [(live)](https://green-sky.github.io/imgui_entt_entity_editor_demo/)

Editor
![screenshot0](https://github.com/Green-Sky/imgui_entt_entity_editor_demo/blob/master/imgui_entt_entity_editor_screenshot0.png)

Editor with Entiy-List
![screenshot1](https://github.com/Green-Sky/imgui_entt_entity_editor_demo/blob/master/imgui_entt_entity_editor_screenshot1.png)

With Drag and Drop
![vid](https://github.com/Green-Sky/imgui_entt_entity_editor_demo/blob/master/imgui_entt_entity_editor_dnd0.gif)

# example usage
```c++
struct Transform {
    float x = 0.f;
    float y = 0.f;
};

struct Velocity {
    float x = 0.f;
    float y = 0.f;
};

namespace MM {
template <>
void ComponentEditorWidget<Transform>(entt::registry& reg, entt::registry::entity_type e)
{
	auto& t = reg.get<Transform>(e);
	ImGui::DragFloat("x", &t.x, 0.1f);
	ImGui::DragFloat("y", &t.y, 0.1f);
}

template <>
void ComponentEditorWidget<Velocity>(entt::registry& reg, entt::registry::entity_type e)
{
	auto& v = reg.get<Velocity>(e);
	ImGui::DragFloat("x", &v.x, 0.1f);
	ImGui::DragFloat("y", &v.y, 0.1f);
}
}


entt::registry reg;
MM::EntityEditor<entt::entity> editor;

editor.registerComponent<Transform>("Transform");
editor.registerComponent<Velocity>("Velocity");
```

# Dependencies
The editor uses EnTTv3.11.0 and ImGui. (tested with ImGui 1.68, 1.72b, 1.75, 1.78, 1.82, 1.85, 1.87)
To use it with EnTTv3.0.0, use the dedicated branch.
For specific EnTT version check the tags, if a new EnTT version does not require a update, I won't make a new Release.
Releases available for EnTT 3.1.0, 3.1.1, 3.2.0, 3.2.1, 3.2.2, 3.3.x, 3.4.0, 3.6.0-3.8.1, 3.9.0, 3.10.0, 3.11.0.

