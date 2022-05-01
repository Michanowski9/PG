public class MageController {
    private final MageRepository repository;

    public MageController(MageRepository repository){
        this.repository = repository;
    }
    public String find(String name){
        var result = repository.find(name);
        if (result.isEmpty()){
            return "not found";
        }
        return result.get().toString();
    }
    public String delete(String name){
        try {
            repository.delete(name);
        } catch (IllegalArgumentException e){
            return "not found";
        }
        return "done";
    }
    public String save(String name,String level){
        try{
            repository.save(new Mage(name,Integer.parseInt(level)));
        }catch (IllegalArgumentException e){
            return "bad request";
        }
        return "done";
    }
}
