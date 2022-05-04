# [Dynamic Programming lecture #2 - Coin change, double counting](https://www.youtube.com/watch?v=1mtvm2ubHCY)

## Double counting:
- Sorted paths are unique based on their composition:
  - {1, 2, 1} and {1, 1, 2} are both {1, 1, 2} when sorted, thereby making them the same path
  - Implementation:
    - Store previous choice to limit possible future choices (coinchange2.cpp)
    - Iterate each choice once (coinchange3.cpp)