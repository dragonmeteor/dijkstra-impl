#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

class Vertex {
public:
  explicit Vertex(absl::string_view name);
  Vertex(const Vertex &other) = delete;
  Vertex &operator=(const Vertex &other) = delete;

  absl::string_view name() const;

private:
  std::string name_;
};

class Edge {
public:
  explicit Edge(const Vertex *source, const Vertex *dest, double weight);
  Edge(const Edge &edge) = delete;
  Edge &operator=(const Edge &other) = delete;

  const Vertex *source() const;
  const Vertex *dest() const;
  double weight() const;

private:
  const Vertex *source_;
  const Vertex *dest_;
  double weight_;
};

class Graph {
public:
  Graph(const Graph &other) = delete;
  Graph &operator=(const Graph &other) = delete;

  absl::Status AddVertex(absl::string_view name);
  const absl::flat_hash_map<absl::string_view, const Vertex *> &GetNameToVertexMap() const;
  absl::StatusOr<const Vertex *> GetVertex(absl::string_view name) const;

  absl::Status AddEdge(const Vertex *source, const Vertex *dest, double weight);
private:
  std::vector<std::unique_ptr<Vertex>> vertices_;
  absl::flat_hash_map<absl::string_view, const Vertex *> name_to_vertex_;

  std::vector<std::unique_ptr<Edge>> edges_;
  std::vector<std::unique_ptr<std::vector<const Edge *>>> adj_lists_;
  absl::flat_hash_map<const Vertex *, const std::vector<const Edge *> *>
      vertex_to_adj_list_;
};

#endif