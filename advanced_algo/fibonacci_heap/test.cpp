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
  std::cout << "    Size of root is " 
      << my_fibonacci_heap->roots_.size() << std::endl;
  std::cout << "    Bucket size is " 
      << my_fibonacci_heap->buckets_.size() << std::endl;
  std::cout << "    First bucket size is " 
      << my_fibonacci_heap->buckets_[0].size() << std::endl;

  // Second insert
  my_fibonacci_heap->advanced_algo::FibHeap::insert(112, 9);
  std::cout << "Inserting {k = 112, v = 9}" << std::endl;
  std::cout << "    Key with min val is " << 
      my_fibonacci_heap->advanced_algo::FibHeap::find_min() << std::endl;
  std::cout << "    Size of root is " 
      << my_fibonacci_heap->roots_.size() << std::endl;
  std::cout << "    Bucket size is " 
      << my_fibonacci_heap->buckets_.size() << std::endl;
  std::cout << "    First bucket size is " 
      << my_fibonacci_heap->buckets_[0].size() << std::endl;
  std::cout << "    Second bucket size is " 
      << my_fibonacci_heap->buckets_[1].size() << std::endl;

  // Delete min
  my_fibonacci_heap->advanced_algo::FibHeap::delete_min();
  std::cout << "Deleting min" << std::endl;
  std::cout << "    Key with min val is " << 
      my_fibonacci_heap->advanced_algo::FibHeap::find_min() << std::endl;
  std::cout << "    Size of root is " 
      << my_fibonacci_heap->roots_.size() << std::endl;
  std::cout << "    Bucket size is " 
      << my_fibonacci_heap->buckets_.size() << std::endl;
  std::cout << "    First bucket size is " 
      << my_fibonacci_heap->buckets_[0].size() << std::endl;
  std::cout << "    Second bucket size is " 
      << my_fibonacci_heap->buckets_[1].size() << std::endl;

  return 0;
}
