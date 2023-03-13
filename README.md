
<h1 style="text-align: center;">(Nextpow2) Rounding to the next power of 2 </h1>



Out of boredom I started thinking about ways of finding the first lower or equal power of 2 for a given x. For example if x = 10 than that number would be 8 because 2^3 is the last power of 2 that is smaller or equal from it. Than I started thinking about the first higher or equal power for a given x. I was wondering if there is a way to compute both of those functions faster than a loop.





<h1 style="text-align: center;"> The Idea </h1>



Let's name the lower or equal power of 2 `lep2` and higher or equal power of 2 `hep2` then:
$$
lep2(x) = \begin{Bmatrix}
  none & x < 0 \\
 0 &  x = 0\\
  2^{\left\lfloor\log_2x\right\rfloor}  & x > 0 \\
\end{Bmatrix}
$$
and 
$$
hep2(x) = \begin{Bmatrix}
  none & x < 0 \\
 0 &  x = 0\\
  2^{\left\lceil\log_2x\right\rceil}  & x > 0 \\
\end{Bmatrix}
$$
Calculating $2^{\left\lceil\log_2x\right\rceil}$ is expensive because of the logarithm. Fortunately we have one trick that will let us calculate `lep2` and `hep2` in constant time.





 <h1 style="text-align: center;"> Algorithm </h1>



Lets consider that in our program we use `32-bit unsigned integer` x for which we want to find  `lep2` and `hep2` (`unsigned` because  any negative number would be thrown out by both functions so we don't need it and for the next step we would need all the bits). 

Let `x` be equal to 9. If we look at it its binary form we see `00000000000000000000000000001001`. If we know the leading number of zeros `lnz` (in the case of 9 its 28) we can subtract it from the total number of bits which we chose to be 32. The number we get is $k$ where (in our example $k = 32 - 28 = 4$) :
$$
2^k \leq x
$$
So `lep2` and `hep2 ` can be written as:
$$
\large \begin{matrix}
lep2(x) = 2^{bitsize - lnz(x)} &&
hep2(x) = 2^{bitsize - lnz(x) + 1}
\end{matrix}
$$





 <h1 style="text-align: center;"> Lep2 implementation </h1>



Pseudo-code for `lep2` would look like this : 

```pseudocode
def lep2(ui32: x):    
    x = x or x right-shifted by 1
    x = x or x right-shifted by 2
    x = x or x right-shifted by 4
    x = x or x right-shifted by 8
    x = x or x right-shifted by 16
    
    return x xor x right-shifted by 1
```



In the first 5 operations of the function we will replace any `0` into `1` in the first `k` bits from the right.

```pseudocode
Eg. 
x = 9 = 00000000000000000000000000001001

1.    x = x or x right-shifted by 1
2.    x = x or x right-shifted by 2
3.    x = x or x right-shifted by 4
4.    x = x or x right-shifted by 8
5.    x = x or x right-shifted by 16


Operation 1
	00000000000000000000000000001001
or 	00000000000000000000000000000100
------------------------------------
=	00000000000000000000000000001101	
	
Operation 2
	00000000000000000000000000001101
or 	00000000000000000000000000000011
------------------------------------
=	00000000000000000000000000001111	

Operation 3
	00000000000000000000000000001111
or 	00000000000000000000000000000000
------------------------------------
=	00000000000000000000000000001111	

Operation 4
	00000000000000000000000000001111
or 	00000000000000000000000000000000
------------------------------------
=	00000000000000000000000000001111

Operation 5
	00000000000000000000000000001111
or 	00000000000000000000000000000000
------------------------------------
=	00000000000000000000000000001111

```



For the last operation where the function returns the result we need to extract:
$$
2^k
$$
so we **XOR** modified `x` with its **right-shifted** by 1 copy:

```pseudocode
...
6. return x xor x right-shifted by 1


Operation 6
	00000000000000000000000000001111
xor	00000000000000000000000000000111
------------------------------------
=	00000000000000000000000000001000

return 00000000000000000000000000001000 = 8 

```

`closest lower or eqal power of 2 for 9 is 8`

To recap with function `lep2` we first set all bits from the right to **k-th** to `1`. Than we unset all bits except the **k-th**  one. This way we get 1 **left-shifted** to the left by `k` which is equal to $2^k$.





<h1 style="text-align: center;"> Hep2 implementation </h1>



Pseudo-code for `hep2` would look like this : 

 ```pseudocode
def hep2(ui32: x):
	x = x - 1
	x = x and x right-shifted by 1
    x = x and x right-shifted by 2
    x = x and x right-shifted by 4
    x = x and x right-shifted by 8
    x = x and x right-shifted by 16
    
    return x + 1
 ```



In the first operation we subtract `1` from x. 

```pseudocode
Eg.
x = 9 = 00000000000000000000000000001001

1. x = x - 1

Operation 1
	00000000000000000000000000001001
-	00000000000000000000000000000001
------------------------------------
=	00000000000000000000000000001000
```



In the next 5 operations of the function we will replace any `0` into `1` in the first `k` bits from the right just like in `lep2`.

```pseudocode
...
2.    x = x or x right-shifted by 1
3.    x = x or x right-shifted by 2
4.    x = x or x right-shifted by 4
5.    x = x or x right-shifted by 8
6.    x = x or x right-shifted by 16


Operation 2
	00000000000000000000000000001001
or 	00000000000000000000000000000100
------------------------------------
=	00000000000000000000000000001101	
	
Operation 3
	00000000000000000000000000001101
or 	00000000000000000000000000000011
------------------------------------
=	00000000000000000000000000001111	

Operation 4
	00000000000000000000000000001111
or 	00000000000000000000000000000000
------------------------------------
=	00000000000000000000000000001111	

Operation 5
	00000000000000000000000000001111
or 	00000000000000000000000000000000
------------------------------------
=	00000000000000000000000000001111

Operation 6
	00000000000000000000000000001111
or 	00000000000000000000000000000000
------------------------------------
=	00000000000000000000000000001111

```



After operations **(1 - 6)**:
$$
x \geq 2^k-1
$$
so we just add `1` to x:

```pseudocode
...
6. return x + 1


Operation 6
	00000000000000000000000000001111
+	00000000000000000000000000000001
------------------------------------
=	00000000000000000000000000010000

return 00000000000000000000000000010000 = 16 

```

`closest higher or eqal power of 2 for 9 is 16`

To recap with function `hep2` we first subtract `1` from it and than set all bits from the right to **k-th** to `1`. Than we add `1` which makes :
$$
x + 1\geq 2^k
$$





<h1 style="text-align: center;"> C++ Code </h1>



Here are both functions written in c++:



# [Lep2.cpp](./lep2.cpp)
```c++
int lep2(unsigned int x){
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	
	return x ^ (x >> 1);
}
```

# [Hep2.cpp](./hep2.cpp)

```c++
int hep2(unsigned int x){
	x--;
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x+1;
}
```





fin.

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>
