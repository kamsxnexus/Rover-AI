# C Gotchas Log

A running log of real C bugs and surprises I've hit while building Rover AI — written in my own words so future-me remembers *why*, not just *what*.

---

## 1. Integer division truncates before float conversion

**Date:** July 2026

**What I wrote:**
```c
float final = P - (P*D/100);
```

**What went wrong:**
`P` and `D` are both `int`, so `P*D/100` does **integer division** and truncates the decimal part *first* — the result only gets converted to `float` *after* the truncation already happened. Passed the sample input (which divided evenly) but failed other test cases where the discount didn't divide evenly.

**Fix:**
```c
float final = P - ((float)(P * D) / 100);
```

**Lesson:** casting to `float` has to happen *before* the division that needs decimal precision — not after. The type of the variable you're storing the result in doesn't retroactively fix math that already happened in `int`.

---

## 2. `void main()` doesn't return a value — but `main()` still needs `return 0;`

**Date:** July 2026

**What I wrote:**
```c
void age() {
    int age;
    scanf("%d", &age);
    printf("Your age is: %d", age);
}
age();
```

**What went wrong:**
Tried to make my function the entry point instead of using `main()`. C always starts running at `main()` — nothing runs just because it's sitting in the file. Also had `age()` called outside any function, which isn't valid; calls have to happen inside another function.

**Fix:**
```c
#include <stdio.h>

void AGE() {
    int age;
    scanf("%d", &age);
    printf("Your age is: %d", age);
}

int main() {
    AGE();
    return 0;
}
```

**Lesson:** every C program needs `int main()` as the real entry point, and `main()` should `return 0;` for success — even if other functions are `void`.

---

## 3. Single quotes vs double quotes are NOT interchangeable

**Date:** July 2026

**What I wrote:**
```c
scanf( '%d', &age);
printf( 'Your age is: %d', age);
```

**What went wrong:**
Used single quotes `' '` around format strings. In C, single quotes are only for a single character (like `'A'`), and double quotes `" "` are for strings of text. `"%d"` is a string, so it needs double quotes — using single quotes here is a compiler error, not just a style issue.

**Fix:**
```c
scanf("%d", &age);
printf("Your age is: %d", age);
```

**Lesson:** `' '` = one character, `" "` = a string. Never mix them up for format strings.

---

## 4. `=` (assignment) inside an `if` condition silently does the wrong thing

**Date:** July 2026

**What I got wrong:**
Predicted that `if (x = 10) { ... }` would throw a compiler error, since it looks like a comparison mistake.

**What actually happens:**
`x = 10` is completely legal C — it assigns `10` to `x`, and the assignment expression itself evaluates to `10`. Since `10` is nonzero, C treats the `if` condition as **true**, every time, regardless of what `x` was before. No error, no warning by default — it just silently runs the "true" branch and overwrites `x`.

**Fix:**
Always use `==` to compare, `=` only to assign:
```c
if (x == 10) { ... }
```

**Lesson:** C won't stop you from writing `=` where you meant `==` — this is one of the most common real C bugs, and I hit the wrong prediction on it more than once before it stuck. Double-check every `if` condition for this specifically.

---

## 5. `switch` case values must be constant integers (or `char`) — not `float`, not variables

**Date:** July 2026

**What I got wrong:**
Guessed that `switch` case values could be `float`, since Python doesn't really have this restriction in the same form.

**What's actually true:**
C `switch` statements only accept **constant integral types** — `int` or `char` literals (or `#define`d constants). `float` values and regular variables aren't allowed as case labels at all; it won't compile.

**Lesson:** `switch` in C is stricter than it looks coming from Python — always check what's allowed as a case value before assuming it behaves like a generic comparison.

---

## Template for new entries

```markdown
## N. Short title of the gotcha

**Date:** 

**What I wrote:**
```c
// the buggy code
```

**What went wrong:**


**Fix:**
```c
// the corrected code
```

**Lesson:**

```
