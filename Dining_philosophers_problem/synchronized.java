public class Dining_philosophers_problem
{
    //有多少个哲学家
    static final int N = 5;
    
    //哲学家的id
    static int currentId = 0;
    
    public static void main(String[] args)
    {
        Forks f = new Forks();
        
        //用start方法启动线程
        for(int i = 0; i < N; i++)
            new Philosopher(f).start();
    }
    
    //哲学家
    static class Philosopher extends Thread
    {
        int id;//哲学家的id
        
        //建立起这个哲学家的线程
        private Forks fork;
        
        //赋予各个哲学家的id
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
                fork.takeFork();//开始尝试拿餐具
                
                //重要！！！
                //需要哲学家在进餐后先放弃自己的时间片
                //让其他哲学家运行
                //以防止一个哲学家线程占用
                try{ sleep(10); }
                catch(InterruptedException e){ e.printStackTrace(); }
                
                fork.putFork();//放下餐具
            }
        }
    }
    
    //用管程来实现哲学家的进餐
    static class Forks extends Thread
    {
        //记录餐哲学家状态：0-思考;1-饥饿;2进餐
        private int[] the_status = {0, 0, 0, 0, 0};
        
        // synchronized 某线程执行时不允许其他线程执行
        public synchronized void takeFork()
        {
            //获取当前线程
            Philosopher p = (Philosopher)Thread.currentThread();
            
            int id = p.id;
            the_status[id] = 1;//转换为饥饿状态
            
            //检测是否能进餐
            test(id);
        }
        
        public synchronized void putFork()
        {
            
            Philosopher p = (Philosopher)Thread.currentThread();
    
            int id = p.id;
        
            //如果哲学家是饥饿状态，每拿到筷子自然不能放下筷子
            //所以直接返回
            if(the_status[id] == 1) return;
            
            //放下筷子，转变为思考状态
            the_status[id] = 0;
            
            System.out.println("Philosopher " + id + ": THINKING");
            try{ sleep(1000); }
            catch(InterruptedException e){ e.printStackTrace(); }
            
            //检测左右的哲学家是否可以进餐了
            test((id+N-1) % N);
            test((id+1) % N);
            
        }
    
        public synchronized void test(int i)
        {
            //当且仅当哲学家为饥饿状态且左右没有哲学家在进餐时才可以进餐
            if(the_status[i] == 1 && the_status[(i+N-1) % N] != 2 && the_status[(i+1) % N] != 2)
            {
                //记录为进餐状态
                the_status[i] = 2;
                
                System.out.println("Philosopher " + i + ": EATING");
                try{ sleep(1000); }
                catch(InterruptedException e){ e.printStackTrace(); }
            }
        }
    }
}
