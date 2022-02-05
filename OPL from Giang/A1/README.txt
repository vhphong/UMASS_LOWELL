* Comparison/Contrast?
Every program done as part of the assignment prompts the user for an input N and K during runtime,
however Prolog does not prompt the user for an input. While you're running the prolog terminal,
to get the N and K inputs you'd just do a function call "combination(K, N, L)." within the terminal to
output the combination. You'd enter a value for the variables "K" and "N" while leaving L as just "L"
when you call the function. For example, in the terminal you'd just type "combination(2, 4, L)." to call
the function.

Python and ADA resemble pseudo-code in some way.

The outputs for all these programs appear to be the same, with the standard being one line for every
unique combination, however Chhoung and I were unable to get that standard format working for Haskell.
Haskkell prints values of a list inside of a list rather than in columns like the other results.

Another thing to mention is that C# handles a recursive solution compared to the rest which rely on iterators.
C# looks more object-oriented language compared to the other languages.

* What was easy?
Python was definitely the easiest out of all the other assignments. Python syntax feels more like pseudo-code than actual programming which
allowed for easy readibility and implementation. Not to mention, I've had a few years of experience with Python so creating this was very easy.

* What was hard?
I would say Haskell would be the hardest. Chhoung and I struggled to work on the code because the syntax is hard to understand, however that
gist.github solution helped us to get the output as well as to break down how the combination worked for this assignment. Although even with
the explanation, it's still hard to understand how the code is working during runtime as the code gets confusing.

ADA was second to being the hardest. I would not have been able to get the ADA combination if it weren't for the help of the rosettacode solution
down below in the sources. While it was the hardest, I could definitely understand the solution as it does resemble pseudo-like code. I noticed that
with ADA, it handles declarations first before attempting to run through the function body after the 'begin' statement, and for every begin, if, or
loop statements put, it would always need an end statement to tell the computer that the statements have served their purpose. I also noticed that
not a lot of the low level tasks exists within the libraries of ADA, so in the code here it defines procedures which you can also view them as
functions, types, as well as subtypes that have been developed manually.

* Are there noticeable differences in speed?
I didn't seem to notice any differences in speed with the assignments. Though if I were to guess would be the slowest in large cases,
it might be the C# code because of the fact that it's written in recursion. I'm aware recursion is slower than iteration so that's why.

* What do you like/dislike?
I definitely like either Python or C#. Both are more intuitive to read and contain many libraries that take care of lower level tasks.
What I would say I would dislike is everything else besides those two languages. Every one of those other languages have a steeper
learning curve to using them proficiently and can be annoying to read as well as debug.

* Did you find iterators to be helpful?
I will say that iterators are indeed helpful. They're very convenient for traversing through values contained in different data types
such as arrays and lists.

Sources:
https://stackoverflow.com/questions/26546523/print-2d-list-of-lists-in-haskell
https://gist.github.com/cdepillabout/92e6c6bde7eec5e29227
http://www.swi-prolog.org/man/clpfd.html
http://rosettacode.org/wiki/Combinations
