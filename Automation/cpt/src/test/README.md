### Test Results Preview
```
v Test set #1                                     [1]
    init    s OK, g OK, c CW                      [2]
  > cases   67 OK, 5 RE(s), 1 RE(c) 27 WA         [3]
v Test set #2
    init    s OK, g OK, c OK
  v cases   1 OK, 2 RE(s), 1 WA
      OK         RE (s)      WA
      598273     87534       523874               [4]
                 524387
```
1. Test set dropdowns should be open by default since it's only +2 lines.
1. Hovering over an init verdict should open the init details in the inspect window.
1. Longer test details should be opened in the inspect window. Should this be enforced? Maybe a good compromise would be to only show the head in the dropdown.
1. Hovering over a test case should open the test case details in the inspect window.
