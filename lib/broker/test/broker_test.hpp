#pragma once

#include "broker.hpp"

#include <cassert>

#include <unity.h>

#include "some_resumable.hpp"

namespace Test_Broker {

void test_broker() {
    Queue<SomeResumable::Event, 64>  queue;
    SomeResumable::StateMachine      resumable;
    Broker<SomeResumable::Event, 32> broker(queue);
    broker.register_resumable(&resumable);

    TEST_ASSERT(resumable.get_state() == SomeResumable::State::Init);
    queue.push(SomeResumable::Event::Start);
    broker.run(1);
    TEST_ASSERT(resumable.get_state() == SomeResumable::State::Process);

    queue.push(SomeResumable::Event::DoStuff);
    broker.run(1);
    TEST_ASSERT(resumable.get_state() == SomeResumable::State::Final);

    queue.push(SomeResumable::Event::Finalize);
    broker.run(1);
    TEST_ASSERT(resumable.get_state() == SomeResumable::State::Init);
}

void test_all() {
    UNITY_BEGIN();
    RUN_TEST(test_broker);
    UNITY_END();
}
} // namespace Test_Broker
