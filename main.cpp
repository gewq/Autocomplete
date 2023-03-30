/**
\file main.cpp
\brief Программа выполняет автодополнение введенного слова по изначально заданному словарю.

Автодополнение реализовано посредством префиксного дерева, содержащего заранее заданный словарь.
После ввода части слова пользователь по нажатию клавишы ' ' получает список вариантов слов по введённой части.
Ограничение:
- только символы латинского алфавита нижнего регистра
*/

#include <iostream>

#include "Node/Node.h"
#include "Trie/Trie.h"

#include <memory>


/**
Протестировать модули программы
*/
static void test();


int main(int argc, char** argv)
{
  try {
    test();

    Trie wordsBase;	//База слов для автодополнения
    //Словарь для внесения в базу
    std::vector<std::string> dictionary = {
      "caller",
      "call",
      "cat",
      "cult",
      "run",
      "rut"
    };
    wordsBase.loadWords(dictionary);

    std::cout << "Program shows words at base by user input prefix.\n";
    std::cout << "To exit type '.'\n\n";

    std::string userInput;
    while (true) {
      std::cout << "Please type string to autocomplete: ";
      std::cin >> userInput;
      if (userInput == ".") {
        break;
      }
      auto words = wordsBase.prefixSearch(userInput);

      if (words.empty()) {
        std::cout << "Prefix (" << userInput << ") is not contained\n";
        std::cout << std::endl;
      }

      else {
        for (size_t i=0; i<words.size(); ++i) {
          std::cout << words.at(i) << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
      }
    }
  }
  catch (std::bad_alloc& error) {
    std::cerr << "Memory allocation error: " << error.what() << std::endl;
  }
  catch (const std::out_of_range& error) {
  	std::cerr << "Out_of_range error: " << error.what() << std::endl;
  }
  catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Undefined exception" << std::endl;
  }

  return EXIT_SUCCESS;
}



static void test()
{
  node::runTest();
  trie::runTest();
}