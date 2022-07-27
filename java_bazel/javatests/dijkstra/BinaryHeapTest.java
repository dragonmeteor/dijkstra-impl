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

  @Test
  public void addRaw() {
    BinaryHeap<String, Double> heap = new BinaryHeap<>();
    heap.addRaw("A", 10.0);
    heap.addRaw("B", 20.0);

    heap.checkRep();
    assertThat(heap.isHeapOrder()).isTrue();
    assertThat(heap.size()).isEqualTo(2);
    assertThat(heap.getValue("A")).hasValue(10.0);
    assertThat(heap.getValue("B")).hasValue(20.0);
    assertThat(heap.getValue("C")).isEmpty();
  }

  @Test
  public void isHeapOrder_false() {
    BinaryHeap<String, Double> heap = new BinaryHeap<>();
    heap.addRaw("A", 10.0);
    heap.addRaw("B", 20.0);
    heap.addRaw("C", 5.0);

    assertThat(heap.isHeapOrder()).isFalse();
  }
}
