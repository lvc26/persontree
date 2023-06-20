#include "tree.h"
#include "doctest.h"
#include <iostream>
#include <numeric>
#include <vector>


/***********************************************************************************************//**
*     \brief Запросить ввод из консоли номера телефона
*
*     \return Введённый пользователем номер телефона.
****************************************************************************************************/
Phone getPhone()
{
  Phone phone{};
  std::cout << "Введите номер телефона (только цифры): ";
  std::cin >> phone;
  return phone;
}

int main()
{

  // Путь к файлу с данными для загрузки в двоичное дерево
  const std::string csvFilePath = "/Users/lvc/Desktop/prok/pro/pro/PersonTree.csv";

  // Экземпляр двоичного дерева с персональными данными
  tree t;

  if (t.load(csvFilePath))
  {
    std::cout << "Данные двоичного дерева успешно загружены из файла " << csvFilePath << std::endl;
  }
  else
  {
    std::cout << "ОШИБКА! Не удалось загрузить данные из файла " << csvFilePath << std::endl;
    return 1; // Завершаем выполнение программы с ошибкой
  }

  // Бесконечный цикл консольного интерфейса
  while (true)
  {
    std::cout << std::endl << std::endl;
    std::cout << "Выберите действие:" << std::endl;
    std::cout << " 1. Вывести дерево" << std::endl;
    std::cout << " 2. Найти пользователя по номеру телефона" << std::endl;
    std::cout << " 3. Добавить нового пользователя" << std::endl;
    std::cout << " 4. Удалить пользователя" << std::endl;
    std::cout << " 5. Сохранить дерево в файл" << std::endl;
    std::cout << " 6. Запустить тесты" << std::endl;
    std::cout << " 0. Закончить работу" << std::endl;

    std::cout << "Ваш выбор: ";
    int choice{};
    std::cin >> choice;
    std::string str;
    std::getline(std::cin, str);
    std::cout << std::endl;

    switch (choice)
    {
    case 0:
      std::cout << "Работа с двоичным деревом завершена." << std::endl;
      return 0; // Штатное завершение программы

    case 1:
      std::cout << "Содержимое дерева:" << std::endl;
      for (const Person &person : t.to_vector())
      {
        std::cout << person << std::endl;
      }
      break;

    case 2:
      if (tree_node *found = t.find(getPhone()))
      {
        std::cout << "Данные найдены:" << std::endl << found->value;
      }
      else
      {
        std::cout << "Данные не найдены!" << std::endl;
      }
      break;

    case 3:
    {
      Person newPerson;
      std::cin >> newPerson;
      t.insert(newPerson);
      break;
    }

    case 4:
      if (tree_node *found = t.find(getPhone()))
      {
        const Person person = found->value;
        if (t.remove(found->value))
        {
          std::cout << "Следующие данные найдены и успешно удалены из дерева:" << std::endl << person;
        }
        else
        {
          std::cout << "Данные найдены, но из дерева их удалить не удалось!" << std::endl << person;
        }
      }
      else
      {
        std::cout << "Данные не найдены, из дерева ничего не удалено!" << std::endl;
      }
      break;

    case 5:
      if (t.save(csvFilePath))
      {
        std::cout << "Данные успешно сохранены в файл " << csvFilePath << std::endl;
      }
      else
      {
        std::cout << "ОШИБКА! Не удалось сохранить данные в файл " << csvFilePath << std::endl;
      }
      break;

    case 6:
      doctest::Context().run();
      break;

    default:
      break;
    }
  }
}
