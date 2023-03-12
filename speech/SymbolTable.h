#ifndef SHERPA_SYMBOL_TABLE_H_
#define SHERPA_SYMBOL_TABLE_H_

#include <string>
#include <unordered_map>

class SymbolTable 
{
public:
    SymbolTable() = default;
    /// Construct a symbol table from a file.
    /// Each line in the file contains two fields:
    ///
    ///    sym ID
    ///
    /// Fields are separated by space(s).
    explicit SymbolTable(const std::string &filename);

    explicit SymbolTable(const std::unordered_map<std::string, int32_t>& table);

    /// Return a string representation of this symbol table
    std::string ToString() const;

    /// Return the symbol corresponding to the given ID.
    const std::string &operator[](int32_t id) const;
    /// Return the symbol corresponding to the given ID.
    const std::string &at(int32_t id) const;
    /// Return the ID corresponding to the given symbol.
    int32_t operator[](const std::string &sym) const;
    /// Return the ID corresponding to the given symbol.
    int32_t at(const std::string &sym) const;

    /// Return true if there is a symbol with the given ID.
    bool contains(int32_t id) const;

    /// Return true if there is a given symbol in the symbol table.
    bool contains(const std::string &sym) const;

    void Init(std::istream &is);

    std::unordered_map<std::string, int32_t> sym2id_;
    std::unordered_map<int32_t, std::string> id2sym_;
};

#endif /* SHERPA_SYMBOL_TABLE_H_ */
