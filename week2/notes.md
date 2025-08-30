# Notes

for const use capitals e.g. const int N = 3
use casting for changing types e.g. ints to float use (float)

int const N = 3;
int scores[N];
So makes array of length N which would be 3

For function passing  in C would be int array[], also need int length to tell length of it

double quotes "" for strings, '' for chars - just a convention but implies to interpreter to end with /0, which you dont want with char

char c1 = 'H' -> use %i will get into ascii value 72

string s = "HI!"
printf("%c%c%c", s[0], s[1], s[2])
prints HI!

String is sequence of chars, so really a more precise type of array containing chars

string always has one extra byte to represent end of it, always 0 usually \0

so using %i for the s[0] etc gets 72, 73, 33 and for s[3] a 0 conventionally called NUL 
a sentinel character, terminating

string words[2]
words[0] = "HI!"
words[1] = "BYE!"

printf("%c%c%c", words[0][0], words[0][1], words[0][2]) would print HI!

Don't use checks in a loop, e.g. for i = 0; i < strlen(baaa); i++
or better do i = 0, n = strlen(baaa); i < n; i++ - note the comma not

command line arguments
int argc, string argv[] instea of void in for main
integer (argument count) and array of strings (argument vector)

argv[0] will have program name, so argv[1] to get first actual input
so argc to check user has put in right number of args
argv[argc-1] to get last element

echo $?
to get exit status

int hours[5] = {1, 2, 3, 4, 5}

return 0 to indicate succes, though after c99 its automatic

variables passed to functions are passed by value so are only copies in C
pointers for passed by reference, passing reference to original memory so can get changed

arrays are passed by reference in C