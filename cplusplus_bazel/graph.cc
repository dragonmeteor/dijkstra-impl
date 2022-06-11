#include "graph.h"

Vertex::Vertex(absl::string_view name) : name_(name) {
  // NO-OP
}

absl::string_view Vertex::name() const { return name_; }

Edge::Edge(const Vertex *source, const Vertex *dest, double weight)
    : source_(source), dest_(dest), weight_(weight) {
  // NO-OP
}

const Vertex *Edge::source() const { return source_; }

const Vertex *Edge::dest() const { return dest_; }

double Edge::weight() const { return weight_; }

absl::Status Graph::AddVertex(absl::string_view name) {
  if (name_to_vertex_.find(name) != name_to_vertex_.end()) {
    return absl::InvalidArgumentError(
        absl::StrCat("Vertex with name '", name, "' already exists!"));
  }
  std::unique_ptr<Vertex> vertex = std::make_unique<Vertex>(name);
  const Vertex *vertex_ptr = vertex.get();
  vertices_.push_back(std::move(vertex));
  name_to_vertex_[vertex_ptr->name()] = vertex_ptr;

  std::unique_ptr<std::vector<const Edge *>> adj_list;
  const std::vector<const Edge *>* adj_list_ptr = adj_list.get();
  adj_lists_.push_back(std::move(adj_list));
  vertex_to_adj_list_[vertex_ptr] = adj_list_ptr;

  return absl::OkStatus();
}

const absl::flat_hash_map<absl::string_view, const Vertex *> &
Graph::GetNameToVertexMap() const {
  return name_to_vertex_;
}

absl::StatusOr<const Vertex *> Graph::GetVertex(absl::string_view name) const {
  if (name_to_vertex_.find(name) == name_to_vertex_.end()) {
    return absl::NotFoundError(
        absl::StrCat("Vertex with name '", name, "' does not exist!"));
  }
  const Vertex *ptr = name_to_vertex_.at(name);
  return ptr;
}

absl::Status Graph::AddEdge(const Vertex* source, const Vertex* dest, double weight) {
    if (vertex_to_adj_list_.find(source) == vertex_to_adj_list_.end()) {
        return absl::InvalidArgumentError("Source vertex is not in the graph.");
    }
    if (vertex_to_adj_list_.find(dest) == vertex_to_adj_list_.end()) {
        return absl::InvalidArgumentError("Target vertex is not in the graph");
    }
    
    std::unique_ptr<Edge> edge = std::make_unique<Edge>(source, dest, weight);
    const Edge* edge_ptr = edge.get();
    edges_.push_back(std::move(edge));

    return absl::OkStatus();
}