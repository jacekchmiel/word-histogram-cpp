#include "cli.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cctype>
#include <utility>
#include <fstream>
#include <vector>
#include <algorithm>

class WordStore {
    typedef std::unordered_map<std::string, uint64_t> store_type;
    typedef store_type::value_type item_type;
    store_type m_store;

 public:
    void consume_stream(std::istream& is) {
        while(true) {
            std::string w = read_word(is);
            if (not w.empty()) {
                record_word(std::move(w));
            } else {
                // Empty word means end of stream
                break;
            }
        }
    }

    void print_results() const {
        print_items(m_store.cbegin(), m_store.cend());
    }

    /// Print first_n largest entries sorted alphabetically
    void print_summary(size_t first_n) const {
        // Copy data for sorting purposes
        // Note:
        //   could use another approach: use heap keeping track only of `first_n` largest items
        //   would result with less space required, faster sort afterwards but slower copy
        std::vector<std::pair<std::string, uint64_t>> v(m_store.cbegin(), m_store.cend());

        // Sort data by number of occurences
        std::sort(v.begin(), v.end(),
             [](const item_type& a, const item_type& b) -> bool
             {
                 return a.second > b.second;
             });

        // Select only first_n elements
        v.resize(first_n);

        // Sort alphabetically
        std::sort(v.begin(), v.end());

        print_items(v.cbegin(), v.cend());
    }

    template<typename Iterator>
    static void print_items(Iterator begin, Iterator end) {
        for(Iterator it = begin; it != end; ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
        }
    }

 private:
    std::string read_word(std::istream& is) {
        std::ostringstream word;
        while (true) {
            auto c = is.get();
            if (c == std::char_traits<char>::eof()) {
                break;
            }
            if (std::isspace(c)) {
                if (not word.str().empty()) {
                    break;
                } else {
                    continue;
                }
            } else {
                word.put(static_cast<char>(c));
                continue;
            }
        }
        return word.str();
    }

    void record_word(std::string&& w) {
        auto it = m_store.find(w);
        if (it == m_store.end()) {
            m_store.insert(std::make_pair(std::move(w), 1u));
        } else {
            it->second += 1;
        }
    }
};

int main(int ac, char* av[]) {
    auto args = Args::from_commandline(ac, av);
    if(args) {
        std::ifstream s;
        s.open(args->file);
        WordStore store;
        store.consume_stream(s);
        store.print_summary(10);
    }

}
