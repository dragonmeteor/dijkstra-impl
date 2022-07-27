package dijkstra;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

import static com.google.common.truth.Truth.assertThat;
import static com.google.common.truth.Truth8.assertThat;

@RunWith(JUnit4.class)
public class BinaryHeapTest {
  @Test
  public void emptyBinaryHeap() {
    BinaryHeap<String, Double> heap = new BinaryHeap<>();

    heap.checkRep();
    assertThat(heap.size()).isEqualTo(0);
    assertThat(heap.getValue("A")).isEmpty();
  }
}
