# Entity Component System (ecs)

> A pure entity component system with a focus on performance and multi-threading

# Core concepts

- Components are just POD structs with no logic implmented
- Entities are just identifiers
- Systems are where the logic is implemented on components
- In systems you query for components.
- Systems are jobs that will execute in parallel.
- Components should be broken up into smaller components so that the memory copied is as small as posible.
    - example: break up the transform component into position, rotation and scale so if you only need positions you only work with positions

## Job/system details

Jobs will be added to `groups` that have a start and end job. Systems will depend on other systems in a hiarcical manner.
When the job group will be executed the start/root job will be started. This will then run all of it's children as seperate threads.
At the end of the job group is the sync point where all the threads and data syncs together and another job group starts.
Queries will return you a copy of the data in a contugous block of memory that can be iterated though very cache friendly.


## Questions

- how does the query copy work and how does that data then sync with the component database at sync points?

## Api design ideas

```c++
// -------------------------------------------
// define a component

struct position_t : public component_t
{
    float x, y, z;
};

struct velocity_t : public component_t
{
    float x, y, z;
};

struct acceleration_t : public component_t
{
    float x, y, z;
};

struct name_t : public component_t
{
    std::string name;
};

// -------------------------------------------
// define systems

// list of access rights
enum class access_rights_t
{
    none,       // Use the type in the query but do not return a copy of the component list in the query
    read_write, // The copy result can be read and written to
    read_only,  // The copy result can only be read
    write_only  // The copy result can only be written to
};

// Note this is what the definition of has is
template<typename Type, access_rights_t AccessRights = access_rights_t::none>
constexpr some_query_component_t has(){ ... }

class movement_t : public system_t
{
public:
    // create a query object that will define the query and be applied every process update
    // `build` will return a query_t object with the compiled query steps
    constexpr query_t query = query_t::build(
        has<position_t, access_rights_t::read_write>()  &&
        has<acceleration_t, access_rights_t::read_only> &&
        has<velocity_t, access_rights_t::read_only>     &&
        !has<name_t> // Not (!) should not have any access_rights_t other than none
    );

    void process(float delta_time)
    {
        // The query will preform the query that has been built. This will return a query result.
        // A query_result will hold a copy of the component from the database. Each array of component types
        // will be the same size and each index coresponds with the same entity
        query_result_t result = query.execute();

        // Note on query's not sure how || will work with the query result.
        // If the result is A || B then A might be there or not. Same with b

        // not sure how you handle the result after that

        // now at the end of processing the system how do you then sync up the component data?
        // If the system after this depends on the data that you changed or added how does that work?

        // I guess one way that this can me handled is by creating sync points after each layer in the job group.
    }
};
```

## More about queries

****

## Interesting ideas and resources

- https://www.fluentcpp.com/2018/07/03/how-to-reduce-the-code-bloat-of-a-variadic-crtp/
- https://www.fluentcpp.com/2018/06/22/variadic-crtp-opt-in-for-class-features-at-compile-time/
