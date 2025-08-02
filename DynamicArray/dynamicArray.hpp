#pragma once
#include <stdexcept>
#include <memory>    
#include <algorithm>  

using namespace std;

namespace TK
{
    template<typename T>
    class DynamicArray
    {
    private:
        T* m_data = nullptr;
        size_t m_size = 0;
        size_t m_capacity = 0;

        static constexpr size_t DEFAULT_CAPACITY = 10;

        void reallocate(size_t newCapacity)
        {
            T* newData = new T[newCapacity];
            for (size_t i = 0; i < m_size; ++i)
                newData[i] = move(m_data[i]);

            delete[] m_data;
            m_data = newData;
            m_capacity = newCapacity;
        }

     
        void ensure_capacity()
        {
            if (m_size >= m_capacity)
            {
                size_t newCapacity = (m_capacity == 0) ? DEFAULT_CAPACITY : m_capacity * 2;
                if (newCapacity == m_capacity) newCapacity++; 
                reallocate(newCapacity);
            }
        }

    public:
        
        DynamicArray() : m_data(new T[DEFAULT_CAPACITY]), m_size(0), m_capacity(DEFAULT_CAPACITY) {}

        
        DynamicArray(size_t initialCapacity) : m_data(new T[initialCapacity]), m_size(0), m_capacity(initialCapacity) {}

        
        DynamicArray(size_t count, const T& value) : m_data(new T[count]), m_size(count), m_capacity(count)
        {
            for (size_t i = 0; i < count; ++i)
                m_data[i] = value;
        }

        
        DynamicArray(const DynamicArray& other) : m_data(new T[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity)
        {
            copy(other.m_data, other.m_data + other.m_size, m_data);
        }

       
        DynamicArray& operator=(const DynamicArray& other)
        {
            if (this != &other)
            {
                T* newData = new T[other.m_capacity];
                copy(other.m_data, other.m_data + other.m_size, newData);

                delete[] m_data;
                m_data = newData;
                m_size = other.m_size;
                m_capacity = other.m_capacity;
            }
            return *this;
        }

        
        ~DynamicArray()
        {
            delete[] m_data;
        }

      
        void push_back(const T& value)
        {
            ensure_capacity();
            m_data[m_size++] = value;
        }

        void push_back(T&& value)
        {
            ensure_capacity();
            m_data[m_size++] = move(value);
        }

      
        void pop_back()
        {
            if (m_size == 0) throw underflow_error("DynamicArray is empty");
            --m_size;
        }

       
        T& at(size_t index)
        {
            if (index >= m_size) throw out_of_range("Index out of range");
            return m_data[index];
        }

        const T& at(size_t index) const
        {
            if (index >= m_size) throw out_of_range("Index out of range");
            return m_data[index];
        }

      
        T& operator[](size_t index) { return m_data[index]; }
        const T& operator[](size_t index) const { return m_data[index]; }


        T& front()
        {
            if (m_size == 0) throw underflow_error("DynamicArray is empty");
            return m_data[0];
        }

        const T& front() const
        {
            if (m_size == 0) throw underflow_error("DynamicArray is empty");
            return m_data[0];
        }

        T& back()
        {
            if (m_size == 0) throw underflow_error("DynamicArray is empty");
            return m_data[m_size - 1];
        }

        const T& back() const
        {
            if (m_size == 0) throw underflow_error("DynamicArray is empty");
            return m_data[m_size - 1];
        }

       
        size_t size() const { return m_size; }
        size_t capacity() const { return m_capacity; }
        bool empty() const { return m_size == 0; }

        void reserve(size_t newCapacity)
        {
            if (newCapacity > m_capacity)
                reallocate(newCapacity);
        }

        void clear() { m_size = 0; }

        size_t memory_usage() const
        {
            return m_capacity * sizeof(T);
        }

        T* data_ptr() { return m_data; }
        const T* data_ptr() const { return m_data; }

        void dump() const 
        {
            cout << "DynamicArray Dump:" << endl;
            cout << " Size:     " << m_size << endl;
            cout << " Capacity: " << m_capacity << endl;
            cout << " Elements: [";
            for (size_t i = 0; i < m_size; ++i) 
            {
                cout << m_data[i];
                if (i != m_size - 1)
                    cout << ", ";
            }
            cout << "]" << endl;
        }
    };
}