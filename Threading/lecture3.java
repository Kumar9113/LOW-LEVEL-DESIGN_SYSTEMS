import java.util.concurrent.*;

class EmailService {

    private static final ExecutorService executor =
            Executors.newFixedThreadPool(10);

    public static void sendEmail(String recipient) {
        executor.submit(() -> {
            System.out.println("Sending email to: " + recipient +
                    " on " + Thread.currentThread().getName());

            try {
                Thread.sleep(2000); // Simulate sending email
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }

            System.out.println("Email sent to: " + recipient);
        });
    }

    public static void main(String[] args) {

        for (int i = 1; i <= 20; i++) {
            sendEmail("user" + i + "@example.com");
        }

        executor.shutdown();
    }
}