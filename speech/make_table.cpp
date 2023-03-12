#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "SymbolTable.h"

int main(int argc, char *argv[])
{
    std::string tokens = argv[1];
    std::string table_name = argv[2];
    SymbolTable sym(tokens);
    std::vector<std::pair<int32_t, std::string>> table;
    for (auto item : sym.id2sym_)
        table.push_back(item);
    std::sort(table.begin(), table.end(),
              [](const std::pair<int32_t, std::string> &a,
                const std::pair<int32_t, std::string> &b)
    {
        return a.first < b.first;
    });
    std::fstream file_table;
    file_table.open("table.h", std::ios_base::out);
    if (file_table.is_open())
    {
      file_table << "#pragma once" << std::endl;
      file_table << "#include <unordered_map>" << std::endl;
      file_table
          << "static const std::unordered_map<std::string, int32_t> " << table_name << " = "
          << std::endl;
      file_table << "{" << std::endl;
      file_table << "{\""
                 << "\\"
                 << "n\", -1}," << std::endl;
      for (auto item : table)
      {
          file_table << "{\"" << item.second << "\""
                      << ", " << item.first << "}," << std::endl;
      }
      file_table << "};";
      file_table.close();
    }

    return 0;
}