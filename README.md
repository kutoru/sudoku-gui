# What is this?
This is my attempt at writing a GUI application with C++.\
In the past I wrote a few small CLI Sudoku apps, but this time I wanted to try making a GUI app with some user authorization elements.\
This project is entirely based on WinForms.\
I also wanted to learn how C++ can interact with databases, so I also used MySQL here.

# How to try it?
You will have to setup MySQL database and optionally compile the hashdyn project.

MySQL setup:\
Make sure that you are running MySQL.\
You might also need to specify MySQL `include` and `lib` folders in the project's settings, in "VC++ Directories" category.\
Create a table called `sudoku` and run the `create_db.sql` script.\
After that enter your MySQL password in the `db.h` file.

Password encryption setup:\
For password encryption I used [Crypto++ 8.7.0](https://www.cryptopp.com/index.html) library.\
If you don't care about the encryption, you can just delete the elements related to it in the code. To do that, change the contents of the `EncryptPassword` function and delete the `"hashdyn.h"` import (both function and import are in `util.h`).\
If you do care, you will have to compile the code from the `hashdyn` folder.\
To do that, make sure you have Crypto++ library downloaded and compiled. If you want more detail on that, search it online.\
After that go into the `hashdyn` project settings and make sure to specify path to Crypto++ in categories "VC++ Directories" and "Linker > General".\
And finally after that you should be able to compile hashdyn and it should work in the Sudoku project.

# Project status
The project is quite a mess, but I did everything I originally wanted to, so I consider it done.
