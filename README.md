# Horo Language
:sparkles: An elegant language that compiles into C++ :sparkles:


## Synopsis

* a small language with clear and easy-to-read syntax
* keep C++ logic and get better coding experience
* made for C++ algorithm developer


## Hello World!

```C++
#include <iostream>
using namespace std

int main
	cout << "Hello World!" << endl
	=> 0
```


## How to Install

1. Prerequisites:
	* ```g++``` 4.8.1 or newer
	* GNU Make 3.82 or newer

2. Open your terminal and run these commands:
	```bash
	$ git clone https://github.com/jjwong0915/horo-lang.git
	$ cd horo-lang/compiler
	$ make
	$ sudo make install
	```

3. Try ```horo --help``` if it's successfully then you're done :D


## Syntax Guide

* Functions
```C++
int add int a int b
	=> a + b 
bool less int x int y
	=> x < y
```

* Variables
```C++
int a = 1
double b = 0.5
char c[] = 'INFOR'
```

* Loops
```C++
for i = 0 to 10
	cout << i << " "
// result: 0 1 2 3 4 5 6 7 8 9
```

* Conditions
```C++
if a > b
	cout << "a is bigger than b"
else if a == b
	cout << "a is equal to b"
else 
	cout << "a is smaller than b"
```

* Structures
```C++
struct node
	int data
	node* next
```


## Contributors
*  [@jjwong0915](https://github.com/jjwong0915) - JJ Wong <[jjwong0915@gmail.com](mailto:jwong0915@gmail.com)>
*  [@eethan1](https://github.com/eethan1) - Ethan Lin <[call132call132@gmail.com](mailto:call132call132@gmail.com)>


## License
[ISC License](https://raw.githubusercontent.com/jjwong0915/horo-lang/compiler/LICENSE)