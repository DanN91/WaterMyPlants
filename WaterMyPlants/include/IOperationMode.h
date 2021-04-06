/*
    Author: Daniel Nistor
    Purpose: Interface for having multiple operations mode and choosing between them at runtime. (Strategy pattern)
    MIT License, 2021
*/

#pragma once

class IOperationMode
{
public:
    IOperationMode() = default;
    virtual ~IOperationMode() = default;

    virtual void Run() = 0;
};