#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/status.h"
#include "graph.h"

struct Path {
  double length;
  std::vector<const Vertex*> vertices;
};

struct DijkstraResult {
  const Vertex* source;
  absl::flat_hash_map<const Vertex*, double> shortest_path_distance;
  absl::flat_hash_map<const Vertex*, const Vertex*> pred;
};

absl::Status GetPathFromSource(const DijkstraResult &result, const Vertex* vertex, Path& path);
absl::Status RunDijkstra(const Graph& graph, const Vertex* source, DijkstraResult &result);

#endif