#ifndef __ENGINE_RESOURCE_H__
#define __ENGINE_RESOURCE_H__

#include "Engine_Imaging.h"
#include "Engine_Font.h"

#include <iostream>

namespace Engine {
    /// @brief The Resource class, can be use to managing resources.
    class Resource final {
    private:
        static std::unordered_map<size_t, std::unordered_map<size_t, void*>> __data;
    public:
        /// @brief Add a value to the Resource. If there's already a value with the same type and the given name, will replace it.
        /// @tparam T The type of the value to add.
        /// @param Name The name of the value, use for finding the value.
        /// @param Value The value to add.
        template <typename T>
        static void Add(const std::string& Name, T* Value) {
            size_t type_hash_value = typeid(T).hash_code();
            size_t hash_value = std::hash<std::string>()(Name);

            if (Resource::__data.count(type_hash_value) == 0)
                Resource::__data[type_hash_value] = std::unordered_map<size_t, void*>();
            
            Resource::__data[type_hash_value][hash_value] = Value;
        }

        /// @brief Get a value from the Resource.
        /// @tparam T The type of the value to get.
        /// @param Name The name of the value, use for finding the value.
        /// @return The value with the given type and name. Will return nullptr if not found.
        template <typename T>
        static T* Get(const std::string& Name) {
            size_t type_hash_value = typeid(T).hash_code();
            if (Resource::__data.count(type_hash_value) == 0)
                return nullptr;
            
            size_t hash_value = std::hash<std::string>()(Name);
            if (Resource::__data[type_hash_value].count(hash_value) == 0)
                return nullptr;
            
            return (T*)Resource::__data[type_hash_value][hash_value];
        }

        /// @brief Remove all value added to the Resource.
        static void Clear() { Resource::__data.clear(); }
    };
}

std::unordered_map<size_t, std::unordered_map<size_t, void*>> Engine::Resource::__data =
    std::unordered_map<size_t, std::unordered_map<size_t, void*>>();

#endif // __ENGINE_RESOURCE_H__