## A implementation of SKIBCS'B'C'Y combinator calculus using binary tree 


### SKIBCS'B'C'Y combinator

```
Ix = x
Kfx = f  
Sfgx = (fx)(gx)    (=fx(gx))
Bfgx = f(gx)
Cfgx = (fx)g       (=fxg)
S'ufgx = u(fx)(gx)
B'ufgx = uf(gx) 
C'ufgx = u(fx)g

Yf = f(Yf) = f(f(Yf)) = f(f(f(Yf))) = ...
```

### Combinator expressions can be represented as a binary tree

the next expression is "not x"
``` 
C(CI(KI))Kx

 -- conversion to binary tree -->

    r---x
---
   |    r---K
    l---
       |            r---I
       |        r---
       |       |    l---K
       |    r---
       |   |   |    r---I
       |   |    l---
       |   |        l---C
        l---
            l---C
```

### Running the tests 

unzip [SKIBCY-win64.zip](https://github.com/AkiraHakuta/SKIBCY/releases)   

Open `Dos Command Prompt`  

``` 
/* test1.txt */

Ix;
Kfx;
Sfgx;
Bfgx;
Cfgx;
S'ufgx;
B'ufgx;
C'ufgx;
```

```
> skibcy.exe test1.txt -t

trace:

Ix

 -- conversion to binary tree -->

    r---x
---
    l---I

 -- reduction -->

---x


Kfx

 -- conversion to binary tree -->

    r---x
---
   |    r---f
    l---
        l---K

 -- reduction -->

---f


Sfgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
            l---S

 -- reduction -->

        r---x
    r---
   |    l---g
---
   |    r---x
    l---
        l---f


Bfgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
            l---B

 -- reduction -->

        r---x
    r---
   |    l---g
---
    l---f


Cfgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
            l---C

 -- reduction -->

    r---g
---
   |    r---x
    l---
        l---f


S'ufgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
           |    r---u
            l---
                l---S'

 -- reduction -->

        r---x
    r---
   |    l---g
---
   |        r---x
   |    r---
   |   |    l---f
    l---
        l---u


B'ufgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
           |    r---u
            l---
                l---B'

 -- reduction -->

        r---x
    r---
   |    l---g
---
   |    r---f
    l---
        l---u


C'ufgx

 -- conversion to binary tree -->

    r---x
---
   |    r---g
    l---
       |    r---f
        l---
           |    r---u
            l---
                l---C'

 -- reduction -->

    r---g
---
   |        r---x
   |    r---
   |   |    l---f
    l---
        l---u
```

```
/* test2.txt */

Yf; // Y is Fixed-point combinator
```

the next input won't stop, break it

```
> skibcy.exe test3.txt -t

trace:

Yf

 -- conversion to binary tree -->

    r---f
---
    l---Y

 -- reduction -->

        r---f
    r---
   |    l---Y
---
    l---f

 -- reduction -->

            r---f
        r---
       |    l---Y
    r---
   |    l---f
---
    l---f

 -- reduction -->

                r---f
            r---
           |    l---Y
        r---
       |    l---f
    r---
   |    l---f
---
    l---f

 -- reduction -->
  .
  .
  .

```

```
/* test3.txt (reverse xy) */

S(K(SI))Kxy;

```

``` 
> skibcy.exe test3.txt -t

trace:

S(K(SI))Kxy

 -- conversion to binary tree -->

    r---y
---
   |    r---x
    l---
       |    r---K
        l---
           |            r---I
           |        r---
           |       |    l---S
           |    r---
           |   |    l---K
            l---
                l---S

 -- reduction -->

    r---y
---
   |        r---x
   |    r---
   |   |    l---K
    l---
       |    r---x
        l---
           |        r---I
           |    r---
           |   |    l---S
            l---
                l---K

 -- reduction -->

        r---y
    r---
   |   |    r---x
   |    l---
   |        l---K
---
   |    r---y
    l---
        l---I

 -- reduction -->

    r---x
---
    l---y
``` 

```
                                                reducted?   displayed?
[name]    = M  -- skibcy.exe --> [name]   = N       Y           Y
[name]   := M  -- skibcy.exe --> [name]  := M       N           Y       
[name]   |= M  -- skibcy.exe --> 　　　　　　        Y           N
[name]  |:= M  -- skibcy.exe -->                    N           N         

``` 

```
          lambda term                               SKIBCS'B'C' combinators
[pair] |= \x.\y.\f.(fxy);   -- lambda2c.exe -->    [pair] |= (BC(CI));
``` 


see [Lambda2Combinator](https://github.com/AkiraHakuta/Lambda2Combinator)

```
/* header.h */

//fixedpoint combinators
[Y] |:= (B(SII)(CB(SII)));
[Z] |:= (B(SII)(CB(SII)));
[T] |:= (B'SI(SII))(B'SI(SII));
//The simplest fixed-point combinator, found by John Tromp, is
[Y''] |:= (SCI)(SB(C'S(CI)I));

//booleans
[tru] |= K;
[fls] |= (KI);
[and] |= (CC[fls]);
[or] |= (C(CI[tru]));
[not] |= (C(CI[fls])[tru]);

//church numerals
[0] |= [fls];
[succ] |= (SB);
[1] |= [succ][0];
[2] |= [succ][1];
[3] |= [succ][2];
[4] |= [succ][3];
[5] |= [succ][4];
[6] |= [succ][5];
[7] |= [succ][6];
[8] |= [succ][7];
[9] |= [succ][8];
[10] |= [succ][9];
[pred] |= (C(C(CI(C(CI[1])[succ]))(K[0]))[0]);
[iszero] |= (C(CI(K[fls]))[tru]);
[add] |= (BSB');
[mult] |= B;
[sub] |= (C(CI[pred]));
//[power]xy=y^x
[power] |= I;

//pairs
[pair] |= (BC(CI));
[fst] |= (CI[tru]);
[snd] |= (CI[fls]);

//lists
[cons] |= [pair];
[head] |= [fst];
[tail] |= [snd];
[nil] |= (K[tru]);
[isnil] |= (CI(K(K[fls])));
[nth] |= (B'B[head](C(CI[tail])));

//etc
[fact_x] |:= (S(C[iszero][1])(S[mult](B[fact_x][pred])));
[fact_fx] |= (B'S(C[iszero][1])(B'S[mult](CB[pred])));
[sum_list] |:= (S(C[isnil][0])(S'[add][head](B[sum_list][tail])));
[map] |:= (B'S(C[isnil][nil])(S'(S'[cons])(CB[head])(C(B'[map])[tail])));
[fold_left] |:= (B'(S'S)(C[isnil])(C(S'C'(BS'[fold_left])(C'CB'[head]))[tail]));
[max_x_y] |= (S'C(C'(S'[iszero])[sub]I)I);
[pick] |:= (S(C'S'[iszero][head])(C'(B'[pick])[pred][tail]));

//list example
/* [list2431] := [cons][2]([cons][4]([cons][3]([cons][1][nil]))) */
```

```
/* test4.txt (pick) */
#include "header.h"

[list2431] := [cons][2]([cons][4]([cons][3]([cons][1][nil])));
[pick_2_list2431_xy] = [pick][2][list2431]xy;
```

```
> skibcy.exe test4.txt

result (binary tree):

[list2431] :=
                r---[nil]
            r---
           |   |    r---[1]
           |    l---
           |        l---[cons]
        r---
       |   |    r---[3]
       |    l---
       |        l---[cons]
    r---
   |   |    r---[4]
   |    l---
   |        l---[cons]
---
   |    r---[2]
    l---
        l---[cons]

[pick_2_list2431_xy] =
            r---y
        r---
       |    l---x
    r---
   |    l---x
---
    l---x
``` 

  
test5.txt (factorial)  
test6.txt (sum list)  
test7.txt (map)  
test8.txt (fold_left)  


### Building (Windows only)   
<ol>
<li>

Install [mingw-w64](https://www.mingw-w64.org/downloads/)  

</li>
<li>

Install [cmake](https://cmake.org/download/)   
 
</li>
<li>

Install antlr4 of the Cpp target  
see [antlr4_Cpp_examples](https://github.com/AkiraHakuta/antlr4_Cpp_examples)  

</li>

Compile   
open Dos Command Prompt  
from `C:/.../SKIBCY`  

```
> mkdir build
> cd build
> cmake -G "MinGW Makefiles" ..
> mingw32-make.exe  
```
</li>  
</ol>

### References  

-  D.A. Turner, Another algorithm for bracket abstraction (1979)
-  D.A. Turner, A new implementation technique for applicative languages (1979)
-  Wikipedia [Combinatory logic](https://en.wikipedia.org/wiki/Combinatory_logic)