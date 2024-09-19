#include <cstddef>
#include <iostream>
namespace s21 {
template <typename T, typename D>
class Tree {
  friend class IteratorTree;

 public:
  using data_type = D;
  using data_reference = D&;
  using data_const_reference = const D&;
  using key_type = T;
  using key_reference = T&;
  using key_const_reference = const T&;
  using size_type = size_t;

  enum Color { Red, Black };

 private:
  struct node {
    node* parent;
    node* left;
    node* right;
    key_type key;    //   &???
    data_type data;  //  &???
    Color leaf_color;
  };

  size_type size_tree;
  node* root;
  node* Nil;

 public:
  void NilInit() {
    Nil = new node;
    Nil->key = -1;
    Nil->left = Nil;
    Nil->right = Nil;
    Nil->leaf_color = Black;
  }

  Tree() {
    NilInit();
    root = Nil;
    root->parent = Nil;
    this->size_tree = 0;
  }

  node* getnil() { return Nil; }
  node* getRoot() { return root; }
  node* find_space(key_const_reference value) {
    node* finder = root;
    node* new_leaf = nullptr;
    while (!new_leaf) {
      if (finder->key >= value && finder->left != Nil)
        finder = finder->left;
      else if (finder->key >= value && finder->left == Nil) {
        new_leaf = new node;
        finder->left = new_leaf;
        new_leaf->parent = finder;
      } else if (finder->key < value && finder->right != Nil)
        finder = finder->right;
      else if (finder->key < value && finder->right == Nil) {
        new_leaf = new node;
        finder->right = new_leaf;
        new_leaf->parent = finder;
      }
    }

    return new_leaf;
  }
  bool empty() { return !size_tree; }
  void PrintTree() {
    if (root != nullptr && root != Nil) {
      std::cout << "---------------\n";
      printnodeWithCenterRoot(this->root, 0);
      std::cout << "---------------\n";
    }
  }
  void printnodeWithCenterRoot(node* leaf, int level) {
    if (leaf != Nil) {
      printnodeWithCenterRoot(leaf->right, level + 1);
      std::string indentation(level * 4, ' ');
      std::cout << indentation << leaf->key << std::endl;
      printnodeWithCenterRoot(leaf->left, level + 1);
    }
  }
  void PrintTreeMap() {
    if (root != nullptr && root != Nil) {
      std::cout << "---------------\n";
      printnodeWithCenterRootMap(this->root, 0);
      std::cout << "---------------\n";
    }
  }
  void printnodeWithCenterRootMap(node* leaf, int level) {
    if (leaf != Nil) {
      printnodeWithCenterRootMap(leaf->right, level + 1);
      std::string indentation(level * 4, ' ');
      std::cout << indentation << leaf->key << '-' << leaf->data << std::endl;
      printnodeWithCenterRootMap(leaf->left, level + 1);
    }
  }
  size_type size() { return size_tree; }
  Tree(std::initializer_list<key_type> const& items) {
    NilInit();
    this->root = Nil;
    this->size_tree = 0;
    for (auto& item : items) insert(item);
  };

  void fixInsert(node* leaf) {
    while (leaf != root && parent(leaf)->leaf_color == Red) {
      if (parent(leaf) == grandparent(leaf)->left) {
        node* y = grandparent(leaf)->right;
        if (y->leaf_color == Red) {
          parent(leaf)->leaf_color = Black;
          y->leaf_color = Black;
          grandparent(leaf)->leaf_color = Red;
          leaf = grandparent(leaf);
        } else {
          if (leaf == parent(leaf)->right) {
            leaf = parent(leaf);
            rotateLeft(leaf);
          }
          parent(leaf)->leaf_color = Black;
          grandparent(leaf)->leaf_color = Red;
          rotateRight(grandparent(leaf));
        }
      } else {
        node* y = grandparent(leaf)->left;
        if (y->leaf_color == Red) {
          parent(leaf)->leaf_color = Black;
          y->leaf_color = Black;
          grandparent(leaf)->leaf_color = Red;
          leaf = grandparent(leaf);
        } else {
          if (leaf == parent(leaf)->left) {
            leaf = parent(leaf);
            rotateRight(leaf);
          }
          parent(leaf)->leaf_color = Black;
          grandparent(leaf)->leaf_color = Red;
          rotateLeft(grandparent(leaf));
        }
      }
    }
    root->leaf_color = Black;
  }

