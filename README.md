Chinese Remainder Theorem
- ATTENTION! Unhandled exceptions:
1) Be careful, that $$\forall i, j \in \mathbb{N} $$ : $$1 \leq i, j \leq n$$, $$i \neq j$$, should fulfilled gcd($$m_{i}$$, $$m_{j}$$) = 1 - pairwise coprime numbers. In this code it doesn't check;
2) If one of $$m_{i} = 0$$ - will be error (program will be crashed);
3) If one of $$gcd(m_{i}, m_{j}) \neq 1$$, you will get $$x = 0$$ - wrong answer code, because $$\nexists x$$.
