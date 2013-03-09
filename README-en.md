aese is An ANSI Escape Sequences Emulator
=========================================

What can we do?
--------------

Terminal standard Windows, "Command Prompt" so called, does not support the ANSI escape sequences.

aese command to reproduce the ANSI escape sequences in the Windows API.

I have implemented the following functions.

1. Remove the escape sequence receives the standard output
2. Reproduce the character attributes(partial)
3. Reproduction of the movement of the cursor(not implemented)

How to use
----------

    echo ^[[43maaa^[[0m|aese

^[ is entered as CTRL + [. Code is 0x1B.

License
-------

Copyright(c) 2013 sharkpp All rights reserved.

This program is published under The MIT License.
