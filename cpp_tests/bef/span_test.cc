/*
 * Copyright 2022 The TensorFlow Runtime Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "tfrt/bef/span.h"

#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace tfrt {
namespace bef {
namespace {

TEST(SpanTest, SpanOfTrivial) {
  tfrt::bef::Buffer buffer;
  tfrt::bef::Allocator alloc(&buffer);

  auto ctor = bef::New<bef::Vector<uint32_t>>(&alloc, /*size=*/4);

  for (int i = 0; i < 4; ++i) {
    ctor.ConstructAt(i, i);
  }

  bef::Vector<uint32_t> vec(buffer.Get(ctor.address()));
  bef::Span<uint32_t> span(vec);

  ASSERT_EQ(span.size(), 4);
  EXPECT_EQ(span[0], 0);
  EXPECT_EQ(span[1], 1);
  EXPECT_EQ(span[2], 2);
  EXPECT_EQ(span[3], 3);

  EXPECT_THAT(span, testing::ElementsAreArray({0, 1, 2, 3}));
}

TEST(BefTest, SpanOfVector) {
  tfrt::bef::Buffer buffer;
  tfrt::bef::Allocator alloc(&buffer);

  using T = bef::Vector<uint32_t>;
  using V = bef::Vector<T>;

  auto vctor = bef::New<V>(&alloc, 3);

  {
    auto tctor = vctor.ConstructAt(0, 2);
    tctor.ConstructAt(0, 0);
    tctor.ConstructAt(1, 1);
  }

  {
    auto tctor = vctor.ConstructAt(1, 1);
    tctor.ConstructAt(0, 2);
  }

  vctor.ConstructAt(2, 0);

  V v(buffer.Get(vctor.address()));
  bef::Span<T> span(v);

  T t0 = span[0];
  ASSERT_EQ(t0.size(), 2);
  EXPECT_EQ(t0[0], 0);
  EXPECT_EQ(t0[1], 1);
  EXPECT_THAT(t0, testing::ElementsAreArray({0, 1}));

  T t1 = span[1];
  ASSERT_EQ(t1.size(), 1);
  EXPECT_EQ(t1[0], 2);
  EXPECT_THAT(t1, testing::ElementsAreArray({2}));

  T t2 = span[2];
  ASSERT_EQ(t2.size(), 0);
}

}  // namespace
}  // namespace bef
}  // namespace tfrt
