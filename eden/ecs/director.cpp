
#include "director.hpp"

namespace eden::ecs
{
director_t::director_t(size_t chunk_size)
{
    versions_.reserve(chunk_size);
    masks_.reserve(chunk_size);
}

director_t::~director_t()
{
    for (internal::base_store_t* base : stores_)
    {
        if (base)
            delete base;
    }

    stores_.clear();
    masks_.clear();
    versions_.clear();
    next_free_indexes_.clear();
}

entity_t director_t::create()
{
    ++count_;
    index_t index = find_new_entity_index();
    size_t slots_required = index + 1;

    if (versions_.size() < slots_required)
    {
        versions_.resize(slots_required);
        masks_.resize(slots_required, mask_t(0));
    }

    return get_entity(index);
}

std::vector<entity_t> director_t::create(const size_t num_of_entities)
{
    std::vector<entity_t> new_entities;
    size_t entities_left = num_of_entities;
    new_entities.reserve(entities_left);

    while (!free_list_.empty() && entities_left > 0)
    {
        new_entities.push_back(get_entity(free_list_.back()));
        free_list_.pop_back();
        --entities_left;
    }

    if (entities_left != 0)
    {
        index_t block_index = 0;
        index_t current = EDEN_CACHE_LINE_SIZE;
        size_t slots_required;

        if (!block_index_.empty())
        {
            block_index = block_index_[block_index_.size() - 1];
            current = next_free_indexes_[block_index];
            slots_required = block_count_ * EDEN_CACHE_LINE_SIZE + current + entities_left;
        }
        else
        {
            slots_required = block_count_ * EDEN_CACHE_LINE_SIZE + entities_left;
        }

        versions_.resize(slots_required);
        masks_.resize(slots_required, mask_t(0));

        while (entities_left)
        {
            for (; current < EDEN_CACHE_LINE_SIZE && entities_left; ++current)
            {
                new_entities.push_back(get_entity(current + EDEN_CACHE_LINE_SIZE * block_index));
                entities_left--;
            }

            if (entities_left)
            {
                block_index = block_count_;
                create_new_block(0);
                ++block_count_;
                current = 0;
            }
        }
    }

    count_ += num_of_entities;
    return new_entities;
}

size_t director_t::count()
{
    return count_;
}

index_t director_t::find_new_entity_index()
{
    if (!free_list_.empty())
    {
        auto index = free_list_.back();
        free_list_.pop_back();
        return index;
    }

    if (!block_index_.empty())
    {
        auto& block_index = block_index_[block_index_.size() - 1];
        auto& current = next_free_indexes_[block_index];
        if (EDEN_CACHE_LINE_SIZE > current)
            return (current++) + EDEN_CACHE_LINE_SIZE * block_index;
    }
    create_new_block(1);
    return (block_count_++) * EDEN_CACHE_LINE_SIZE;
}

void director_t::create_new_block(index_t next_free_index)
{
    block_index_.push_back(block_count_);
    next_free_indexes_.resize(block_count_ + 1);
    next_free_indexes_[block_count_] = next_free_index;
}

internal::base_store_t& director_t::get_store(size_t component_index)
{
    return *stores_[component_index];
}
const internal::base_store_t& director_t::get_store(size_t component_index) const
{
    return *stores_[component_index];
}

void director_t::remove_all_components(entity_t& entity)
{
    for (auto store : stores_)
    {
        if (store && has_component(entity, store->mask()))
            store->remove(entity.id_.index);
    }
}

void director_t::clear_mask(entity_t& entity)
{
    masks_[entity.id_.index].reset();
}

bool director_t::has_component(entity_t& entity, mask_t component_mask)
{
    return (mask(entity) & component_mask) == component_mask;
}

bool director_t::has_component(const entity_t& entity, const mask_t& component_mask) const
{
    return (mask(entity) & component_mask) == component_mask;
}

bool director_t::is_valid(entity_t& entity)
{
    return entity.id_.index < versions_.size() && entity.id_.version == versions_[entity.id_.index];
}

bool director_t::is_valid(const entity_t& entity) const
{
    return entity.id_.index < versions_.size() && entity.id_.version == versions_[entity.id_.index];
}

void director_t::destroy(entity_t& entity)
{
    index_t index = entity.id_.index;
    remove_all_components(entity);
    ++versions_[index];
    free_list_.push_back(index);
    --count_;
}

mask_t& director_t::mask(entity_t& entity)
{
    return mask(entity.id_.index);
}

const mask_t& director_t::mask(const entity_t& entity) const
{
    return mask(entity.id_.index);
}

mask_t& director_t::mask(index_t index)
{
    return masks_[index];
}

const mask_t& director_t::mask(index_t index) const
{
    return masks_[index];
}

entity_t director_t::get_entity(id_t id)
{
    return entity_t(this, id);
}

entity_t director_t::get_entity(index_t index)
{
    return get_entity(id_t(index, versions_[index]));
}

size_t director_t::capacity() const
{
    return versions_.capacity();
}
} // namespace eden::ecs
