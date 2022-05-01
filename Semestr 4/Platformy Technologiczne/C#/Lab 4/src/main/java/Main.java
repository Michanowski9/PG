import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;

public class Main {
    public static void main(String[] args) throws IOException {
        //turning off INFO logs from hibernate
        java.util.logging.Logger.getLogger("org.hibernate").setLevel(java.util.logging.Level.OFF);

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        Program manager = new Program();
        fillDB(manager);

        while(true){
            System.out.print("Enter command: ");
            String command = reader.readLine();
            switch (command){
                case "add":
                    addDB(manager, reader);
                    break;
                case "print":
                    printDB(manager);
                    break;
                case "remove":
                    removeDB(manager, reader);
                    break;
                case "query":
                    queryDB(manager);
                    break;
                case "quit":
                    return;
            }
        }
    }

    public static void fillDB(Program p){
        //Towers
        p.addTower("Tower1", 5);
        p.addTower("Tower2", 6);
        p.addTower("Tower3", 3);

        //Mages
        p.addMage("Mage1", 3, "Tower1");
        p.addMage("Mage2", 2, "Tower1");
        p.addMage("Mage3", 4, "Tower1");
        p.addMage("Mage4", 5, "Tower2");
        p.addMage("Mage5", 1, "Tower2");
        p.addMage("Mage6", 6, "Tower2");

        //Wrong level
        p.addMage("Mage7", 100, "Tower2");
        p.addMage("Mage8", 1, "Tower4");
    }

    public static void addDB(Program p, BufferedReader r) throws IOException {
        System.out.print("Enter data: ");
        String data = r.readLine();
        var temp = data.split(",");
        if (Objects.equals(temp[0], "mage")){
            p.addMage(temp[1], Integer.parseInt(temp[2]), temp[3]);
        }
        else if(Objects.equals(temp[0], "tower")){
            p.addTower(temp[1], Integer.parseInt(temp[2]));
        }
    }
    public static void removeDB(Program p, BufferedReader r) throws IOException {
        System.out.print("Mage or Tower: ");
        String option = r.readLine();

        System.out.print("Enter id: ");
        String id = r.readLine();

        if(option.equals("mage")){
            p.removeMage(id);
        }
        else if(option.equals("tower")){
            p.removeTower(id);
        }
    }
    public static void queryDB(Program p){
        var q = p.query();
        if(q.isEmpty()){
            System.out.println("no results");
        }
        else {
            for (var m : q) {
                System.out.println(m);
            }
        }
    }
    public static void printDB(Program p) {
        var towers = p.getTowers();
        var mages = p.getMages();

        for(var t : towers) {
            System.out.println("\t" + t);
        }
        for(var m : mages) {
            System.out.println("\t\t" + m);
        }
    }

}
