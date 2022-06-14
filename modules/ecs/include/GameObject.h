//
// Created by Ewout on 9-6-2022.
//

#pragma once

#include "interfaces/UpdateAble.h"
#include "interfaces/DrawAble.h"
#include "Component.h"

#include <vector>
#include <memory>


class GameObject : public UpdateAble, public DrawAble
{
    std::vector<std::shared_ptr<Component> > components;

public:
    void Draw() override;

    void Update() override;


    template<class T, std::enable_if_t<std::is_base_of<Component, T>::value, bool> = true, typename ... Args>
    //advanced c++
    std::shared_ptr<T> AddComponent(Args &&... args)
    {
        std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);

        components.push_back(std::static_pointer_cast<Component>(component));

        return component;
    }

    template<class T, std::enable_if_t<std::is_base_of<Component, T>::value, bool> = true>
    std::shared_ptr<T> FindGameObject() const
    {
        std::shared_ptr<T> result(nullptr);

        for (const auto &component: components)
        {
            auto castedComponent = std::dynamic_pointer_cast<T>(component);
            if (castedComponent)
            {
                result = castedComponent;
                break;
            }
        }
        return result;
    }

};
