#pragma once

namespace Roguelike {
class Scene {
   public:
    virtual void Start() = 0;
    virtual void Restart() = 0;
    virtual void Stop() = 0;
    virtual ~Scene() = default;
};
}  // namespace Roguelike