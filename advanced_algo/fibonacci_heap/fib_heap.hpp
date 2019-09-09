#ifndef FIB_HEAP_H_
#define FIB_HEAP_H_

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace advanced_algo  {

// HeapNodes 
class HeapNode {
 public:
  // Constructors
  HeapNode() = default;
  HeapNode(int val) : HeapNode() {val_ = val;}
  HeapNode(const HeapNode& other) = default;

  // Destructor
  ~HeapNode();

  // Getters and setters
  HeapNode* get_parent() {return parent_;}
  HeapNode* get_left_child() {return left_child_;} // the first child added
  HeapNode* get_right_sibling() {return right_sibling_;}
  HeapNode* get_left_sibling() {return left_sibling_;}
  int get_val() {return val_;}
  int get_deg() {return deg_;}
  bool is_mark() {return mark_;}

  void set_parent(HeapNode *node) {parent_ = node;}
  void set_left_child(HeapNode *node) {left_child_ = node;}
  void set_left_sibling(HeapNode *node) {left_sibling_ = node;}
  void set_right_sibling(HeapNode *node) {right_sibling_ = node;}
  void set_val(int val) {val_ = val;}
  void set_deg(int deg) {deg_ = deg;}
  void set_mark(bool mark) {mark_ = mark;}

  void inc_deg() {this->set_deg(this->get_deg() + 1);}
  void dec_deg() {this->set_deg(this->get_deg() - 1);}

  // Other functions
  void add_child(HeapNode *child);
  void cut_child();

 private:
  HeapNode *parent_;
  HeapNode *left_child_;
  HeapNode *left_sibling_;
  HeapNode *right_sibling_;
  int val_;
  int deg_;
  bool mark_;
}; // class HeapNode

// Fibonacci heap implementation
class FibHeap {
 public:
  // Constructor
  FibHeap(); 
  FibHeap(const FibHeap& other) = default;

  // Destructor
  ~FibHeap();

  // Heap functions
  void insert(int key, int val);
  int find_min(); // this returns the key and not the value
  void delete_min();
  void decrease_key(int key, int nval);

 // private:
  int min_val_;
  HeapNode *min_pointer_;

  std::unordered_set<HeapNode*> roots_;
  std::vector<std::unordered_set<HeapNode*>> buckets_;

  // Only purpose of this is to work directly with HeapNodes and not with keys
  std::unordered_map<int,HeapNode*> kv_map_;
  // Only purpose of this to return a key for find_min
  std::unordered_map<HeapNode*,int> vk_map_;

  // Private functions
  void make_root_(HeapNode * node);
  void cascading_cut_(HeapNode *node);
  void add_to_bucket_(HeapNode *node);
  void consolidate_bucket_(int deg);
  void remove_node_(HeapNode *node);

  // Private helper functions
  bool is_empty_() {return (kv_map_.size() == 0);}

  int get_key_from_vk_map_(HeapNode *node) {return vk_map_.find(node)->second;}
  HeapNode* get_key_from_kv_map_(int key) {return kv_map_.find(key)->second;}

  void remove_node_from_bucket_(HeapNode *node) 
      {buckets_[node->HeapNode::get_deg()].erase(node);}
  void remove_node_from_roots_(HeapNode *node) {roots_.erase(node);}

  void recalibrate_min_(); // log(N) recalibration
  void update_min_(HeapNode *node); // O(1) update
}; // class FibHeap
} // namespace 6.854

#endif //FIB_HEAP_H_
