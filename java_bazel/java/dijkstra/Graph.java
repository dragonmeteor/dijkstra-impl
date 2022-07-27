package dijkstra;

import com.google.auto.value.AutoValue;
import com.google.common.base.Preconditions;
import com.google.common.collect.ImmutableList;
import com.google.common.collect.ImmutableMap;
import com.google.common.collect.ImmutableSet;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

import static com.google.common.collect.ImmutableMap.toImmutableMap;

@AutoValue
public abstract class Graph {
  public abstract ImmutableSet<String> vertices();

  public abstract ImmutableMap<String, ImmutableList<Edge>> vertexToAdjList();

  public static class Builder {
    private final HashSet<String> vertices = new HashSet<>();
    private final HashMap<String, ArrayList<Edge>> vertexToAdjList = new HashMap<>();

    public Builder addVertex(String name) {
      Preconditions.checkArgument(!name.isEmpty(), "Vertex name cannot be empty!");
      Preconditions.checkArgument(!vertices.contains(name), String.format("Vertex '%s' already exists!", name));
      vertices.add(name);
      vertexToAdjList.put(name, new ArrayList<>());
      return this;
    }

    public Builder addEdge(String source, String dest, double weight) {
      Preconditions.checkArgument(vertices.contains(source), String.format("Vertex '%s' does not exists!", source));
      Preconditions.checkArgument(vertices.contains(dest), String.format("Vertex '%s' does not exists!", dest));
      Preconditions.checkArgument(weight >= 0, "Edge weight must be non-negative.");
      ArrayList<Edge> adjList = vertexToAdjList.get(source);
      adjList.add(Edge.create(source, dest, weight));
      return this;
    }

    public Graph build() {
      ImmutableSet<String> immutableVertices = ImmutableSet.copyOf(vertices);
      ImmutableMap<String, ImmutableList<Edge>> immutableVertexToAdjList =
          vertexToAdjList.entrySet().stream().collect(toImmutableMap(
              Map.Entry::getKey,
              entry -> ImmutableList.copyOf(entry.getValue())));
      return new AutoValue_Graph(immutableVertices, immutableVertexToAdjList);
    }
  }

  public static Builder builder() {
    return new Builder();
  }
}
