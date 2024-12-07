# INTRODUCTION
This program is a small, customizable customer database with a few different functions to help utilize it. I wrote this program entirely from scratch on Ubuntu for my C language class at UCSC! It uses a hash table to store the customers in the database. Each customer's personal information is stored within a linked list. When the program starts, it will simply prompt the user to type a command. Next, I'll offer a brief description of the program's command functionalities.
# list
The first command is **list**. Typing "list" will display the entire current state of the database, customer by customer.
# add
The next command is **add**. Typing "add" will tell the program that the user wants to add a customer to the database. It will prompt the user to enter the customer's email, name, shoe size, and favorite food (in that order). If the user types in an email address that already exists in the database, the program will simply overwrite the currently existing customer's other information, as entered by the user.
# delete
By typing "delete," users can delete customers from the database. The program will subsequently prompt the user to type the email address of the customer they want to delete from the database. Then, the program will delete that customer and **all** of their associated information from the database.
# lookup
Typing "lookup" into the command prompt will let the user find the information of a specific customer in the database. After typing "lookup," the program will prompt the user to enter the desired customer's email address. Then, the program will display the customer's **entire** associated information.
# save
This one is pretty self-explanatory. Typing "save" into the command prompt will update the customer database file with the **current** state of the database within the program. Any changes made, such as customers being added or deleted, will be saved to the file. So, if the user runs the program again after saving and quitting, their changes will be a part of the initial database.
# quit
Lastly, typing "quit" into the command prompt will exit the program, freeing all memory being used while the program was running. The program will **not** be saved when the user quits unless they previously typed "save."
