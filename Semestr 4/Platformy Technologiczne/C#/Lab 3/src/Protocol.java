public class Protocol {
    private static final int WAITING = 0;
    private static final int GETTING_NUMBER = 1;
    private static final int FINISHED = 2;

    private int currentState = WAITING;
    private int messagesCounter = -1;

    public String processMessages(Message message) {
        messagesCounter--;
        if (messagesCounter == 0) {
            currentState = FINISHED;
        }
        return "Server Received Message ID:" + message.getNumber() + " : " + message.getContent();
    }

    public String processInput(String theInput) {
        if (currentState == WAITING) {
            currentState = GETTING_NUMBER;
            return "Ready";
        }
        else if (currentState == GETTING_NUMBER) {
            messagesCounter = Integer.parseInt(theInput);
            currentState = WAITING;
            return "Ready to receive messages(" + theInput + ")";
        }
        else if (currentState == FINISHED) {
            return "Thread Finished";
        }
        else {
            return "ERROR";
        }
    }
}
