#pragma once

#include <unordered_map>
#include <iostream>

class WordStore {
    typedef std::unordered_map<std::string, uint64_t> store_type;
    typedef store_type::value_type item_type;
    store_type m_store;

 public:
    /// Consumes stream collecting word occurences
    void consume_stream(std::istream& is);

    /// Prints every word along with it's count
    void print_all() const {
        print_items(m_store.cbegin(), m_store.cend());
    }

    /// Print first_n largest entries sorted alphabetically
    void print_summary(size_t first_n) const;


 private:
    std::string read_word(std::istream& is);
    void record_word(std::string&& w);

    template<typename Iterator>
    static void print_items(Iterator begin, Iterator end) {
        for(Iterator it = begin; it != end; ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
        }
    }
};
