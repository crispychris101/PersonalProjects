import time 
from datetime import datetime

# Define functions with docstrings
global library
library = []
def add_book(title, author, isbn, copies):
    """
    This function allows the user to add a book to the system.
    """
    
    book = {}
    book['title'] = title
    book['author'] = author
    book['isbn'] = isbn
    book['copies'] = copies
    library.append(book)
    print(f"Book '{title}' by {author} has been added to the library.")
    return 

def remove_book():
    """
    This function allows the user to remove a book from the system.
    """
    print()
    remove = input("If you want to remove all books enter 'all', otherwise enter the book's title: ")
    if remove == "all":
        library.clear()
        print("all gone")
    else:
        for book in library:
            if book['title'] == remove:
                library.remove(book)
                print()
                print(remove, "has been removed from the system")
                print()
                break
            if book['title'] != remove:
                print()
                print("Cant remove a book that isn't in the system")
                print()
    return


def modify_book():
    """
    This function allows the user to modify a book in the system.
    """
    print()
    title = input("Enter title of book that needs to be modified: ")
    print()
    # Nested menu
    print("What information of the book do you want to change?")
    print("1. Title")
    print("2. Author")
    print("3. ISBN")
    print("4. Number of Copies")
    choice = input("Enter your choice: ")
    if choice == "1":
        # Modify title
        for book in library:
          book['title'] = input("Enter a new title: ")
        pass
    elif choice == "2":
        # Modify author
        for book in library:
          book['author'] = input("Enter a new author: ")
        pass
    elif choice == "3":
        # Modify ISBN
        for book in library:
          book['isbn'] = input("Enter a new ISBN: ")
        pass
    elif choice == "4":
        # Modify number of copies
        for book in library:
          book['copies'] = input("Enter a new number of copies: ")
        pass
    else:
        print("Invalid choice.")

def check_out_book():
    """
    This function allows the user to check out a book from the system.
    """
    print()
    title = input("Pleae enter the title of the book you wish to check out: ")
    print()
    for book in library:
      if book['title'] == title:
        
        copy = book['copies']
        copy = int(copy)
        if copy == 0:
          print("No more bookes currently in system, wait until someone returns one!")
          print()
          break
        copy = copy - 1
        copy = str(copy)
        book['copies'] = copy
        print("Checked out!")
        print()
        return
      else:
        print("Book not found, please add it to the catalog or check your spelling")
        print()
    pass

def check_in_book():
    """
    This function allows the user to check in a book to the system.
    """
    title = input("Pleae enter the title of the book you wish to check in: ")
    print()
    for book in library:
      if book['title'] == title:
        copy = book['copies']
        copy = int(copy)
        copy = copy + 1
        copy = str(copy)
        book['copies'] = copy
        print("Checked in!")
        print()
        return
      else:
        print("Book not found, please add it to the catalog or check your spelling")
        print()
    pass

def view_books(library):
    """
    This function displays all the books in the system.
    """
    print()
    if len(library) == 0:
      print("No bookes in Library")
    else:
      print("Library Contents:")
      print()
      for book in library:
        print("Title:", book['title'])
        print("Author:", book['author'])
        print("ISBN:", book['isbn'])
        print("Number of copies:", book['copies'])
        print()
        
        
def check_due_time(): # basically we input a time that we check out a book, and this function cheks our current time(as of rn) then compares too se if its overdue or no
    # we get the current time
    
    checkout_time = input("Enter the checkout time (enter with pm/am): ")

    # Get user input for due time
    due_time = input("Enter the due time (enter with pm/am): ")
    current = datetime.now().time()

    # Convert the checkout time to datetime object, the weird looking string is to show the am/pm clock
    checkout_datetime = datetime.strptime(checkout_time, "%I:%M%p").time()
    due_datetime = datetime.strptime(due_time, "%I:%M%p").time()

    # Compare the checkout time with the current time
    if current > due_datetime:
        print("The book is overdue.")
    elif current >= checkout_datetime and current <= due_datetime:
        print("The book is not yet due.")
    else:
        print("The book is not yet checked out.")

        
# Display instructions for each menu item
def display_instructions():
    print()
    print("Hi welcome to our program,what do you want to do?")
    print("1. Add a book")
    print("2. Remove a book / clear all books")
    print("3. Modify a book")
    print("4. Check out a book")
    print("5. Check in a book")
    print("6. View all books")
    print("7. Quit")
    print("8. when is my book due?")

# Loop to continuously display menu until user quits
while True:
    display_instructions()
    choice = input("Enter your choice: ")

    # Check user input for validity using try-except block
    try:
        choice = int(choice)
    except ValueError:
        print("Invalid choice. Please enter a number.")
        continue

    # Use if-elif-else statement to call functions based on user choice
    if choice == 1:
        booktitle = input("Please enter the book's title: ")
        bookauthor = input("Please enter the book's author: ")
        bookisbn = input("Please enter the book's ISBN: ")
        bookcopies = input("Please enter the amount of books (copies): ")
        library2 = add_book(booktitle,bookauthor, bookisbn, bookcopies)
        
        
    elif choice == 2:
       
        
        remove_book()
    elif choice == 3:
        modify_book()
    elif choice == 4:
        check_out_book()
    elif choice == 5:
        check_in_book()
    elif choice == 6:
        view_books(library)
    elif choice == 7:
        print("Thank you for using the program.")
        break
    elif choice == 8:
        check_due_time()
        
    else:
        print("Invalid choice.")
        
