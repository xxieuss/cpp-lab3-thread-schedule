# Schedule (scheme 6, nt = 5)

Ideal model: every action takes 1 second.
70 actions / 5 threads = 14 seconds, the lower bound. This schedule reaches it.

```
sec   1  2  3  4  5  6  7  8  9 10 11 12 13 14
T1   a1 a2 a3 a4 a5 a6 a7 a8 a9 j1 j2 j3 j4 f1
T2   e1 e2 e3 e4 e5 e6 e7 e8 e9 h1 h2 h3 h4 f2
T3   d1 d2 d3 d4 d5 d6 d7 d8 b5 j5 j6 j7 h9 f3
T4   g1 g2 g3 g4 g5 b1 b2 b3 b4 h5 h6 h7 h8 f4
T5   c1 c2 c3 c4 c5 c6 c7 i1 i2 i3 i4 i5 i6 f5
```

## Synchronization points

| Latch    | Counted actions | Count | Waited by           | Opens (ideal)   |
|----------|-----------------|-------|---------------------|-----------------|
| before_i | g, c            | 12    | T5 before i         | after second 7  |
| before_j | a, d            | 17    | T1, T3 before j     | after second 9  |
| before_h | e, b            | 14    | T2, T3, T4 before h | after second 9  |
| before_f | j, h, i         | 22    | all threads before f | after second 13 |