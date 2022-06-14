//
// Created by Ewout on 9-6-2022.
//

#pragma once


#include "interfaces/UpdateAble.h"
#include "interfaces/DrawAble.h"

class Component : public UpdateAble, public DrawAble
{
public:
    void Draw() override;

    void Update() override;

};

