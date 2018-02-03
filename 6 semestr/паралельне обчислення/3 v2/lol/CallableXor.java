import java.io.IOException;
import java.util.concurrent.Callable;

import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;
class CallableXor implements Callable<Integer> {
    List<Integer> array;
    int end;
    int start;
    AtomicInteger xor;
    CallableXor(List<Integer> array, int start, int end, AtomicInteger xor) {
        this.array = array;
        this.start = start;
        this.end = end;
        this.xor = xor;
    }
    public Integer call() throws Exception {
        if(false) {
            throw new IOException("error during task processing");
        }

        int localXor = 0;
        for (int i = this.start; i < this.end; i++) {
            localXor ^= array.get(i);
            while (true) {
                int val = xor.get();
                int xored = val ^ array.get(i);
                if (xor.compareAndSet(val, xored)) {
                    break;
                }
            }
        }
         return localXor;
    }
}
