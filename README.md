# CS50 Solutions

## Important Notes

* When I first started with CS50, I wanted to learn vim as well. So I decided that I would code all of CS50's problem sets (that I can use vim with) with vim. While you are exploring the code you might find that some of my code might have weird 'learning-vim-artifacts' or are simply defunct of proper documentation, because I was just so done with vim. (Vim is a great editor! Just that it has a super steep learning curve to learn to use. And that might bring you lots of frustration, which it did for me.)
* I already have some semblance of C knowledge when I started with CS50. So for some of the problem sets, I might have made use of certain knowledge that hasn't been introduced yet to solve the problem more efficiently. An example of this would be 'crack' in problem set 2, where I used recursion and used pointers before they were even introduced during the course to solve the problem more efficiently.
* Like I said, I already know some C, so I made it a point to complete the problem sets without using CS50's helper functions in CS50.h, and try to do it the typical 'C-way'. I like being in more control over the verbose implementation details of my code.

## Notes about my solutions for individual problem sets

1. Problem Set 0
* Did not really attempt as I am already quite familiar with programming/control structures, and I am quite familiar with scratch.
2. Problem Set 1
* Credit - Implementation of Luhn's algorithm was fine but the other validation checks (checking of number of digits, first digits, etc) was quite sloppily coded by me. You can just compare the whole credit card number directly to check what type of CC it is, instead of isolating individual digits to check them.
3. Problem Set 2
* Crack - If you plan on compiling it locally, make sure you have the compilation flags '-lcrypt' for your linker to include the code needed for crypt() to run. My solution uses pointers as well as recursive functions which are only introduced in subsequent lectures, so that might be a bit confusing for you. Other than that, I think the code is pretty efficient and it can bruteforce DES hashes of any length (until it overflows of course).
4. Problem Set 3
* Resize (more comfortable) - I couldn't be bothered with some error checking of inputs but check50 doesn't check for malicious input anyway. (Yeah I think my code breaks if you enter a negative scale factor, dunno haven't tried) But yes, the code resizes correctly for all positive scale factors. (0.0, infinity)
5. Problem Set 4
* I faced a problem with working on the pset on my local Linux machine. The Makefile provided by CS50 does not include "dictionary.h" as a dependency so it doesn't rebuild when you call `make`, even if you have made changes to the source file. If you face the same problem (you won't face this problem if you are using the online CS50 IDE), you can just clone my Makefile in the pset4 folders.
* I managed to get 25th place in the [speller big board challenge](https://speller.cs50.net/cs50/2019/x/challenges/speller/#user/chrisgzf)! The code that I used to achieve that is unfortunately, not here. Go try the challenge!
![Big Board Challenge Results](https://raw.githubusercontent.com/chrisgzf/cs50/master/pset4/25th_place.png "25th Place!")

Have fun coding! Do let me know if you have any questions regarding my code.
