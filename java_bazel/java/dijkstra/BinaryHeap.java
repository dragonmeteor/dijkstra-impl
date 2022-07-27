package dijkstra;

import com.google.common.base.Preconditions;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Optional;

public class BinaryHeap<KeyType, ValueType extends Comparable<ValueType>> {
  private final HashMap<KeyType, ValueType> values = new HashMap<>();
  private final HashMap<KeyType, Integer> valueToPostion = new HashMap<>();
  private final ArrayList<KeyType> keyArray = new ArrayList<>();

  public BinaryHeap() {
    // NO-OP
  }

  void addRaw(KeyType key, ValueType value) {
    Preconditions.checkArgument(!values.containsKey(key), String.format("Key '%s' already exists", key));
    values.put(key, value);
    keyArray.add(key);
    valueToPostion.put(key, keyArray.size() - 1);
  }

  public boolean isHeapOrder() {
    for (int i = 0; i < values.size() / 2; i++) {
      KeyType currentKey = keyArray.get(i);
      ValueType currentValue = values.get(currentKey);

      int left = 2 * i + 1;
      if (left < values.size()) {
        KeyType leftKey = keyArray.get(left);
        ValueType leftValue = values.get(leftKey);
        if (currentValue.compareTo(leftValue) > 0) {
          return false;
        }
      }

      int right = 2 * i + 2;
      if (right < values.size()) {
        KeyType rightKey = keyArray.get(right);
        ValueType rightValue = values.get(rightKey);
        if (currentValue.compareTo(rightValue) > 0) {
          return false;
        }
      }
    }

    return true;
  }

  public void checkRep() {
    Preconditions.checkState(values.size() == keyArray.size());
    Preconditions.checkArgument(values.size() == valueToPostion.size());
    for (int i = 0; i < keyArray.size(); i++) {
      KeyType key = keyArray.get(i);
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
}
