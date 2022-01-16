# APC-Library

Hi all, this is our 2nd Advanced topic for Advanced Programming Concepts. For this topic we are going to dive head-first into two types of standard library types, the `pair` and the `set` type.

We have all used various types of containers provided by the C++ standard library before. These containers are the foundation of data storage and manipulation in our C++ programs.
The C++ standard library takes away the need to set these containers up yourself.

Where this is good on one hand, the fact that these container types are given to us ready to be used can cause you to make mistakes in implementing the containers, as you might not fully understand the basics behind them.

To help you to better understand these container types, we will dive into `std::pair`, `std::vector` and `std::map` of the C++ standard library.
We will be looking at the [GNU ISO C++ Library](https://gcc.gnu.org/onlinedocs/libstdc++/) specifically.
We will first look into how these containers are implemented in the GNU ISO library, after which we will implement our own (basic) version of the containers.

##The GNU ISO C++ Library
###`std::pair`

`std::pair` is a special, simpler type of `std::tuple`. Where std::tuple doesn't have a fixed number of member variables, `std::pair` only ever has two.

The GNU ISO C++ library states the basis of `std::pair` as follows:

```c
  template<typename _T1, typename _T2>
    struct pair
    : private __pair_base<_T1, _T2>
    {
        typedef _T1 first_type;    ///< The type of the `first` member
        typedef _T2 second_type;   ///< The type of the `second` member
    
        _T1 first;                 ///< The first member
        _T2 second;                ///< The second member
        
    public:
        //Many member functions
    };
```
Here, `first` and `second` are the pair's private member variables of types `_T1` and `_T2`. This part of the pair class is still fairly straight forward.

The template shows a struct that holds two variables of types `_T1` and `_T2`. `std::pair` has several basic member functions, such as a number of constructors among which:
```c
#if __cplusplus >= 201103L
        constexpr pair(const pair&) = default;	///< Copy constructor
        constexpr pair(pair&&) = default;		///< Move constructor

        // DR 811.
        template<typename _U1, typename
        enable_if<_PCCP::template
        _MoveCopyPair<true, _U1, _T2>(),
                bool>::type=true>
        constexpr pair(_U1&& __x, const _T2& __y)
                : first(std::forward<_U1>(__x)), second(__y) { }
```
These are a move and copy constructor which take a different pair and construct a pair copying or moving the `first` and `second` of the passed pair. 
There is also a template for a constructor that takes two values and sets up the pair with these two values. 
Where the move and copy constructor are pretty readable, the third constructor has a lot more generic template-shenanigans going on. 
These are necessary to make a universal library that works with all systems, but it may cause a user who wants to take a quick look into the library to understand what is going on to be overwhelmed, and preventing them from properly understanding what is actually going on.

`std::pair` doesn't need any get functions, as the member variables `first` and `second` are public.

Lastly `std::pair` has several swap functions, one of which looks as follows:

```c
    /// Swap the first members and then the second members.
    _GLIBCXX20_CONSTEXPR void
    swap(pair& __p)
    noexcept(__and_<__is_nothrow_swappable<_T1>,
            __is_nothrow_swappable<_T2>>::value)
    {
        using std::swap;
        swap(first, __p.first);
        swap(second, __p.second);
    }
```

As we can see in this example, `std::pair::swap()` makes use of `std::swap()` to swap the member variables of one pair with those of a second pair.
There is a `noexcept()` with some generic statements that may, again, be hard for a novice to understand.

We will guide you through implementing your own simplified version of `std::pair` later on.
But first we will look into `std::vector` and `std::map`.

###`std::vector`

Secondly, we will be looking at `std::vector`. One could say `std::vector` is just a glorified array, which is true to some extent.
`std::vector` makes use of a base struct `_Vector_base` which looks like this:
```c
  template<typename _Tp, typename _Alloc>
    struct _Vector_base
    {
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
	rebind<_Tp>::other _Tp_alloc_type;
      typedef typename __gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer
       	pointer;

      struct _Vector_impl_data
      {
      pointer _M_start;
      pointer _M_finish;
      pointer _M_end_of_storage;
      
      //some functions (bases for copy & swap)
      };
      
      //some functions (bases for std::vector functions)
    }
```

In this base struct, `_M_start`, `_M_finish` and `_M_end_of_storage` are defined. 
These are pointers of type `__gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer`, which can be seen as simple pointers to the first and last element in the array, and to the end of the storage, which can be seen as `_M_start` + `capacity`.
The use of this base struct is quite confusing if you are trying to quickly look into the header to gain some understanding of the logic behind `std::vector`.

Because the data is stored in this `_Vector_base` struct, the class `vector` serves as a wrapper expanding on the functionality of the `_Vector_base` struct.
the `vector` class adds functions like a bunch of constructors, `begin()` and `end()` functions, as well as some data-altering functions such as `insert()`, `erase()`, `push_back()` and `pop_back()`.

All of these functions refer back to the `_Vector_base` struct, as can be seen in the `capacity()` function below:

```c
      size_type
      capacity() const _GLIBCXX_NOEXCEPT
      { return size_type(this->_M_impl._M_end_of_storage
			 - this->_M_impl._M_start); }
```

In our own implementation of the `vector` header, we will get rid of this `_Vector_base` subclass and focus on simplicity to help you understand how `vector` works at its base.


###`std::map`

At its base, `std::map` looks like this:

```c
  template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
	    typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
    class map
    {
    public:
      typedef _Key					key_type;
      typedef _Tp					mapped_type;
      typedef std::pair<const _Key, _Tp>		value_type;
      typedef _Compare					key_compare;
      typedef _Alloc					allocator_type;

    public:
      class value_compare   
      : public std::binary_function<value_type, value_type, bool>
      {
        {...}      
      };

    private:
      /// This turns a red-black tree into a [multi]map.
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
	rebind<value_type>::other _Pair_alloc_type;

      typedef _Rb_tree<key_type, value_type, _Select1st<value_type>,
		       key_compare, _Pair_alloc_type> _Rep_type;

      /// The actual tree structure.
      _Rep_type _M_t;
      
    public:
      //A lot of constructors and functions
```

We can see that `_M_t` is the main member variable of type `_Rep_type`, which is a Red-Black tree made up of `std::pair` nodes.
A Red-Black tree is used in `std::map` because it is a fast type of container that is easy to maintain and to keep sorted.

A place where this is very clearly visible, is in the `begin()` function of `std::map`:

```c
//stl_map.h:
    iterator
    begin() _GLIBCXX_NOEXCEPT
    { return _M_t.begin(); }
      
//stl_tree.h:
    iterator
    begin() _GLIBCXX_NOEXCEPT
    { return iterator(this->_M_impl._M_header._M_left); }
```

Here we can see the first `begin()` function of `std::map` that has to return an iterator to the first element. 
Because the data is stored in a Red-Black tree, the left-most element of this tree has to be returned. 
This is what the second `begin()` function is for. It returns an iterator to the left-most element of the tree.

In our simplified version of the `std::map` we will use a vector instead of a Red-Black tree. 
This way we can make use of our own `mc::vector` and `mc::pair` classes to create the `mc::map`.

##The MC library

To further illustrate, we will now implement the functionalities of `std::pair`, `std::vector` and `std::map` in simple C++ classes ourselves.
This library will be the MC library, named after its creators.


###`mc::pair`

Starting off with `pair`, we will create a header file `pair.h` and create a base class in the `mc` namespace:

```c
namespace mc {

    template <typename T1, typename T2>
    class pair {
        
    public:
        T1 m_first;
        T2 m_second;
    };
    
}
```

We declare a template with typenames `T1` and `T2` for the ability to handle any variable/container type.
We declare two member variables `m_first` and `m_second` of type `T1` and `T2` respectively.
These variables are public just like in the `std::pair` implementation.

Now that we have a place for data to be stored, let's make some constructors that can actually get data in our pair.

####Constructors

Let's start the constructors off with the default and parameterized constructors:

```c
// Default constructor
pair() = default;

// Parameterized constructor
pair(T1 first, T2 second) : 
    m_first {first}, 
    m_second {second}
    {
        //Nothing to do here
    }
```

and a copy constructor:

```c
// Copy constructor
pair(const pair& other):
    m_first{other.m_first},
    m_second{other.m_second}
    {
        //Nothing to do here
    }
```

