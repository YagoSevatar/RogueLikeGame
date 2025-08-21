#pragma once
#include "../Engine/Component.h"

namespace Roguelike {
class ArmorComponent : public EngineZ::Component {
   public:
    ArmorComponent(EngineZ::GameObject* gameObject);
    void SetArmor(int armor);
    int GetArmor() const;
    int ReduceDamage(int damage);

    void Update(float deltaTime) override {}
    void Render() override {}

   private:
    int armorValue = 0;
};
}  // namespace Roguelike