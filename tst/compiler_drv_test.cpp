#include <gtest/gtest.h>
#include "ir/ir.h"
#include "frontend/frontend.h"

TEST(CompilerDrvTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}
