/**
 * Created by Katya on 15.05.2017.
 */
import java.io.IOException;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.atomic.AtomicInteger;

class CallableSum implements Callable<Integer> {
    List<Integer> array;
    int end;
    int start;
    AtomicInteger sumOfArray;
    CallableSum(List<Integer> array, int start, int end, AtomicInteger sumOfArray) {
        this.array = array;
        this.start = start;
        this.end = end;
        this.sumOfArray = sumOfArray;
    }
    public Integer call() throws Exception {
        if(false) {
            throw new IOException("error during task processing");
        }

        int localSum = 0;
        for (int i = this.start; i < this.end; i++) {
            localSum += array.get(i);
            while (true) {
                int val = sumOfArray.get();
                int newSum = val + array.get(i);
                if (sumOfArray.compareAndSet(val, newSum)) {
                    break;
                }
            }
        }

        return localSum;
    }
}

