package dijkstra;

import com.google.common.collect.ImmutableList;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

import static com.google.common.truth.Truth.assertThat;
import static org.junit.Assert.assertThrows;

@RunWith(JUnit4.class)
public class GraphTest {
  @Test
  public void build_emptyGraph() {
    Graph graph = Graph.builder().build();

    assertThat(graph.vertices()).isEmpty();
    assertThat(graph.vertexToAdjList()).isEmpty();
    ;
  }

  @Test
  public void build_oneVertex() {
    Graph graph = Graph.builder()
        .addVertex("A")
        .build();

    assertThat(graph.vertices()).containsExactly("A");
    assertThat(graph.vertexToAdjList()).containsExactly("A", ImmutableList.of());
  }

  @Test
  public void build_oneEdge() {
    Graph graph = Graph.builder()
        .addVertex("A")
        .addVertex("B")
        .addEdge("A", "B", 1)
        .build();

    assertThat(graph.vertices()).containsExactly("A", "B");
    assertThat(graph.vertexToAdjList()).containsExactly(
        "A", ImmutableList.of(Edge.create("A", "B", 1)),
        "B", ImmutableList.of()
    );
  }

  @Test
  public void build_threeEdges() {
    Graph graph = Graph.builder()
        .addVertex("A")
        .addVertex("B")
        .addVertex("C")
        .addEdge("A", "B", 10)
        .addEdge("B", "C", 10)
        .addEdge("A", "C", 30)
        .build();

    assertThat(graph.vertices()).containsExactly("A", "B", "C");
    assertThat(graph.vertexToAdjList()).containsExactly(
        "A", ImmutableList.of(Edge.create("A", "B", 10), Edge.create("A", "C", 30)),
        "B", ImmutableList.of(Edge.create("B", "C", 10)),
        "C", ImmutableList.of()
    );
  }

  @Test
  public void build_emptyVertexName() {
    IllegalArgumentException exception = assertThrows(
        IllegalArgumentException.class,
        () -> Graph.builder()
            .addVertex("")
            .build());

    assertThat(exception).hasMessageThat().startsWith("Vertex name cannot be empty!");
  }

  @Test
  public void build_duplicatedVertexNames() {
    IllegalArgumentException exception = assertThrows(
        IllegalArgumentException.class,
        () -> Graph.builder()
            .addVertex("A")
            .addVertex("A")
            .build());

    assertThat(exception).hasMessageThat().startsWith("Vertex 'A' already exists!");
  }

  @Test
  public void build_addEdgeWithNonExistingVertices() {
    IllegalArgumentException exception = assertThrows(
        IllegalArgumentException.class,
        () -> Graph.builder()
            .addEdge("A", "B", 10)
            .build());

    assertThat(exception).hasMessageThat().startsWith("Vertex 'A' does not exists!");
  }

  @Test
  public void build_addEdgeWithNegativeWeight() {
    IllegalArgumentException exception = assertThrows(
        IllegalArgumentException.class,
        () -> Graph.builder()
            .addVertex("A")
            .addVertex("B")
            .addEdge("A", "B", -10)
            .build());

    assertThat(exception).hasMessageThat().startsWith("Edge weight must be non-negative.");
  }
}