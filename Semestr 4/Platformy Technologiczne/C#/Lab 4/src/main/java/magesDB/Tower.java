package magesDB;

import lombok.*;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

@Setter
@Getter
@Builder
@NoArgsConstructor
@AllArgsConstructor
@Entity
public class Tower {
    @Id
    private String id;

    private int height;

    @OneToMany(orphanRemoval = true, cascade = CascadeType.PERSIST, mappedBy = "tower")
    private List<Mage> mages;

    public void setMages(){
        if (mages == null){
            mages = new ArrayList<>();
        }
    }
    public void addMage(Mage mage){
        mages.add(mage);
    }
    public void removeMage(Mage mage) {
        mages.remove(mage);
    }

    @Override
    public String toString() {
        var result = getClass().getSimpleName() + "{id=" + id + ", height=" + height + " mages=";
        if (mages.isEmpty()) {
            result += "null";
        }
        else{
            result += mages.stream().map(Mage::getId).collect(Collectors.joining(","));
        }
        result += "}";
        return result;
    }
}