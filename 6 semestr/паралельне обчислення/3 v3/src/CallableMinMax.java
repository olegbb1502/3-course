/**
 * Created by Katya on 15.05.2017.
 */
import java.io.IOException;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.atomic.AtomicReference;


class CallableMinMax implements Callable<MinMax[]> {
    List<Integer> array;
    int end;
    int start;
    AtomicReference<MinMax> minAtomic;
    AtomicReference<MinMax> maxAtomic;

    CallableMinMax(List<Integer> array, int start, int end,
                   AtomicReference<MinMax> minAtomic, AtomicReference<MinMax> maxAtomic) {
        this.array = array;
        this.start = start;
        this.end = end;
        this.minAtomic = minAtomic;
        this.maxAtomic = maxAtomic;
    }

    public MinMax[] call() throws Exception {
        if(false) {
            throw new IOException("error during task processing");
        }

        int minIndex = start;
        int maxIndex = start;

        for (int i = start; i < end; i++) {
            if (array.get(minIndex) > array.get(i)) {
                minIndex = i;
            }

            while (true) {
                MinMax minVal = minAtomic.get();
                if (minVal.getValue() > array.get(i)) {
                    MinMax newMin = new MinMax("Min", array.get(i), i);
                    if (minAtomic.compareAndSet(minVal, newMin)) {
                        break;
                    }
                } else {
                    break;
                }
            }


            if (array.get(maxIndex) < array.get(i)) {
                maxIndex = i;
            }

            while (true) {
                MinMax maxVal = maxAtomic.get();
                if (maxVal.getValue() < array.get(i)) {
                    MinMax newMax = new MinMax("Max", array.get(i), i);
                    if (maxAtomic.compareAndSet(maxVal, newMax)) {
                        break;
                    }
                } else {
                    break;
                }
            }
        }

        MinMax minMax[] = new MinMax[2];
        minMax[0] = new MinMax("Min", array.get(minIndex), minIndex);
        minMax[1] = new MinMax("Max", array.get(maxIndex), maxIndex);


        return minMax;
    }
}

