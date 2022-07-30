package dijkstra;

import com.google.auto.value.AutoValue;
import com.google.common.base.Preconditions;
import com.google.common.collect.ImmutableList;
import com.google.common.collect.ImmutableMap;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class Dijkstra {
  @AutoValue
  public static abstract class Result {
    abstract String source();

    abstract ImmutableMap<String, String> prev();

    abstract ImmutableMap<String, Double> distance();

    public static Result create(String source, Map<String, String> prev, Map<String, Double> distance) {
      return new AutoValue_Dijkstra_Result(source, ImmutableMap.copyOf(prev), ImmutableMap.copyOf(distance));
    }
  }

  public static Result run(Graph graph, String source) {
    Preconditions.checkArgument(graph.vertices().contains(source));

    HashMap<String, String> prev = new HashMap<>();
    HashMap<String, Double> distance = new HashMap<>();
    HashMap<String, Boolean> visited = new HashMap<>();

    prev.put(source, "");
    distance.put(source, 0.0);
    visited.put(source, false);
    BinaryHeap<String, Double> heap = new BinaryHeap<>();
    heap.add(source, 0.0);

    while (!heap.isEmpty()) {
      Optional<String> optionalU = heap.deleteMin();
      if (optionalU.isEmpty()) {
        break;
      }
      String u = optionalU.orElseThrow();
      visited.put(u, true);
      Double uDist = distance.get(u);
      ImmutableList<Edge> edges = Preconditions.checkNotNull(graph.vertexToAdjList().get(u));
      for (Edge edge : edges) {
        String v = edge.dest();
        Double w = edge.weight();
        if (visited.containsKey(v) && visited.get(v)) {
          continue;
        }
        if (!distance.containsKey(v)) {
          distance.put(v, Double.MAX_VALUE);
          heap.add(v, Double.MAX_VALUE);
        }
        if (!visited.containsKey(v)) {
          visited.put(v, false);
        }
        Double vDist = distance.get(v);
        if (uDist + w < vDist) {
          distance.put(v, uDist + w);
          heap.changeValue(v, uDist + w);
          prev.put(v, u);
        }
      }
    }

    return Result.create(source, prev, distance);
  }
}
