package dijkstra;

import com.google.common.base.Preconditions;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Optional;

public class BinaryHeap<KeyType, ValueType extends Comparable<ValueType>> {
  private final HashMap<KeyType, ValueType> values = new HashMap<>();
  private final HashMap<KeyType, Integer> valueToPostion = new HashMap<>();
  private final ArrayList<KeyType> keys = new ArrayList<>();

  public BinaryHeap() {
    // NO-OP
  }

  void addRaw(KeyType key, ValueType value) {
    Preconditions.checkArgument(!values.containsKey(key), String.format("Key '%s' already exists", key));
    values.put(key, value);
    keys.add(key);
    valueToPostion.put(key, keys.size() - 1);
  }

  public boolean isHeapOrder() {
    for (int i = 0; i < values.size() / 2; i++) {
      KeyType currentKey = keys.get(i);
      ValueType currentValue = values.get(currentKey);

      int left = 2 * i + 1;
      if (left < values.size()) {
        KeyType leftKey = keys.get(left);
        ValueType leftValue = values.get(leftKey);
        if (currentValue.compareTo(leftValue) > 0) {
          return false;
        }
      }

      int right = 2 * i + 2;
      if (right < values.size()) {
        KeyType rightKey = keys.get(right);
        ValueType rightValue = values.get(rightKey);
        if (currentValue.compareTo(rightValue) > 0) {
          return false;
        }
      }
    }

    return true;
  }

  public void checkRep() {
    Preconditions.checkState(values.size() == keys.size());
    Preconditions.checkArgument(values.size() == valueToPostion.size());
    for (int i = 0; i < keys.size(); i++) {
      KeyType key = keys.get(i);
      Preconditions.checkState(valueToPostion.get(key) == i);
      Preconditions.checkState(values.containsKey(key));
    }
  }

  public int size() {
    return values.size();
  }

  public Optional<ValueType> getValue(KeyType key) {
    if (!values.containsKey(key)) {
      return Optional.empty();
    } else {
      return Optional.of(values.get(key));
    }
  }

  void percolateUp(int index) {
    Preconditions.checkArgument(0 <= index && index < keys.size());
    KeyType currentKey = keys.get(index);
    ValueType currentValue = values.get(currentKey);

    while (index > 0) {
      int parent = (index - 1) / 2;
      KeyType parentKey = keys.get(parent);
      ValueType parentValue = values.get(parentKey);
      if (parentValue.compareTo(currentValue) > 0) {
        swap(index, parent);
      }
      index = parent;
    }
  }

  void swap(int index0, int index1) {
    Preconditions.checkArgument(0 <= index0 && index0 < keys.size());
    Preconditions.checkArgument(0 <= index1 && index1 < keys.size());
    if (index0 == index1) {
      return;
    }
    KeyType key0 = keys.get(index0);
    KeyType key1 = keys.get(index1);
    valueToPostion.put(key0, index1);
    valueToPostion.put(key1, index1);
    keys.set(index0, key1);
    keys.set(index1, key0);
  }
}
