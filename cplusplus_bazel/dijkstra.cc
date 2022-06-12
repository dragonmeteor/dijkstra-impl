#include "dijkstra.h"

#include "absl/container/flat_hash_set.h"
#include "absl/strings/str_format.h"
#include "binary_heap.h"

absl::Status GetPathFromSource(const DijkstraResult& result, const Vertex* vertex, Path& path) {
  path.length = std::numeric_limits<double>::max();
  path.vertices.clear();

  if (!result.shortest_path_distance.contains(vertex)) {
    return absl::FailedPreconditionError("No path to specified vertex.");
  }

  std::vector<const Vertex*> vertices;
  const Vertex* v = vertex;
  while (v != result.source) {
    vertices.push_back(v);
    v = result.pred.at(v);
  }
  vertices.push_back(result.source);

  path.length = result.shortest_path_distance.at(vertex);
  for (int i = vertices.size() - 1; i >= 0; i--) {
    path.vertices.push_back(vertices[i]);
  }
  return absl::OkStatus();
}

absl::Status RunDijkstra(const Graph& graph, const Vertex* source, DijkstraResult& result) {
  result.pred.clear();
  result.shortest_path_distance.clear();
  result.source = source;

  result.pred[source] = nullptr;
  result.shortest_path_distance[source] = 0.0;

  BinaryHeap<const Vertex*, double> heap;
  if (!heap.Add(source, 0.0).ok()) {
    return absl::InternalError("Cannot add source vertex to heap");
  }

  absl::flat_hash_set<const Vertex*> processed_vertices;
  while (!heap.empty()) {
    auto u = heap.Pop().value().object;
    
    processed_vertices.insert(u);
    auto adj_list_result = graph.GetAdjList(u);
    if (!adj_list_result.ok()) {
      return absl::InternalError(
          absl::StrFormat("Cannot get adjacenty list of Vertex %s.", u->name()));
    }
    auto adj_list = adj_list_result.value();

    for (auto it = adj_list->begin(); it != adj_list->end(); it++) {
      const Edge* edge = *it;
      if (processed_vertices.contains(edge->dest())) {
        continue;
      }
      if (!result.shortest_path_distance.contains(edge->dest())) {
        result.shortest_path_distance[edge->dest()] = std::numeric_limits<double>::max();
        result.pred[edge->dest()] = nullptr;
        if (!heap.Add(edge->dest(), result.shortest_path_distance[edge->dest()]).ok()) {
          return absl::InternalError(
              absl::StrFormat("Cannot add Vertex %s to the heap", edge->dest()->name()));
        }
      }
      double new_distance = result.shortest_path_distance[edge->source()] + edge->weight();
      if (new_distance < result.shortest_path_distance[edge->dest()]) {
        result.shortest_path_distance[edge->dest()] = new_distance;
        result.pred[edge->dest()] = edge->source();
        if (!heap.ChangeValue(edge->dest(), new_distance).ok()) {
          return absl::InternalError(
              absl::StrFormat("Cannot change heap value of Vertex %s", edge->dest()->name()));
        }
      }
    }
  }

  return absl::OkStatus();
}