  node* grandparent(node* leaf) {
    node* grandparent = Nil;
    if (leaf != Nil && leaf->parent != Nil) {
      grandparent = leaf->parent->parent;
    }
    return grandparent;
  }

  node* parent(node* leaf) {
    node* parent = Nil;
    if (leaf != Nil && leaf->parent != Nil) {
      parent = leaf->parent;
    }
    return parent;
  }

  void rotateLeft(node* leaf) {
    node* pivot = leaf->right;
    pivot->parent = leaf->parent;
    if (leaf->parent != Nil) {
      if (leaf->parent->left == leaf)
        leaf->parent->left = pivot;
      else
        leaf->parent->right = pivot;
    } else
      root = pivot;
    leaf->right = pivot->left;
    if (pivot->left != Nil) pivot->left->parent = leaf;
    leaf->parent = pivot;
    pivot->left = leaf;
  }

  void rotateRight(node* leaf) {
    node* pivot = leaf->left;
    pivot->parent = leaf->parent;
    if (leaf->parent != Nil) {
      if (leaf->parent->left == leaf)
        leaf->parent->left = pivot;
      else
        leaf->parent->right = pivot;
    } else
      root = pivot;
    leaf->left = pivot->right;
    if (pivot->left != Nil) pivot->right->parent = leaf;
    leaf->parent = pivot;
    pivot->right = leaf;
  }

  key_type getKey(node* leaf) const { return leaf->key; }

  data_type getData(node* leaf) const { return leaf->data; }

  node* getNil() { return Nil; }
  const node* getNil() const { return Nil; }

