#pragma once

#include "resumable.hpp"

#include <cassert>

namespace SomeResumable {

enum class Event {
    Start,
    DoStuff,
    DoOtherStuff,
    Finalize,
};

enum class State {
    Init,
    Process,
    Final,
};

class StateMachine : public Resumable<Event> {
    public:
    void advance(const void *event, size_t event_size) override {
        switch (this->state) {
            case State::Init: {
                this->internal_state = (*(size_t *) event) + 1;
                this->state          = State::Process;
            } break;
            case State::Process: {
                this->internal_state = (*(size_t *) event) + 10;
                this->state          = State::Final;
            } break;
            case State::Final: {
                this->internal_state = 0;
                this->state          = State::Init;
            } break;
        }
    }

    bool can_proceed_on(Event &event) {
        switch (this->state) {
            case State::Init: return event == Event::Start;
            case State::Process: return event == Event::DoStuff || event == Event::DoOtherStuff;
            case State::Final: return event == Event::Finalize;
        }
        return false;
    }

    size_t get_internal_state() {
        return this->internal_state;
    }

    State get_state() {
        return this->state;
    }

    private:
    size_t internal_state = 0;
    State  state          = State::Init;
};
} // namespace SomeResumable
