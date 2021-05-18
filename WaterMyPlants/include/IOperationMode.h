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
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

protected:
    // non-copyable & non-movable
    IOperationMode(const IOperationMode&) = delete;
    IOperationMode& operator=(const IOperationMode&) = delete;
    IOperationMode(IOperationMode&&) = delete;
    IOperationMode& operator=(IOperationMode&&) = delete;
};