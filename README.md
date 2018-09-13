# TransferTreeToRegex (C++ & QT)
    The code of the program is implemented as a course project in the university. A program for collecting the text of regular 
expressions from its syntactic tree.

    TransferTreeToRegex must be run from the console with the key specified. The program has two modes of operation. 
Test mode, which is included when inserting the flag "-t" and the mode of generating regular expression text from the 
input file to the new generated (in this case, after the "-f" flag, enter the file name with the mask "name.txt").

Examples of calling the program from the command line:
... \ TransferTreeToRegex.exe -f name.txt
... \ TransferTreeToRegex.exe -t


_____________________________________________________________________________________________________________________________________________
_____________________________________________________input_data______________________________________________________________________________
_____________________________________________________________________________________________________________________________________________
    The input is given the path to the txt file, in which the first line contains the syntax tree.
    The syntax tree is written in the form of a reverse Polish notation, where all the arguments are located before the operations. 
    In general, a tree record consists of the basic operands and operations. The operands and operations among themselves are separated
by the SPACE symbol (with the code in the table ASCII 20).
    At the output, the program generates a "result.txt" file, in which it writes the text of the regular expression or error message.
    For the correct execution of the program, all tokens that feed into the file on the input must comply with the rules for describing 
the operations and operands described. Otherwise, the program read input file error.

The syntax tree of the regular expression must be input to the input in the form of a Reverse Polish notation(RPN).
Value                 Internal node             Amount arguments           RegExp
Concatenation         <arg> <arg> p &                  p                 <arg><arg>
example: input - a v c 3 & output - avc
The alternative       <arg> <arg> p |                  p                 <arg>|<Arg>
example: input - a v c 3 | output - a|v|c
_____________________________________________________________________________________________________________________________________________
Where p is a positive integer lying in the range from 1 to infinity is not inclusive. p speaking the number of nodes that are children.
_____________________________________________________________________________________________________________________________________________
Quantifier:
the number n               <arg> n {}                   2                  <arg>{n}
example: input - a 2 {} output - a{2}
Quantifier:
the number from n to m     <arg> n m {,}                3                  <arg>{n, m}
example: input - a zero 6 {,} output - a{,6}
_____________________________________________________________________________________________________________________________________________
Where m and n are positive integers, and also infinity and zero; In this case, n and m is the range of instances of a symbol,
group, or class of characters. It is worth noting that n can not take infinity, and m take zero.
_____________________________________________________________________________________________________________________________________________
Quantifier:
+ one or more               <arg> +                     1                   <arg>+
example: input - a + output - a+
Quantifier:
? zero or one               <arg> ?                     1                   <arg>?
example: input - a ? output - a?
Quantifier:
* zero or more              <arg> *                     1                   <arg>*
example: input - a * output - a*
