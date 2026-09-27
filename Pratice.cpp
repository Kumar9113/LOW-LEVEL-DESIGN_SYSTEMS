#include<bits/stdc++.h>
using namespace std;

class payment{
    public:
    virtual void pay()=0;
}
class phonePay:public payment{
    public:
    void pay(){
        count<<"pay bye phonePay"<<endl;
    }
}

class factory{
    public:
    virtual payment* getInstance()=0;
}