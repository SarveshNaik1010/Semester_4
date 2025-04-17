abstract class BankAccount {
    protected String fullName;
    protected String city;
    protected int age; 
    protected int balance; 

    abstract void setAccountDetails(String fullName, int age, String city);
    abstract void deposit(int amount);
    abstract void withdraw(int amount);
    abstract void displayAccountDetails(); // renamed from getAccountDetails
}

class SavingsAccount extends BankAccount {
    public void setAccountDetails(String fullName, int age, String city) {
        this.fullName = fullName;
        this.age = age;
        this.city = city;
        this.balance = 0;
        System.out.println("Savings Account created successfully.");
    }

    public void deposit(int amount) {
        balance += amount;
        System.out.println("Rs. " + amount + " deposited successfully.");
        System.out.println("Current balance: Rs. " + balance);
    }

    public void withdraw(int amount) {
        try {
            if (this.balance < amount)
                throw new Exception("Insufficient balance");
            balance -= amount;
            System.out.println("Rs. " + amount + " withdrew successfully.");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void displayAccountDetails() {
        System.out.println("--- Savings Account Details ---");
        System.out.println("Name: " + fullName);
        System.out.println("Age: " + age);
        System.out.println("City: " + city);
        System.out.println("Balance: Rs. " + balance);
    }
}

class CurrentAccount extends BankAccount {
    public void setAccountDetails(String fullName, int age, String city) {
        this.fullName = fullName;
        this.age = age;
        this.city = city;
        this.balance = 0;
        System.out.println("Current Account created successfully.");
    }

    public void deposit(int amount) {
        balance += amount;
        System.out.println("Rs. " + amount + " deposited successfully.");
        System.out.println("Current balance: Rs. " + balance);
    }

    public void withdraw(int amount) {
        try {
            if (this.balance < amount)
                throw new Exception("Insufficient balance");
            balance -= amount;
            System.out.println("Rs. " + amount + " withdrew successfully.");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void displayAccountDetails() {
        System.out.println("--- Current Account Details ---");
        System.out.println("Name: " + fullName);
        System.out.println("Age: " + age);
        System.out.println("City: " + city);
        System.out.println("Balance: Rs. " + balance);
    }
}

public class Assignment3 {
    public static void main(String[] args) {
        SavingsAccount sa = new SavingsAccount();
        sa.setAccountDetails("Sarvesh Naik", 20, "Pune");
        sa.deposit(1000);
        sa.withdraw(500);
        sa.withdraw(600);
        sa.displayAccountDetails();

        System.out.println("----");

        CurrentAccount ca = new CurrentAccount();
        ca.setAccountDetails("Anurag Yadav", 21, "Mumbai");
        ca.deposit(2000);
        ca.withdraw(1000);
        ca.withdraw(1500);
        ca.displayAccountDetails();
    }
}
