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

namespace Widgets {
	void Velocity(::Velocity& v) {
		ImGui::DragFloat("x##Velocity", &v.x, 0.1f);
		ImGui::DragFloat("y##Velocity", &v.y, 0.1f);
	}
} // Widgets

entt::registry reg;

MM::ImGuiEntityEditor<decltype(reg)> editor;

// "registerTrivial" registers the type, name, create and destroy functions for trivialy costructable(and destroyable) types.
// you just need to provide a "widget" function if you use this method.
editor.registerTrivial<Transform>(reg, "Transform");
editor.registerTrivial<Velocity>(reg, "Velocity");

editor.registerComponentWidgetFn(
	reg.type<Transform>(),
	[](entt::registry& reg, auto e) {
		auto& t = reg.get<Transform>(e);

		// the "##Transform" ensures that you can use the name "x" in multiple lables
		ImGui::DragFloat("x##Transform", &t.x, 0.1f);
		ImGui::DragFloat("y##Transform", &t.y, 0.1f);
	});

editor.registerComponentWidgetFn(
	reg.type<Velocity>(),
	[](entt::registry& reg, auto e) {
		auto& v = reg.get<Velocity>(e);
		Widgets::Velocity(v);
	});

```

# dependencies
The editor uses the latest EnTTv3-wip interface and ImGui 1.72b but should work with prior versions. (tested with ImGui 1.68)
To use it with EnTTv2 you have to rename the calls to the library acording to the old CamelCase.

