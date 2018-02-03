public class CPU extends Thread
{

    private CPUQueuePool queuePool;

    public int id;
    private int delay;

    public CPU(int id, CPUQueuePool queuePool, int delay)
    {
        System.out.println("Creating a CPU #" + id);
        this.id = id;
        this.queuePool = queuePool;
        this.delay = delay;
    }

    public void run()
    {

        try
        {
            CPUProcess currentProcess;
            while (System.currentTimeMillis() - Main.startTime < Main.RUN_MILLISEC)
            {
                currentProcess = (this.id == 1 ? this.queuePool.pullQueue1() : this.queuePool.pullQueue2());
                runProcess(currentProcess);
            }
        }
        catch (InterruptedException ex)
        {
            ex.printStackTrace();
        }
    }

    private void runProcess(CPUProcess process) throws InterruptedException
    {
        System.out.println("CPU #" + this.id + " got a task from queue #" + process.id);
        Thread.sleep(process.lastingTime+this.delay);
        System.out.println("CPU #" + this.id + ": task from queue #" + process.id + " completed");
    }
}

