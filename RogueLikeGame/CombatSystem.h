#pragma once
#include <vector>

#include "HealthComponent.h"

namespace Roguelike {
class CombatSystem {
   public:
    static CombatSystem* Instance();
    void Update();
    void RegisterHealthComponent(HealthComponent* healthComponent);

   private:
    CombatSystem() = default;
    std::vector<HealthComponent*> healthComponents;
};
}  // namespace Roguelike
