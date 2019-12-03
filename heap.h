#include <utility>
#include <vector>
#include <stdexcept>

template<typename KeyType, typename ValueType>
class Heap4
{
public:
    using KeyValueType = std::pair< KeyType, ValueType>;

    bool empty() const noexcept{
        return heap.empty();
    }

    void insert(KeyType const & key, ValueType const & value)
    {
        insert(std::pair<KeyType, ValueType>(key, value));
    }

    void insert(KeyValueType const & key_value)
    {
        size_t i, j;
        heap.push_back(key_value);
        i = heap.size()-1;
        j = parent(i);
        while(key_value.first < heap[j].first && i > 0 ){
            swap(heap[i], heap[j]);
            i = j;
            j = parent(i);
        }
    }

    KeyValueType const & peek() const
    {
        if (heap.empty())
            throw std::logic_error("Heap is empty");
        return heap[0];
    }

    KeyValueType pop() noexcept
    {
        KeyValueType v = heap[0];;
        swap(heap[0], heap[heap.size()-1]);
        heap.pop_back();

        size_t j = 0;
        while( child(j, 0) < heap.size() )
        {
            size_t min = child(j, 0);
            for (int i = 1; i < 4; ++i) {
                if (child(j, i) >= heap.size()) break;
                if (heap[min].first > heap[child(j, i)].first)
                    min = child(j, i);
            }
            if ( heap[min].first < heap[j].first )
                swap(heap[min], heap[j]);
            else
                break;
            j = min;

        }

        return v;
    }

    size_t size() const noexcept
    {
        return heap.size();
    }

    template<typename StreamType>
    void print(StreamType & stream) const
    {
        for (size_t i = 0 ; i < heap.size(); ++i )
            stream << heap[i].first << " ";
        stream << std::endl;
        recursivePrint(stream, 0, 0);
    }

private:

    std::vector<KeyValueType> heap;

    size_t parent( size_t k ) const {
        return (k-1)/4;
    }

    size_t child( size_t k, int i ) const {
        return 4*k+i+1;
    }

    template<typename StreamType>
    void recursivePrint(StreamType & stream, size_t k,  int spaces ) const {
        if ( k >= heap.size()) return;
        for ( int i = 0; i < spaces; ++i )
            stream << " ";
        stream << heap[k].first << std::endl;
        for (int i = 0; i < 4; ++i )
            recursivePrint(stream, child(k, i), spaces + 3 );
    }
};

