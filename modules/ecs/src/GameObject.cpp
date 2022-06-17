//
// Created by Ewout on 9-6-2022.
//

#include "GameObject.h"

void GameObject::Draw()
{
	for (const auto& component : Components)
	{
		component->Draw();
	}
}

void GameObject::Update()
{
	Components.erase(remove_if(Components.begin(), Components.end(),
	                           [](const std::shared_ptr<Component>& component) { return component->GetShouldBeRemoved(); }),
	                 Components.end());

	if (Components.empty())
	{
		ShouldBeRemoved = true;
	}

	for (const auto& component : Components)
	{
		component->Update();
	}
}
bool GameObject::GetShouldBeRemoved() const
{
	return ShouldBeRemoved;
}

GameObject::~GameObject()
{
	std::cout << "GameObject has been destroyed" << std::endl;
}
