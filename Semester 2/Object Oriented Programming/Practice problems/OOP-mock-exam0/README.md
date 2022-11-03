# OOP-mock-exam0

Write an application which simulates the development and testing of a software application, as 
follows:
1. The information about the development team is in a text file. Each member of the team - User
has a name (string) and a type (string), which indicates whether the user is a tester or a 
programmer. This file is manually created and it is read when the application starts.
2. Another file contains information about the issues reported by the testers. Each Issue has a 
description (string), a status (can be open or closed), the reporter – the name of the person who 
reported it and the solver – the name of the person who solved it. These are read when the 
application starts and are also stored in the file by the program.
3. When the application is launched, a new window is created for each user, having as title the user’s 
name and type (tester or programmer). (1p)
4. Each window will show all the issues, with their description, status, reporter and solver, sorted by 
status and by description. (1p)
5. Only testers can report issues, by inputting the issue’s description and pressing a button “Add”. 
The issue’s reporter will automatically be set – this will be the name of the tester who added it. 
This operation fails if the description is empty or if there is another issue with the same 
description. The user will be informed if the operation fails. (1.25p)
6. Both programmers and users can remove issues. An issue can only be removed if its status is 
closed. (1p)
7. Only programmers can resolve issues, by selecting the issue and pressing a button “Resolve”. This 
button is activated only if the status of selected issue is open. When an issue is resolved, the name 
of the issue’s solver is automatically updated to the name of the programmer who solved it. 
(1.25p)
8. When a modification is made by any user, all the other users will see the modified list of issues. 
(2p)
9. When the application is finished, the issues file will be updated. (0.5p)



Observations
1. 1p - of
2. Specify and test the following functions (repository / service):
a. Function which adds an issue. (0.5p)
b. Function which updates an issue’s status and programmer. (0.5p)
3. The application must use layered architecture in order for functionalities to be graded.
4. If you do not read the data from file, you will receive 50% of functionalities 3, 4, 5 and 6.
