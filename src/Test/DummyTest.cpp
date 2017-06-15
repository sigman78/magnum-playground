#include <Corrade/TestSuite/Tester.h>

struct DummyTest: TestSuite::Tester {
    explicit DummyTest();

    void test1();
    void test2();
};

DummyTest::DummyTest() {
    addTests({&DummyTest::test1,
              &ArrayTest::test2});
}

void DummyTest::test1() {
    CORRADE_COMPARE(1 + 1, 2);
}

void DummyTest::test2() {
    CORRADE_VERIFY(true);
}

CORRADE_TEST_MAIN(DummyTest)
