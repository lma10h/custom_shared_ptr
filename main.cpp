#include <iostream>

#include <catch_amalgamated.hpp>
#include <custom_shared_ptr.h>

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

using namespace std;

class Foo
{
public:
    Foo(int value = 0)
        : m_value(value)
    {
    }

    int value() const
    {
        return m_value;
    }

private:
    int m_value = 0;
};

class Bar
{
};

TEST_CASE("constructor", "")
{
    {
        // check default contructor
        CustomSharedPtr<Foo> shared;
        REQUIRE(shared.get() == nullptr);
        REQUIRE(shared.use_count() == 0);
    }

    {
        // check contructor(new Class)
        Foo *foo = new Foo;
        CustomSharedPtr<Foo> shared(foo);
        REQUIRE(shared.get() == foo);
        REQUIRE(shared.use_count() == 1);
    }

    {
        // check copy from default constructor
        CustomSharedPtr<Foo> shared1;
        CustomSharedPtr<Foo> shared2(shared1);
        REQUIRE(shared1.get() == nullptr);
        REQUIRE(shared1.use_count() == 0);
        REQUIRE(shared2.get() == nullptr);
        REQUIRE(shared2.use_count() == 0);
    }

    {
        // check copy constructor
        CustomSharedPtr<Foo> shared1(new Foo);
        CustomSharedPtr<Foo> shared2(shared1);
        REQUIRE(shared1.get() == shared2.get());
        REQUIRE(shared1.use_count() == shared2.use_count());
    }

    {
        // check move constructor
        Foo *foo = new Foo;
        CustomSharedPtr<Foo> shared1(foo);
        CustomSharedPtr<Foo> shared2(std::move(shared1));
        REQUIRE(shared2.use_count() == 1);
        REQUIRE(shared2.get() == foo);
    }

    {
        // check operator=(const &)
        Foo *foo = new Foo;
        CustomSharedPtr<Foo> shared1(foo);
        CustomSharedPtr<Foo> shared2 = shared1;
        REQUIRE(shared1.use_count() == 2);
        REQUIRE(shared1.get() == foo);
        REQUIRE(shared2.use_count() == 2);
        REQUIRE(shared2.get() == foo);
    }

    {
        // check operator=(&&)
        Foo *foo = new Foo;
        CustomSharedPtr<Foo> shared1(foo);
        CustomSharedPtr<Foo> shared2 = std::move(shared1);
        REQUIRE(shared2.use_count() == 1);
        REQUIRE(shared2.get() == foo);
    }

    {
        // check operator*()
        int *foo = new int(5);
        CustomSharedPtr<int> shared1(foo);
        REQUIRE(*shared1 == 5);
        REQUIRE(shared1.get() == foo);
    }

    {
        // check operator->()
        Foo *foo = new Foo(5);
        CustomSharedPtr<Foo> shared1(foo);
        REQUIRE(shared1->value() == foo->value());
        REQUIRE(shared1.get() == foo);
    }

    {
        // check reset
        CustomSharedPtr<Foo> shared1;
        shared1.reset();
        REQUIRE(shared1.use_count() == 0);
        REQUIRE(shared1.get() == nullptr);

        Foo *foo = new Foo;
        shared1.reset(foo);
        REQUIRE(shared1.use_count() == 1);
        REQUIRE(shared1.get() == foo);
        shared1.reset();
        REQUIRE(shared1.use_count() == 0);
        REQUIRE(shared1.get() == nullptr);
    }
}
