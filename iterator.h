#include <stdlib.h>

namespace homemade {

    template <typename T>
    class Iterator;

    template <typename T>
    class Vector {
        template <typename S>
        friend class Iterator;

        private:
            T* _array;
            size_t _capacity;
            size_t _size;

        public:
            Vector(size_t capacity, size_t size=0) : _capacity(capacity), _size(size) {
                _array = new T[capacity];
            }

            Vector(const Vector& vector) : _capacity(vector.capacity), _size(vector.size) {
                _array = new T[vector._capacity];
                for (unsigned i=0; i<_size; i++) {
                    _array[i] = vector[i];
                }
            }

            Vector<T>& operator=(const Vector& vector) {
                if (this != &vector) {
                    delete [] _array;
                    _capacity = vector.capacity;
                    _size = vector.size;
                    _array = new T[vector._capacity];
                    for (unsigned i=0; i<_size; i++) {
                        _array[i] = vector[i];
                    }
                }
                return *this;
            }

            ~Vector() {
                delete [] _array;
            }

            void push_back(const T& elem) {
                _array[_size++] = elem;
            }

            const T& operator[](unsigned idx) {
                return _array[idx];
            }

            Iterator<T> begin() {
                return Iterator<T>(*this);
            }

            Iterator<T> end() {
                return Iterator<T>(*this, _size);
            }
    };

    template <typename T>
    class Iterator {
        private:
            Vector<T>& _vector;
            unsigned _idx;

        public:
            Iterator(Vector<T>& vector, unsigned idx=0) : _vector(vector), _idx(idx) {

            }

            const T& next() {
                if (hasNext()) {
                    ++_idx;
                    return _vector[_idx-1];
                }
                throw std::out_of_range("beyond iterator's scope");
            }

            bool hasNext() const {
                return _idx + 1 <= _vector._size;
            }
            
            const T& operator*() const {
                return _vector[_idx];
            }

            Iterator& operator++() {
                if (operator==(_vector.end())) {
                    throw std::out_of_range("beyond iterator's scope");
                }
                ++_idx;
                return *this;
            }

            Iterator operator++(int) {
                if (operator==(_vector.end())) {
                    throw std::out_of_range("beyond iterator's scope");
                }
                Iterator<T> tmp(*this);
                operator++();
                return tmp;
            }

            bool operator==(const Iterator<T>& it) {
                return (&this->_vector == &it._vector) && (this->_idx == it._idx);
            }

            bool operator!=(const Iterator<T>& it) {
                return !operator==(it);
            }
    };
};

