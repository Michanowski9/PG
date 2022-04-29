import java.util.HashSet;
import java.util.Objects;
import java.util.*;

public class FamilyMember implements Comparable<FamilyMember> {
    private String name;
    private int age;
    private int height;
    private Set<FamilyMember> children;

    private static String mode;

    public static void SetMode(String mode){
        FamilyMember.mode = mode;
    }

    public FamilyMember(String name, int age, int height){
        this.name = name;
        this.age = age;
        this.height = height;

        if(FamilyMember.mode.equals("natural")) {
            children = new TreeSet<>();
        }
        else if(FamilyMember.mode.equals("alternative")){
            children = new TreeSet<>(new FamilyMemberComparator());
        }
        else {
            children = new HashSet<>();
        }
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public int getHeight() {
        return height;
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other == null || this.getClass() != other.getClass()) {
            return false;
        }
        FamilyMember that = (FamilyMember) other;
        return age == that.age && height == that.height && name.equals(that.name) && children.equals(that.children);
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result = 31 * result + age + height;
        return result;
    }

    @Override
    public int compareTo(FamilyMember other) {
        if(age != other.age){
           return age - other.age;
        }
        else if(0 != name.compareTo(other.name)){
            return name.compareTo(other.name);
        }
        else if(height != other.height){
            return height - other.height;
        }
        return 0;
    }

    @Override
    public String toString() {
        return "FamilyMember{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", height=" + height +
                ", children number=" + children.size() +
                '}';
    }

    public void AddChild(FamilyMember child){
        this.children.add(child);
    }

    public void PrintFamily(){
        printFamily(1);
    }

    private void printFamily(int depth){
        String result = "";
        for(int i = 0; i < depth; i++){
            System.out.print("-");
        }
        System.out.println(this);
        for(FamilyMember member : this.children){
            member.printFamily(depth + 1);
        }
    }
}
