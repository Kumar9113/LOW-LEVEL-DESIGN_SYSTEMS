
class Task1 extends Thread{
    public void run(){
        for(int i=0; i<5; i++){
            System.out.println("Task 1 is running.");
        }
    }
};

class Task2 extends Thread{
    public void run(){
        for(int i=0; i<5; i++){
            System.out.println("Task 2 is running.");
        }
    }
}

public class Multi_Thread {
    public static void main(){
        System.out.println("This is a multi thread program.");
        Task1 t1 = new Task1();
        Task2 t2 = new Task2();

        t1.start();
        t2.start();
    }
}
