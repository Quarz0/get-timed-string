#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <limits.h>

/*
 * Reads  a line of text from standard input, within a
 * specified time (t)  in seconds, and returns it as a
 * string (char *),  sans trailing newline  character.
 * (Ergo,  if  user  inputs only "\n",  returns "" not
 * NULL.)   Returns  NULL * upon  error  or  no  input
 * whatsoever (i.e., just EOF), or if the user  failed
 * to provided an  input  within  the  specified time.
 * Leading  and  trailing  whitespace  is not ignored.
 * Stores string on heap (via malloc);  memory must be
 * freed by caller to avoid leak.
 * With each key pressed, the contents of the  current
 * line in the terminal window is rewritten (the timer
 * and  the text entered by the user)  to  update  the
 * remaining time left.
 */

char*
GetTimedString(int t)
{
    time_t a = time(NULL);
    int z = 0, l=0;
    // growable buffer for chars
    char* buffer = NULL;

    // capacity of buffer
    unsigned int capacity = 0;

    // number of chars actually in buffer
    unsigned int n = 0;

    // character read or EOF
    int c;
    // iteratively get chars from standard input
    int minutes = t / 60;
    int seconds = t - minutes * 60;
    printf("\rTime Left(%02d:%02d)  ", minutes, seconds);
    while (c != EOF)
    {
        time_t b = time(NULL);
		// if there is still time left, rewrite the current line
		// with the updated time and the text entered by the user so far
		if (b-a-z >= 1)
        {
            z = b-a;
            t--;
            minutes = t / 60;
            seconds = t - minutes * 60;
            printf("\rTime Left(%02d:%02d)  ", minutes, seconds);
            if (buffer != NULL)
            {
                buffer[n] = '\0';
                printf("%s", buffer);
            }

        }
		// if time is up, return NULL
        if (t <= 0)
            return NULL;

		// when a key is pressed
        if (_kbhit())
        {
            c = _getch();
            l++;
			// user entered a new line
            if (c == '\r')
            {
                printf("\n");
                break;
            }
			// user pressed the backspace key
            else if(c == '\b')
            {
                if (buffer == NULL)
                    continue;
                else if (buffer[0] == 0)
                    continue;

                buffer[--n] = '\0';
                printf("\b \b");
                continue;
            }
			// any other key
            else
				printf("%c", c);
        }
        else
            continue;

        // grow buffer if necessary
        if (n + 1 > capacity)
        {
            // determine new capacity: start at 32 then double
            if (capacity == 0)
                capacity = 32;
            else if (capacity <= (UINT_MAX / 2))
                capacity *= 2;
            else
            {
                free(buffer);
                return NULL;
            }

            // extend buffer's capacity
            char* temp = realloc(buffer, capacity * sizeof(char));
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[n++] = c;
    }

    // return NULL if user provided no input
    if (n == 0 && c == EOF)
        return NULL;

    // minimize buffer
    char* minimal = malloc((n + 1) * sizeof(char));
    strncpy(minimal, buffer, n);
    free(buffer);

    // terminate char*
    minimal[n] = '\0';

    // return char*
    return minimal;
}
