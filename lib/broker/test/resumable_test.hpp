#pragma once

#include "resumable.hpp"

#include <cassert>

#include <unity.h>

#include "some_resumable.hpp"

namespace Test_Resumable {

void test_resumable() {
    SomeResumable::StateMachine resumable;
    TEST_ASSERT(resumable.get_state() == SomeResumable::State::Init);
    TEST_ASSERT(resumable.get_internal_state() == 0);

    size_t event_code = 100;
    resumable.advance(&event_code, sizeof(size_t));
    TEST_ASSERT(resumable.get_state() == SomeResumable::State::Process);
    TEST_ASSERT(resumable.get_internal_state() == 101);

    event_code = 200;
    resumable.advance(&event_code, sizeof(size_t));
    TEST_ASSERT(resumable.get_state() == SomeResumable::State::Final);
    TEST_ASSERT(resumable.get_internal_state() == 210);

    event_code = 300;
    resumable.advance(&event_code, sizeof(size_t));
    TEST_ASSERT(resumable.get_state() == SomeResumable::State::Init);
    TEST_ASSERT(resumable.get_internal_state() == 0);
}

void test_all() {
    UNITY_BEGIN();
    RUN_TEST(test_resumable);
    UNITY_END();
}
} // namespace Test_Resumable
