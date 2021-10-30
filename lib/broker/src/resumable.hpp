#pragma once

#include <cstddef>
#include <cstdint>

template <typename Event> class Resumable {
    public:
    virtual void advance(const void *event, size_t event_size) = 0;
    virtual bool can_proceed_on(Event &event)                  = 0;

    protected:
    size_t local_continuation = 0;

    private:
    void * locals      = nullptr;
    size_t locals_size = 0;
};
