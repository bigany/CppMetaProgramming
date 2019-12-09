#include <boost/foreach.hpp>
#include <boost/assign.hpp>

#include <iostream>

using namespace std;
void foreach_test(){
    using namespace boost::assign;

    vector<int> v = (list_of(1), 2, 3, 4, 5);

    BOOST_FOREACH(auto& x, v){
        cout << x << ", ";
    }
    cout << endl;

    BOOST_REVERSE_FOREACH(auto& x, v){
        cout << x << ", ";
    }
    cout << endl;
}

int main(){

    foreach_test();
    return 0;
}
