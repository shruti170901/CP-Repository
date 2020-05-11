Chef has N vases in a row (numbered 1 through N, initially from left to right). He wants to sort them in a particular order which he finds the most beautiful. You are given a permutation p1,p2,…,pN of the integers 1 through N; for each valid i, Chef wants the i-th vase to end up as the pi-th vase from the left.

In order to achieve this, Chef can swap vases. Any two vases can be swapped in 1 minute. Chef also has a very efficient, but limited, robot at his disposal. You are given M pairs (X1,Y1),(X2,Y2),…,(XM,YM). For each valid i, the robot can instantly swap two vases whenever one of them is at the position Xi and the other at the position Yi. Note that the initial positions of the vases are irrelevant to the robot.

Formally, Chef, at any moment, may choose to perform one of the following actions, until the vases are sorted in the desired order:

Choose two indices i and j (1≤i,j≤N) and swap the vases that are currently at the positions i and j. It takes 1 minute to perform this action.
Choose an integer k (1≤k≤M) and order the robot to swap the vases that are currently at the positions Xk and Yk. It takes 0 minutes to perform this action.
Chef cannot perform multiple operations at the same time ― if he chooses to perform some operation of the first type, he has to wait for 1 minute before performing any further operations.

What is the minimum number of minutes that Chef needs to sort the vases?

Input
The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
The first line of each test case contains two space-separated integers N and M.
The second line contains N space-separated integers p1,p2,…,pN.
M lines follow. For each valid i, the i-th of these lines contains two space-separated integers Xi and Yi.
Output
For each test case, print a single line containing one integer ― the minimum number of minutes Chef needs to sort the vases.

Constraints
1≤T≤100
1≤N≤18
0≤M≤18
1≤pi≤N for each valid i
1≤Xi,Yi≤N for each valid i
Xi≠Yi for each valid i
N>10 holds in at most one test case
Subtasks
Subtask #1 (20 points): M=0
Subtask #2 (20 points): N≤5
Subtask #3 (60 points): original constraints

Example Input
3
3 1
2 3 1
2 3
5 10
2 4 5 1 3
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
4 1
3 1 4 2
1 2
Example Output
1
0
2
Explanation
Example case 1: Chef can ask the robot to swap the vases at the positions 2 and 3, and then he can swap the vases at the positions 1 and 2.

Example case 2: The robot can swap each pair of vases, so the answer is 0.

Example case 3: Chef can swap the vases at the positions 1 and 4, then ask the robot to swap the vases at the positions 1 and 2, and then swap the vases at the positions 3 and 4, taking a total of two minutes.
