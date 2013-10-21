#include <iostream>
#include <string>
#include <stack>

using std::cin;
using std::cout;
using std::stack;
using std::string;
using std::endl;


namespace brackets {   

    const int NUMBER_OF_BRACKET_TYPES = 3;

    const char OPEN_BRACKETS[] = {'(', '[', '{'};

    const char CLOSE_BRACKETS[] = {')', ']', '}'};

    const char* search(const char* begin, const char* end, char symbol) {
        const char* current;
        for (current = begin; current < end; ++current) {
            if ( (*current) == symbol )
                return current;
        }
        return current;
    }

    bool is_open(char bracket) {
        const char* begin = OPEN_BRACKETS;
        const char* end = OPEN_BRACKETS + NUMBER_OF_BRACKET_TYPES;
        return search(begin, end, bracket) != end;
    }

    bool is_closed(char bracket) {
        const char* begin = CLOSE_BRACKETS;
        const char* end = CLOSE_BRACKETS + NUMBER_OF_BRACKET_TYPES;
        return search(begin, end, bracket) != end;
    }

    bool is_make_pair(char open_bracket, char closed_bracket) {
        int index_of_open = search(OPEN_BRACKETS, OPEN_BRACKETS + NUMBER_OF_BRACKET_TYPES, 
            open_bracket) - OPEN_BRACKETS;
        int index_of_closed = search(CLOSE_BRACKETS, CLOSE_BRACKETS + NUMBER_OF_BRACKET_TYPES,
            closed_bracket) - CLOSE_BRACKETS;
        return index_of_open == index_of_closed;
    }

    bool is_right_bracket_sequence(const string& bracket_sequence,
        int & number_of_symbols_in_nearly_right_sequence) {
            stack<char> open_brackets_stack;

            for (int current_bracket_index = 0;
                current_bracket_index < bracket_sequence.length(); ++current_bracket_index) {
                    char current_bracket = bracket_sequence[current_bracket_index];

                    if (is_open(current_bracket)) {
                        open_brackets_stack.push(current_bracket);
                    }

                    if (is_closed(current_bracket)) {
                        if (open_brackets_stack.empty()) {
                            number_of_symbols_in_nearly_right_sequence = current_bracket_index;
                            return false;
                        }
                        char open_bracket = open_brackets_stack.top();
                        open_brackets_stack.pop();
                        if (!is_make_pair(open_bracket, current_bracket)) {
                            number_of_symbols_in_nearly_right_sequence = current_bracket_index;
                            return false;
                        }
                    }
            }

            if (open_brackets_stack.empty()) {
                return true;
            }
            number_of_symbols_in_nearly_right_sequence = bracket_sequence.length();
            return false;
    }

}

const char* CORRECT = "CORRECT";

int main() {

    string bracket_sequence;
    getline(cin, bracket_sequence);

    int number_of_symbols_in_nearly_right_sequence;

    if (brackets::is_right_bracket_sequence(bracket_sequence, 
        number_of_symbols_in_nearly_right_sequence)) {
        cout << CORRECT << endl;
    }
    else {
        cout << number_of_symbols_in_nearly_right_sequence << endl;
    }

    return 0;
}
