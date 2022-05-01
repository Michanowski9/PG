import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client {
    private static final String hostName = "localhost";
    private static final int portNumber = 4444;

    public static void main(String[] args) {
        try(
                Socket socket = new Socket(hostName, portNumber);
                ObjectInputStream objectInputStream = new ObjectInputStream(socket.getInputStream());
                ObjectOutputStream objectOutputStream = new ObjectOutputStream(socket.getOutputStream())
        ) {
            Scanner input = new Scanner(System.in);

            //Ready
            System.out.println("Server: " + objectInputStream.readObject());

            //Get number of ints
            int n = Integer.parseInt(input.nextLine());
            objectOutputStream.writeObject(n);

            //Ready for messages
            System.out.println("Server: " + objectInputStream.readObject());

            //Sending and receiving messages
            for (int i = 0; i < n; i++){
                objectOutputStream.writeObject(new Message(i, "My message to server"));
                System.out.println("Server: " + objectInputStream.readObject());
            }

            //Finished connection
            System.out.println("Server: " + objectInputStream.readObject());
        }
        catch (UnknownHostException e) {
            System.err.println("Unknown host " + hostName);
            System.exit(1);
        }
        catch (IOException e) {
            System.err.println("Can't connect to " + hostName);
            System.exit(1);
        }
        catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }


}
