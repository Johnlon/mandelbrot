# Fixed point Integer and Floating point Mandelbrot implementations

A Fixed point integer implementation and a line by line equivalent Floating point implementations of Mandelbrot in C.

The fixed point implementation is part one of understanding how to translate the floating point implementation into 8 bit assembler
or other non-floating point platforms or languages.

This will be used as the basis for the Mandelbrot implementations in the [SPAM-1 cpu](https://github.com/Johnlon/spam-1).

The fixed point impl uses "8.8" encoding in 16 bit "short" integers, where for example decimal 3.5 is hex 0x380 and decimal 2.25 is hex 0x240 (0x40 being 1/4 of 0x100).

# floatText.c

```text
$ gcc floatText.c && ./a.out 

   : 0         10        20        30
00 : ........,,'''''''~~~=:[+~~'',,,,
01 : .......,,'''''''~~~=+[X:=~~'',,,
02 : .......,'''''''~~~=+;   ==~''',,
03 : ......,'''''''~~~=+:[  <:+=~'',,
04 : ......,''''''~~==:#&     [?=''',
05 : ......''''''~===+;        #=~'',
06 : ......''''~=+==+:         <+~'''
07 : .....,''~~=:;;;:[          <~'''
08 : .....'~~~==:x  o&          :~'''
09 : .....'~~==:/               :~'''
10 : .....~~=+:<O               +~~''
11 : .....                     [+~~''
12 : .....~~=+:<O               +~~''
13 : .....'~~==:/               :~'''
14 : .....'~~~==:x  o&          :~'''
15 : .....,''~~=:;;;:[          <~'''
16 : ......''''~=+==+:         <+~'''
17 : ......''''''~===+;        #=~'',
18 : ......,''''''~~==:#&     [?=''',
19 : ......,'''''''~~~=+:[  <:+=~'',,
20 : .......,'''''''~~~=+;   ==~''',,
21 : .......,,'''''''~~~=+[X:=~~'',,,

```

# floatColour.c

```
$ gcc floatColour.c && ./a.out  
```

![float.png](float.png)


# integer.c

```
$ gcc integer.c -lm  && ./a.out  
```

![integer.png](integer.png)

