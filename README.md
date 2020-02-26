# imgui_entt_entity_editor
A drop-in, single-file entity editor for EnTT, with ImGui as graphical backend.

[demo-code](https://github.com/Green-Sky/imgui_entt_entity_editor_demo) [(live)](http://scam.rocks/imgui_entt_entity_editor_demo/)

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
    // the "##Transform" ensures that you can use the name "x" in multiple lables
    ImGui::DragFloat("x##Transform", &t.x, 0.1f);
    ImGui::DragFloat("y##Transform", &t.y, 0.1f);
}

template <>
void ComponentEditorWidget<Velocity>(entt::registry& reg, entt::registry::entity_type e)
{
    auto& v = reg.get<Velocity>(e);
    ImGui::DragFloat("x##Velocity", &v.x, 0.1f);
    ImGui::DragFloat("y##Velocity", &v.y, 0.1f);
}
}


entt::registry reg;
MM::EntityEditor<entt::entity> editor;

editor.registerComponent<Transform>("Transform");
editor.registerComponent<Velocity>("Velocity");
```

# dependencies
The editor uses (the latest) EnTTv3.2.2 interface and ImGui 1.72b but should work with prior versions. (tested with ImGui 1.68)
To use it with EnTTv3.0.0, use the dedicated branch.
Tested against EnTT 3.1.0, 3.1.1, 3.2.0, 3.2.1, 3.2.2.

