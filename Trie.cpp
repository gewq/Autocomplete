#include "Trie.h"

#include <iostream>
#include <string>
#include <assert.h>


namespace {
  //Разрешённые символы в дереве
  std::string ALLOWED_CHARS = "abcdefghijklmnopqrstuvwxyz";
}



static bool isContainForbiddenChars(const std::string& stringToCheck, const std::string& allowedChars)
{
	//Искать в строке любой НЕразрешённый символ
  size_t pos = stringToCheck.find_first_not_of(allowedChars);
  //Найден хотя бы один НЕразрешённый символ
  if (pos != std::string::npos) {
    return true;
  }
  return false;
}



Trie::Trie()
{
  root_ = new Node;
}



Trie::~Trie()
{
  delete root_;
}



void Trie::addWord(const std::string& word)
{
  if (word.empty()) {
    return;
  }

  //Итератор по узлам дерева
  Node* currentNode = root_;

  //Пройти по дереву по направлению каждой буквы добавляемого слова word
  for (size_t i=0; i<word.size(); ++i) {
    //Определить индекс по которому искать следующий узел (зависит от текущей буквы)
    size_t id = word.at(i) - 'a';	//Смещение от 'a'

    //Нет буквы в дереве - создать узел и поместить в дерево
    if (!currentNode->getChild(id)) {
      Node* newNode = new Node;
      currentNode->setChild(newNode, id);
    }
    currentNode = currentNode->getChild(id);	//Перейти вниз по дереву
  }
  //Последний узел слова отметить признаком - конец слова
  currentNode->setIsEndWord();
}



void Trie::removeWord(const std::string& word)
{
  //Дерево пустое
  if (!root_) {
    return;
  }

  //Нечего удалять
  if (word.empty()) {
    return;
  }

  size_t depth = 0; //Счётчик глубины погружения в дерево для контроля положения в нём

  size_t id = word.at(0) - 'a';	//Начинаем обход дерева с первой [0] буквы
  removeNode(root_->getChild(id), word, depth);
}



bool Trie::isExist(const std::string& word) const
{
  if (word.empty()) {
    return false;
  }

  //Итератор по узлам дерева
  Node* currentNode = root_;

  //Пройти по дереву по направлению каждой буквы проверяемого слова
  for (size_t i=0; i<word.size(); ++i) {
    //Определить индекс по которому искать следующий узел (зависит от текущей буквы)
    size_t id = word.at(i) - 'a';	//Смещение от 'a'

    //Нет буквы в дереве - конец проверки (слова нет)
    if (!currentNode->getChild(id)) {
      return false;
    }

    currentNode = currentNode->getChild(id);	//Перейти вниз по дереву
  }

  return ( (currentNode != nullptr) && ( currentNode->isEndWord() ) );
}



std::vector<std::string> Trie::prefixSearch(const std::string& prefix)
{
  std::vector<std::string> resultWords;
  if (prefix.empty()) {
    return resultWords;
  }

  Node* startNode = getNodeEndString(prefix);	//Узел - последний символ префикса
  //Префикс не найден в дереве
  if (!startNode) {
    return resultWords;
  }

  std::string buffer = prefix;

  //Префикс совпадает со словом в дереве - внести префикс в набор искомых слов
  if (startNode->isEndWord()) {
    resultWords.push_back(buffer);
  }

  enter(startNode, prefix, &buffer, &resultWords);	//Пройти дальше вглубь дерева

  return resultWords;
}



void Trie::loadWords(const std::vector<std::string>& words)
{
  //Нечего добавлять
  if (words.empty()) {
    return;
  }

  for (size_t i=0; i<words.size(); ++i) {
    addWord(words.at(i));
  }
}



//------------------------------------------------------------------------------
void Trie::enter(Node* node, const std::string& prefix, std::string* buffer,
                 std::vector<std::string>* resultWords)
{
  for (size_t i=0; i<node->getMaxNumberChildren(); ++i) {
    if ( node->getChild(i) ) {
      char ch = 'a' + static_cast<char>(i);
      *buffer += ch;
      enter(node->getChild(i), prefix, buffer, resultWords);

      //Узел - конец слова - добавить слово в результирующий набор
      if ( node->getChild(i)->isEndWord() ) {
        resultWords->push_back(*buffer);
      }

      //Поднимаясь наверх по дереву (после выхода из enter() ) -
			//отбросить от buffer последнюю букву
      buffer->pop_back();
    }
  }
}



