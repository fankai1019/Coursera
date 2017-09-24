#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <functional>

using namespace std;
struct StringPtrCompare:public binary_function<const string*, const string*, bool>{
    bool operator()(const string* ps1, const string* ps2){
        return *ps1<*ps2;
//        return ps1<ps2;
    }
};

struct StringPtrCompare2{
    bool operator()(const string* ps1, const string* ps2)const{
        return *ps1<*ps2;
    }
};

int main(){
    // the default value of the second parameter bellow is std::less() which will delegate to operator<. We can also pass a functor class here.
    set<string*, StringPtrCompare> ssp;
    ssp.insert(new string("Anteater"));
    ssp.insert(new string("Wombat"));
    ssp.insert(new string("Lemur"));
    ssp.insert(new string("Penguin"));
    for(set<string*>::iterator it = ssp.begin(); it!=ssp.end();++it)
        cout<<**it<<" ";
    cout<<endl;
    for_each(ssp.begin(), ssp.end(), [](string* ptr){cout<<*ptr<<" ";});
    cout<<endl;

    return 0;
}

