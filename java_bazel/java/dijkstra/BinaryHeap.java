package dijkstra;

import com.google.common.base.Preconditions;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Optional;

public class BinaryHeap<KeyType, ValueType extends Comparable<ValueType>> {
  private final HashMap<KeyType, ValueType> values = new HashMap<>();
  private final HashMap<KeyType, Integer> keyToPosition = new HashMap<>();
  private final ArrayList<KeyType> keys = new ArrayList<>();

  public BinaryHeap() {
    // NO-OP
  }

  public boolean isEmpty() {
    return keys.isEmpty();
  }

  void addRaw(KeyType key, ValueType value) {
    Preconditions.checkArgument(!values.containsKey(key), String.format("Key '%s' already exists", key));
    values.put(key, value);
    keys.add(key);
    keyToPosition.put(key, keys.size() - 1);
  }

  public boolean isHeapOrder() {
    for (int i = 0; i < values.size() / 2; i++) {
      ValueType currentValue = getValueAt(i);

      int left = 2 * i + 1;
      if (left < values.size()) {
        ValueType leftValue = getValueAt(left);
        if (currentValue.compareTo(leftValue) > 0) {
          return false;
        }
      }

      int right = 2 * i + 2;
      if (right < values.size()) {
        ValueType rightValue = getValueAt(right);
        if (currentValue.compareTo(rightValue) > 0) {
          return false;
        }
      }
    }

    return true;
  }

  public void checkRep() {
    Preconditions.checkState(values.size() == keys.size());
    Preconditions.checkArgument(values.size() == keyToPosition.size());
    for (int i = 0; i < keys.size(); i++) {
      KeyType key = keys.get(i);
      Preconditions.checkState(keyToPosition.get(key) == i);
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

  private ValueType getValueAt(int index) {
    Preconditions.checkArgument(0 <= index && index < keys.size());
    KeyType key = keys.get(index);
    return values.get(key);
  }

  private void percolateUp(int index) {
    Preconditions.checkArgument(0 <= index && index < keys.size());
    KeyType currentKey = keys.get(index);
    ValueType currentValue = values.get(currentKey);

    while (index > 0) {
      int parent = (index - 1) / 2;
      ValueType parentValue = getValueAt(parent);
      if (parentValue.compareTo(currentValue) > 0) {
        swap(index, parent);
      }
      index = parent;
    }
  }

  private void percolateDown(int index) {
    Preconditions.checkArgument(0 <= index && index < keys.size());
    while (index < keys.size() / 2) {
      int minIndex = index;

      int leftIndex = 2 * index + 1;
      if (leftIndex < keys.size()) {
        ValueType candidateValue = getValueAt(leftIndex);
        ValueType currentMinValue = getValueAt(minIndex);
        if (candidateValue.compareTo(currentMinValue) < 0) {
          minIndex = leftIndex;
        }
      }

      int rightIndex = 2 * index + 2;
      if (rightIndex < keys.size()) {
        ValueType candidateValue = getValueAt(rightIndex);
        ValueType currentMinValue = getValueAt(minIndex);
        if (candidateValue.compareTo(currentMinValue) < 0) {
          minIndex = rightIndex;
        }
      }

      if (minIndex != index) {
        swap(index, minIndex);
        index = minIndex;
      } else {
        break;
      }
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
    keyToPosition.put(key0, index1);
    keyToPosition.put(key1, index0);
    keys.set(index0, key1);
    keys.set(index1, key0);
  }

  public void build() {
    for (int i = keys.size() / 2; i >= 0; i--) {
      percolateDown(i);
    }
  }

  public void changeValue(KeyType key, ValueType newValue) {
    Preconditions.checkArgument(values.containsKey(key));
    ValueType oldValue = values.get(key);
    values.put(key, newValue);
    int position = keyToPosition.get(key);
    if (oldValue.compareTo(newValue) < 0) {
      percolateDown(position);
    } else {
      percolateUp(position);
    }
  }

  public Optional<KeyType> deleteMin() {
    if (keys.isEmpty()) {
      return Optional.empty();
    }
    KeyType output = keys.get(0);
    swap(0, keys.size() - 1);
    keys.remove(keys.size() - 1);
    keyToPosition.remove(output);
    values.remove(output);
    if (!values.isEmpty()) {
      percolateDown(0);
    }
    return Optional.of(output);
  }

  public void add(KeyType key, ValueType value) {
    Preconditions.checkArgument(!values.containsKey(key));
    addRaw(key, value);
    percolateUp(keys.size() - 1);
  }
}
