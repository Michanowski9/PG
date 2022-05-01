import org.junit.jupiter.api.Test;

import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

public class MageControllerTest {
    @Test
    public void delete_notExistingElement_notFound(){
        MageRepository repository = mock(MageRepository.class);
        MageController mageController = new MageController(repository);
        doThrow(new IllegalArgumentException()).when(repository).delete("sth");

        String result = mageController.delete("sth");

        assertEquals("not found",result);
    }
    @Test
    public void delete_existingElement_done(){
        MageRepository repository = mock(MageRepository.class);
        MageController mageController = new MageController(repository);
        doNothing().when(repository).delete("mage1");

        String result = mageController.delete("mage1");

        assertEquals("done",result);
    }
    @Test
    public void find_notExistingElement_notFound(){
        MageRepository repository = mock(MageRepository.class);
        MageController mageController = new MageController(repository);
        doReturn(Optional.empty()).when(repository).find("sth");

        String result = mageController.find("sth");

        assertEquals("not found",result);
    }
    @Test
    public void find_existingElement_representation(){
        MageRepository repository = mock(MageRepository.class);
        MageController mageController = new MageController(repository);
        doReturn(Optional.of(new Mage("mage", 1))).when(repository).find("mage");

        String result = mageController.find("mage");
        Mage wanted = new Mage("mage", 1);

        assertEquals(wanted.toString(),result);
    }
    @Test
    public void save_correctInput_done(){
        MageRepository repository = mock(MageRepository.class);
        MageController mageController = new MageController(repository);
        doNothing().when(repository).save(new Mage("mage",1));

        String result = mageController.save("mage","1");

        assertEquals("done",result);
    }
    @Test
    public void save_exsistInRepo_badRequest(){
        MageRepository repository = mock(MageRepository.class);
        MageController mageController = new MageController(repository);
        doThrow(new IllegalArgumentException()).when(repository).save(new Mage("mage",1));

        String result = mageController.save("mage","1");

        assertEquals("bad request",result);
    }
}