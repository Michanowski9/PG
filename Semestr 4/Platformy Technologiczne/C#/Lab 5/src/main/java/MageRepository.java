import lombok.Builder;

import java.util.Collection;
import java.util.HashSet;
import java.util.Objects;
import java.util.Optional;


public class MageRepository {
    private final Collection<Mage> collection;

    public MageRepository() {
        this.collection = new HashSet<Mage>();
    }

    public Optional<Mage> find(String name){
        return collection.stream().filter(e-> Objects.equals(e.getName(), name)).findAny();
    }
    public void delete(String name){
        if(!collection.removeIf(e -> Objects.equals(e.getName(), name))){
            throw new IllegalArgumentException();
        }
    }
    public void save(Mage mage){
        if(collection.contains(mage)){
            throw new IllegalArgumentException();
        }
        collection.add(mage);
    }
}
