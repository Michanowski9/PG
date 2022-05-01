import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class ServerThread implements Runnable {
    private final Socket socket;
    private int id = 0;

    public ServerThread(Socket socket, int id) {
        this.socket = socket;
        this.id = id;
    }

    @Override
    public void run() {
        System.out.println("Client(" + this.id + ") thread starting");

        try (
                ObjectOutputStream objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
                ObjectInputStream objectInputStream = new ObjectInputStream(socket.getInputStream())
        ) {
            Protocol protocol = new Protocol();

            //Ready
            objectOutputStream.writeObject(protocol.processInput(null));

            //Get number of messages
            int messagesNumber = Integer.parseInt(objectInputStream.readObject().toString());
            objectOutputStream.writeObject(protocol.processInput(Integer.toString(messagesNumber)));

            for (int i = 0; i < messagesNumber; i++) {
                Message inputMessage = (Message) objectInputStream.readObject();
                System.out.println("Message incoming from Client(" + this.id + "): " + inputMessage.getContent());
                objectOutputStream.writeObject(protocol.processMessages(inputMessage));
            }

            //Finished connection
            objectOutputStream.writeObject(protocol.processInput(null));

            System.out.println("Client(" + this.id + ") thread closing");
            socket.close();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
