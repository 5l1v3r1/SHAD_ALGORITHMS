#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;
using std::pair;


namespace sequences {
    
    typedef pair<int, int> element_and_sequence_index;

    class priority_queue {
    private:
        vector<element_and_sequence_index> elements;
        void sift_down(int index);
        void sift_up(int index);
    public:
        priority_queue() {}
        explicit priority_queue(const vector< vector<int> > & sequence2D );
        element_and_sequence_index min();
        void push(element_and_sequence_index element);
        void pop_min();
        bool empty();
        ~priority_queue() {}
    };    

   
    priority_queue::priority_queue(const vector< vector<int> > & sequence2D) {

        for (int sequence_index = 0; sequence_index < sequence2D.size(); ++sequence_index) {
            push(element_and_sequence_index(sequence2D[sequence_index][0], sequence_index));
        }

    }
    
    void priority_queue::sift_down(int index) {

        int first_child_index = 2 * index + 1;
        int second_child_index = 2 * index + 2;

        if (first_child_index >= elements.size()) {
            return;
        }
        
        if ( second_child_index == elements.size() ) {

            if ( elements[first_child_index] < elements[index] ) {
              swap(elements[first_child_index], elements[index]);
            }

            return;
        }

        if ( !(elements[index] > elements[first_child_index]) &&
            !(elements[index] > elements[second_child_index])) {
                return;
        }

        if ( elements[second_child_index] > elements[first_child_index] ) {
            swap(elements[first_child_index], elements[index]);
            sift_down(first_child_index);
        }
        else {
            swap(elements[second_child_index], elements[index]);
            sift_down(second_child_index);
        }

    }
   
    void priority_queue::sift_up(int index) {

        if (index == 0) {
            return;
        }

        int parent_index = (index - 1) / 2;

        if ( elements[parent_index] > elements[index] ) {
            swap(elements[index], elements[parent_index]);
            sift_up(parent_index);
        }

    }

    element_and_sequence_index priority_queue::min() {
        return elements[0];
    }
    
    void priority_queue::push(element_and_sequence_index element) {
        elements.push_back(element);
        sift_up(elements.size() - 1);
    }
   
    void priority_queue::pop_min() {
        elements[0] = elements.back();        
        elements.pop_back();
        sift_down(0);
    }
  
    bool priority_queue::empty() {
        return elements.empty();
    }

    vector<int> merge_sequences(const vector< vector<int> > & sequence2D) {

        int number_of_elements_in_sequence = sequence2D[0].size();
        int number_of_sequences = sequence2D.size();

        priority_queue queue(sequence2D);
        vector<int> indexes_of_first_elements_not_in_queue_and_result(number_of_sequences, 0);
        vector<int> result;

        while (!queue.empty()) {

            element_and_sequence_index pair = queue.min();
            queue.pop_min();

            int index_of_sequece = pair.second;
            int current_element = pair.first;

            result.push_back(current_element);

            int next_index_of_element = 
                ++indexes_of_first_elements_not_in_queue_and_result[index_of_sequece];           

            if (indexes_of_first_elements_not_in_queue_and_result[index_of_sequece] !=
                number_of_elements_in_sequence) {
                int next_element = sequence2D[index_of_sequece][next_index_of_element];
                queue.push(element_and_sequence_index(next_element, index_of_sequece));
            }                

        }
        
        return result;
    }

}

vector< vector<int> >  read_sequences() {

    vector< vector<int> > result;

    int number_of_sequences;
    int number_of_elements_in_sequence;
    cin >> number_of_sequences;
    cin >> number_of_elements_in_sequence;

    for (int sequence_index = 0; sequence_index < number_of_sequences; ++sequence_index) {

        result.push_back(vector<int>());

        for (int element_index = 0; element_index < number_of_elements_in_sequence; 
            ++element_index) {
                int element;
                cin >> element;
                result[sequence_index].push_back(element);
        }        
    }

    return result;
}

void write_big_sequence(const vector<int> & result) {

    if (result.empty())
        return;

    for (int element_index = 0; element_index + 1 < result.size(); ++element_index) {
        cout << result[element_index] << " ";
    }

    cout << result.back() << endl;

}

int main() {
    vector< vector<int> > sequecnce2D = read_sequences();
    vector<int> result = sequences::merge_sequences(sequecnce2D);
    write_big_sequence(result);
    return 0;
}
