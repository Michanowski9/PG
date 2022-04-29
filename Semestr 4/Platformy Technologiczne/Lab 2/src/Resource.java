import java.util.LinkedList;

public class Resource {
    //private final Object inputLock = new Object();
    //private final Object resultLock = new Object();

    LinkedList<Task> inputContainer = new LinkedList<>();
    LinkedList<DoneTask> resultContainer = new LinkedList<>();


    public synchronized Task takeTask() throws InterruptedException {
        while (inputContainer.isEmpty()) {
            wait();
        }
        return inputContainer.pop();
    }

    public synchronized void putTask(Task element) {
        inputContainer.add(element);
        notifyAll();
    }

    public synchronized void putResult(DoneTask element){
        resultContainer.add(element);
    }
}
