// statements_lock2.cs
using System;
using System.Threading;

class Account
{
    private Object thisLock = new Object();
    int balance;

    Random r = new Random();

    public Account(int initial)
    {
        balance = initial;
    }

    int Withdraw(int amount)
    {

        // This condition will never be true unless the lock statement
        // is commented out:
        if (balance < 0)
        {
            throw new Exception("Negative Balance");
        }

        // Comment out the next line to see the effect of leaving out 
        // the lock keyword:
        lock(thisLock)
        {
            Console.WriteLine("Withdraw() is executing in thread(" + Thread.CurrentThread.GetHashCode() + ")" );

            if (balance >= amount)
            {
                Console.WriteLine("Balance before Withdrawal :  " + balance);
                Console.WriteLine("Amount to Withdraw        : -" + amount);
                balance = balance - amount;
                Console.WriteLine("Balance after Withdrawal  :  " + balance);
                return amount;
            }
            else
            {
                return 0; // transaction rejected
            }
        }
    }

    public void DoTransactions()
    {
        Console.WriteLine("DoTransactions is executing in thread(" + Thread.CurrentThread.GetHashCode() + ")" );
        for (int i = 0; i < 30; i++)
        {
            Withdraw(r.Next(1, 10));
            Thread.Sleep(300);
        }
    }
}

class Test
{
    private const int NUM_THREADS = 3;
    static void Main()
    {
        Console.WriteLine("Main() is executing in thread(" + Thread.CurrentThread.GetHashCode() + ")" );
        Thread[] threads = new Thread[NUM_THREADS];
        Account acc = new Account(1000);
        for (int i = 0; i < NUM_THREADS; i++)
        {
            Thread t = new Thread(new ThreadStart(acc.DoTransactions));
            threads[i] = t;
        }
        for (int i = 0; i < NUM_THREADS; i++)
        {
            threads[i].Start();
        }
    }
}

