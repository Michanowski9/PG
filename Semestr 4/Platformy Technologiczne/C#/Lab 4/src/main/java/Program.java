import magesDB.Mage;
import magesDB.Tower;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.Query;
import java.util.List;

public class Program {
    private final EntityManager em;

    Program(){
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("Mages");
        em = emf.createEntityManager();
    }

    public void addTower(String id, int height ){
        Tower tower = Tower.builder()
                .id(id)
                .height(height)
                .build();
        tower.setMages();
        em.getTransaction().begin();
        em.persist(tower);
        em.getTransaction().commit();
    }
    public void addMage(String id, int level, String towerId){
        Tower tower = em.find(Tower.class, towerId);
        if(tower == null || level > tower.getHeight()){
            System.out.println("Error: Wrong data");
            return;
        }
        Mage mage = Mage.builder()
                .id(id)
                .level(level)
                .tower(tower)
                .build();
        em.getTransaction().begin();
        em.persist(mage);
        tower.addMage(mage);
        em.getTransaction().commit();
    }
    public void removeMage(String id){
        var mage = em.find(Mage.class, id);
        var tower = em.find(Tower.class, mage.getTower().getId());
        tower.removeMage(mage);

        em.getTransaction().begin();
        em.merge(tower);
        em.getTransaction().commit();

    }
    public void removeTower(String id){
        var tower = em.find(Tower.class, id);

        em.getTransaction().begin();
        em.remove(tower);
        em.getTransaction().commit();
    }
    public List<Mage> query(){
        Query q = em.createQuery("SELECT m FROM Mage m WHERE m.tower.id=:id2 AND m.level > (SELECT MIN(m.level) FROM m WHERE m.tower.id=:id1)");
        q.setParameter("id1", "Tower1");
        q.setParameter("id2", "Tower2");
        return q.getResultList();
    }
    public List<Tower> getTowers(){
        return em.createQuery("SELECT p FROM Tower p", Tower.class).getResultList();
    }
    public List<Mage> getMages() {
        return em.createQuery("SELECT p FROM Mage p", Mage.class).getResultList();
    }
}
