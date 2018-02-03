public class CPU extends Thread
{

    private CPUQueuePool queuePool;

    public int id;
    private int delay;

    public CPU(CPUQueuePool queuePool, int delay)
    {
        System.out.println("Creating a CPU");
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
                currentProcess = this.queuePool.pull();
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
        Thread.sleep(process.lastingTime + this.delay);
        System.out.println("CPU #" + this.id + ": task from queue #" + process.id + " completed");
    }
}

