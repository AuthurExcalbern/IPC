//线程模拟实现
class Philosopher extends Thread
{
    private int thinkingTime = 0;//已经思考了多少时间
    private int eatingTime = 0;//已经进餐了多少时间
    
    int id;//哲学家的id
    static int currentId = 0;//目前的id（记录已经有多少个哲学家
    
    //建立起这个哲学家的线程
    private Forks fork;
    
    //赋予各个哲学家的id和线程
    public Philosopher(Forks fork)
    {
        super();
        id = currentId;
        currentId++;
        this.fork = fork;
    }
    
    //哲学家线程开始运行
    public void run()
    {
        //线程状态会一直在思考和进餐间转换
        while(true)
        {
            thinking();//未进餐的思考状态
            fork.takeFork();//开始尝试拿餐具
            eating();//成功拿起餐具后开始进餐
            fork.putFork();//放下餐具
        }
    }
    
    //哲学家的思考状态
    private void thinking()
    {
        //记录哲学家和思考时间
        thinkingTime++;
        System.out.println("Philosopher " + id + " : thinking start!");
        System.out.println("Time : " + thinkingTime);
        
        //休眠
        try{ sleep(1000); }
        catch(InterruptedException e)
        {
            e.printStackTrace();
        }
    }
    
    //哲学家的进餐状态
    private void eating()
    {
        //记录哲学家和进餐时间
        eatingTime++;
        System.out.println("Philosopher " + id + " : eating start!");
        System.out.println("Time : " + eatingTime);
        
        //休眠
        try{ sleep(1000); }
        catch(InterruptedException e)
        {
            e.printStackTrace();
        }
    }
}

class Forks
{
    //记录餐具是否被拿起，false为未拿起
    private boolean[] used = {false, false, false, false, false};
    
    // synchronized 某线程执行时不允许其他线程执行
    
    //
    public synchronized void takeFork()
    {
        //获取当前线程
        Philosopher p = (Philosopher)Thread.currentThread();
        
        int id = p.id;
        
        //当哲学家左右餐具都未被拿起时才可以跳出等待状态
        while(used[id] || used[(id + 1) % 5])
        {
            try{ wait(); }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
        }
        
        System.out.println("Philosopher " + id + " : takeFork!");
        
        //改变餐具状态
        used[id] = true;
        used[(id + 1) % 5] = true;
    }
    
    public synchronized void putFork()
    {
        Philosopher p = (Philosopher)Thread.currentThread();
        int id = p.id;
        
        System.out.println("Philosopher " + id + " : putFork!");
        
        used[id] = false;
        used[(id + 1) % 5] = false;
    }
}

public class Dining_philosophers_problem
{
    public static void main(String[] args)
    {
        Forks f = new Forks();
        
        //用start方法启动线程
        new Philosopher(f).start();
        new Philosopher(f).start();
        new Philosopher(f).start();
        new Philosopher(f).start();
        new Philosopher(f).start();
    }
}