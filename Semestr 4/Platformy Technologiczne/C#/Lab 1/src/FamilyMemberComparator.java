package Program;

import java.util.Comparator;

public class FamilyMemberComparator implements Comparator<FamilyMember> {
    @Override
    public int compare(FamilyMember o1, FamilyMember o2) {
        if(0 != o1.getName().compareTo(o2.getName())){
            return o1.getName().compareTo(o2.getName());
        }
        else if(o1.getHeight() != o2.getHeight()){
            return o1.getHeight() - o2.getHeight();
        }
        else if(o1.getAge() != o2.getAge()){
            return o1.getAge()-o2.getAge();
        }
        return 0;
    }
}
