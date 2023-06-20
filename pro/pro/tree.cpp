#include "tree.h"
#include <fstream>

/// Начало заимствованного (с изменениями) фрагмента кода //////////////////////
tree_node* InsertHelper(std::unique_ptr<tree_node>& node, const Person &val, tree_node* parent) {
    if (!node)
    {
        node = std::make_unique<tree_node>(val, parent);
        return node.get(); 
    }
    if (val < node->value)
        return InsertHelper(node->left, val, node.get());
    if (val > node->value)
        return InsertHelper(node->right, val, node.get());
    return node.get();
}
tree_node* tree::insert(const Person &val) {
    return InsertHelper(root, val, nullptr);
}
bool RemoveHelper(std::unique_ptr<tree_node>& node, const Person &val){
    if (!node)
        return false;
    if (val < node->value)
        return RemoveHelper(node->left, val);
    if (val > node->value)
        return RemoveHelper(node->right, val);
    if (!node->left) {
        node = std::move(node->right);
        return true;
    }
    if (!node->right) {
        node = std::move(node->left);
        return true;
    }
    auto min_right_node = node->right.get();
    while (min_right_node->left)
        min_right_node = min_right_node->left.get();
    node->value = min_right_node->value;
    return RemoveHelper(node->right, min_right_node->value);
}
bool tree::remove(const Person &val) {
    return RemoveHelper(root, val);
}

void Tree_to_vector(tree_node const &t, std::vector<Person> &res)
{
  if (t.left)
    Tree_to_vector(*t.left, res);
  res.push_back(t.value);
  if (t.right)
    Tree_to_vector(*t.right, res);
}

std::vector<Person> tree::to_vector() const
{
  std::vector<Person> result;
  if (root)
    Tree_to_vector(*root, result);
  return result;
}
/// Конец заимствованного (с изменениями) фрагмента кода //////////////////////

bool tree::load(const std::string &path)
{
  std::fstream f(path);
  if (!f.is_open())
  {
    return false;
  }

  std::string csv;
  while (std::getline(f, csv))
  {
    insert(Person{csv});
  }

  return true;
}

bool tree::save(const std::string &path) const
{
  std::fstream f;
  f.open(path, std::fstream::out);
  if (!f.is_open())
  {
    return false;
  }

  for (const auto &v : to_vector())
  {
    f << v.toCsv() << std::endl;
  }

  return true;
}

tree_node* FindHelper(const std::unique_ptr<tree_node>& node, const Phone &phone, tree_node* parent = nullptr) {
  if (!node)
  {
    return nullptr;
  }
  if (phone < node->value.m_phone)
    return FindHelper(node->left, phone, node.get());
  if (phone > node->value.m_phone)
    return FindHelper(node->right, phone, node.get());
  return node.get();
}

tree_node* tree::find(const Phone &phone) const
{
  return FindHelper(root, phone);
}
