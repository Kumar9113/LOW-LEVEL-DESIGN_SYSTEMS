
// //single threaded application
// #include <iostream>
// #include <thread>
// #include <chrono>
// using namespace std;

// class OrderService {
// public:
//     static void placeOrder() {
//         cout << "Placing order..." << endl;

//         sendSMS();
//         cout << "Task 1 done..." << endl;

//         sendEmail();
//         cout << "Task 2 done..." << endl;

//         string eta = calculateETA();

//         cout << "Order placed with ETA: " << eta << endl;
//         cout << "Task 3 done..." << endl;
//     }

// private:
//     static void sendSMS() {
//         this_thread::sleep_for(chrono::seconds(2));
//         cout << "SMS Sent" << endl;
//     }

//     static void sendEmail() {
//         this_thread::sleep_for(chrono::seconds(3));
//         cout << "Email Sent" << endl;
//     }

//     static string calculateETA() {
//         this_thread::sleep_for(chrono::seconds(1));
//         return "2 hours";
//     }
// };

// int main() {
//     OrderService::placeOrder();
//     return 0;
// }


//multi theading

// #include <iostream>
// #include <thread>
// #include <chrono>
// using namespace std;

// class Thread{

//     private:
//         thread t;
//     public:
//     virtual void run() = 0;

//     void start(){
//         th = thread(&Thread::run, this);
//     }

//     void join(){
//         if(th.joinable()){
//             th.join();
//         }
//     }

// };

// class EmailThread : public Thread{
//     public:
//     void run() override{
//         cout<<"Sending Email..."<<endl;
//         this_thread::sleep_for(chrono::seconds(3));
//         cout << "Email Sent" << endl;
//     }
// };
// class SMSThread : public Thread{
//     public:
//     void run() override{
//         cout<<"Sending SMS..."<<endl;
//         this_thread::sleep_for(chrono::seconds(2));
//         cout << "SMS Sent" << endl;
//     }
// };
// int main(){
//     EmailThread emailThread;
//     SMSThread smsThread;

//     emailThread.start();
//     smsThread.start();

//     try{
//         emailThread.join();
//         smsThread.join();
//          cout<<"All tasks done..."<<endl;
//     }
//     catch(const exception& e)
//     {
//         cout<<"Error: "<<e.what()<<endl;
//     }
   
   
//     return 0;
// }

//** */ if you call run method directly then it will execute in the main thread and will not be concurrent. 
//By using start method we are creating a new thread for each task, allowing them to run concurrently.**/


//*** in c++ we don't have a built-in runnable interface like in Java */
/* so we use inheritance and virtual functions */

// #include <iostream>
// #include <thread>
// #include <chrono>
// using namespace std;

// class Runnable{
//     public:
//     virtual void run() = 0;
// };
// class EmailTask  :public Runnable{
    
//     public:
//     void run(){
//         cout<<"Sending Email..."<<endl;
//         this_thread::sleep_for(chrono::seconds(3));
//         cout << "Email Sent" << endl;
//     }
// };
// class SMSTask : public Runnable{
//     public:
//     void run(){
//         cout<<"Sending SMS..."<<endl;
//         this_thread::sleep_for(chrono::seconds(2));
//         cout << "SMS Sent" << endl;
//     }
// };
// int main(){
//     EmailTask email;
//     thread t(&EmailTask::run,&email);
//     t.join();
//     return 0;
// }

//Thread lifecycle management
//new -> start()->runnable->running->blocked/waiting/timed-waiting ->notify/sleep ->runnable->terminated

