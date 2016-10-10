# get-timed-string
Reads  a line of text from standard input, within a specified time (t)  in seconds, and returns it as a string (char *),  sans trailing newline  character. (Ergo,  if  user  inputs only "\n",  returns "" not NULL.)   Returns  NULL * upon  error  or  no  input whatsoever (i.e., just EOF), or if the user  failed to provided an  input  within  the  specified time. Leading  and  trailing  whitespace  is not ignored. Stores string on heap (via malloc);  memory must be freed by caller to avoid leak. With each key pressed, the contents of the  current line in the terminal window is rewritten (the timer and  the text entered by the user)  to  update  the remaining time left.

This function is a modified version of CS50's library's (https://manual.cs50.net/library/) GetString function.
Supports Windows only since it makes use of "conio" library.
