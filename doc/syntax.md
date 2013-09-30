
# lexical grammar

This will be extended in the near future, but for now:

 - `;` marks the beginning of a comment, which extends until the end of
   the line.
 - `(` and `)` are tokens by themselves
 - any sequence of other non-whitespace printable characters (as
   defined by the c function `isprint`) is a token of type `atom`.
