# assignment-2
Write a program to read a postifx expression and compute its value. Variables are string of one or more characters and numbers are one or more digits. All tokens are separated with a single space.

###Sample I/O
```sh
Enter a postfix expression with a $ at the end: ab 22 * c + $

Enter the value of ab: 2

Enter the value of c: 4
Final Value: 48

Continue (y/n)? y
Enter a postfix expression with a $ at the end: tom jerry 123 + tom * - $

Enter the value of tom: 2

Enter the value of jerry: 3
Final Value: 250

Continue (y/n)?
```

##Source.cpp works however it uses (vectors & sstream) in addition to everything else used in the original source from Assignment #1.

##Main.cpp has a bug but it doesn't need additional libraries like Source.cpp
