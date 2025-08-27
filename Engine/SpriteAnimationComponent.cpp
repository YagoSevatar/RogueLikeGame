#include "pch.h"
#include "SpriteAnimationComponent.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"


namespace EngineZ {
SpriteAnimationComponent::SpriteAnimationComponent(GameObject* gameObject)
    : Component(gameObject) {
    rendererComponent = gameObject->GetComponent<SpriteRendererComponent>();
    if (rendererComponent == nullptr) {
        std::cout
            << "SpriteRendererComponent required for SpriteAnimationComponent."
            << std::endl;
        gameObject->RemoveComponent(this);
    }
}

void SpriteAnimationComponent::Update(float deltaTime) {
    timer += deltaTime;
    if (timer >= timePerFrame) {
        timer = 0.0f;
        currentFrame++;
        if (currentFrame >= framesTextures.size()) {
            if (isLoop) {
                ResetAnimation();
            } else {
                currentAnimationName = defaultAnimationName;
                StartCurrentAnimation();
            }
        }
        UpdateRendererTexture();
    }
}

void SpriteAnimationComponent::Render() {}

void SpriteAnimationComponent::AddAnimation(const std::string& animationName,
                                            const Animation& animation,
                                            bool isDefault) {
    animations[animationName] = animation;
    if (isDefault || defaultAnimationName.empty()) {
        defaultAnimationName = animationName;
    }
}

void SpriteAnimationComponent::RemoveAnimation(
    const std::string& animationName) {
    auto it = animations.find(animationName);
    if (it != animations.end()) {
        animations.erase(it);
    }
}

void SpriteAnimationComponent::StartAnimation(const std::string& animationName,
                                              bool ignorePriority) {
    auto newAnimation = animations.find(animationName);
    if (newAnimation != animations.end()) {
        if (animationName != currentAnimationName) {
            auto currentAnimation = animations.find(currentAnimationName);
            if (ignorePriority || currentAnimation == animations.end() ||
                currentAnimation->second.priority <=
                    newAnimation->second.priority) {
                currentAnimationName = animationName;
                StartCurrentAnimation();
            }
        }
    }
}

void SpriteAnimationComponent::StartCurrentAnimation() {
    auto animation = animations.find(currentAnimationName);
    if (animation != animations.end()) {
        framesTextures.clear();
        for (int frameID : animation->second.frameIDs) {
            framesTextures.push_back(
                ResourceSystem::Instance()->GetTextureMapElementShared(
                    animation->second.textureMapName, frameID));
        }
        isRightDirected = animation->second.isRightDirected;
        timePerFrame = animation->second.time /
                       static_cast<float>(animation->second.frameIDs.size());
        isLoop = animation->second.isLoop;
        ResetAnimation();
    }
}

void SpriteAnimationComponent::ResetAnimation() {
    timer = 0.0f;
    currentFrame = 0;
    UpdateRendererTexture();
}

void EngineZ::SpriteAnimationComponent::UpdateRendererTexture() const {
    if (rendererComponent && currentFrame < framesTextures.size() &&
        framesTextures[currentFrame] != nullptr) {
        rendererComponent->SetTexture(*framesTextures[currentFrame]);
        rendererComponent->FlipX(!isRightDirected);
    } else {
        std::cout << "Failed to update texture for frame " << currentFrame
                  << " (total frames: " << framesTextures.size() << ")"
                  << std::endl;
    }
}
}  // namespace EngineZ