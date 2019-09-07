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
  Node *new_node = new Node(val);

  // Put into the heap
  kv_map_.insert({key, new_node});
  vk_map_.insert({new_node, key});

  // O(1) insertion
  FibHeap::make_root_(new_node);

  // Recalibrate min pointer in O(1)
  update_min_(new_node);
}

// Find min is easy since we maintain a min pointer
int FibHeap::find_min(){
  return get_key_from_vk_map_(min_pointer_);
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
  Node *node = (kv_map_.find(key))->second;

  // Update value
  node->Node::set_val(nval);

  // Perform a cascading cut at this node in amortized O(1)
  FibHeap::cascading_cut_(node);
}


// Internal helper functions

/* Take input a hanging tree (from cutting or inserting or delete_min), 
 * register as roots and uopdate bucket
 */
void FibHeap::make_root_(Node *node){
  roots_.insert(node);
  add_to_bucket_(node); // amortized O(1)
}

/* Perform a cascading cut to make sure that each node loses as most 2 children
 *    to maintain degree guarantee.
 */
void FibHeap::cascading_cut_(Node *child){
  Node *parent = child->Node::get_parent();

  child->Node::cut_child(); // actually cutting the child, manipulating pointers
  FibHeap::make_root_(child);
  child->Node::set_mark(false);

  if(parent->Node::is_mark()){ // has the parent loses a child before?
    FibHeap::cascading_cut_(parent);
  } else {
    parent->Node::set_mark(true);
  }
}

/* Maintaining a bucket indexed into the degree of trees in the root set. 
 * This is to make sure that roots with degree d has 2^d descendants, which
 *    is essential in degree guarantee.
 * A node is added to the bucket according to its degree and consolidated
 */
void FibHeap::add_to_bucket_(Node * node){
  int destination_deg = node->Node::get_deg();

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
    Node *parent, *child;

    // Get 2 arbitrary elements in the bucket
    auto it = buckets_[deg].begin();
    Node *first_tree = *it;
    it++;
    Node *second_tree = *it;

    // Compete
    if(first_tree->Node::get_val() < second_tree->Node::get_val()){
      parent = first_tree; 
      child = second_tree;
    } else {
      parent = second_tree;
      child = first_tree;
    }

    // Log changes
    remove_node_from_bucket_(child);
    remove_node_from_bucket_(parent);
    remove_node_from_roots_(child);

    parent->Node::add_child(child);

    add_to_bucket_(parent); //cascade if necessary
  }
}

// Straightfoward linear scan at the roots, when min pointer is no longer valid
void FibHeap::recalibrate_min_(){
  min_val_ = std::numeric_limits<int>::max();
  for(Node *candidate : roots_){
    int candidate_val = candidate->Node::get_val();
    if(min_val_ > candidate_val) {
      min_val_ = candidate_val;
      min_pointer_ = candidate;
    }
  }
}

// Fast O(1) comparison with min pointer
void FibHeap::update_min_(Node *node){
  int val = node->Node::get_val();
  if(min_val_ > val) {
    min_pointer_ = node;
    min_val_ = val;
  }
}

// Remove a node from the graph completely (eg. from delete_min)
void FibHeap::remove_node_(Node *node){
  remove_node_from_roots_(node);
  remove_node_from_bucket_(node);

  kv_map_.erase(get_key_from_vk_map_(node));
  vk_map_.erase(node);


  // Destroyed nodes are always at the top so parents and sibling 
  //    must be NULL 
  Node *left_child = node->Node::get_left_child();
  if(left_child != NULL){
    Node *current_child = left_child;
    while(current_child->Node::get_parent() != NULL){
      FibHeap::make_root_(current_child);

      current_child->Node::set_parent(NULL);
      current_child->Node::set_left_sibling(NULL);
      current_child->Node::set_right_sibling(NULL);
    }
  }

  free(node);
}

// Make a node a child of another node, more pointers manipuations
void Node::add_child(Node *child){
  Node *current_left_child = get_left_child();

  if(current_left_child == NULL){
    this->Node::set_left_child(child);
    child->Node::set_right_sibling(child);
    child->Node::set_left_child(child);
  } else {
    Node *current_second_to_left_child = 
        current_left_child->Node::get_right_sibling();
    current_left_child->Node::set_right_sibling(child);
    child->Node::set_right_sibling(current_second_to_left_child); 
    child->Node::set_left_sibling(current_left_child);
  }
  child->Node::set_parent(this);

  this->Node::inc_deg();
}


// Make a node from another node, more pointers manipuations
void Node::cut_child(){
  Node *parent = this->Node::get_parent();
  Node *right_sibling = this->Node::get_right_sibling();
  Node *left_sibling = this->Node::get_left_sibling();

  this->Node::set_parent(NULL);
  this->Node::set_right_sibling(NULL);

  if(left_sibling == this){ // the parent has only 1 child
    parent->Node::set_left_child(NULL);
  } else {
    if(parent->Node::get_left_child() == this)
      parent->Node::set_left_child(left_sibling);

    right_sibling->Node::set_left_sibling(left_sibling);
    left_sibling->Node::set_right_sibling(right_sibling);
  }

  parent->Node::dec_deg(); 
}
} // namespace advanced_algo

