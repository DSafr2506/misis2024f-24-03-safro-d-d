#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "queuea/queuea.hpp"

TEST_CASE("Testing QueueA") {
    SUBCASE("Constructor and Destructor") {
        QueueA q;
        CHECK(q.IsEmpty());
    }

    SUBCASE("Push and Pop") {
        QueueA q;
        q.Push(1);
        q.Push(2);
        q.Push(3);

        CHECK(!q.IsEmpty());
        CHECK_EQ(q.Top(), 1);
        q.Pop();
        CHECK_EQ(q.Top(), 2);
        q.Pop();
        CHECK_EQ(q.Top(), 3);
        q.Pop();
        CHECK(q.IsEmpty());
    }

    SUBCASE("Copy Constructor") {
        QueueA q;
        q.Push(1);
        q.Push(2);
        q.Push(3);

        QueueA copy(q);
        CHECK_EQ(copy.Top(), 1);
        copy.Pop();
        CHECK_EQ(copy.Top(), 2);
        copy.Pop();
        CHECK_EQ(copy.Top(), 3);
        copy.Pop();
        CHECK(copy.IsEmpty());
    }

    SUBCASE("Assignment Operator") {
        QueueA q;
        q.Push(1);
        q.Push(2);
        q.Push(3);

        QueueA assign;
        assign = q;
        CHECK_EQ(assign.Top(), 1);
        assign.Pop();
        CHECK_EQ(assign.Top(), 2);
        assign.Pop();
        CHECK_EQ(assign.Top(), 3);
        assign.Pop();
        CHECK(assign.IsEmpty());
    }

    SUBCASE("Move Constructor") {
        QueueA q;
        q.Push(1);
        q.Push(2);
        q.Push(3);

        QueueA moved(std::move(q));
        CHECK(moved.Top() == 1);
        moved.Pop();
        CHECK(moved.Top() == 2);
        moved.Pop();
        CHECK(moved.Top() == 3);
        moved.Pop();
        CHECK(moved.IsEmpty());
    }

    SUBCASE("Move Assignment") {
        QueueA q;
        q.Push(1);
        q.Push(2);
        q.Push(3);

        QueueA move_assign;
        move_assign = std::move(q);
        CHECK(move_assign.Top() == 1);
        move_assign.Pop();
        CHECK(move_assign.Top() == 2);
        move_assign.Pop();
        CHECK(move_assign.Top() == 3);
        move_assign.Pop();
        CHECK(move_assign.IsEmpty());
    }

    SUBCASE("Clear") {
        QueueA q;
        q.Push(1);
        q.Push(2);
        q.Clear();
        CHECK(q.IsEmpty());
    }

    SUBCASE("Exception Handling") {
        QueueA q;
        CHECK_THROWS_AS(q.Top(), std::logic_error);
    }
}
