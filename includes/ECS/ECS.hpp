#pragma once
#include "Components.hpp"
#include <vector>
#include <memory>
#include <any>
#include <typeindex>
#include <unordered_map>

using Entity = std::size_t;

class ECS {
  private:
    std::unordered_map<std::type_index, std::unordered_map<Entity, std::any>> componentStorage;
    Entity nextEntityID = 1;
  public:
    Entity createEntity() {
      return nextEntityID++;
    };
    template<typename Component>
    void addComponent(Entity e, Component c) {
      componentStorage[typeid(Component)][e] = c;
    };
    template<typename Component>
    bool hasComponent(Entity e) {
      auto itr = componentStorage.find(typeid(Component));
      if (itr == componentStorage.end()) {
        return false;
      };
      return itr->second.count(e) > 0;
    };
    template<typename Component>
    Component* getComponent(Entity entity) {
      auto itr = componentStores.find(typeid(Component));
      if (itr == componentStorage.end()) {
        return nullptr;
      };
      auto itr2 = itr->second.find(e);
      if (itr2 == itr->second.end()) {
        return nullptr;
      };

      return std::any_cast<Component>(&(itr2->second));
    };
  };
