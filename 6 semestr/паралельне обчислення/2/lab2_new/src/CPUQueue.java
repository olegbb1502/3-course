import java.util.LinkedList;
import java.util.List;

public class CPUQueue
{
    private List<CPUProcess> processes = new LinkedList<CPUProcess>();
    public int id;
    public static int MAX_QUEUE_SIZE = 1000;

    public CPUQueue(int id)
    {
        this.id = id;
    }

    public synchronized void push(CPUProcess process)
    {
        try
        {
            while (processes.size() == MAX_QUEUE_SIZE)
            {
                wait();
            }

            this.processes.add(process);

        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }

    public synchronized CPUProcess pull()
    {
        CPUProcess result = null;
        if (!processes.isEmpty())
        {
            result = processes.remove(0);
            notify();
        }

        return result;
    }

}
