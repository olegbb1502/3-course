/**
 * Created by Katya on 15.05.2017.
 */
import java.io.IOException;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.atomic.AtomicInteger;


class CallableCount implements Callable<Integer> {
    List<Integer> array;
    int end;
    int start;
    AtomicInteger countOfEven;

    CallableCount(List<Integer> array, int start, int end, AtomicInteger countOfEven) {
        this.array = array;
        this.start = start;
        this.end = end;
        this.countOfEven = countOfEven;
    }

    public Integer call() throws Exception {
        if(false) {
            throw new IOException("error during task processing");
        }
        int localCount = 0;
        int currentValue = 0;

        for (int i = this.start; i < this.end; i++) {
            currentValue = array.get(i);
            if (currentValue % 2 == 0) {
                localCount += 1;
                while (true) {
                    int val = countOfEven.get();
                    int incremented = val + 1;
                    if (countOfEven.compareAndSet(val, incremented)) {
                        break;
                    }
                }
            }
        }

        return localCount;
    }
}

