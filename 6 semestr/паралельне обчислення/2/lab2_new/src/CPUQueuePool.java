/**
 * Created by user on 4/4/17.
 */
public class CPUQueuePool
{
    private CPUQueue queue1;
    private CPUQueue queue2;

    public CPUQueuePool()
    {
        this.queue1 = new CPUQueue(1);
        this.queue2 = new CPUQueue(2);
    }

    public synchronized CPUProcess pullQueue1()
    {
        CPUProcess process = null;
        try
        {
            while (process == null)
            {
                process = queue1.pull();
                if (process == null)
                {
                    process = queue2.pull();
                    if (process == null)
                    {
                        wait();
                    }
                }
            }
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
        return process;
    }

    public synchronized CPUProcess pullQueue2()
    {
        CPUProcess process = null;
        try
        {
            while (process == null)
            {
                process = queue2.pull();
                if (process == null)
                {
                    process = queue1.pull();
                    if (process == null)
                    {
                        wait();
                    }
                }
            }
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
        return process;
    }

    public void pushQueue1(CPUProcess process)
    {
        queue1.push(process);
        notify();
    }

    public void pushQueue2(CPUProcess process)
    {
        queue2.push(process);
        notify();
    }
}
