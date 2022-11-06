# zero_one_knapsack

0/1 Knapsack Problem study, following the [educative.io](https://www.educative.io/courses/grokking-dynamic-programming-patterns-for-coding-interviews/RM1BDv71V60) tutorial.

## Useful Links
- [link1](https://youtu.be/nLmhmB6NzcM)
- [link2](https://youtu.be/xOlhR_2QCXY)
- [link3](https://youtu.be/xCbYmUPvc2Q)
- [link4](https://youtu.be/cJ21moQpofY)
- [link5](https://youtu.be/zRza99HPvkQ)
- [link5](https://youtu.be/yV1d-b_NeK8)

## Formula
- N is the number of items
- C is the knapsack capacity
- P is the profits vector
- W is the weights vector
- X is the answer vector

$$N \in \mathbb{N}$$

$$C \in \mathbb{R}, \ C \geq 0$$

$$\forall i \in \mathbb{N}, \ 0 \leq i < N$$

$$P = \\{p_i \ | \ p_i \in \mathbb{R} \\}$$

$$W = \\{w_i \ | \ w_i \in \mathbb{R}\\}$$

$$X = \\{x_i \ | \ x_i \in \\{0, 1\\}\\}$$


Find the X vector such that $\forall x_i \in X$ satisfies the following criterias

$$max\sum_{i=0}^{N-1}x_ip_i$$

$$\sum_{i=0}^{N-1}x_iw_i \leq C$$



## Compiler
