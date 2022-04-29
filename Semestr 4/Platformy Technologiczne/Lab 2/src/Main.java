import java.util.Scanner;

public class Main {

    private static final int THREADS_NUMBER = 2;

    public static void main(String[] args) throws InterruptedException {

        Resource resource = new Resource();
        Thread[] calculator = new Thread[THREADS_NUMBER];

        //adding tasks
        for(int i = 1; i < 5; i++){
            Task task = new Task(i);
            System.out.println(
                    "putting task id:" + task.getJobId() +
                    " prec:" + task.getPrecision()
            );
            resource.putTask(task);
        }

        for(int i = 0; i < THREADS_NUMBER; i++){
            calculator[i] = new Thread(new Calculator(resource));
            calculator[i].start();
        }

        //program loop - getting input
        while(true) {
            Scanner input = new Scanner(System.in);
            int inputNumber = input.nextInt();
            if(inputNumber == 0){
                break;
            }
            resource.putTask(new Task(inputNumber));
        }

        for(Thread thread : calculator){
            thread.interrupt();
            thread.join();
            System.out.println("thread closed");
        }


    }
}
