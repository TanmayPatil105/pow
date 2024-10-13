This program implements an algorithm to calculate the value of 'A' raised to the power of 'B'. ie. A ^ B

No! This does not take less time than the original pow implemented in glibc.
The original glibc implementation is almost twice as fast as this one.

But worth the time wasted.

## Algorithm

Let's go step by step.\
If you have taken a look at the code. you'll see a magic `(mgk)` array defined and it's calculation takes up most of the time.
Here are the magic array's computed for different B values:

```
1 -> [ 1]
2 -> [ 1, 2]
3 -> [ 1, 6, 6]
4 -> [ 1, 14, 36, 24]
5 -> [ 1, 30, 150, 240, 120]
6 -> [ 1, 62, 540, 1560, 1800, 720]
7 -> [ 1, 126, 1806, 8400, 16800, 15120, 5040]
```

Let's dissect on what's happening here:

For this algorithm what is we use is recursive difference method.\
In order to find this algorithm first I had to do some hardwork of calculating the power's beforehand using a calculator.\
Let's say we want to calculate `3^4`.

1. How did we get to the magic array?

![Power of 4](https://github.com/user-attachments/assets/0b290e63-923c-48d9-b401-adbdbec32034)

In the figure above, the blue column displays the numbers from 1 to N, while the purple column shows those numbers raised to the power of 4.\
Now, to get to our magic array, we will perform recursive differences until we obtain a common difference.\
So, if you look at the inclined grid, you'll notice the number present at a location is equal to the difference between the number in the previous column and the number above the number in the previous column.

To better understand here's a expression: `grid[x][y] = grid[x-1][y] - grid[x-1][y-1]`.

This process continues until we obtain a common difference, which in the example above is 24. If you do some quick calculations, you'll realize that 4! = 24.

**We can generalize this: while taking recursive differences of the nth power of numbers, we will reach a common difference equal to n!.**

But where is the magic array?\
The numbers marked in red, combined with the common difference, form our magic array.\
In the case of 4, as we mentioned earlier, it is [1,14,36] + [24].


Let's create the same diagram for power of 3.

![Power of 3](https://github.com/user-attachments/assets/dc11760d-0520-43a8-8a8a-98b2b85d8ae9)

The importance of magic array is we can generate the whole grid above by using it. Take a look:
```
1 = 0 + 1
15 = 1 + 14
16 = 1 + 15
50 = 14 + 36
65 = 15 + 50
81 = 16 + 65
```
which is equal to `3^4`. Similarly, we can calculate fourth power of all other numbers.

2. How to generate this magic arrays?

Now the most important problem is how we can find these numbers in magic arrays. Do they share any patterns, and does this pattern work for all magic arrays?
**Yes!**

![Magic array's](https://github.com/user-attachments/assets/f8789cb4-e4e7-438d-9de7-438faf1afd09)

Here, number present at every location is equal to the sum of number in the previous row and the number to the left to the number the previous row multiplied by the column number.

`grid[x][y] = (grid[x][y-1] + grid[x-1][y-1]) * column`.


### Summary

1. The first step is to generate the magic array.
2. Next, create the inclined grid, and use the sum of its numbers to calculate the powers.
