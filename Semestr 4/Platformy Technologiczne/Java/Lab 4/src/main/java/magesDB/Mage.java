package magesDB;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.ManyToOne;


@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
@Entity
public class Mage {
    @Id
    private String id;

    private int level;

    @ManyToOne
    private Tower tower;

    @Override
    public String toString() {
        return "Mage{" +
                "id='" + id + '\'' +
                ", level=" + level +
                ", tower=" + tower.getId() +
                '}';
    }
}