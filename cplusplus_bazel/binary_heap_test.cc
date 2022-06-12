#include "binary_heap.h"

#include <gtest/gtest.h>

TEST(TestBinaryHeap, NewHeap) {
  BinaryHeap<int, double> heap;
  EXPECT_EQ(heap.size(), 0);
}

TEST(TestBinaryHeap, AddRaw) {
  BinaryHeap<int, double> heap;
  EXPECT_TRUE(heap.AddRaw(1, 10).ok());
  EXPECT_TRUE(heap.AddRaw(2, 20).ok());
  EXPECT_TRUE(heap.AddRaw(3, 30).ok());
  EXPECT_TRUE(absl::IsInvalidArgument(heap.AddRaw(3, 40)));
  EXPECT_EQ(heap.size(), 3);
  EXPECT_TRUE(heap.CheckRep().ok());
}

TEST(TestBinaryHeap, IsHeapOrder) {
  BinaryHeap<int, double> heap;
  EXPECT_TRUE(heap.AddRaw(1, 10).ok());
  EXPECT_TRUE(heap.AddRaw(2, 20).ok());
  EXPECT_TRUE(heap.AddRaw(3, 30).ok());
  EXPECT_TRUE(heap.CheckRep().ok());
  EXPECT_TRUE(heap.IsHeapOrder());
}

TEST(TestBinaryHeap, NotHeapOrder) {
  BinaryHeap<int, double> heap;
  EXPECT_TRUE(heap.AddRaw(1, 30).ok());
  EXPECT_TRUE(heap.AddRaw(2, 20).ok());
  EXPECT_TRUE(heap.AddRaw(3, 10).ok());
  EXPECT_TRUE(heap.CheckRep().ok());
  EXPECT_FALSE(heap.IsHeapOrder());
}

TEST(TestBinaryHeap, Build) {
  BinaryHeap<int, double> heap;
  EXPECT_TRUE(heap.AddRaw(1, 30).ok());
  EXPECT_TRUE(heap.AddRaw(2, 20).ok());
  EXPECT_TRUE(heap.AddRaw(3, 10).ok());
  heap.Build();
  EXPECT_TRUE(heap.CheckRep().ok());
  EXPECT_TRUE(heap.IsHeapOrder());
}

TEST(TestBinaryHeap, Add) {
  BinaryHeap<int, double> heap;
  EXPECT_TRUE(heap.Add(1, 30).ok());
  EXPECT_TRUE(heap.Add(2, 20).ok());
  EXPECT_TRUE(heap.Add(3, 10).ok());
  EXPECT_TRUE(heap.CheckRep().ok());
  EXPECT_TRUE(heap.IsHeapOrder());
}

TEST(TestBinaryHeap, Pop) {
  BinaryHeap<int, double> heap;
  EXPECT_TRUE(heap.Add(1, 30).ok());
  EXPECT_TRUE(heap.Add(2, 20).ok());
  EXPECT_TRUE(heap.Add(3, 10).ok());

  absl::optional<HeapEntry<int, double>> pop_result = heap.Pop();
  EXPECT_EQ(pop_result.value().object, 3);
  EXPECT_EQ(pop_result.value().value, 10);
  EXPECT_EQ(heap.size(), 2);
  EXPECT_TRUE(heap.CheckRep().ok());

  pop_result = heap.Pop();  
  EXPECT_EQ(pop_result.value().object, 2);
  EXPECT_EQ(pop_result.value().value, 20);
  EXPECT_EQ(heap.size(), 1);
  EXPECT_TRUE(heap.CheckRep().ok());

  pop_result = heap.Pop();  
  EXPECT_EQ(pop_result.value().object, 1);
  EXPECT_EQ(pop_result.value().value, 30);
  EXPECT_TRUE(heap.CheckRep().ok());

  pop_result = heap.Pop();
  EXPECT_FALSE(pop_result.has_value());
  EXPECT_TRUE(heap.CheckRep().ok());
}

TEST(TestBinaryHeap, GetValue) {
  BinaryHeap<int, double> heap;
  EXPECT_TRUE(heap.Add(1, 30).ok());
  EXPECT_TRUE(heap.Add(2, 20).ok());
  EXPECT_TRUE(heap.Add(3, 10).ok());

  EXPECT_EQ(heap.GetValue(1).value(), 30);
  EXPECT_EQ(heap.GetValue(2).value(), 20);
  EXPECT_EQ(heap.GetValue(3).value(), 10);
  EXPECT_FALSE(heap.GetValue(4).has_value());
}

TEST(TestBinaryHeap, ChangeValue) {
  BinaryHeap<int, double> heap;
  EXPECT_TRUE(heap.Add(1, 30).ok());
  EXPECT_TRUE(heap.Add(2, 20).ok());
  EXPECT_TRUE(heap.Add(3, 10).ok());

  EXPECT_TRUE(heap.ChangeValue(1, 0).ok());
  EXPECT_TRUE(heap.CheckRep().ok());
  EXPECT_TRUE(heap.IsHeapOrder());

  EXPECT_EQ(heap.GetValue(1).value(), 0);
  EXPECT_EQ(heap.GetValue(2).value(), 20);
  EXPECT_EQ(heap.GetValue(3).value(), 10);
}