  node* find(key_const_reference key, node* leaf) {
    node* current = leaf;
    while (current != Nil) {
      if (key == getKey(current)) {
        return current;
      } else if (key < getKey(current)) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return Nil;
  }
  node* find(key_const_reference key) { return find(key, root); }
  void printAllAbout(node* leaf) {
    std::cout << '\n';
    if (leaf)
      std::cout << '\n'
                << "addr leaf " << leaf << " key= " << leaf->key
                << " color =" << leaf->leaf_color;
    else
      throw std::out_of_range("leaf - nullptr?");
    if (leaf->left)
      std::cout << '\n'
                << "addr leaf->left = " << leaf->left
                << " key=" << leaf->left->key
                << " color =" << leaf->left->leaf_color;
    else
      throw std::out_of_range("leaf->left - nullptr?");
    if (leaf->right)
      std::cout << '\n'
                << "addr leaf->right = " << leaf->right
                << " key=" << leaf->right->key
                << " color =" << leaf->right->leaf_color;
    else
      throw std::out_of_range("leaf->right - nullptr?");
    if (leaf->parent)
      std::cout << '\n'
                << "addr leaf->parent = " << leaf->parent
                << " key=" << leaf->parent->key
                << " color =" << leaf->parent->leaf_color;
    else
      throw std::out_of_range("leaf->parent - nullptr?");
    if (leaf)
      std::cout << '\n'
                << "addr Nil " << Nil << " key= " << Nil->key
                << " color =" << Nil->leaf_color;
    else
      throw std::out_of_range("Nil - nullptr?");
    std::cout << '\n';
  }
  void remove(key_const_reference key) { remove(key, root); }
  void remove(key_const_reference key, node* leaf) {
    node* delete_node = find(key, leaf);
    if (delete_node == Nil) return;

    if (delete_node->left == Nil && delete_node->right == Nil) {
      if (delete_node == root) {
        root = Nil;
        Nil->parent = Nil;
      } else if (delete_node == delete_node->parent->left) {
        delete_node->parent->left = Nil;
      } else {
        delete_node->parent->right = Nil;
      }
      delete delete_node;
      this->size_tree--;
    } else if ((delete_node->left != Nil && delete_node->right == Nil) ||
               (delete_node->left == Nil && delete_node->right != Nil)) {
      node* child =
          (delete_node->left != Nil) ? delete_node->left : delete_node->right;
      if (delete_node == root) {
        root = child;
      } else if (delete_node == delete_node->parent->left) {
        delete_node->parent->left = child;
      } else {
        delete_node->parent->right = child;
      }
      child->parent = delete_node->parent;
      delete delete_node;
      this->size_tree--;
      if (child->leaf_color == Black) fixDelete(child);

    }
    //два потомка
    else if (delete_node->left != Nil && delete_node->right != Nil) {
      node* successor = maximum(delete_node->left);
      delete_node->key = successor->key;
      delete_node->data = successor->data;
      remove(successor->key, successor);
      if (delete_node->leaf_color == Black) fixDelete(delete_node);
    }
  }

  node* minimum(node* leaf) {
    while (leaf->left != Nil) {
      leaf = leaf->left;
    }
    return leaf;
  }
  node* minium(node* leaf) const {
    if (leaf == Nil) return leaf;
    while (leaf->left != Nil) {
      leaf = leaf->left;
    }
    return leaf;
  }
  node* maximum(node* leaf) {
    while (leaf->right != Nil) {
      leaf = leaf->right;
    }
    return leaf;
  }

  void fixDelete(node* leaf) {
    while (leaf != root && leaf->leaf_color == Black && leaf != Nil &&
           root != Nil) {
      if (leaf == leaf->parent->left) {
        node* adjacent = leaf->parent->right;
        if (adjacent->leaf_color == Red) {
          adjacent->leaf_color = Black;
          leaf->parent->leaf_color = Red;
          rotateLeft(leaf->parent);
          adjacent = leaf->parent->right;
        }
        if (adjacent->left->leaf_color == Black &&
            adjacent->right->leaf_color == Black) {
          adjacent->leaf_color = Red;
          leaf = leaf->parent;
        } else {
          if (adjacent->right->leaf_color == Black) {
            adjacent->left->leaf_color = Black;
            adjacent->leaf_color = Red;
            rotateRight(adjacent);
            adjacent = leaf->parent->right;
          }
          adjacent->leaf_color = leaf->parent->leaf_color;
          leaf->parent->leaf_color = Black;
          adjacent->right->leaf_color = Black;
          rotateLeft(leaf->parent);
          leaf = root;
        }
      } else {
        node* adjacent = leaf->parent->left;
        if (adjacent->leaf_color == Red) {
          adjacent->leaf_color = Black;
          leaf->parent->leaf_color = Red;
          rotateRight(leaf->parent);
          adjacent = leaf->parent->left;
        }
        if (adjacent->right->leaf_color == Black &&
            adjacent->left->leaf_color == Black) {
          adjacent->leaf_color = Red;
          leaf = leaf->parent;
        } else {
          if (adjacent->left->leaf_color == Black) {
            adjacent->right->leaf_color = Black;
            adjacent->leaf_color = Red;
            rotateLeft(adjacent);
            adjacent = leaf->parent->left;
          }
          adjacent->leaf_color = leaf->parent->leaf_color;
          leaf->parent->leaf_color = Black;
          adjacent->left->leaf_color = Black;
          rotateRight(leaf->parent);
          leaf = root;
        }
      }
    }
    leaf->leaf_color = Black;
  }

 public:
  template <bool Const>

  class IteratorTree {
    friend class Tree;
    friend class IteratorTree<!Const>;

    using node_pointer = std::conditional_t<Const, const node*, node*>;

   public:
    IteratorTree(Tree<T, D>* tree, node_pointer ptr) : ptr(ptr), tree(tree){};
    IteratorTree(node_pointer ptr) : ptr(ptr){};

   private:
    Tree<T, D>* tree;
    node_pointer ptr;
    const node* Nil = Nilfind();

   public:
    using key_type = Tree::key_type;
    using key_reference = Tree::key_reference;
    using data_type = Tree::data_type;
    using data_reference = Tree::data_reference;
    key_const_reference operator*() const noexcept { return ptr->key; }
    ~IteratorTree() = default;
    node* getPtr() { return this->ptr; }

    data_type getData() { return this->ptr->data; }
    key_type getKey() { return this->ptr->key; }

    node* prevNode() {
      node* p = nullptr;
      if (ptr->left != Nil) {
        ptr = ptr->left;
        while (ptr->right != Nil) {
          ptr = ptr->right;
        }
      } else {
        p = ptr->parent;
        while (p != Nil && ptr == p->left) {
          ptr = p;
          p = p->parent;
        }
        ptr = p;
      }
      return ptr;
    }

    auto nextNode() {
      node* p = nullptr;
      if (ptr->right != Nil) {
        ptr = ptr->right;
        while (ptr->left != Nil) {
          ptr = ptr->left;
        }
      } else {
        p = ptr->parent;
        while (p != Nil && ptr == p->right) {
          ptr = p;
          p = p->parent;
        }
        ptr = p;
      }
      return ptr;
    }

    auto& operator++() noexcept {
      this->ptr = nextNode();
      return *this;
    }

    auto operator++(int) noexcept {
      auto tmp = ptr;
      this->ptr = nextNode();
      return IteratorTree{tmp};
    }

    IteratorTree& operator--() noexcept {
      this->ptr = prevNode();
      return *this;
    }

    IteratorTree operator--(int) noexcept {
      auto tmp = ptr;
      this->ptr = prevNode();
      return IteratorTree{tmp};
    }

    const node* Nilfind() {
      const node* Nil = ptr;
      while (Nil != Nil->left) Nil = Nil->left;
      return Nil;
    }

    template <bool R>
    bool operator==(const IteratorTree<R>& other) const {
      return this->ptr == other.ptr;
    }

    template <bool R>
    bool operator!=(const IteratorTree<R>& other) const {
      return !(this->ptr == other.ptr);
    }

    operator IteratorTree<true>() const { return IteratorTree<true>{ptr}; }
  };

  using const_iterator = IteratorTree<true>;
  using iterator = IteratorTree<false>;
  iterator begin() { return iterator{minimum(this->root)}; }
  iterator end() { return iterator{getNil()}; }
  iterator rbegin() { return iterator{maximum(this->root)}; }
  iterator rend() { return iterator{getNil()}; }
  const_iterator begin() const { return iterator{minium(root)}; }
  const_iterator end() const { return iterator{Nil}; }
  iterator insert(key_const_reference value) { return insert(value, 0); }
  iterator insert(key_const_reference value,
                  data_const_reference data_) {  // node*
    node* new_leaf;
    if (root == Nil) {
      new_leaf = new node;
      if (new_leaf) {
        new_leaf->left = Nil;
        new_leaf->right = Nil;
        new_leaf->key = value;
        new_leaf->parent = Nil;
        new_leaf->leaf_color = Black;
        new_leaf->data = data_;
        this->size_tree = 1;
        root = new_leaf;
      }
    } else {
      new_leaf = this->find_space(value);
      if (new_leaf) {
        new_leaf->data = data_;
        new_leaf->left = Nil;
        new_leaf->right = Nil;
        new_leaf->key = value;
        new_leaf->leaf_color = Red;
        this->size_tree++;
        fixInsert(new_leaf);
      }
    }
    return iterator{new_leaf};
  }
  Tree(const Tree& other) {
    NilInit();
    this->root = Nil;
    for (auto i = other.begin(); i != other.end(); i++) {
      this->insert(*i, i.getData());
    }
  };
  Tree(Tree&& other) {
    this->size_tree = std::move(other.size_tree);
    this->Nil = std::move(other.Nil);
    this->root = std::move(other.root);
    other.size_tree = 0;
    other.Nil = nullptr;
    other.root = nullptr;
  }
  Tree operator=(Tree&& other) {
    NilInit();
    this->root = Nil;
    for (auto i = other.begin(); i != other.end(); i++) {
      this->insert(*i, i.getData());
    }
    other.~Tree();
    other.root = nullptr;
    return *this;
  }
  Tree& operator=(const Tree& other) {
    for (auto i = other.begin(); i != other.end(); i++) {
      this->insert(*i, i.getData());
    }
    return *this;
  }
  data_type& getMap(iterator pos) {
    node* n = pos.getPtr();
    data_type& map = (n->data);
    return map;
  }
  void DeleteTreeRecursive(node* node_) {
    if (node_ && node_ != Nil) {
      DeleteTreeRecursive(node_->left);
      DeleteTreeRecursive(node_->right);
      if (node_->parent != Nil) {
        if (node_->parent->left == node_)
          node_->parent->left = Nil;
        else if (node_->parent->right == node_)
          node_->parent->right = Nil;
      }
      delete node_;
    }
  }
  ~Tree() {
    if (root != nullptr) {
      DeleteTreeRecursive(root);
      delete Nil;
      root = nullptr;
    }
    size_tree = 0;
  }

  void swap(Tree& other) {
    std::swap(this->root, other.root);
    std::swap(this->Nil, other.Nil);
    std::swap(this->size_tree, other.size_tree);
  }
  void erase(iterator pos) { remove(pos.getKey(), pos.getPtr()); }
};

};  // namespace s21