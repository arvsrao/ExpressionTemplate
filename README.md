# Expression Template

## Goal:

When naively adding several vectors 

```c++
auto sum = v + (w + (l + b));
```

temporary vectors are created for `l+b`,  `w + l + b`, and `v + w + l + b` before assignment to `sum`. The temporaries 
created prior to assignment could be elided if instead an expression tree was iteratively built up. The final evaluation
would be deferred when assignment is requested.

[Eigen][2] uses [CRTP][3] and expression trees to prevent the creation of temporaries and lazy evaluate summation and 
product of matrices. This project is a toy demonstration of what [Eigen][2] does. Specifically, summation of vectors without
creating temporary objects.

## References
[Slides][1] from a presentation of [Eigen][2] at Ecole Polytechnique.


[1]: http://downloads.tuxfamily.org/eigen/eigen_CGLibs_Giugno_Pisa_2013.pdf
[2]: https://eigen.tuxfamily.org/dox/index.html
[3]: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern