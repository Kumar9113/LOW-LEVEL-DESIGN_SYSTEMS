/*1.why not create threads directly?*/

#include <iostream>
#include <thread>
using namespace std;
/*1.why not create threads directly?*/
/* creation a lot of threads is resource-intensive and can lead to performance issues */

class RideMatch{

    public:
    void rideMatch(){
        cout<<"Matching ride..."<<endl;
       
        cout<<"Ride Matched!"<<endl;
       
    }

};
int main(){
   RideMatch r1;
   RideMatch r2;
   cout<<"r1 is running"<<endl;
   thread t1(&RideMatch::rideMatch, &r1);
   cout<<"r2 is running"<<endl;
  
    thread t2(&RideMatch::rideMatch, &r2);
    
    t1.join();
    t2.join();
    
   
   
   
    return 0;
}

/* creation a lot of threads is resource-intensive and can lead to performance issues */
/* thread explosion - os cannot handle a large number of  requests  at same time*/
/* memory overhead - each thread requires its own stack space */
/*thread leakage - if threads are not properly managed, they can accumulate and consume system resources*/
/*context switching overhead - frequent context switches between threads can impact performance*/

/*solution: use thread pool*/
/*use a pool of worker threads to execute tasks*/
/* introduce execution framework*/



