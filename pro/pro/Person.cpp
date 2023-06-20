#include "Person.h"
#include <vector>
#include <sstream>
#include <iostream>

// Разделитель полей в строке CSV-файла
#define delim '\x09'

Person::Person(const std::string &csv)
{
  std::stringstream data(csv);
  std::string field;
  std::vector<std::string> fields;

  while (std::getline(data, field, delim))
  {
    fields.push_back(field);
  }

  if (fields.size() < 4)
  {
    throw std::runtime_error("Неверная CSV-строка: " + csv);
  }

  m_phone = std::stoull(fields[0]); // Телефон
  m_fio = fields[1]; // ФИО
  m_age= static_cast<unsigned int>(std::stoul(fields[2])); // Возраст
  m_address = fields[3]; // Адрес
}

std::string Person::toCsv() const
{
  std::stringstream csv;
  csv << m_phone << delim << m_fio << delim << m_age << delim << m_address;
  return csv.str();
}

bool Person::operator <(const Person &other) const
{
  return m_phone < other.m_phone;
}

bool Person::operator >(const Person &other) const
{
  return m_phone > other.m_phone;
}

std::ostream &operator << (std::ostream &s, const Person &person)
{
  return s << "ФИО: " << person.m_fio << std::endl
           << "Адрес: " << person.m_address << std::endl
           << "Тел.: +" << person.m_phone << std::endl
           << "Возраст: " << person.m_age << std::endl;
}

std::istream &operator >> (std::istream &s, Person &person)
{
  std::cout << "Введите персональные данные:" << std::endl;
  std::cout << "ФИО: "; std::getline(s, person.m_fio);
  std::cout << "Адрес: "; std::getline(s, person.m_address);
  std::cout << "Тел. (только цифры): "; s >> person.m_phone;
  std::cout << "Возраст: "; s >> person.m_age;
  return s;
}
