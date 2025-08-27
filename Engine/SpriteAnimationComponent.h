#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Component.h"
#include "GameObject.h"
#include "SpriteRendererComponent.h"

namespace EngineZ {
struct Animation {
    std::string textureMapName;
    std::vector<int> frameIDs;
    float time;
    bool isRightDirected;
    int priority;
    bool isLoop = false;
};

class SpriteAnimationComponent : public Component {
   public:
    explicit SpriteAnimationComponent(GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override;

    void AddAnimation(const std::string& animationName,
                      const Animation& animation, bool isDefault = false);
    void RemoveAnimation(const std::string& animationName);
    void StartAnimation(const std::string& animationName,
                        bool ignorePriority = false);

   protected:
    void StartCurrentAnimation();
    void ResetAnimation();
    void UpdateRendererTexture() const;

    std::unordered_map<std::string, Animation> animations;
    std::string defaultAnimationName;
    std::string currentAnimationName;
    std::vector<const sf::Texture*> framesTextures;
    SpriteRendererComponent* rendererComponent;
    float timePerFrame = 0.0f;
    float timer = 0.0f;
    int currentFrame = 0;
    bool isRightDirected = true;
    bool isLoop = true;
};
}  // namespace EngineZ