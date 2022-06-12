#include "graph.h"

#include <gtest/gtest.h>

TEST(TestGraph, AddVertex) {
  Graph graph;
  EXPECT_TRUE(graph.AddVertex("A").ok());
  EXPECT_TRUE(graph.AddVertex("B").ok());
}

TEST(TestGraph, AddDuplicatedVertices) {
  Graph graph;
  EXPECT_TRUE(graph.AddVertex("A").ok());
  EXPECT_TRUE(absl::IsInvalidArgument(graph.AddVertex("A")));
}

TEST(TestGraph, GetNameToVertexMap) {
  Graph graph;
  graph.AddVertex("A").IgnoreError();
  graph.AddVertex("B").IgnoreError();
  graph.AddVertex("C").IgnoreError();
  auto name_to_vertex = graph.GetNameToVertexMap();
  
  EXPECT_EQ(name_to_vertex.size(), 3);
  EXPECT_EQ(name_to_vertex["A"]->name(), "A");
  EXPECT_EQ(name_to_vertex["B"]->name(), "B");
  EXPECT_EQ(name_to_vertex["C"]->name(), "C");
  EXPECT_EQ(name_to_vertex.find("D"), name_to_vertex.end());
}

TEST(TestGraph, AddEdge) {
  Graph graph;
  graph.AddVertex("A").IgnoreError();
  graph.AddVertex("B").IgnoreError();
  graph.AddVertex("C").IgnoreError();

  auto A = graph.GetVertex("A").value_or(nullptr);
  auto B = graph.GetVertex("B").value_or(nullptr);
  auto C = graph.GetVertex("C").value_or(nullptr);

  EXPECT_TRUE(graph.AddEdge(A, B, 10.0).ok());
  EXPECT_TRUE(graph.AddEdge(B, C, 10.0).ok());
  EXPECT_TRUE(graph.AddEdge(A, C, 30.0).ok());

  auto ab_edge = graph.GetAdjList(A).value()->at(0);
  EXPECT_EQ(ab_edge->source(), A);
  EXPECT_EQ(ab_edge->dest(), B);
  EXPECT_EQ(ab_edge->weight(), 10.0);

  auto bc_edge = graph.GetAdjList(B).value()->at(0);
  EXPECT_EQ(bc_edge->source(), B);
  EXPECT_EQ(bc_edge->dest(), C);
  EXPECT_EQ(bc_edge->weight(), 10.0);

  auto ac_edge = graph.GetAdjList(A).value()->at(1);
  EXPECT_EQ(ac_edge->source(), A);
  EXPECT_EQ(ac_edge->dest(), C);
  EXPECT_EQ(ac_edge->weight(), 30.0);
}