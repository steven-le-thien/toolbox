#include "fib_heap.hpp"

#include <limits>
#include <iostream>

// Make the private fields of FibHeap public to use this test unit
int main(){
  advanced_algo::FibHeap *my_fibonacci_heap = new advanced_algo::FibHeap; 

  // First insert
  my_fibonacci_heap->advanced_algo::FibHeap::insert(199, 90);
  std::cout << "Inserting {k = 199, v = 90}" << std::endl;
  std::cout << "    Key with min val is " << 
      my_fibonacci_heap->advanced_algo::FibHeap::find_min() << std::endl;

  // Second insert
  my_fibonacci_heap->advanced_algo::FibHeap::insert(112, 9);
  std::cout << "Inserting {k = 112, v = 9}" << std::endl;
  std::cout << "    Key with min val is " << 
      my_fibonacci_heap->advanced_algo::FibHeap::find_min() << std::endl;

  // Delete min
  my_fibonacci_heap->advanced_algo::FibHeap::delete_min();
  std::cout << "Deleting min" << std::endl;
  std::cout << "    Key with min val is " << 
      my_fibonacci_heap->advanced_algo::FibHeap::find_min() << std::endl;

  // Third insert
  my_fibonacci_heap->advanced_algo::FibHeap::insert(12, 123);
  std::cout << "Inserting {k = 12, v = 123}" << std::endl;
  std::cout << "    Key with min val is " << 
      my_fibonacci_heap->advanced_algo::FibHeap::find_min() << std::endl;

  // Decrease key
  my_fibonacci_heap->advanced_algo::FibHeap::decrease_key(12, 10);
  std::cout << "Decreasing key {k = 12, v = 10}" << std::endl;
  std::cout << "    Key with min val is " << 
      my_fibonacci_heap->advanced_algo::FibHeap::find_min() << std::endl;

  // Delete min
  my_fibonacci_heap->advanced_algo::FibHeap::delete_min();
  std::cout << "Deleting min" << std::endl;
  std::cout << "    Key with min val is " << 
      my_fibonacci_heap->advanced_algo::FibHeap::find_min() << std::endl;

  return 0;
}
