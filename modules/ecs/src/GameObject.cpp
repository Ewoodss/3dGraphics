//
// Created by Ewout on 9-6-2022.
//

#include "GameObject.h"

void GameObject::Draw()
{
    for (const auto &component: components)
    {
        component->Draw();
    }
}

void GameObject::Update()
{
    for (const auto &component: components)
    {
        component->Update();
    }
}

