public class Main
{

    public static final long RUN_MILLISEC = 2000;
    public static long startTime;
    public static int N = 5;

    public static void main(String[] args) throws InterruptedException
    {

        CPUQueuePool queuePool = new CPUQueuePool();

        CPU cpu1 = new CPU(queuePool, 1);

        ProcessGenerator processGenerator1 = new ProcessGenerator(1, queuePool);
        ProcessGenerator processGenerator2 = new ProcessGenerator(2, queuePool);

        startTime = System.currentTimeMillis();
        cpu1.start();
        processGenerator1.start();
        processGenerator2.start();

        cpu1.join();
        processGenerator1.join();
        processGenerator2.join();
    }
}