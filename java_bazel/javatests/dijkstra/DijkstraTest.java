package dijkstra;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

import static com.google.common.truth.Truth.assertThat;

@RunWith(JUnit4.class)
public class DijkstraTest {
  @Test
  public void run_oneVertexGraph() {
    Graph graph = Graph.builder()
        .addVertex("A")
        .build();

    Dijkstra.Result result = Dijkstra.run(graph, "A");

    assertThat(result.source()).isEqualTo("A");
    assertThat(result.prev().get("A")).isEqualTo("");
    assertThat(result.distance().get("A")).isEqualTo(0.0);
  }

  @Test
  public void run_twoVerticesGraph() {
    Graph graph = Graph.builder()
        .addVertex("A")
        .addVertex("B")
        .addEdge("A", "B", 10.0)
        .build();

    Dijkstra.Result result = Dijkstra.run(graph, "A");

    assertThat(result.source()).isEqualTo("A");
    assertThat(result.prev().get("A")).isEqualTo("");
    assertThat(result.distance().get("A")).isEqualTo(0.0);
    assertThat(result.prev().get("B")).isEqualTo("A");
    assertThat(result.distance().get("B")).isEqualTo(10.0);
  }

  @Test
  public void run_threeVerticesGraph() {
    Graph graph = Graph.builder()
        .addVertex("A")
        .addVertex("B")
        .addVertex("C")
        .addEdge("A", "B", 10.0)
        .addEdge("A", "C", 30.0)
        .addEdge("B", "C", 10.0)
        .build();

    Dijkstra.Result result = Dijkstra.run(graph, "A");

    assertThat(result.source()).isEqualTo("A");
    assertThat(result.prev().get("A")).isEqualTo("");
    assertThat(result.distance().get("A")).isEqualTo(0.0);
    assertThat(result.prev().get("B")).isEqualTo("A");
    assertThat(result.distance().get("B")).isEqualTo(10.0);
    assertThat(result.prev().get("C")).isEqualTo("B");
    assertThat(result.distance().get("C")).isEqualTo(20.0);
  }
}
