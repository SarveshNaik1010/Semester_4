import java.util.*;

class Employee {
    int empId;
    String empName;
    String empDept;
    double empSalary;
    double empBonus;
    double empAllowance;
    boolean isFixed = true;
    Scanner sc = new Scanner(System.in);

    // Full time based employees
    Employee() {
        System.out.println("----FULL TIME BASED EMPLOYEE----");
        System.out.println("Enter your ID, Name, Dept, Salary, Bonus and Allowance");
        this.empId = sc.nextInt();
        sc.nextLine();
        this.empName = sc.nextLine();
        this.empDept = sc.nextLine();
        this.empSalary = sc.nextFloat();
        sc.nextLine();
        this.empBonus = sc.nextFloat();
        sc.nextLine();
        this.empAllowance = sc.nextFloat();
        sc.nextLine();
        this.isFixed = true;
    }

    // Contract based employees
    Employee(boolean isFixed) {
        if (isFixed) {
            System.out.println("You are a full-time employee");
            return;
        }
        
        System.out.println("----CONTRACT BASED EMPLOYEE----");
        System.out.println("Enter your ID, Name, Dept, Salary");
        this.empId = sc.nextInt();
        sc.nextLine(); // Consume newline
        this.empName = sc.nextLine();
        this.empDept = sc.nextLine();
        this.empSalary = sc.nextFloat();
        sc.nextLine(); // Consume newline
    }

    Employee(Employee emp) {
        if(emp.isFixed) {
            this.empBonus = emp.empBonus;
            this.empAllowance = emp.empAllowance;
        }
        this.empId = emp.empId;
        this.empName =  emp.empName;
        this.empDept = emp.empDept;
        this.empSalary = emp.empSalary;
    }

    void displayEmpDetails() {
        System.out.println("---- EMPLOYEE DETAILS ----");
        System.out.println("ID: " + empId);
        System.out.println("Name: " + empName);
        System.out.println("Department: " + empDept);
        System.out.println("Salary: " + empSalary);
        if (isFixed) {
            System.out.println("Bonus: " + empBonus);
            System.out.println("Allowance: " + empAllowance);
        } else {
            System.out.println("Employment Type: Contract-Based");
        }
    }

}

class Assignment1 {
    public static void main(String args[]) {
        Employee e1 = new Employee();
        Employee e2 = new Employee(false);
        Employee e3 = new Employee(e2);

        e1.displayEmpDetails();
        e2.displayEmpDetails();
        e3.displayEmpDetails();
    }    
}