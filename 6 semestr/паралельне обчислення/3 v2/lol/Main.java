import java.util.concurrent.*;
import java.io.IOException;

import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

class Main {
    public static int SIZE = 100;
    public static int NUMBER_OF_PARTS = 5; // К-ть частин на які розбиваємо масив

    public static void waite(Future futureArray[]) {
        for (int i = 0; i < NUMBER_OF_PARTS; i++) {
            while (!futureArray[i].isDone()) {
            }
        }
    }

    public static int countOfEvenByAtomicAndFuture(List<Integer> array, ExecutorService ex) {
        Future<Integer> countOfEvenResults[] = new Future[NUMBER_OF_PARTS];
        AtomicInteger countOfEvent = new AtomicInteger(0);

        for(int i = 0; i < NUMBER_OF_PARTS; i++) {
            countOfEvenResults[i] = ex.submit(new CallableCount(array,
                    SIZE / NUMBER_OF_PARTS * i,
                    i == NUMBER_OF_PARTS - 1 ? SIZE : SIZE / NUMBER_OF_PARTS * (i + 1), countOfEvent));
        }

        waite(countOfEvenResults);

        try {
            //Отримуэмо результат
            int count = 0;
            for (int i = 0; i < NUMBER_OF_PARTS; i++) {
                count += countOfEvenResults[i].get();
            }
            System.out.println("Count of even by futures results: " + count);

        } catch (InterruptedException ie) {
            ie.printStackTrace(System.err);
        } catch (ExecutionException ee) {
            ee.printStackTrace(System.err);
        }

        System.out.println("Count of even result by Atomic: " + countOfEvent.get());

        return 0;
    }

    public static int sumOfArrayByAtomicAndFuture(List<Integer> array, ExecutorService ex) {
        Future<Integer> sumResults[] = new Future[NUMBER_OF_PARTS];
        AtomicInteger sumOfArray = new AtomicInteger(0);

        for(int i = 0; i < NUMBER_OF_PARTS; i++) {
            sumResults[i] = ex.submit(new CallableSum(array,
                    SIZE / NUMBER_OF_PARTS * i,
                    i == NUMBER_OF_PARTS - 1 ? SIZE : SIZE / NUMBER_OF_PARTS * (i + 1), sumOfArray));
        }

        waite(sumResults);

        try {
            //Отримуэмо результат
            int sum = 0;
            for (int i = 0; i < NUMBER_OF_PARTS; i++) {
                sum += sumResults[i].get();
            }

            System.out.println("Sum result by futures results: " + sum);
        } catch (InterruptedException ie) {
            ie.printStackTrace(System.err);
        } catch (ExecutionException ee) {
            ee.printStackTrace(System.err);
        }

        System.out.println("Sum result by Atomic: " + sumOfArray.get());

        return 0;
    }

    public static int xorOfArrayByAtomicAndFuture(List<Integer> array, ExecutorService ex) {
        Future<Integer> xorResults[] = new Future[NUMBER_OF_PARTS];
        AtomicInteger xorResult = new AtomicInteger(0);

        for(int i = 0; i < NUMBER_OF_PARTS; i++) {
            xorResults[i] = ex.submit(new CallableXor(array,
                    SIZE / NUMBER_OF_PARTS * i,
                    i == NUMBER_OF_PARTS - 1 ? SIZE : SIZE / NUMBER_OF_PARTS * (i + 1),xorResult));
        }

        waite(xorResults);

        try {
            //Отримуэмо результат
            int xor = 0;
            for (int i = 0; i < NUMBER_OF_PARTS; i++) {
                xor ^= xorResults[i].get();
            }

            System.out.println("Xor result by futures: " + xor);

        } catch (InterruptedException ie) {
            ie.printStackTrace(System.err);
        } catch (ExecutionException ee) {
            ee.printStackTrace(System.err);
        }

        System.out.println("Xor result by atomic: " + xorResult.get());

        return 0;
    }

    public static int minMaxOfArrayByAtomicAndFuture(List<Integer> array, ExecutorService ex) {
        Future<MinMax[]> minMaxResults[] = new Future[NUMBER_OF_PARTS];
        MinMax ob = new MinMax();
        AtomicReference<MinMax> minAtomic = new AtomicReference<>(new MinMax("Min", array.get(0), 0));
        AtomicReference<MinMax> maxAtomic = new AtomicReference<>(new MinMax("Max", array.get(0), 0));

        // Calculate Min and Max
        for(int i = 0; i < NUMBER_OF_PARTS; i++) {
            minMaxResults[i] = ex.submit(new CallableMinMax(array,
                    SIZE / NUMBER_OF_PARTS * i,
                    i == NUMBER_OF_PARTS - 1 ? SIZE : SIZE / NUMBER_OF_PARTS * (i + 1),
                    minAtomic, maxAtomic));
        }

        waite(minMaxResults);

        try {
            //Отримуэмо результат
            int min = minMaxResults[0].get()[0].getIndex();
            int max = minMaxResults[0].get()[1].getIndex();

            for (int i = 1; i < NUMBER_OF_PARTS; i++) {
                if (array.get(min) > array.get(minMaxResults[i].get()[0].getIndex())) {
                    min = minMaxResults[i].get()[0].getIndex();
                }

                if (array.get(max) < array.get(minMaxResults[i].get()[1].getIndex())) {
                    max = minMaxResults[i].get()[1].getIndex();
                }
            }

            System.out.println("Min value= " + array.get(min) + ", index= " + min);
            System.out.println("Max value= " + array.get(max) + ", index= " + max);
        } catch (InterruptedException ie) {
            ie.printStackTrace(System.err);
        } catch (ExecutionException ee) {
            ee.printStackTrace(System.err);
        }

        System.out.println("Min by Atomic: " + minAtomic.get().getValue() + ", index: " +
                minAtomic.get().getIndex());
        System.out.println("Max by Atomic: " + maxAtomic.get().getValue() + ", index: " +
                maxAtomic.get().getIndex());

        return 0;
    }

    public static void main(String[] args) {
        List<Integer> array = new ArrayList<Integer>();
        for(int i = 0; i < SIZE; i++) {
            array.add(i, i);
        }
        array.set(2, -100); // For example, let min = -100;

        ExecutorService es1 = Executors.newFixedThreadPool(5);

        countOfEvenByAtomicAndFuture(array, es1);
        sumOfArrayByAtomicAndFuture(array, es1);
        xorOfArrayByAtomicAndFuture(array, es1);
        minMaxOfArrayByAtomicAndFuture(array, es1);

        System.out.println();

        es1.shutdown();
    }
}