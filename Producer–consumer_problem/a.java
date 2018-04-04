class producer extends Thread
{
    

class Buf
{
    private buf_data = 0;

    public synchronized void put_data()
    {
        
    }
    
    public synchronized void get_data()
    {
    }
}


public class a
{
    public static void main(String[] args)
    {
        Buf f = new Buf();
        
        new producer(f).start();
        new consumer(f).start();
    }
}