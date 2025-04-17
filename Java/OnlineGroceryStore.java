import java.io.*;
import java.util.*;

class EnvLoader {
    public static Properties loadEnv(String path) {
        Properties props = new Properties();
        try(FileInputStream fis = new FileInputStream(path)) {
            props.load(fis);
        } catch (IOException e) {
            System.out.println("Error loading environment variables: " + e.getMessage());
        }

        return props;
    }
}

// Product class
class Product implements Serializable {
    int id;
    String name;
    String category;
    double price;
    int quantity;

    public Product(int id, String name, String category, double price, int quantity) {
        this.id = id;
        this.name = name;
        this.category = category;
        this.price = price;
        this.quantity = quantity;
    }

    public String toString() {
        return id + ". " + name + " | Category: " + category + " | Price: Rs." + price + " | Stock: " + quantity;
    }
}

// Cart class
class Cart {
    List<Product> cartItems = new ArrayList<>();

    public void addToCart(Product p, int qty) {
        Product cartProduct = new Product(p.id, p.name, p.category, p.price, qty);
        cartItems.add(cartProduct);
        System.out.println(qty + " x " + p.name + " added to cart.");
    }

    public void viewCart() {
        if (cartItems.isEmpty()) {
            System.out.println("Cart is empty.");
            return;
        }
        System.out.println("\nYour Cart:");
        double total = 0;
        for (Product p : cartItems) {
            System.out.println(p.name + " x " + p.quantity + " = Rs." + (p.price * p.quantity));
            total += p.price * p.quantity;
        }
        System.out.println("Total: Rs." + total);
    }

    public void checkout(List<Product> inventory) {
        for (Product cartItem : cartItems) {
            for (Product inv : inventory) {
                if (inv.id == cartItem.id) {
                    inv.quantity -= cartItem.quantity;
                }
            }
        }
        System.out.println("\nCheckout complete. Thank you for shopping!");
        cartItems.clear();
    }
}

// Inventory Manager
class InventoryManager {
    private final String fileName = "inventory.dat";

    public void saveInventory(List<Product> inventory) throws IOException {
        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(fileName));
        oos.writeObject(inventory);
        oos.close();
    }

    public List<Product> loadInventory() throws IOException, ClassNotFoundException {
        File file = new File(fileName);
        if (!file.exists()) return new ArrayList<>();
        ObjectInputStream ois = new ObjectInputStream(new FileInputStream(fileName));
        List<Product> inventory = (List<Product>) ois.readObject();
        ois.close();
        return inventory;
    }
}

public class OnlineGroceryStore {
    static Scanner sc = new Scanner(System.in);
    static Cart cart = new Cart();
    static InventoryManager inventoryManager = new InventoryManager();

    public static void main(String[] args) {
        List<Product> inventory;

        try {
            inventory = inventoryManager.loadInventory();
            inventory = getDefaultInventory();
            inventoryManager.saveInventory(inventory);
            
        } catch (Exception e) {
            inventory = getDefaultInventory();
            try {
                inventoryManager.saveInventory(inventory);
            } catch (IOException ex) {
                System.out.println("Error initializing inventory.");
            }
        }

        while (true) {
            System.out.println("\n===== Online Grocery Store =====");
            System.out.println("1. Browse Products by Category");
            System.out.println("2. View Cart");
            System.out.println("3. Checkout");
            System.out.println("4. Add Product to Inventory (Admin)");
            System.out.println("5. Exit");
            System.out.print("Enter choice: ");
            int choice = sc.nextInt();
            sc.nextLine();

            switch (choice) {
                case 1:
                    browseProducts(inventory);
                    break;
                case 2:
                    cart.viewCart();
                    break;
                case 3:
                    cart.viewCart();
                    cart.checkout(inventory);
                    try {
                        inventoryManager.saveInventory(inventory);
                    } catch (IOException e) {
                        System.out.println("Error saving inventory.");
                    }
                    break;
                case 4:
                    Properties env = EnvLoader.loadEnv(".env"); 
                    String adminPassword = env.getProperty("ADMIN_PASSWORD");
                    System.out.print("Enter admin password: ");
                    String inputPassword = sc.nextLine();
                    if(!inputPassword.equals(adminPassword)) {
                        System.out.println("Invalid password. Access denied.");
                        break;
                    }
                    System.out.println("Admin access granted.");
                    addProduct(inventory);
                    try {
                        
                        inventoryManager.saveInventory(inventory);
                    } catch (IOException e) {
                        System.out.println("Error saving inventory.");
                    }
                    break;
                case 5:
                    System.out.println("Exiting... Goodbye!");
                    return;
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }

    public static List<Product> getDefaultInventory() {
        List<Product> defaults = new ArrayList<>();
        Product[] defaultProducts = {
            new Product(1, "Apple", "Fruits", 120, 50),
            new Product(2, "Banana", "Fruits", 60, 100),
            new Product(3, "Milk", "Dairy", 55, 80),
            new Product(4, "Cheese", "Dairy", 250, 40),
            new Product(5, "Carrot", "Vegetables", 40, 70),
            new Product(6, "Tomato", "Vegetables", 30, 90),
            new Product(7, "Onion", "Vegetables", 35, 100),
            new Product(8, "Rice", "Grains", 60, 200),
            new Product(9, "Wheat Flour", "Grains", 50, 150),
            new Product(10, "Sugar", "Essentials", 45, 100),
            new Product(11, "Salt", "Essentials", 20, 150),
            new Product(12, "Bread", "Bakery", 35, 60),
            new Product(13, "Butter", "Dairy", 180, 30),
            new Product(14, "Eggs", "Poultry", 6, 120),
            new Product(15, "Chicken", "Poultry", 240, 50),
            new Product(16, "Tea", "Beverages", 150, 80),
            new Product(17, "Coffee", "Beverages", 250, 60),
            new Product(18, "Biscuits", "Snacks", 30, 100),
            new Product(19, "Chips", "Snacks", 20, 90),
            new Product(20, "Juice", "Beverages", 80, 70)
        };

        for (Product p : defaultProducts) {
            defaults.add(p);
        }

        return defaults;
    }

    public static void browseProducts(List<Product> inventory) {
        System.out.print("Enter category to browse (e.g., Fruits, Dairy): ");
        String category = sc.nextLine();
        List<Product> filtered = new ArrayList<>();
        for (Product p : inventory) {
            if (p.category.equalsIgnoreCase(category)) {
                filtered.add(p);
            }
        }
        if (filtered.isEmpty()) {
            System.out.println("No products found in this category.");
            return;
        }
        for (Product p : filtered) {
            System.out.println(p);
        }
        System.out.print("Enter Product ID to add to cart or 0 to go back: ");
        int pid = sc.nextInt();
        if (pid == 0) return;
        System.out.print("Enter quantity: ");
        int qty = sc.nextInt();
        for (Product p : filtered) {
            if (p.id == pid && p.quantity >= qty) {
                cart.addToCart(p, qty);
                return;
            }
        }
        System.out.println("Product not available or insufficient quantity.");
    }

    public static void addProduct(List<Product> inventory) {
        System.out.print("Enter Product Name: ");
        String name = sc.nextLine();
        System.out.print("Enter Category: ");
        String category = sc.nextLine();
        System.out.print("Enter Price: ");
        double price = sc.nextDouble();
        System.out.print("Enter Quantity: ");
        int qty = sc.nextInt();
        int id = inventory.size() + 1;
        inventory.add(new Product(id, name, category, price, qty));
        System.out.println("Product added to inventory.");
    }
}
