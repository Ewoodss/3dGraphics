//
// Created by Ewout on 9-6-2022.
//

#pragma once

#include "interfaces/DrawAble.h"
#include "interfaces/UpdateAble.h"

class Component : public UpdateAble, public DrawAble
{
protected:
	bool shouldBeRemoved = false;

public:
	void Draw() override;

	void Update() override;

	[[nodiscard]] bool ShouldBeRemoved() const;
};
