expr =
  [ '(' expr ')' ] : parens
  identifier : ident
  number : literal
 .operators prefix
  '-' : negative
 .operators infix flat
  '*' : times
  '/' : divided-by
 .operators infix flat
  '+' : plus
  '-' : minus
