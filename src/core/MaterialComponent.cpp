// include/core/MaterialComponent.cpp

#include "core/MaterialComponent.h"
#include "imgui.h"

void MaterialComponent::DrawImGui()
{
    ImGui::PushID(this);

    if (ImGui::CollapsingHeader("Material Settings"))
    {
        ImGui::ColorEdit3("Base Color", (float*)&material.baseColor);
        ImGui::SliderFloat("Metallic", &material.metallic, 0.0f, 1.0f);
        ImGui::SliderFloat("Roughness", &material.roughness, 0.0f, 1.0f);
        ImGui::SliderFloat("Ambient", &material.ambient, 0.0f, 1.0f);
        ImGui::SliderFloat("Diffuse", &material.diffuse, 0.0f, 1.0f);
        ImGui::SliderFloat("Specular", &material.specular, 0.0f, 1.0f);
    }

    ImGui::PopID();
}
