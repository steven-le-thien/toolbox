#include "fib_heap.hpp"

#include <limits>
#include <iostream>

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


  // std::cout << "Second problem, inserting a sorted array of 64" << std::endl;
  // advanced_algo::FibHeap *problem_two = new advanced_algo::FibHeap;
  // for(int i = 0; i < 64; i++){
  //   std::cout << "Number of trees at " << (i) << " is " << problem_two->roots_.size() << std::endl;
  //   problem_two->advanced_algo::FibHeap::insert((63 - i) * 100, (63 - i) * 100);
  //   if(i > 2) 
  //     problem_two->advanced_algo::FibHeap::decrease_key((63 - 2) * 100, (63 - 2) * 100 - i - 1);
  // }
  // std::cout << "Number of trees " << problem_two->roots_.size() << std::endl;

  // auto it = problem_two->roots_.begin();

  // advanced_algo::HeapNode *traversal_node = *(it);
  // int height = 0;
  // while(auto child = traversal_node->advanced_algo::HeapNode::get_left_child()){
  //   height++;
  //   traversal_node = traversal_node->advanced_algo::HeapNode::get_left_child();
  //   std::cout << "Is sole child: " << (child->advanced_algo::HeapNode::get_left_sibling() == child->advanced_algo::HeapNode::get_right_sibling()) << std::endl;
  // }
  // std::cout << "Height of the first tree is " << height << std::endl;
  // it++;

  // *traversal_node = *(it);
  // int height = 0;
  // while(auto child = traversal_node->advanced_algo::HeapNode::get_left_child()){
  //   height++;
  //   traversal_node = traversal_node->advanced_algo::HeapNode::get_left_child();
  //   std::cout << "Is sole child: " << (child->advanced_algo::HeapNode::get_left_sibling() == child->advanced_algo::HeapNode::get_right_sibling()) << std::endl;
  // }
  // std::cout << "Height of the first tree is " << height << std::endl;

  return 0;
}
