class Philosopher extends Thread
{
    private int thinkingtimes = 0;//思考次数
    private int eatingtimes = 0;//吃饭次数
    int id;//是哪位哲学家
    static int currentid = 0;//下一个可用编号
    private Forks fork;
    public Philosopher(Forks fork)//使用叉子
    {
        super();
        id = currentid;
        currentid++;
        this.fork = fork;
    }
    public void run()
    {
        while(true)//每位哲学家都先思考，再去申请叉子，然后在放下叉子
        {
            thinking();
            fork.takeFork();
            eating();
            fork.putFork();
        }
    }
    private void thinking()
    {
        thinkingtimes++;
        System.out.println("Philosopher " + id + " : thinking start!  Times : " + thinkingtimes);
        try {
            sleep(1000);//用sleep来模拟思考的时间
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    private void eating()
    {
        eatingtimes++;
        System.out.println("Philosopher " + id + " : eating start!  Times : " + eatingtimes);
        try {
            sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Forks
{
    private boolean[] used = {false, false, false, false, false};
    public synchronized void takeFork()
    {
        Philosopher p = (Philosopher) Thread.currentThread();
        int id = p.id;
        while(used[id] || used[(id + 1) % 5])
        {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("Philosopher " + id + " : takeFork!");
        used[id] = true;//两个叉子同时被使用
        used[(id + 1) % 5] = true;
    }
    public synchronized void putFork()
    {
        Philosopher p = (Philosopher) Thread.currentThread();
        int id = p.id;
        System.out.println("Philosopher " + id + " : putFork!");
        used[id] = false;//两个叉子
        used[(id + 1) % 5] = false;
        notifyAll();//如果之前是锁住的，则唤醒周围的哲学家来使用叉子。
    }
}

 class DiningPhilosophers{
    public static void main(String[] args)
    {
        Forks f = new Forks();
        new Philosopher(f).start();//五位哲学家创建
        new Philosopher(f).start();
        new Philosopher(f).start();
        new Philosopher(f).start();
        new Philosopher(f).start();
    }
}
