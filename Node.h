/**
\file Node.h
\brief Класс - узел префиксного дерева

Каждый объект содержит:
- признак является ли узел концом слова
- массив дочерних узлов
*/
#pragma once

#include <array>


class Node {
  public:
    static const size_t ALPHABET_SIZE = 26; ///<Количество букв в английском алфавите

    Node();

    //Запретить копирование и перемещение
    Node(const Node& other) = delete;
    Node(Node&& other) = delete;

    Node& operator= (const Node& other) = delete;
    Node& operator= (Node&& other) = delete;

    ~Node();

    /**
    Вернуть дочерний узел
    \param[in] id Индекс узла в массиве дочерних узлов
    \return Указатель на дочерний узел
    */
    Node* getChild(size_t id) const;

    /**
    Задать дочерний узел
    \param[in] child Указатель на узел который сделать дочерним
    \param[in] id Индекс узла в массиве дочерних узлов
    */
    void setChild(Node* child, size_t id);

    /**
    Установить признак - конец слова
    */
    void setIsEndWord();

    /**
    Сбросить признак - конец слова
    */
    void resetIsEndWord();

    /**
    Вернуть признак - является ли узел концом слова
    \return Признак - конец слова
    */
    bool isEndWord() const;

    /**
    Вернуть максимально возможное количество дочерних узлов
    \return Признак - конец слова
    */
    size_t getMaxNumberChildren() const;

    /**
    Вернуть признак - есть ли хотя бы один дочерний узел
    \return Признак - конец слова
    */
    bool isHaveChild() const;

  private:
    bool isEndWord_;		///<Признак того, что узел является концом слова
    std::array<Node*, ALPHABET_SIZE> children_;	///<Массив указателей на дочерние узлы
};



namespace node {
  /**
  Протестировать методы класса
  */
  void runTest();
};