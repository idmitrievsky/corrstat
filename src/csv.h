//
//  csv.h
//  corrstat
//
//  Created by Ivan Dmitrievsky on 23/06/15.
//  Copyright (c) 2015 Иван Дмитриевский. All rights reserved.
//

#ifndef corrstat_csv_h
#define corrstat_csv_h

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow {
public:
  std::string const& operator[](std::size_t index) const {
    return m_data[index];
  }
  std::size_t size() const { return m_data.size(); }
  void readNextRow(std::istream& str) {
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    m_data.clear();
    while (std::getline(lineStream, cell, ';') && cell != "\r") {
      m_data.push_back(cell);
    }
  }

private:
  std::vector<std::string> m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data) {
  data.readNextRow(str);
  return str;
}

class CSVIterator {
public:
  typedef std::input_iterator_tag iterator_category;
  typedef CSVRow value_type;
  typedef std::size_t difference_type;
  typedef CSVRow* pointer;
  typedef CSVRow& reference;

  CSVIterator(std::istream& str) : m_str(str.good() ? &str : NULL) {
    ++(*this);
  }
  CSVIterator() : m_str(NULL) {}

  CSVIterator& operator++() {
    if (m_str) {
      (*m_str) >> m_row;
      m_str = m_str->good() ? m_str : NULL;
    }
    return *this;
  }

  CSVIterator operator++(int) {
    CSVIterator tmp(*this);
    ++(*this);
    return tmp;
  }
  CSVRow const& operator*() const { return m_row; }
  CSVRow const* operator->() const { return &m_row; }

  bool operator==(CSVIterator const& rhs) {
    return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));
  }
  bool operator!=(CSVIterator const& rhs) { return !((*this) == rhs); }

private:
  std::istream* m_str;
  CSVRow m_row;
};

#endif
