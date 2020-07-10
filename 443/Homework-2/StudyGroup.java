public class StudyGroup {
    private String name;
    private Lab lab;
    private LightSwitch groupSwitch;
    public StudyGroup(String name, Lab lab){
        this.name=name;
        this.lab=lab;
        groupSwitch= new LightSwitch();
    }
    public String getName(){
        return name;
    }
    public Lab getLab(){
        return lab;
    }
    public void startStudyingWith(){
        lab.lockTurnstile();
        lock();
        lab.unlockTurnstile();
        lab.lockFull();
        //study here

    }
    public void stopStudyingWith(){
        lab.unlockFull();
        unlock();
    }
    public void lock(){
        groupSwitch.lock(lab.getEmpty());
    }
    public void unlock(){
        groupSwitch.unlock(lab.getEmpty());
    }
}
