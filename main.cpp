#include <iostream>
using namespace std;

template <typename T>
struct Fun_{ using type = T; };
template <>
struct Fun_<int> { 
    using type = unsigned int; 
    using reference_type = int&;
    using const_reference_type = const int&;
    using value_type = int;
};

template <typename T>
using Fun = typename Fun_<T>::type;

template <template <typename> class T1, typename T2>
struct Type_{ using type = typename T1<T2>::type; };


template <bool AddOrRemoveRef> struct Ref_;

template <>
struct Ref_<true>{
    template <typename T>
    using type = std::add_lvalue_reference<T>;
};

template <>
struct Ref_<false>{
    template <typename T>
    using type = std::remove_reference<T>;
};



template <bool AddOrRemove, typename T>
using Ref = typename Ref_<AddOrRemove>::template type<T>;

template <typename T>
using Res_ = Ref<true>;

int main(){
    Fun<int> h = 3;
    cout << h << endl;
    Type_<std::remove_reference, int&>::type d = 4;
    return 0;
}
