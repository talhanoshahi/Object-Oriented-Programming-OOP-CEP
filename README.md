# Object-Oriented-Programming-OOP-CEP

Main Algorithm:
The attached C++ code takes a simple text file (the only condition is that the file can be read and should be in format), which contain the information about the Graph’s Nodes and Edges and the information is stored in an object of a graph class. After reading and closing the input file, the data is then flushed into the output file (of format .dot or .gv). After flushing the data into output file, the output file is compiled by dot tool of Graphviz to convert it into a supported pictorial format.

Supported Formats:
• Input Format:
	Any readable text file.

• DOT Formats:
	i. .dot
	ii. .gv

• Pictorial Output Formats:
	i. bmp
	ii. png
	iii. pdf
	iv. eps
	v. jpe
	vi. jpg
	vii. jpeg
	viii. ps
	ix. gif

Input Format:

The input in the file should be in the following format:

#Following are nodes
//They would be stored as nodes in program
;Nodes
NodeNumber1 NodeName1
NodeNumber2 NodeName2
NodeNumber3 NodeName3
#following are edges
// They would be stored as edges in program

;Edges
NodeNumber1 NodeNumber2 Weight1
NodeNumber1 NodeNumber3 Weight2

#following is the graph type
// They would tell the program its operator type
;Graph Type
Graph Type

Explaination:
The input file is compulsory to be in the above format as it tells the program how to store data. 

"#" and "//" are used to tell the program that this is a comment and the program will leave the line as it is a won’t include in the Graph class. ";" tells the program that this change the reading mode of the program and if it was previously reading edges, it will now read nodes or graph type depending upon the given data. Edges can come anywhere between the Nodes data and Graph Type but changing reading type will require ";" followed by the the data type.

Writing the graph type is optional, but if you do not write it or it is out of format, the program would assume the graph to be undirected.

Command Line Parameters:
The program can be compiled using a makefile with the command make and the created object files can be deleted using make clean. After compiling the program, the program can be executed by writing any one of these commads.

1. ./GraphWriter
2. ./GraphWriter "Inputfilename.txt"
3. ./GraphWriter "Inputfilename.txt" "PictorialOutputFile.format"
4. ./GraphWriter "Inputfilename.txt" "DOT_OutputFile.format" "PictorialOutputFile.format"

Note that command number 2 and 3 would not generate a dot or gv file, while command number 4 will generate a dot or gv file depending the format you pass in the 3rd parameter. The first command will ask you if you want to generate a dot or gv file and will act accordingly.
