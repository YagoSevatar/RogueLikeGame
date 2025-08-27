#include "pch.h"
#include "GameObject.h"


namespace EngineZ {
GameObject::GameObject() {
    name = "GameObject";
    AddComponent<TransformComponent>();
}
GameObject::GameObject(std::string newName) {
    name = newName;
    AddComponent<TransformComponent>();
}

GameObject::~GameObject() {
    for (auto component : components) {
        delete component;
    }
    components.clear();
    children.clear();
}

std::string GameObject::GetName() const { return name; }

void GameObject::Print(int depth) const {
    std::cout << std::string(depth * 2, ' ') << GetName() << std::endl;
    for (auto& component : components) {
        std::cout << std::string(depth * 2, ' ') << "::" << component
                  << std::endl;
    }

    for (GameObject* child : children) {
        child->Print(depth + 1);
    }
}

void GameObject::Update(float deltaTime) {
    for (auto it = components.begin(); it != components.end();) {
        if (*it == nullptr) {
            it = components.erase(it);
            continue;
        }

        try {
            (*it)->Update(deltaTime);
            ++it;
        } catch (...) {
            std::cout << "Error updating component: " << *it << std::endl;
            it = components.erase(it);
        }
    }

    // Обновляем детей
    for (auto it = children.begin(); it != children.end();) {
        if (*it == nullptr) {
            it = children.erase(it);
            continue;
        }

        try {
            (*it)->Update(deltaTime);
            ++it;
        } catch (...) {
            std::cout << "Error updating child: " << *it << std::endl;
            it = children.erase(it);
        }
    }
}
void GameObject::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

void GameObject::AddChild(GameObject* child) { children.push_back(child); }
void GameObject::RemoveChild(GameObject* child) {
    children.erase(
        std::remove_if(children.begin(), children.end(),
                       [child](GameObject* obj) { return obj == child; }),
        children.end());
}
}  // namespace EngineZ