Node* Trie::getNodeEndString(const std::string& string)
{
  //Запрещённые символы
  if (isContainForbiddenChars(string, ALLOWED_CHARS)) {
    return nullptr;
  }

  if (string.empty()) {
    return nullptr;
  }
  
  //Итератор по узлам дерева
  Node* currentNode = root_;
  for (size_t i=0; i<string.size(); ++i) {
    //Индекс в массиве указателей зависит от буквы
    size_t id = string.at(i) - 'a';	//Смещение от 'a'
    if (!currentNode->getChild(id)) {
      return nullptr;
    }
    currentNode = currentNode->getChild(id);
  }
  return currentNode;
}



void Trie::removeNode(Node* node, const std::string& word, size_t& depth)
{
  ++depth;	//При входе в узел увеличить счётчик глубины

  //Узел - последняя буква удаляемого слова
  if (depth == word.size()) {
    //Есть дочерние узлы
    if (node->isHaveChild()) {
      node->resetIsEndWord();	//Cнять признак - конец слова
    }

    //Нет дочерних узлов - удалить узел
    else {
      delete node;
    }
  }

  //Промежуточный узел
  else {
    //Пройти дальше вглубь дерева
    size_t id = word.at(depth) - 'a';
    removeNode(node->getChild(id), word, depth);
  }
  //Здесь вернулись обратно в текущий узел

  //Нет дочерних узлов - удалить узел
  if (!node->isHaveChild()) {
    delete node;
  }
  --depth;	//При выходе из узла уменьшить счётчик глубины
}



//==============================================================================
static void testConstructor();
static void testAddWord();
static void testLoadWords();
static void testRemoveWord();
static void testPrefixSearch();



void trie::runTest()
{
  testConstructor();
  testAddWord();
  testLoadWords();
  testRemoveWord();
  testPrefixSearch();
}



static void testConstructor()
{
  Trie dictionary;

  //Запрет конструктора копирования
//  Trie dictionaryTst(dictionary);

  //Запрет конструктора перемещения
//  Trie dictionaryTst(std::move(dictionary));

  //Запрет оператора присваивания
//  Trie dictionary_1;
//  Trie dictionary_2;
//  dictionary_1 = dictionary_2;
}



static void testAddWord()
{
  Trie dictionary;
  std::vector<std::string> testWords = {
    "caller",
    "call",
    "cat",
    "cult",
    "run",
    "rut"
  };

  //До добавления слов в дерево
  for (size_t i=0; i<testWords.size(); ++i) {
    assert(dictionary.isExist(testWords.at(i)) == false);
  }

  //После добавления слов в дерево
  for (size_t i=0; i<testWords.size(); ++i) {
    dictionary.addWord(testWords.at(i));
    assert(dictionary.isExist(testWords.at(i)) == true);
  }
}



static void testLoadWords()
{
  Trie dictionary;
  std::vector<std::string> testWords = {
    "caller",
    "call",
    "cat",
    "cult",
    "run",
    "rut"
  };

  //До добавления слов в дерево
  for (size_t i=0; i<testWords.size(); ++i) {
    assert(dictionary.isExist(testWords.at(i)) == false);
  }

  dictionary.loadWords(testWords);

  //После добавления слов в дерево
  for (size_t i=0; i<testWords.size(); ++i) {
    assert(dictionary.isExist(testWords.at(i)) == true);
  }
}



static void testRemoveWord()
{
  Trie dictionary;
  std::vector<std::string> testWords = {
    "caller",
    "call",
    "cat",
    "cult",
    "run",
    "rut"
  };

  for (size_t i=0; i<testWords.size(); ++i) {
    dictionary.addWord(testWords.at(i));
  }

  std::string wordToRemove = "call";
  dictionary.removeWord(wordToRemove);

  for (size_t i=0; i<testWords.size(); ++i) {
  	//Слово которое удалено
    if (testWords.at(i) == wordToRemove) {
      assert(dictionary.isExist(wordToRemove) == false);
    }
    //Остальные слова остались в дереве
    else {
      assert(dictionary.isExist(testWords.at(i)) == true);
    }
  }
}



static void testPrefixSearch()
{
  Trie dictionary;
  std::vector<std::string> testWords = {
    "caller",
    "call",
    "cat",
    "cult",
    "run",
    "rut"
  };

  for (size_t i=0; i<testWords.size(); ++i) {
    dictionary.addWord(testWords.at(i));
  }

  auto wordsByPrefix = dictionary.prefixSearch("1");
  for (size_t i=0; i<wordsByPrefix.size(); ++i) {
    assert(wordsByPrefix.at(i) == testWords.at(i));
  }
}