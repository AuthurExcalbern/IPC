public class Producer_consumer_problem
{
    //缓冲区容量的大小
    static final int N = 20;
    
    static int the_data = 0;
    
    //初始化两个线程
    static Producer p = new Producer();
    static Consumer c = new Consumer();
    
    //初始化一个新的管程
    static our_monitor mon = new our_monitor();
    
    //开始生产者和消费者的线程
    public static void main(String args[])
    {
        p.start();
        c.start();
    }
    
    //生产者线程
    static class Producer extends Thread
    {
        //run方法包含了线程代码
        public void run()
        {
            int item;
            
            //生产者循环：产生数据和插入数据到缓冲区
            while(true)
            {
                item = produce_item();
                mon.insert(item);
            }
        }
        
        //产生数据
        private int produce_item()
        {
            if(the_data < 100)
            {
                the_data++;
                return the_data;
            }
            else
                return -1;
        }
    }
    
    //消费者线程
    static class Consumer extends Thread
    {
        public void run()
        {
            int item;
            
            //消费者循环：从缓冲区移走数据并对移走的数据进行操作
            while(true)
            {
                item = mon.remove();
                consume_item(item);
            }
        }
        
        //对数据操作
        private void consume_item(int item)
        {
            if(item == -1)
                System.exit(0);
        }
    }
    
    //这是一个管程
    static class our_monitor extends Thread
    {
        //缓冲区
        private int buffer[] = new int[N];
        
        //计数 + 索引
        private int count = 0, lo = 0, hi = 0;
        
        //插入
        public synchronized void insert(int val)
        {
            //缓冲区满则休眠
            if(count == N) go_to_sleep();
            
            //存入数据 + 设置下一存入位置 + 数据项计数
            buffer[hi] = val;
            hi = (hi + 1) % N;
            count = count + 1;
            
            System.out.println("Insert data: " + val);
            try{ sleep(50); }
            catch(InterruptedException e){ e.printStackTrace(); }
            
            //刚刚count为0,消费者在休眠
            //唤醒消费者
            if(count == 1) notify();
        }
        
        //移走
        public synchronized int remove()
        {
            int val;
            
            //缓冲区为空则休眠
            if(count == 0) go_to_sleep();
            
            //取出数据 + 设置下一取出位置 + 数据项计数
            val = buffer[lo];
            lo = (lo + 1) % N;
            count = count - 1;
            
            System.out.println("Remove data: " + val);
            try{ sleep(50); }
            catch(InterruptedException e){ e.printStackTrace(); }
            
            //刚刚count可能为N，生产者在休眠
            //唤醒生产者
            if(count == N - 1) notify();
            
            //返回取出的数据
            return val;
        }
        
        //进入休眠并释放锁
        private void go_to_sleep()
        {
            try{ wait(); }
            catch(InterruptedException e){};
        }
    }
}