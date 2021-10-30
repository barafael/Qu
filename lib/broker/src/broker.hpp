#pragma once

#include <map>
#include <set>

#include "queue.hpp"
#include "resumable.hpp"

template <typename Event, size_t MAX_EVENT_SIZE> class Broker {
    public:
    Broker(Queue<Event, 64> &queue) : queue(queue) {
    }

    void register_resumable(Resumable<Event> *resumable) {
        this->registry.insert(resumable);
    }

    void run(bool &run) {
        while (run) {
            if (!this->queue.is_empty()) {
                Event e = this->queue.pop();
                for (Resumable<Event> *resumable : this->registry) {
                    if (resumable->can_proceed_on(e)) {
                        resumable.advance(&this->event_data, 0);
                    }
                }
            }
        }
    }

    void run(size_t iterations) {
        for (size_t index = 0; index < iterations; index += 1) {
            while (this->queue.is_empty()) { continue; }
            Event e = this->queue.pop();
            for (Resumable<Event> *resumable : this->registry) {
                if (resumable->can_proceed_on(e)) {
                    resumable->advance(&this->event_data, sizeof(size_t));
                }
            }
        }
    }

    private:
    Queue<Event, 64> &           queue;
    std::set<Resumable<Event> *> registry;
    uint8_t                      event_data[MAX_EVENT_SIZE] = { 0 };
};
