# CSCI201FinalProject
Library simulation project.
This program simulates a library system. Users can load lists of books and patrons into the library system from files. They can also check out and return books, search for books by genre, and save book and patron lists to files.

Notes on program use:

•	Users can select an action from a menu by entering an int value that corresponds to the selected action.

•	Books and patrons must be loaded to the library system before any other actions can be performed.
     
     o	To load books, enter the file name book_list_long.txt (this should be stored in the same folder as the source code). After book_list_long.txt is loaded, you can load book_list_short.txt to test handling duplicates.
     
     o	To load patrons, enter the file name patrons.txt (this should be stored in the same folder as the source code). After patrons.txt is loaded, you can load patrons2.txt to test handling duplicates.

     o	Errors in file opening will return a message and users will be sent back to the main menu.

     o	If users attempt to load a duplicate book or patron, they will see a message that the book or patron is already loaded; the remaining books or patrons on the list will be added to the library.

•	Users can view a list of books or a list of patrons

     o	Book list contains genre, title, author, book type, size, and status

     o	Patron list contains patron ID, patron name, and a list of any checked out books

•	Users can check out or return a book. When selecting one of those menu items, user is prompted for their ID and the title of the book.

     o	If a book is already checked out or returned, users will see a message and they will be returned to the main menu.

     o	If users enter an invalid ID or book title, they will see a message and they will be sent to the main menu.

•	Users can search for books by genre. They will be prompted to enter a genre from a list, and the program will return a list of all books matching the genre.

•	Before exiting the program, you can save the book list to the file LibraryBooks.txt, and you can save the list of patrons to the file LibraryPatrons.txt.
