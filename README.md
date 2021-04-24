# Dijkstra's-Algorithm-in-C++

There is a node class to store the information of all nodes like id, coordinates and other variables like cost, nearest_node_id that are helpful while implementing the algorithm.

## Flow of code:

### In main function
1. Object for all the nodes is created and stored in a dictionary.
2. Connections of nodes are specified.
3. find_shortest_path function is called

### In find_shortest_path function:
1. This function takes in the ids of start and end nodes alongwith the dictionary that has the complete information.
2. Usually cost of all the nodes is set with respect to start node, but here cost is set with respect to end node. (This is because it makes the job of finding the shortest path easier)
3. Referring to end node's object, set_costs function is called that takes in the dictionary and sets the cost after resetting them. (-1 is there instead of infinity)
4. While setting the costs, it stores the id of the nearest node for the node whose cost is to be set.
5. After this function is over, find_shortest_path function tracks the nearest node starting from start node until it reaches end node and stores this tracking route in a list.
6. This list is then returned to main function, which is displayed in the end.
