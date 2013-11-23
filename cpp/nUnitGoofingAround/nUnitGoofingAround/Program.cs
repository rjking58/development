using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;

namespace bank
{

    public class InsufficientFundsException : ApplicationException
    {
    }

    public class Account
    {
        private float balance;
        private float minimumBalance = 10.00F;



        public void Deposit(float amount)
        {
            balance += amount;
        }

        public void Withdraw(float amount)
        {
            balance -= amount;
        }

        public void TransferFunds(Account destination, float amount)
        {
            destination.Deposit(amount);
            if ((balance - amount) < minimumBalance)
            {
                throw new InsufficientFundsException();
            }
            Withdraw(amount);
        }

        public float Balance
        {
            get { return balance; }
        }

        public float MinimumBalance
        {
            get { return minimumBalance; }
        }

    }

    [TestFixture]
    public class AccountTest
    {
        Account source;
        Account destination;
        
        [SetUp]
        public void Init()
        {
            source = new Account();
            source.Deposit(200.00F);
            destination = new Account();
            destination.Deposit(150.00F);
        }
        
        [Test]
        public void TransferFunds()
        {
            source.TransferFunds(destination, 100.00F);
            Assert.AreEqual(250.00F, destination.Balance);
            Assert.AreEqual(100.00F, source.Balance);

        }
        [Test]
        [ExpectedException(typeof(InsufficientFundsException))]
        public void TransferWithInsufficientFunds()
        {
            source.TransferFunds(destination, 300.00F);
        }
        [Test]
        [Ignore("decide how to do account management later")]
        public void TransferWithInsufficientFundsAtomicity()
        {
        	try
        	{
        		source.TransferFunds(destination, 300.00F);
        	}
        	catch(InsufficientFundsException expected)
        	{
        	}
        
        	Assert.AreEqual(200.00F,source.Balance);
        	Assert.AreEqual(150.00F,destination.Balance);
        }
    }

    public class bankProg
    {
        static void Main()
        {
        }
    }

 
}