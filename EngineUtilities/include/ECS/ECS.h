#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <typeindex>
#include <type_traits>
#include <memory>
#include <cassert>

/**
 * @file ECS.h
 * @brief Base simple para Entity Component System (ECS).
 */

  namespace EU::ECS {

  using Entity = uint32_t;
  constexpr Entity MAX_ENTITIES = 5000;

  /// Clase base vacía para componentes.
  struct Component {
    virtual ~Component() = default;
  };

  /// Maneja IDs únicos para tipos de componentes.
  class ComponentTypeID {
  public:
    template<typename T>
    static size_t GetID() {
      static size_t id = nextID++;
      return id;
    }
  private:
    static size_t nextID;
  };
  size_t ComponentTypeID::nextID = 0;

  /// Maneja almacenamiento y acceso a componentes de un tipo.
  template<typename T>
  class ComponentArray {
    std::unordered_map<Entity, T> components;

  public:
    void InsertData(Entity entity, T component) {
      assert(components.find(entity) == components.end() && "Component added twice.");
      components[entity] = component;
    }

    void RemoveData(Entity entity) {
      assert(components.find(entity) != components.end() && "Removing non-existent component.");
      components.erase(entity);
    }

    T* GetData(Entity entity) {
      auto it = components.find(entity);
      if (it != components.end())
        return &(it->second);
      return nullptr;
    }

    bool HasComponent(Entity entity) {
      return components.find(entity) != components.end();
    }
  };

  /// Administra todos los tipos de componentes.
  class ComponentManager {
    std::unordered_map<size_t, std::shared_ptr<void>> componentArrays;

  public:
    template<typename T>
    void RegisterComponent() {
      size_t typeID = ComponentTypeID::GetID<T>();
      componentArrays[typeID] = std::make_shared<ComponentArray<T>>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
      GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
      GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T* GetComponent(Entity entity) {
      return GetComponentArray<T>()->GetData(entity);
    }

    template<typename T>
    bool HasComponent(Entity entity) {
      return GetComponentArray<T>()->HasComponent(entity);
    }

  private:
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray() {
      size_t typeID = ComponentTypeID::GetID<T>();
      return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeID]);
    }
  };

  /// Crea y destruye entidades.
  class EntityManager {
    Entity nextEntity = 0;
    std::unordered_set<Entity> livingEntities;

  public:
    Entity CreateEntity() {
      assert(nextEntity < MAX_ENTITIES && "Max entities reached");
      Entity id = nextEntity++;
      livingEntities.insert(id);
      return id;
    }

    void DestroyEntity(Entity entity) {
      livingEntities.erase(entity);
    }

    bool IsAlive(Entity entity) const {
      return livingEntities.find(entity) != livingEntities.end();
    }
  };

  /// Sistema base que contiene entidades.
  class System {
  protected:
    std::unordered_set<Entity> entities;

  public:
    virtual ~System() = default;

    void AddEntity(Entity entity) {
      entities.insert(entity);
    }

    void RemoveEntity(Entity entity) {
      entities.erase(entity);
    }

    bool HasEntity(Entity entity) {
      return entities.find(entity) != entities.end();
    }

    /// Método para que cada sistema implemente su lógica.
    virtual void Update(float deltaTime) = 0;
  };

  /// Clase coordinadora que junta todo.
  class Coordinator {
    EntityManager entityManager;
    ComponentManager componentManager;

  public:
    Entity CreateEntity() {
      return entityManager.CreateEntity();
    }

    void DestroyEntity(Entity entity) {
      entityManager.DestroyEntity(entity);
      // Aquí podrías agregar lógica para limpiar componentes
    }

    template<typename T>
    void RegisterComponent() {
      componentManager.RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
      componentManager.AddComponent<T>(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
      componentManager.RemoveComponent<T>(entity);
    }

    template<typename T>
    T* GetComponent(Entity entity) {
      return componentManager.GetComponent<T>(entity);
    }

    template<typename T>
    bool HasComponent(Entity entity) {
      return componentManager.HasComponent<T>(entity);
    }
  };

}
