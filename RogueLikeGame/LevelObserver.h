#pragma once
#include <functional>
#include <vector>

namespace Roguelike {
class LevelObserver {
   public:
    virtual ~LevelObserver() = default;
    virtual void OnLevelCompleted() = 0;
    virtual void OnLevelFailed() = 0;
};

class LevelSubject {
   public:
    void AddObserver(LevelObserver* observer) { observers.push_back(observer); }

    void RemoveObserver(LevelObserver* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end());
    }

    void NotifyLevelCompleted() {
        for (auto observer : observers) {
            observer->OnLevelCompleted();
        }
    }

    void NotifyLevelFailed() {
        for (auto observer : observers) {
            observer->OnLevelFailed();
        }
    }

   private:
    std::vector<LevelObserver*> observers;
};
}  // namespace Roguelike