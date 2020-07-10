import java.util.concurrent.Semaphore;

public class Lab {
    private String name;
    private int capacity;
    private Semaphore empty;
    private Semaphore full ;
    private Semaphore turnstile ;
    public Lab(String name, int capacity){
        this.name=name;
        this.capacity=capacity;
        empty = new Semaphore(1);
        full = new Semaphore(capacity);
        turnstile= new Semaphore(1);
    }
    public String getName(){
        return name;
    }
    public int getCapacity(){
        return capacity;
    }
    public Semaphore getEmpty(){
        return empty;
    }
    public void lockFull(){
        try {
            full.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    public void unlockFull(){
        full.release();
    }
    public void lockTurnstile(){
        try {
            turnstile.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    public void unlockTurnstile(){
        turnstile.release();
    }
}
