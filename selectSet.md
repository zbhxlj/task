Vn :=  非终结符

Vt := 终结符

V := Vn ∪ Vt





SELECT( Q  → PQ) = FIRST( PQ ) = { Integer ,  Identifier}

SELECT( Q → ε) = FOLLOW( Q ) = { ) }

SELECT( P'' →  ε ) = FOLLOW( p'' ) = { ; ,  ) ,   &&,   || ,  + , - , * , /,  == , !=,  > ,  < ,  >= , <=  }

SELECT( P'' →  ( Q )  ) =  FIRST( ( Q ) ) = { ( } 

SELECT( P"  →  = P) = FIRST( = P ) = { = }

SELECT( P' →  && P) = { && }

......

SELECT( P''' →  P'P''') = FIRST( P'P''' ) = { &&,   || ,  + , - , * , /,  == , !=,  > ,  < ,  >= , <= }

SELECT( P'''  →  ε) = FOLLOW( P''' ) = { ; , ) , }

SELECT( P  →  IntegerP''' ) = FIRST( IntegerP''') = { Integer }

SELECT( P  →  IdentifierP''P''') = { Identifier }

SELECT( O' → else O) = { else }

SELECT( O'  →  ε) = FOLLOW( O' ) = { # }

SELECT( O  →  P;) = FIRST( P; ) = { Integer,  Identifier }

SELECT( O  →  return P; ) = { return }

SELECT( O → if ( P ) O O') = { if }

SELECT( O  → while( P ) O ) = { while }

SELECT( O  → break; ) = { break; }

SELECT( O  →  continue;  ) =  { continue; }

SELECT(O  → for ( P ; P ; P) O) = { for }

SELECT( M  →  OM) = FIRST( OM ) = { Integer, Identifier, return, if, while, break, continue, for}

SELECT( M  →  ε) = FOLLOW( M ) = {  }  }

SELECT( N  →  aE; )  = { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( L  →  N L) =   { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( L  →  ε)  = FOLLOW( L ) = { # }

SELECT( J  →  { L M }) = {  {  }

SELECT(K  →  ah) =  { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( I  →  K, I) =  { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( I  →  ε) =  {  )  }

SELECT( G →  ah( I ) J) = { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( E'  →  , E)  = { , }

SELECT( E'  →  ε) =  { ; }

SELECT( E  →  hE') = {  Identifier  }

SELECT( C  →  aE) = { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( B  →  C) = { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( B  →  G ) = { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( A'  →  A ) =  { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( A'  →  ε)  = { # }

SELECT( A  →  BA' )  = { int,  float,  char,  int[integer],  float[integer],  char[integer] }

SELECT( S  →  A )  =  { int,  float,  char,  int[integer],  float[integer],  char[integer] }