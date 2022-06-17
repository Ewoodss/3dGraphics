//
// Created by Ewout on 9-6-2022.
//

#include "GameObject.h"

void GameObject::Draw()
{
	for (const auto& component : components)
	{
		component->Draw();
	}
}

void GameObject::Update()
{
	components.erase(remove_if(components.begin(), components.end(),
	                           [](const std::shared_ptr<Component>& component) { return component->ShouldBeRemoved(); }),
	                 components.end());

	if (components.empty())
	{
		shouldBeRemoved = true;
	}

	for (const auto& component : components)
	{
		component->Update();
	}
}
bool GameObject::ShouldBeRemoved() const
{
	return shouldBeRemoved;
}

GameObject::~GameObject()
{
	std::cout << "GameObject has been destroyed" << std::endl;
}

void GameObject::AddComponent(const std::shared_ptr<Component>& component)
{
	components.push_back(component);
}
