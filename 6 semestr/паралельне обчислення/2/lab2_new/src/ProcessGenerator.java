public class ProcessGenerator extends Thread
{

    CPUQueuePool queuePool;
    public int id;

    public ProcessGenerator(int id, CPUQueuePool queuePool)
    {
        System.out.println("Creating generator #" + id);
        this.id = id;
        this.queuePool = queuePool;
    }

    public void run()
    {
        CPUProcess process;
        while (System.currentTimeMillis()-Main.startTime < Main.RUN_MILLISEC)
        {
            try
            {
                process = new CPUProcess((int)(Math.random()*5)+5, this.id);
                if (this.id == 1)
                {
                    this.queuePool.pushQueue1(process);
                }
                else
                {
                    this.queuePool.pushQueue2(process);
                }
                System.out.println("ProcessGenerator #" + this.id + " pushed a process into queue #" + this.id);
                Thread.sleep((int)(Math.random()*10)+100);
            }
            catch (InterruptedException ex)
            {
                ex.printStackTrace();
            }
        }
    }
}

