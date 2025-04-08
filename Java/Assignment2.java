import java.util.ArrayList;

class Book {
    String title, author;
    Book(String title, String author) {
        this.title = title;
        this.author = author;
    }

    public void displayDetails() {
        System.out.println("Book Details");
        System.out.println("Title " + this.title);
        System.out.println("Author " + this.author);
        System.out.println("----------------------------");
    }

}

class EBook extends Book {
    String type = "EBook";
    EBook(String title, String author) {
        super(title, author);
    }
    
    public void displayDetails() {
        System.out.println("EBook Book Details");
        System.out.println("Title " + this.title);
        System.out.println("Author " + this.author);
        System.out.println("----------------------------");
    }

}

class PrintedBook extends Book {
    String type = "Printed";
    PrintedBook(String title, String author) {
        super(title, author);
    }

    public void displayDetails() {
        System.out.println("Printed Book Details");
        System.out.println("Title " + this.title);
        System.out.println("Author " + this.author);
        System.out.println("----------------------------");
    }

}

class Library {
    ArrayList<Book> books = new ArrayList<>();

    void addBook(Book book) {
        books.add(book);
    }

    int searchBook(String title) {
        for(int i = 0; i < books.size(); i++) {
            if(books.get(i).title == title) {
                System.out.println("Book Found!");
                books.get(i).displayDetails();
                return 1;
            } 
        }
        System.out.println("Book not found");
        return 0;
    }

    int searchBook(String title, String author) {
        for(int i = 0; i < books.size(); i++) {
            if (books.get(i).title.equals(title) && books.get(i).author.equals(author)) {
                System.out.println("Book Found!");
                books.get(i).displayDetails();
                return 1;
            } 
        }
        System.out.println("Book not found");
        System.out.println("----------------------------");
        return 0;
    }

}

public class Assignment2 {
    public static void main(String args[]) {
        System.out.println("*******************************");
        System.out.println("Data Overriding");
        System.out.println("*******************************");
        Book atomicHabits = new Book("Atomic Habits", "James Clear");
        EBook andThenThereWereNone = new EBook("And then there were none", "Agatha Christe");
        PrintedBook verity = new PrintedBook("Verity", "Coolen Hover");
        atomicHabits.displayDetails();
        andThenThereWereNone.displayDetails();
        verity.displayDetails();

        System.out.println("*******************************");
        System.out.println("Data Overriding");
        System.out.println("*******************************");
        Book twilight1 = new Book("Twilight", "Elie Wiesel");
        Book twilight2 = new Book("Twilight", "Stephenie Meyer");

        Library lib = new Library();
        lib.addBook(atomicHabits);
        lib.addBook(andThenThereWereNone);
        lib.addBook(verity);
        lib.addBook(twilight1);
        lib.addBook(twilight2);
        lib.searchBook("Twilight");
        lib.searchBook("Verity");
        lib.searchBook("Back to me");
        lib.searchBook("Twilight", "Stephenie Meyer");
    }
}