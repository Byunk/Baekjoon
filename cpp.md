# cpp

Frequently used cpp syntax

## Unsync with stdio

```cpp
ios::sync_with_stdio(false);
cin.tie(NULL);
```

## Define custom operator

```cpp
matrix operator * (const matrix& a, const matrix& b) {
	matrix ret(N, vector<ll>(N));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				ret[i][j] += a[i][k] * b[k][j];
			}
			ret[i][j] %= 1000;
		}
	}
	return ret;
}
```

# Frequent mistakes

## Separation even and odd cases during DP

bad case: recursively handle odd cases that generates two recursive function calls

```cpp
matrix ret;
if (b % 2 == 0) {
  matrix mm = m*m;
  ret = solve(mm, b / 2);
} else {
  ret = solve(mm, b / 2) * solve(mm, b / 2 + 1);
}
```

good case: handle odd cases at once

```cpp
matrix ret;
matrix mm = m*m;
if (b % 2 == 0) {
  ret = solve(mm, b / 2);
} else {
  ret = solve(mm, b / 2) * m;
}
```
