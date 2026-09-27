class MyTask implements Runnable {

    @Override
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println(
                Thread.currentThread().getName() + " : " + i
            );

            try {
                Thread.sleep(1000); // 1 second
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class runnable {

    public static void main(String[] args) {

        MyTask task = new MyTask();

        Thread t1 = new Thread(task,"Thread-1");
        Thread t2 = new Thread(task, "Thread-2");

        t1.start();
        t2.start();

        System.out.println("Main thread continues...");
    }
}