# TransferTreeToRegex (C++ & QT)
The code of the program is implemented as a course project in the university. A program for collecting the text of regular expressions from its syntactic tree.

TransferTreeToRegex must be run from the console with the key specified. The program has two modes of operation. 
Test mode, which is included when inserting the flag "-t" and the mode of generating regular expression text from the 
input file to the new generated (in this case, after the "-f" flag, enter the file name with the mask "name.txt").

Examples of calling the program from the command line:
<ul>
    <li>... \ TransferTreeToRegex.exe -f name.txt</li>
    <li/>... \ TransferTreeToRegex.exe -t</li>
</ul>

## input_data
The input is given the path to the txt file, in which the first line contains the syntax tree.

The syntax tree is written in the form of a reverse Polish notation, where all the arguments are located before the operations. 

In general, a tree record consists of the basic operands and operations. The operands and operations among themselves are separated by the SPACE symbol (with the code in the table ASCII 20).

At the output, the program generates a "result.txt" file, in which it writes the text of the regular expression or error message.

For the correct execution of the program, all tokens that feed into the file on the input must comply with the rules for describing the operations and operands described. Otherwise, the program read input file error.

The syntax tree of the regular expression must be input to the input in the form of a Reverse Polish notation(RPN).

<table style="width:100%">
  <tr>
    <th> Value</th>
    <th> Internal node</th> 
    <th> Amount arguments </th>
    <th> RegExp</th>
  </tr>
  <tr>
    <th> Concatenation </th>
    <th> arg arg p &</th> 
    <th> p</th>
    <th> argarg</th>
  </tr>
  <tr>
    <td> Example</td>
    <td> input - a v c 3 &</td> 
    <td> output - avc</td> 
  </tr>
    <tr>
    <th> Alternative</th>
    <th> arg arg p |</th> 
    <th> p</th>
    <th> arg|arg</th>
  </tr>
  <tr>
    <td> Example</td>
    <td> input - a v c 3 |</td> 
    <td> output - a|v|c</td> 
  </tr>
</table>
 Where p is a positive integer lying in the range from 1 to infinity is not inclusive. p speaking the number of nodes that are children.
 
<table style="width:100%">
  <tr>
    <th> Value</th>
    <th> Internal node</th> 
    <th> Amount arguments </th>
    <th> RegExp</th>
  </tr>
  <tr>
    <th> Quantifier: the number n  </th>
    <th> arg n {} </th> 
    <th> 2</th>
    <th> arg{n}</th>
  </tr>
  <tr>
    <td> Example</td>
    <td> input - a 2 {}</td> 
    <td> output - a{2}</td> 
  </tr>
    <tr>
    <th> Quantifier: the number from n to m </th>
    <th> arg n m {,} </th> 
    <th> 3</th>
    <th> arg{n,m}</th>
  </tr>
  <tr>
    <td> Example</td>
    <td> input - a zero 6</td> 
    <td> output - a{,6}</td> 
  </tr>
</table>
Where m and n are positive integers, and also infinity and zero; In this case, n and m is the range of instances of a symbol, group, or class of characters. It is worth noting that n can not take infinity, and m take zero.
<table style="width:100%">
  <tr>
    <th> Value</th>
    <th> Internal node</th> 
    <th> Amount arguments </th>
    <th> RegExp</th>
  </tr>
  <tr>
    <th> Quantifier: + one or more </th>
    <th> arg +</th> 
    <th> 1</th>
    <th> arg+</th>
  </tr>
  <tr>
    <td> Example</td>
    <td> input - a +</td> 
    <td> output - a+</td> 
  </tr>
    <tr>
    <th> Quantifier: ? zero or one    </th>
    <th> arg ? </th> 
    <th> 1</th>
    <th> arg?</th>
  </tr>
  <tr>
    <td> Example</td>
    <td> input - a ?</td> 
    <td> output - a?</td> 
  </tr>
  <tr>
    <th> Quantifier: * zero or more  </th>
    <th> arg *</th> 
    <th> 1</th>
    <th> arg*</th>
  </tr>
  <tr>
    <td> Example</td>
    <td> input - a *</td> 
    <td> output - a*</td> 
  </tr>
</table>
