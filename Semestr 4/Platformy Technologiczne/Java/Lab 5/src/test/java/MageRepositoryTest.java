import org.junit.jupiter.api.Test;

import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;

public class MageRepositoryTest {
    @Test
    public void delete_noElementToDelete_Exception(){
        MageRepository mageRepository = new MageRepository();

        Exception exception = assertThrows(RuntimeException.class, ()-> mageRepository.delete("sth"));

        assertSame(exception.getClass(), IllegalArgumentException.class);
    }
    @Test
    public void find_noElementToFind_EmptyOptional(){
        MageRepository mageRepository = new MageRepository();

        assertSame(mageRepository.find("sth"), Optional.empty());
    }
    @Test
    public void find_oneElementToFind_element(){
        MageRepository mageRepository = new MageRepository();

        mageRepository.save(new Mage("mage", 1));
        var result = mageRepository.find("mage");
        var optional = Optional.of(new Mage("mage", 1));

        assertTrue(result.isPresent());
        assertEquals(result.get(), optional.get());
    }
    @Test
    public void save_sameElementExists_Exception(){
        MageRepository mageRepository = new MageRepository();
        mageRepository.save(new Mage("mage",1));

        Exception exception = assertThrows(RuntimeException.class, ()-> mageRepository.save(new Mage("mage",1)));

        assertSame(exception.getClass(), IllegalArgumentException.class);
    }

}
