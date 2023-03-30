/**
\file Trie.h
\brief Класс - префиксное дерево

Представляет собой дерево узлов.

Каждый узел содержит массив указателей на дочерние узлы.
Каждый узел представляет собой одну букву латинского алфавита.
Какую именно букву - определяется от расположения узла в
массиве дочерних узлов своего родителя (индекс 0 - 'a', 1 - 'b' и т.д.)
*/
#pragma once

#include <string>
#include <array>
#include <vector>

#include "../Node/Node.h"


class Trie {
  public:
    Trie();

    Trie(const Trie& other) = delete;
    Trie(Trie&& other) = delete;

    Trie& operator= (const Trie& other) = delete;
    Trie& operator= (Trie&& other) = delete;

    ~Trie();

    /**
    Добавить слово в дерево
    \param[in] word Слово которое добавить
    */
    void addWord(const std::string& word);

    /**
    Удалить слово из дерева
    \param[in] word Слово которое удалить
    */
    void removeWord(const std::string& word);

    /**
    Вернуть признак - есть ли слово в дерево
    \param[in] word Слово которое проверить
    \return Признак - наличие слова в дереве
    */
    bool isExist(const std::string& word) const;

    /**
    Вернуть набор слов начинающихся с префикса
    \param[in] prefix Префикс
    \return Вектор слов
    */
    std::vector<std::string> prefixSearch(const std::string& prefix);

    /**
    Загрузить в дерево набор слов
    \param[in] words Вектор слов
    */
    void loadWords(const std::vector<std::string>& words);

  private:
    /**
    Посетить узел - собрать слово, соответствующее префиксу
    \param[in] node Узел который посетить
    \param[in] prefix Префикс
    \param[in] buffer Строка в которой собирается по буквам слово
    \param[in] resultWords Набор слов, начинающийся с префикса
    */
    void enter(Node* node, const std::string& prefix, std::string* buffer,
               std::vector<std::string>* resultWords);

    /**
    Вернуть узел - представляющий последнюю букву строки
    \param[in] prefix Префикс
    \return Указатель на узел
    */
    Node* getNodeEndString(const std::string& string);

    /**
    Зайти в узел и удалить его при удалении слова из дерева
    \param[in] node Узел в который зайти
    \param[in] word Слово которое удалить из дерева
    \param[in] depth Уровень глубины погружения в дерево
    */
    void removeNode(Node* node, const std::string& word, size_t& depth);

    Node* root_;	///<Корень дерева
};



namespace trie {
  /**
  Протестировать методы класса
  */
  void runTest();
}