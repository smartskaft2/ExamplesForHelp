#pragma once

#include "assert.h"

// tStaticVector<T,N>:
//    Template for declaring a static container with std::vector syntax, 
//    with which is it possible to store the dynamically created objects
//    on the stack instead of the heap.
//
template <typename T, std::size_t N>
class tStaticVector
{
    public:
        // Append objects in aligned storage
        template<typename ...Args> void emplace_back(Args&&... args)
        {
            // Assert valid action
            assert(Size < N);
              
            // Construct value in memory of aligned storage
            new(&Data[Size++]) T(std::forward<Args>(args)...);
        }
        
        // Access an object in aligned storage
        T& operator[](std::size_t position)
        {
            // Note: needs std::launder as of C++17
            return *reinterpret_cast<T*>(&Data[position]);
        }
        
        const T& operator[](std::size_t position) const
        {
            // Note: needs std::launder as of C++17
            return *reinterpret_cast<const T*>(&Data[position]);
        }
        
        // Get size
        std::size_t size() const 
        {
            return Size;
        }
        
        // Get capacity
        std::size_t capacity() const 
        {
            return N;
        }
        
        // Iteratior
        T* begin()
        {
            // Note: needs std::launder as of C++17
            return reinterpret_cast<T*>(&Data[0]);
        }
        
        T* end()
        {
            // Note: needs std::launder as of C++17
            return reinterpret_cast<T*>(&Data[Size]); // Probably Size-1 instead
        }
        
        const T* cbegin() const
        {
            // Note: needs std::launder as of C++17
            return reinterpret_cast<const T*>(&Data[0]);
        }
        
        const T* cend() const
        {
            // Note: needs std::launder as of C++17
            return reinterpret_cast<const T*>(&Data[Size]); // Probably Size-1 instead
        }
        
        // Destructor
        ~tStaticVector()
        {
            for(auto& object : Data) {
                // Note: needs std::launder as of C++17
                reinterpret_cast<T*>(&object)->~T();
            }
        }
        
    private:
        typename std::aligned_storage<sizeof(T), alignof(T)>::type Data[N];
        std::size_t Size = 0;
};
