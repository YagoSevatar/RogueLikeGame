#pragma once
#include <vector>

namespace Roguelike {
class HealthComponent;

class CombatSystem {
   public:
    static CombatSystem* Instance();
    void Update();
    void RegisterHealthComponent(HealthComponent* healthComponent);
    void UnregisterHealthComponent(HealthComponent* healthComponent);

   private:
    CombatSystem() = default;
    std::vector<HealthComponent*> healthComponents;
};
}  // namespace Roguelike