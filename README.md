# Unorthodox Hello World

This repository contains two strategies for printing `Hello, world!`:

1. Co-called *genetic algorithm*
2. Machine learning like approach

Bascially two approaches have a single input: randomly generated string
out of which each algorithm must derive target string, `Hello, world!`.


## [Genetic* Approach](https://github.com/pvlbzn/evolutionary/blob/master/random_and_linear_transformation_hello_world.ipynb)

This algorithm described numerous times in various blogs and has different
flavours. Logic behind this algorithm is simple: get a *population* and mutate
it until *cost function* will output zero.

This algorithm can get complex with all the mimicry to evolution processes.
In essense it mutates input string/strings unless in a way that cost function
gets better and better results.


## [Machine Learning Like Approach](https://github.com/pvlbzn/evolutionary/blob/master/random_and_linear_transformation_hello_world.ipynb)

This approach relies on a *linear transformation*. Having a target and a random
input string, of the same length as the target, algorithm find such a linear
transformation (function) which converts the input string into the target string.

Linear transformation can be found numerically via change in data representation.
String makes more sense in a shape of array of integers.

![plot](https://github.com/pvlbzn/evolutionary/blob/master/img/plot.png?raw=true)

On this plot `target` represents a target string, `Hello, world!`, `sample` represents
a randomly generated string, subject to transform somehow into the target string.
Dashed line, `weights`, represents a vector. Using simple transformation function

<br>

`f(x, w) = x + w`

<br>

the sample string, `x`, will be transformed to `target` string via weight, `w`,
transformation.

This idea can be seen clearly on the plot where `x = 2`. Sample at `x` is slightly
above target at `x`, and weights at `x` is equally slightly below zero line.
Therefore, after transformation sample at `x` will be equal to target at `x`.
