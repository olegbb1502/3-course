import java.util.LinkedList;
import java.util.List;

public class CPUQueuePool
{
    private List<CPUProcess> queue1 = new LinkedList<CPUProcess>();
    private List<CPUProcess> queue2 = new LinkedList<CPUProcess>();
    public static int MAX_QUEUE_SIZE = 5;
    private int count = 0;

    public synchronized CPUProcess pull()
    {
        CPUProcess process = null;
        this.count = 0;
        try
        {
            while (process == null)
            {
                if (!queue1.isEmpty() && this.count < Main.N)
                {
                    process = queue1.remove(0);
                    this.count++;
                }
                else
                {
                    if (!queue2.isEmpty())
                    {
                        process = queue2.remove(0);
                        this.count = 0;
                    }
                    else
                    {
                        System.out.print("Both queues are empty\n");
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

    public synchronized boolean pushQueue1(CPUProcess process)
    {
        if (queue1.size() < MAX_QUEUE_SIZE)
        {
            queue1.add(process);
            notify();
            return true;
        }
        return false;
    }

    public synchronized boolean pushQueue2(CPUProcess process)
    {
        queue2.add(process);
        notify();
        return true;
    }
}
