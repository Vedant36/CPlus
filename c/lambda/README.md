# C header for lambda functions
## prompt
using your pick of C (emojiC also counts), R, or BQN, create an efficient method of performing lambda functions.

rules:
- use only the language's native libraries (no user-made ones)
- method must be made into the form of a usable header file or plugin/library. for instance, the solution in C may be made into
  "lambda.h".
- must be able to beta-reduce, for instance "(λx.e1) e2 ->β e1[ x := e2 ]" will be simplified to "e1 ->β e1" using the resulting    file.

## explanation
This header uses de-brujin indexing for calculations

```lambda
( λ f . f   x )   y
 1\A\A\A\A\A\A\ \C\
    f f f fCf f f f
      S S S S S S S
        f f f f f f
            x x x x
            C C C C
              A A A
                  y
                  C
```
```lambda
a   ( b   c )
a aCaCaCaCaCa
     1bCbCbCb
         CcCc
            C
            C
```
```lambda
a   b   c
a aCa aCa
    b b b
    C C C
        c
        C
```


>Input: λx.x x
>Preprpcessing: λ 1 1
>Output: λx.x x

>Input: (λf.f x) y
>Preprocessing: (λ 1 2) 3 { internally, the table: [ f, x, y ] is saved }
>β-reduction: 3 2
>Output: y x

>Input: S I I (S I I)
>Expanded: (λxyz.x z (y z)) (λx.x) (λx.x) ((λxyz.x z (y z)) (λx.x) (λx.x))
>Preprocessing: (λ 3 1 (2 1)) (λ 1) (λ 1) ((λ 3 1 (2 1)) (λ 1) (λ 1))
>Reverse polish: λ31c21ccA λ1A c λ1A c λ31c21ccA λ1A c λ1A c
>β-reduction: λ λ1A 1c21ccA λ1A c λ31c21ccA λ1A c λ1A c
>β-reduction: λ121ccA λ1A c λ31c21ccA λ1A c λ1A c
>β-reduction: λ121ccA λ1A c λ31c21ccA λ1A c λ1A c
>β-reduction: λ1 λ1A 1ccA λ31c21ccA λ1A c λ1A c
>β-reduction: λ11cA λ31c21ccA λ1A c λ1A c c
>β-reduction: λ11cA λ11cA
>β-reduction: λ11cA λ11cA
>Output:
