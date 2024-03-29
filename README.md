**C Code for Graph Analysis**

This C code is designed to analyze graphs and perform various operations on them. It includes functionalities for computing shortest paths, maintaining a ranking of top graphs and processing commands from standard input. This README provides an overview of the code's structure and key features.

>Features:
1. Graph Analysis:
The code can read and analyze graphs represented as matrices of node connections and edge weights. It computes the sum of shortest path distances in each graph using Dijkstra's algorithm.

2. Top-K Ranking:
The code maintains a ranking of the top-K graphs with the shortest total path distances. It uses a max heap data structure to efficiently manage and update this ranking as new graphs are processed.

3. Command Line Interface:
The code accepts commands from standard input, allowing you to interact with it. Two main commands are supported:
-A (AggiungiGrafo): Add a new graph to the analysis.
-T (TopK): Retrieve and print the top-K ranked graphs.


>Code Structure:

The code is organized into several sections:

-Global Variables and Definitions:
Global variables are declared to manage data and settings used throughout the code.
Definitions for constants and macros are provided for clarity.

-Graph Analysis Functions:

1.The compute_Dijkstra function calculates the sum of shortest path distances in a graph.
Heap operations (max_heapify and build_max_heap) are used for maintaining the top-K ranking of graphs.

2.The read_and_save_Graph function reads graph data from standard input, computes its shortest path sum, and updates the ranking.

3.The aggiungiGrafo function is called when the "A" command is received to add a new graph to the analysis.

-Top-K Ranking Functions:

1.The print_results_by_index function prints the top-K ranked graphs by their index.

2.The TopK function is called when the "T" command is received to retrieve and print the top-K ranked graphs.

-Main Function:
The main function serves as the entry point of the program.
It reads input commands, processes them, and manages the overall execution of the graph analysis.


>Notes:

The code efficiently maintains a ranking of top-K graphs using a max heap, reducing the need for expensive sorting operations.
It assumes that the input graphs are represented as matrices, with nodes and edge weights specified.

