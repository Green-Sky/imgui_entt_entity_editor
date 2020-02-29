// for the license, see the end of the file
#pragma once

#include <map>
#include <set>

#include <entt/entt.hpp>
#include <imgui.h>

namespace MM {

template <class Component, class EntityType>
void ComponentEditorWidget(entt::basic_registry<EntityType>& registry, EntityType entity) {}

template <class Component, class EntityType>
void ComponentAddAction(entt::basic_registry<EntityType>& registry, EntityType entity)
{
	registry.template assign<Component>(entity);
}

template <class Component, class EntityType>
void ComponentRemoveAction(entt::basic_registry<EntityType>& registry, EntityType entity)
{
	registry.template remove<Component>(entity);
}

template <class EntityType>
class EntityEditor {
public:
	using Registry = entt::basic_registry<EntityType>;

	struct ComponentInfo {
		using Callback = std::function<void(Registry&, EntityType)>;
		std::string name;
		Callback widget, create, destroy;
	};

	bool show_window = true;

private:
	using ComponentTypeID = ENTT_ID_TYPE;

	std::map<ComponentTypeID, ComponentInfo> component_infos;

	bool entityHasComponent(Registry& registry, EntityType& entity, ComponentTypeID type_id)
	{
		ComponentTypeID type[] = { type_id };
		return registry.runtime_view(std::cbegin(type), std::cend(type)).contains(entity);
	}

public:
	template <class Component>
	ComponentInfo& registerComponent(const ComponentInfo& component_info)
	{
		auto index = entt::type_info<Component>::id();
		auto [it, insert_result] = component_infos.insert_or_assign(index, component_info);
		assert(insert_result);
		return std::get<ComponentInfo>(*it);
	}

	template <class Component>
	ComponentInfo& registerComponent(const std::string& name, typename ComponentInfo::Callback widget)
	{
		return registerComponent<Component>(ComponentInfo{
			name,
			widget,
			ComponentAddAction<Component, EntityType>,
			ComponentRemoveAction<Component, EntityType>,
		});
	}

	template <class Component>
	ComponentInfo& registerComponent(const std::string& name)
	{
		return registerComponent<Component>(name, ComponentEditorWidget<Component, EntityType>);
	}

	void render(Registry& registry, EntityType& e)
	{
		if (show_window) {
			if (ImGui::Begin("Entity Editor", &show_window)) {
				ImGui::TextUnformatted("Editing:");
				ImGui::SameLine();

				if (registry.valid(e)) {
					ImGui::Text("ID: %d", entt::to_integral(e));
				} else {
					ImGui::Text("Invalid Entity");
				}

				if (ImGui::Button("New Entity")) {
					e = registry.create();
				}

				ImGui::Separator();

				if (registry.valid(e)) {
					const std::string entity_id = std::to_string(entt::to_integral(e));
					std::map<ComponentTypeID, ComponentInfo> has_not;
					for (auto& [component_type_id, ci] : component_infos) {
						if (entityHasComponent(registry, e, component_type_id)) {
							const std::string component_id = std::to_string(static_cast<int>(component_type_id));
							std::string button_label = "-##" + entity_id + component_id;

							if (ImGui::Button(button_label.c_str())) {
								ci.destroy(registry, e);
								continue; // early out to prevent access to deleted data
							} else {
								ImGui::SameLine();
							}

							std::string label;
							label = ci.name + "##" + entity_id + component_id;

							if (ImGui::CollapsingHeader(label.c_str())) {
								ImGui::Indent(30.f);
								ci.widget(registry, e);

								ImGui::Unindent(30.f);
							}
						} else {
							has_not[component_type_id] = ci;
						}
					}

					if (!has_not.empty()) {
						if (ImGui::Button("+ Add Component")) {
							ImGui::OpenPopup("Add Component");
						}

						if (ImGui::BeginPopup("Add Component")) {
							ImGui::TextUnformatted("Available:");
							ImGui::Separator();

							for (auto& [component_type_id, ci] : has_not) {
								const std::string component_id = std::to_string(static_cast<int>(component_type_id));
								std::string label = ci.name;

								label += "##" + entity_id + component_id;
								if (ImGui::Selectable(label.c_str())) {
									ci.create(registry, e);
								}
							}
							ImGui::EndPopup();
						}
					}
				}
			}
			ImGui::End();
		}
	}
};

} // MM

// MIT License

// Copyright (c) 2019 Erik Scholz, Gnik Droy

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

