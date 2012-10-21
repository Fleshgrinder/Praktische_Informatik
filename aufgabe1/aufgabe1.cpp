/** Exercise 1

    @author Richard Fussenegger <richard@fussenegger.info>
    @docdate 21.10.2012
 */
#include <stdio.h>
#include "merge_lists.cpp"

/** Iterate over given list and print content.

    @param list
    The list to iterate over.
 */
void iterate(intlist list) {
  for (intlist::const_iterator begin = list.begin(), end = list.end(); begin != end; ++begin) {
    printf(" %d", *begin);
  }
  printf("\n");
}

/** Main function.

    @return Zero if no error occurred.
 */
int main() {
  // Create three lists for testing.
  intlist list1;
  intlist list2;
  intlist list3;

  // Create a list to collect the others.
  intlist lists[3];

  // Fill the test lists with some values.
  for (unsigned int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
      list1.push_front(i);
    }
    else if (i % 3 == 0) {
      list2.push_front(i);
    }
    else {
      list3.push_front(i);
    }
  }

  // Put the individual lists together for easy iteration.
  lists[0] = list1;
  lists[1] = list2;
  lists[2] = list3;

  // Print the lists which we're going to sort.
  printf("Lists to sort:\n");
  for (unsigned int i = 0; i < 3; i++) {
    printf("List %d:", i + 1);
    iterate(lists[i]);
  }

  // Sort the lists and print the sorted result.
  intlist result = merge_lists(lists, 3);
  printf("\nSorted result:");
  iterate(result);

  // We're done, exit.
  return 0;
}
