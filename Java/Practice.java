import java.util.*;

class Calculator {
    public static int powerInt(int num1, int num2) {
        return (int) Math.pow(num1, num2);
    }

    public static double powerDouble(double num1, int num2) {
        return Math.pow(num1, num2);
    }
}

class Patient {
    Scanner sc = new Scanner(System.in);       
    String patientName;
    double height = 0;
    double weight = 0;
    void getPatientName() {
        System.out.println("Enter your name");
        this.patientName = sc.nextLine();
    }

    void getHeightWeight() {
        System.out.println("Enter your height");
        this.height = sc.nextDouble();
        System.out.println("Enter your weight");
        this.weight = sc.nextDouble();
    }

    double calculateBMI() {
        if(height == 0 || weight == 0) {
            getHeightWeight();
        }
        double patientBMI = this.weight / Math.pow(this.height, 2);
        System.out.println(this.height + " " + this.weight);
        System.out.println(this.patientName + "'s BMI is " + patientBMI);
        return patientBMI;
    }
}

public class Practice {
    public static void main(String args[]) {
        // Question 1
        int powInt = Calculator.powerInt(4, 3);
        double powDob = Calculator.powerDouble(100, 3);

        System.out.println("Power of integer: " + powInt);
        System.out.println("Power of double: " + powDob);

        // Question 2
        Patient sarvesh = new Patient();
        sarvesh.getPatientName();
        sarvesh.getHeightWeight();
        sarvesh.calculateBMI();
    }
}