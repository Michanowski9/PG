import java.io.Serializable;

public class Message implements Serializable {
    private final int number;
    private final String content;

    public Message(int i, String message) {
        this.number = i;
        this.content = message;
    }

    public int getNumber() {
        return number;
    }

    public String getContent() {
        return content;
    }
}
