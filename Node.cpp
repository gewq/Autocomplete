#include "Node.h"

#include <iostream>
#include <assert.h>
#include <stdexcept>



Node::Node(): isEndWord_(false)
{
  children_.fill(nullptr);
}



Node::~Node()
{
  for (size_t i=0; i<children_.size(); ++i) {
    delete children_.at(i);
  }
}



Node* Node::getChild(size_t id) const
{
  //Выход за пределы диапазона
  if (id > children_.size()-1) {
  	throw std::out_of_range("Node::getChild(" + std::to_string(id) + ")");
  }

  return children_.at(id);
}



void Node::setChild(Node* child, size_t id)
{
  //Выход за пределы диапазона
  if (id > children_.size()-1) {
  	throw std::out_of_range("Node::setChild(" + std::to_string(id) + ")");
  }

  children_.at(id) = child;
}



void Node::setIsEndWord()
{
  isEndWord_ = true;
}



void Node::resetIsEndWord()
{
  isEndWord_ = false;
}



bool Node::isEndWord() const
{
  return isEndWord_;
}



size_t Node::getMaxNumberChildren() const
{
  return children_.size();
}



bool Node::isHaveChild() const
{
  for (size_t i=0; i<children_.size(); ++i) {
    //Есть хотя бы один дочерний узел
    if (children_.at(i)) {
      return true;
    }
  }
  return false;
}



//============================================================
static void testConstructor();
static void testSetResetIsEndWord();
static void testSetChild();
static void testGetMaxNumberChildren();



void node::runTest()
{
  testConstructor();
  testSetResetIsEndWord();
  testSetChild();
  testGetMaxNumberChildren();
}



static void testConstructor()
{
  Node node;

  assert (node.isEndWord() == false);
  for(size_t i=0; i<node.getMaxNumberChildren(); ++i) {
    assert(node.getChild(i) == nullptr);
  }
  //Запрет конструктора копирования
//  Node nodeTst(node);

  //Запрет конструктора перемещения
//  Node nodeTst(std::move(node));

  //Запрет оператора присваивания
//  Node node_1;
//  Node node_2;
//  node_1 = node_2;
}



static void testSetResetIsEndWord()
{
  Node node;
  node.setIsEndWord();
  assert (node.isEndWord() == true);
  node.resetIsEndWord();
  assert (node.isEndWord() == false);
}



static void testSetChild()
{
  Node node;
  Node* child = new Node;
  node.setChild(child, 0);
  assert(node.getChild(0) == child);
  for(size_t i=1; i<node.getMaxNumberChildren(); ++i) {
    assert(node.getChild(i) == nullptr);
  }
}



static void testGetMaxNumberChildren()
{
  Node node;
  assert(node.getMaxNumberChildren() == Node::ALPHABET_SIZE);
}
