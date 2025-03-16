#pragma once

class Renderable
{
public:

    virtual ~Renderable() = default;

    virtual void Draw() = 0;
    virtual void Update() = 0;

    template <typename T, typename Func>
    void ProcessComponent(Renderable *obj, Func func)
    {
        if (auto *specificObj = dynamic_cast<T *>(obj))
        {
            func(specificObj->GetComponent<RigidBody>());
        }
    }
};