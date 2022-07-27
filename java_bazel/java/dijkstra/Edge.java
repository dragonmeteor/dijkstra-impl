package dijkstra;

import com.google.auto.value.AutoValue;

@AutoValue
public abstract class Edge {
  public abstract String source();

  public abstract String dest();

  public abstract double weight();

  public static Edge create(String source, String dest, double weight) {
    return new AutoValue_Edge(source, dest, weight);
  }
}
