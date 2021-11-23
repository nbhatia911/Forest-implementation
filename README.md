# Forest-implementation


- There is a Forest of nodes. Every node in the forest has an ID. 
- The forest nodes can have parent node. 
- The forest has an invariant that every parent ID is smaller than it descendants. 
- The forest support a remove operation of forest node elements. 
- The remove operation receives a list of nodes IDs.


Eg.

- Forest1 has nodes - [0, -1] [1, 0] [2, -1] [3, 1] [4, 2] [5, 2] [6, 3] [7, 3] [8, 5] [9, 6] [10, 7]
- Node with -1 are root nodes and have no parent in forest
- Remove nodes 1,2,6
- Output - [4,-1] [5,-1] [8,5] [0,-1] [3,0] [7,3] [9,3] [10,7] 


# Printing Forest (Forest1)
------ Printing root 2

Level 1: [2,-1] 

Level 2: [5,2] [4,2] 

Level 3: [8,5] 

------ Printing root 0

Level 1: [0,-1] 

Level 2: [1,0] 

Level 3: [3,1] 

Level 4: [7,3] [6,3] 

Level 5: [10,7] [9,6] 

## Removing nodes from forest
Removing node 1

node 1 removed from parent list head

Removing node 2

Deleting root node 2

Removing node 6

node 6 removed from parent list 

## Printing Forest (Forest1 after removal)
------ Printing root 4

Level 1: [4,-1] 

------ Printing root 5

Level 1: [5,-1] 

Level 2: [8,5] 

------ Printing root 0

Level 1: [0,-1] 

Level 2: [3,0] 

Level 3: [7,3] [9,3] 

Level 4: [10,7] 

# Printing Forest (Forest2)
------ Printing root 0

Level 1: [0,-1] 

Level 2: [4,0] [3,0] [2,0] [1,0] 

Level 3: [15,4] [11,3] [14,3] [13,3] [12,3] [10,2] [9,2] [8,2] [7,1] [6,1] [5,1] 

Level 4: [16,11] [17,11] [18,11] [20,12] [19,12] 

## Removing nodes from forest
Removing node 0

Deleting root node 0

Removing node 3

Deleting root node 3

Removing node 11

Deleting root node 11

## Printing Forest (Forest2 after removal)
------ Printing root 18

Level 1: [18,-1] 

------ Printing root 17

Level 1: [17,-1] 

------ Printing root 16

Level 1: [16,-1] 

------ Printing root 12

Level 1: [12,-1] 

Level 2: [20,12] [19,12] 

------ Printing root 13

Level 1: [13,-1] 

------ Printing root 14

Level 1: [14,-1] 

------ Printing root 1

Level 1: [1,-1] 

Level 2: [7,1] [6,1] [5,1] 

------ Printing root 2

Level 1: [2,-1] 

Level 2: [10,2] [9,2] [8,2] 

------ Printing root 4

Level 1: [4,-1] 

Level 2: [15,4] 
