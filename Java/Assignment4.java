// Custom exceptions
class BookNotAvailableException extends Exception {
    public BookNotAvailableException(String msg) {
        super(msg);
    }
}

class InvalidReturnException extends Exception {
    public InvalidReturnException(String msg) {
        super(msg);
    }
}

// Book class
class Book {
    private String title;
    private boolean isBorrowed;

    public Book(String title) {
        this.title = title;
        this.isBorrowed = false;
    }

    public void borrowBook() throws BookNotAvailableException {
        if (isBorrowed) {
            throw new BookNotAvailableException("Book '" + title + "' is already borrowed.");
        } else {
            isBorrowed = true;
            System.out.println("Borrowed: " + title);
        }
    }

    public void returnBook() throws InvalidReturnException {
        if (!isBorrowed) {
            throw new InvalidReturnException("Book '" + title + "' was not borrowed.");
        } else {
            isBorrowed = false;
            System.out.println("Returned: " + title);
        }
    }
}

public class Assignment4 {
    public static void main(String[] args) {
        Book b1 = new Book("Java Basics");

        // 1st borrow
        try {
            b1.borrowBook();
        } catch (BookNotAvailableException e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            System.out.println("Done with borrow attempt.");
        }

        System.out.println("----");

        // 2nd borrow (should throw exception)
        try {
            b1.borrowBook();
        } catch (BookNotAvailableException e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            System.out.println("Done with borrow attempt.");
        }

        System.out.println("----");

        // 1st return
        try {
            b1.returnBook();
        } catch (InvalidReturnException e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            System.out.println("Done with return attempt.");
        }

        System.out.println("----");

        // 2nd return (should throw exception)
        try {
            b1.returnBook();
        } catch (InvalidReturnException e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            System.out.println("Done with return attempt.");
        }
    }
}
