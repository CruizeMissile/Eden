
#pragma once

namespace eden::ecs
{
class director_t;
class dispatcher_t;

class system_t
{
public:
    virtual ~system_t() {}
    virtual void update(float delte_time) = 0;

protected:
    inline director_t& director();

private:
    dispatcher_t* dispatcher_;
};
} // namespace eden::ecs
