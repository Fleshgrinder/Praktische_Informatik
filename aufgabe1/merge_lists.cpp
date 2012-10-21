#include <list>

typedef std::list<unsigned int> intlist;

intlist merge_lists(intlist lists[], unsigned int k) {
  intlist merged;

  do {
    // List index with largest element.
    int m = -1;

    for (unsigned int i = 0; i < k; i++) {
      // Skip list if already empty!
      if (lists[i].empty()) {
        continue;
      }

      // First list we see...
      if (m < 0) {
        m = i;
      }
      // Check first list element of subsequent list.
      else if (lists[i].front() > lists[m].front()) {
        m = i;
      }
    }

    // All lists were empty, done.
    if (m < 0) {
      break;
    }

    // Append largest element to results.
    merged.push_back(lists[m].front());

    // Remove largest element from list.
    lists[m].pop_front();
  } while (true);

  return merged;
}
