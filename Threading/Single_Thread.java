class MyTask extends Thread{
    void task1(){
        System.out.println("This is task 1.");
    }
    void task2(){
        System.out.println("This is task 2.");
    }
    void task3(){
        System.out.println("This is task 3.");
    }
    @Override
    public void run(){
        task1();
        task2();
        task3();
    }
}

public class Single_Thread{
    public static void main(){
        System.out.println("This is a single thread program.");
        MyTask t1 = new MyTask();
        t1.start();
    }
}