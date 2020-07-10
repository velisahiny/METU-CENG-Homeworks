import java.util.concurrent.Semaphore;

public class LightSwitch {
    private int counter;
    private Semaphore mutex;
    public LightSwitch(){
        this.counter = 0;
        this.mutex= new Semaphore(1);
    }
    public void lock(Semaphore sem)  {
        try {
            mutex.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        counter++;
        if(counter==1){
            try {
                sem.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        mutex.release();
    }
    public void unlock(Semaphore  sem){
        try {
            mutex.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        counter--;
        if (counter==0){
            sem.release();
        }
        mutex.release();
    }
}
