#include <iostream>
#include <type_traits>
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


template <typename T>
template <bool AddOrRemove>
using Ref = typename Ref_<AddOrRemove>::template type<T>;

template <typename T>
using Res_ = Ref<true>;

//SFINAE Substitution Failure Is Not An Error.
template <bool Check, std::enable_if_t<Check>* = nullptr>
int fun(){ return (int) 0; }
template <bool Check, std::enable_if_t<!Check>* = nullptr>
double fun() {return (double) 1.0; }


namespace Meta{
    //loop
    template <size_t Input>
    constexpr size_t OneCount = (Input % 2) + OneCount<(Input >> 1)>;
    template<> constexpr size_t OneCount<0> = 0;

    //array
    template<size_t... Inputs> constexpr size_t Accumulate = 0;

    template <size_t CurInput, size_t... Inputs>
    constexpr size_t Accumulate<CurInput, Inputs...> = CurInput + Accumulate<Inputs...>;

    template<size_t N>
    constexpr bool is_odd = ((N % 2) == 1);

    template <bool cur, typename TNext>
    constexpr static bool AndValue = false;

    template<typename TNext>
    constexpr static bool AndValue<true, TNext> = TNext::value;

    template <size_t N>
    struct AllOdd_
    {
        constexpr static bool is_cur_odd = is_odd<N>;
        constexpr static bool value = AndValue<is_cur_odd, AllOdd_<N - 1>>;
    };

    template<>
    struct AllOdd_<0>
    {
        constexpr static bool value = false;
    };
    
    //Curiously Recurring Template Pattern, CRTP
    template <typename D> class Base{};
    class Derived : public Base<Derived> {};
}

template <size_t A>
struct Wrap_
{
    template <size_t ID, typename TDummy = void>
    struct imp{
        constexpr static size_t value = ID + imp<ID-1>::value;
    };

    template<typename TDummy>
    struct imp<0, TDummy>
    {
        constexpr static size_t value = 0;
    };

    template <size_t ID>
    constexpr static size_t value = imp<A + ID>::value;
    
};

template <size_t ID>
struct imp{ constexpr static size_t value = ID + imp<ID - 1>::value; };

template<>
struct imp<0>{ constexpr static size_t value = 0; };

template <size_t A>
struct Wrap
{
    template <size_t ID>
    constexpr static size_t value = imp<A + ID>::value;
};


int main(){
    int h = 3;
    cout << h << endl;
    Type_<std::remove_reference, int&>::type d = 4;
    Res_<int>::type a = h;
    h = 5;
    cout << a << endl;
    cout << fun<true>() << endl;

    constexpr size_t res = Meta::OneCount<45>;
    cout << res << endl;

    constexpr size_t ares = Meta::Accumulate<1,2,3,4,5>;
    cout << ares << endl;
    cerr << Wrap_<3>::value<2> << endl;
    cerr << Wrap<10>::value<2> << endl;
    return 0;
}
