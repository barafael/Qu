#include <unity.h>

#include "../lib/broker/test/broker_test.hpp"
#include "../lib/broker/test/resumable_test.hpp"
#include "../lib/queue/test/test.hpp"

int main(int argc, char **argv) {
    Test_Queue::test_all();
    Test_Resumable::test_all();
    Test_Broker::test_all();

    return 0;
}
