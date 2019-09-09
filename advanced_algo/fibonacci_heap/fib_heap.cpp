#include "fib_heap.hpp"

#include <limits>

#include <iostream>

// Internal functions for easy implementation

namespace advanced_algo {
FibHeap::FibHeap(){
  min_val_ = std::numeric_limits<int>::max();
}

FibHeap::~FibHeap(){
  while(!is_empty_()){
    delete_min();
  }
}

// Insert is done lazily in O(1) by just adding a singleton tree to the forest
void FibHeap::insert(int key, int val){
  // Wrap value around a new node
  HeapNode *new_node = new HeapNode(val);

  // Put into the heap
  kv_map_.insert({key, new_node});
  vk_map_.insert({new_node, key});

  // O(1) insertion
  FibHeap::make_root_(new_node);

  // Recalibrate min pointer in O(1)
  FibHeap::update_min_(new_node);
}

// Find min is easy since we maintain a min pointer
int FibHeap::find_min(){
  return FibHeap::get_key_from_vk_map_(min_pointer_);
}

/* Delete min is also easy since we maintain a min pointer
 * This removes the min pointer and make all of its children roots; then 
 *    recalibrate min. Since it is guaratee that node degree is O(logn)
 *    this step runs in amortized O(logn)
 */
void FibHeap::delete_min(){
  FibHeap::remove_node_(min_pointer_);
  FibHeap::recalibrate_min_();
}

/* Decrease key is done lazily by cutting off the child to maintain heap order
 * To maintain degree guarantee, we make sure that if a node loses a second 
 *    child then we also cut that node, thus cascading upwards the tree
 */
void FibHeap::decrease_key(int key, int nval){
  HeapNode *node = (kv_map_.find(key))->second;

  // Update value
  node->HeapNode::set_val(nval);

  // Perform a cascading cut at this node in amortized O(1)
  FibHeap::cascading_cut_(node);
}


// Internal helper functions

/* Take input a hanging tree (from cutting or inserting or delete_min), 
 * register as roots and uopdate bucket
 */
void FibHeap::make_root_(HeapNode *node){
  roots_.insert(node);
  FibHeap::add_to_bucket_(node); // amortized O(1)
}

/* Perform a cascading cut to make sure that each node loses as most 2 children
 *    to maintain degree guarantee.
 */
void FibHeap::cascading_cut_(HeapNode *child){
  HeapNode *parent = child->HeapNode::get_parent();

  child->HeapNode::cut_child(); //pointer manipulations
  FibHeap::make_root_(child);
  child->HeapNode::set_mark(false);

  FibHeap::update_min_(child);

  if(parent->HeapNode::is_mark()){ // has the parent loses a child before?
    FibHeap::cascading_cut_(parent);
  } else {
    parent->HeapNode::set_mark(true);
  }
}

/* Maintaining a bucket indexed into the degree of trees in the root set. 
 * This is to make sure that roots with degree d has 2^d descendants, which
 *    is essential in degree guarantee.
 * A node is added to the bucket according to its degree and consolidated
 */
void FibHeap::add_to_bucket_(HeapNode *node){
  int destination_deg = node->HeapNode::get_deg();

  if(destination_deg >= buckets_.size()) 
    buckets_.resize(destination_deg + 1);

  buckets_[destination_deg].insert(node);
  FibHeap::consolidate_bucket_(destination_deg);
}

/* Consolidate buckets make sure that there are no more than 2 trees in the same
 * bucket at any time. This is the same idea as union by rank in DSU and is used
 * to show degree guarantee. If there are more than 2 trees in the same bucket, 
 * we take arbitrarily 2 trees and make one a subtree of the order wrt to heap 
 * order.
 */
void FibHeap::consolidate_bucket_(int deg){
  while(buckets_[deg].size() > 1) {
    HeapNode *parent, *child;

    // Get 2 arbitrary elements in the bucket
    auto it = buckets_[deg].begin();
    HeapNode *first_tree = *it;
    it++;
    HeapNode *second_tree = *it;

    // Compete
    if(first_tree->HeapNode::get_val() < second_tree->HeapNode::get_val()){
      parent = first_tree; 
      child = second_tree;
    } else {
      parent = second_tree;
      child = first_tree;
    }

    // Log changes
    FibHeap::remove_node_from_bucket_(child);
    FibHeap::remove_node_from_bucket_(parent);
    FibHeap::remove_node_from_roots_(child);

    parent->HeapNode::add_child(child);

    FibHeap::add_to_bucket_(parent); //cascade if necessary
  }
}

// Straightfoward linear scan at the roots, when min pointer is no longer valid
void FibHeap::recalibrate_min_(){
  min_val_ = std::numeric_limits<int>::max();
  for(HeapNode *candidate : roots_){
    int candidate_val = candidate->HeapNode::get_val();
    if(min_val_ > candidate_val) {
      min_val_ = candidate_val;
      min_pointer_ = candidate;
    }
  }
}

// Fast O(1) comparison with min pointer
void FibHeap::update_min_(HeapNode *node){
  int val = node->HeapNode::get_val();
  if(min_val_ > val) {
    min_pointer_ = node;
    min_val_ = val;
  }
}

// Remove a node from the graph completely (eg. from delete_min)
void FibHeap::remove_node_(HeapNode *node){
  FibHeap::remove_node_from_roots_(node);
  FibHeap::remove_node_from_bucket_(node);

  kv_map_.erase(get_key_from_vk_map_(node));
  vk_map_.erase(node);

  // Destroyed nodes are always at the top so parents and sibling 
  //    must be NULL 
  HeapNode *left_child = node->HeapNode::get_left_child();

  if(left_child != NULL){
    HeapNode *current_child = left_child;
    while(current_child->HeapNode::get_parent() != NULL){
      FibHeap::make_root_(current_child);

      current_child->HeapNode::set_parent(NULL);
      current_child->HeapNode::set_left_sibling(NULL);
      current_child->HeapNode::set_right_sibling(NULL);
    }
  }

  free(node);
}

// Make a node a child of another node, more pointers manipuations
void HeapNode::add_child(HeapNode *child){
  HeapNode *current_left_child = get_left_child();

  if(current_left_child == NULL){

    this->HeapNode::set_left_child(child);
    child->HeapNode::set_right_sibling(child);
    child->HeapNode::set_left_sibling(child);
  } else {
    HeapNode *current_second_to_left_child = 
        current_left_child->HeapNode::get_right_sibling();
    current_left_child->HeapNode::set_right_sibling(child);
    child->HeapNode::set_right_sibling(current_second_to_left_child); 
    child->HeapNode::set_left_sibling(current_left_child);
  }
  child->HeapNode::set_parent(this);

  HeapNode::inc_deg();
}


// Make a node from another node, more pointers manipuations
void HeapNode::cut_child(){
  HeapNode *parent = HeapNode::get_parent();
 
  if(parent == NULL) // at the root
    return;

  HeapNode *right_sibling = HeapNode::get_right_sibling();
  HeapNode *left_sibling = HeapNode::get_left_sibling();

  HeapNode::set_parent(NULL);
  HeapNode::set_right_sibling(NULL);
  HeapNode::set_left_sibling(NULL);

  if(left_sibling == this){ // the parent has only 1 child
    parent->HeapNode::set_left_child(NULL);
  } else {
    if(parent->HeapNode::get_left_child() == this)
      parent->HeapNode::set_left_child(left_sibling);

    right_sibling->HeapNode::set_left_sibling(left_sibling);
    left_sibling->HeapNode::set_right_sibling(right_sibling);
  }

  parent->HeapNode::dec_deg(); 
}
} // namespace advanced_algo

