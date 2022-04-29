import java.io.IOException;
import java.net.ServerSocket;
import java.util.Scanner;

public class Server {
    public static final int portNumber = 4444;
    public static int id = 0;

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(portNumber)){
            while(true) {
                new Thread(new ServerThread(serverSocket.accept(), id)).start();
                Server.id++;
            }
        } catch (IOException e) {
            System.err.println("Problems with listening on port " + portNumber);
            System.exit(2);
        }
    }
}
