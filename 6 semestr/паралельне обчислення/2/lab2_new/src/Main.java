public class Main
{

    public static final long RUN_MILLISEC = 2000;
    public static long startTime;

    public static void main(String[] args) throws InterruptedException
    {

        CPUQueuePool queuePool = new CPUQueuePool();

        CPU cpu1 = new CPU(1, queuePool, 1);
        CPU cpu2 = new CPU(2, queuePool, 100);

        ProcessGenerator processGenerator1 = new ProcessGenerator(1, queuePool);
        ProcessGenerator processGenerator2 = new ProcessGenerator(2, queuePool);

        startTime = System.currentTimeMillis();
        cpu1.start();
        cpu2.start();
        processGenerator1.start();
        processGenerator2.start();

        cpu1.join();
        cpu2.join();
        processGenerator1.join();
        processGenerator2.join();
    }
}