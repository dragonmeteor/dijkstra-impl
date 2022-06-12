#ifndef __BINARY_HEAP_H__
#define __BINARY_HEAP_H__

#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"
#include "absl/types/optional.h"

template <typename ObjectT, typename ValueT>
struct HeapEntry {
  ObjectT object;
  ValueT value;

  HeapEntry(ObjectT object, ValueT value) : object(object), value(value) {
    // NO-OP
  }
};

template <typename ObjectT, typename ValueT>
class BinaryHeap {
 public:
  BinaryHeap() = default;
  BinaryHeap(const BinaryHeap& other) = delete;
  BinaryHeap& operator=(const BinaryHeap& other) = delete;

  int size() const { return entries_.size(); }

  bool empty() const { return entries_.empty(); }

  bool IsHeapOrder() const {
    for (int i = 0; i < entries_.size(); i++) {
      const auto& entry = entries_[i];
      if (i * 2 < entries_.size() && entries_[i * 2].value < entry.value) {
        return false;
      }
      if (i * 2 + 1 < entries_.size() && entries_[i * 2 + 1].value < entry.value) {
        return false;
      }
    }
    return true;
  }

  absl::Status AddRaw(ObjectT object, ValueT value) {
    if (object_position_.find(object) != object_position_.end()) {
      return absl::InvalidArgumentError("Object already exist in heap.");
    }
    entries_.push_back(HeapEntry<ObjectT, ValueT>(object, value));
    object_position_[object] = entries_.size() - 1;
    return absl::OkStatus();
  }

  void Build() {
    for (int i = entries_.size() / 2; i >= 0; i--) {
      PercolateDown(i);
    }
  }

  absl::Status CheckRep() const {
    if (entries_.size() != object_position_.size()) {
      return absl::InternalError("entries_.size() != object_position_.size()");
    }
    for (int i = 0; i < entries_.size(); i++) {
      if (object_position_.find(entries_[i].object) == object_position_.end()) {
        return absl::InternalError(
            absl::StrFormat("object_position_ does not exist for Entry #%d.", i));
      }
      if (object_position_.at(entries_[i].object) != i) {
        return absl::InternalError(
            absl::StrFormat("object_position_ for Entry #%d is not equalt to %d", i, i));
      }
    }
    return absl::OkStatus();
  }

  absl::Status Add(ObjectT object, ValueT value) {
    auto add_raw_result = AddRaw(object, value);
    if (!add_raw_result.ok()) {
      return add_raw_result;
    }
    PercolateUp(entries_.size() - 1);
    return absl::OkStatus();
  }

  absl::optional<HeapEntry<ObjectT, ValueT>> Pop() {
    if (entries_.empty()) {
      return absl::nullopt;
    }
    HeapEntry<ObjectT, ValueT> output = entries_[0];
    Swap(0, entries_.size() - 1);
    entries_.erase(entries_.begin() + (entries_.size() - 1));
    object_position_.erase(object_position_.find(output.object));
    if (!entries_.empty()) {
      PercolateDown(0);
    }
    return output;
  }

  absl::Status ChangeValue(ObjectT object, ValueT value) {
    if (object_position_.find(object) == object_position_.end()) {
      return absl::InvalidArgumentError("Object does not exist in heap");
    }
    int position = object_position_[object];
    ValueT old_value = entries_[position].value;
    entries_[position].value = value;
    if (value < old_value) {
      PercolateUp(position);
    }
    if (value > old_value) {
      PercolateDown(position);
    }
    return absl::OkStatus();
  }

  absl::optional<ValueT> GetValue(ObjectT object) {
    auto it = object_position_.find(object);
    if (it == object_position_.end()) {
      return absl::nullopt;
    }
    return entries_[it->second].value;
  }

 private:
  void PercolateDown(int index) {
    while (index < entries_.size()) {
      int min_index = index;
      if (2 * index < entries_.size() && entries_[2 * index].value < entries_[min_index].value) {
        min_index = 2 * index;
      }
      if (2 * index + 1 < entries_.size() &&
          entries_[2 * index + 1].value < entries_[min_index].value) {
        min_index = 2 * index + 1;
      }
      if (min_index == index) {
        break;
      }
      Swap(index, min_index);
      index = min_index;
    }
  }

  void PercolateUp(int index) {
    while (index > 0) {
      int parent_index = index / 2;
      if (entries_[parent_index].value > entries_[index].value) {
        Swap(parent_index, index);
        index = parent_index;
      } else {
        break;
      }
    }
  }

  void Swap(int a, int b) {
    if (a == b) {
      return;
    }

    object_position_[entries_[a].object] = b;
    object_position_[entries_[b].object] = a;

    HeapEntry<ObjectT, ValueT> temp = entries_[a];
    entries_[a] = entries_[b];
    entries_[b] = temp;
  }

  std::vector<HeapEntry<ObjectT, ValueT>> entries_;
  absl::flat_hash_map<ObjectT, int> object_position_;
};

#endif