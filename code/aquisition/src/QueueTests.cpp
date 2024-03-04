#include "aquisition/Queue.hpp"
#include "gtest/gtest.h"

struct QueueTests : public testing::Test
{
    Queue<int> queue{3u};
};

TEST_F(QueueTests, emptyQueueReturnsNullopt)
{
    EXPECT_EQ(queue.pop(), std::nullopt);
}

TEST_F(QueueTests, elementPushedIntoQueueCanBeRetrieved)
{
    const int pushedIn{1234};
    queue.push(pushedIn);

    EXPECT_EQ(queue.pop(), pushedIn);
}

TEST_F(QueueTests, queueIsAFifo)
{
    const int el1{1234};
    const int el2{5678};
    queue.push(el1);
    queue.push(el2);

    EXPECT_EQ(queue.pop(), el1);
    EXPECT_EQ(queue.pop(), el2);
}

TEST_F(QueueTests, queueIsEmptyAfterAllElementsPopped)
{
    const int el1{9090};
    queue.push(el1);
    queue.pop();

    EXPECT_EQ(queue.pop(), std::nullopt);
}

TEST_F(QueueTests, queueDropsOldestElementWhenOverLimit)
{
    const int el1{1234};
    const int el2{5678};
    const int el3{9012};
    const int el4{3456};
    queue.push(el1);
    queue.push(el2);
    queue.push(el3);
    queue.push(el4);

    EXPECT_EQ(queue.pop(), el2);
}