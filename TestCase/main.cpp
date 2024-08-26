#include "test_case.h"

#include <iostream>

TestCase(main, test) {
    ASSERT_EQ('a', 'a');
    ASSERT_TRUE(true);
}

TestCase(main, tese1) {
    ASSERT_GE(3, 2);
}

TestCase(main, tese2) {
    ASSERT_GE(1, 2);
}

int main() {
    int ret = 0;
    ret = Test::RunAllTestCases();
}