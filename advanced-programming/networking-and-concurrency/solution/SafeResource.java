import java.io.IOException;
import java.util.concurrent.locks.ReentrantLock;


import java.util.concurrent.locks.Lock;


import java.util.ArrayList;
import java.util.List;


public class Makhzan {
    private final ArrayList<Object> listOfObj = new ArrayList<>();
    private final Lock lockedItem = new ReentrantLock();

    public void addNewObject(Object object) {
        lockedItem.lock();

        listOfObj.add(object);

        lockedItem.unlock();

        synchronized (this) {
            notifyAll();
        }
    }

    public Object getNextObject() {
        lockedItem.lock();

        while (listOfObj.isEmpty()) {
            try {
                synchronized (this) {
                    wait();
                }

            }
            catch (InterruptedException e) {
                new RuntimeException(e).getMessage();
            }

            return listOfObj.remove(0);
        }

        lockedItem.unlock();
        return null;
    }

    public List<Object> getObjectList() {
        lockedItem.lock();

        try {
            return new ArrayList<>(listOfObj);
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
         finally {
            lockedItem.unlock();
        }
    }
}
