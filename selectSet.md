Vn :=  非终结符

Vt := 终结符

V := Vn ∪ Vt



SELECT( R  →  int) = FIRST( int r' ) = { int }

SELECT( R  → float   ) = FIRST( float r' ) = { float }

SELECT( R  →   char  )  = FIRST(char r' ) = { char }

SELECT( Q  → PQ) = FIRST( PQ ) = { Integer ,  Identifier}

SELECT( Q → ε) = FOLLOW( Q ) = { ) }

SELECT( P'' →  ε ) = FOLLOW( p'' ) = { ; ,  ) ,   &&,   || ,  + , - , * , /,  == , !=,  > ,  < ,  >= , <=  }

SELECT( P'' →  ( Q )  ) =  FIRST( ( Q ) ) = { ( } 

SELECT( P"  →  = P) = FIRST( = P ) = { = }

SELECT( P' →  && P) = { && }

......

SELECT( P''' →  P'P''') = FIRST( P'P''' ) = { &&,   || ,  + , - , * , /,  == , !=,  > ,  < ,  >= , <= }

SELECT( P'''  →  ε) = FOLLOW( P''' ) = { ;  ,  )  }

SELECT( P  →  IntegerP''' ) = FIRST( IntegerP''') = { Integer }

SELECT( P  →  IdentifierP''P''') = { Identifier }

SELECT(P  →  String )  =  { String }

SELECT( O' → else J) = { else }

SELECT( O'  →  ε) = FOLLOW( O' ) = { # ,   }  }

SELECT( O  →  P;) = FIRST( P; ) = { Integer,  Identifier }

SELECT( O  →  return P; ) = { return }

SELECT( O → if ( P ) J O') = { if }

SELECT( O  → while( P ) J ) = { while }

SELECT( O  → break; ) = { break; }

SELECT( O  →  continue;  ) =  { continue; }

SELECT(O  → for ( P ; P ; P) J) = { for }

SELECT(O   →  L) =  {int, float, long } // 这个情况特殊

SELECT( M  →  OM) = FIRST( OM ) = { Integer, Identifier, return, if, while, break, continue, for, int, char, float}

SELECT( M  →  ε) = FOLLOW( M ) = {  }  }

SELECT( N  →  RE; )  = { int,  float,  char }

SELECT( L  →  N L) =   { int,  float,  char }

SELECT( L  →  ε)  = FOLLOW( L ) = { 非 int  float  char }

SELECT( J  →  { L M }) = {  {  }

SELECT(K  →  RH) =  { int,  float,  char}

SELECT( I'  →  ε)  = { ) }

SELECT( I'  →  , I ) = { , }

SELECT( I  →  K I') =  { int,  float,  char }

SELECT( I  →  ε) =  {  )  }

SELECT( H'  →   [Integer]  ) =  { [   }

SELECT( H'  →  ε) = {  ,   ;   (   )  }

SELECT( H  →  Identifier H' ) = { Identifier }

SELECT( G'  →  ; ) = { ; }

SELECT( G'  →   J )  = {  {  }

SELECT( G →  ( I ) G' ) = { (  }

SELECT( E'  →  , E)  = { , }

SELECT( E'  →  ; ) =  { ; }

SELECT( E  →  HE') = {  Identifier  }

SELECT( C  →  RE) = { int,  float,  char}

SELECT( B'  →  E' ) = { ,   ;  }

SELECT( B' →   G ) =  {  (  }

SELECT( B  →  RHB' ) = { int,  float,  char }

SELECT( A'  →  A ) =  { int,  float,  char }

SELECT( A'  →  ε)  = { # }

SELECT( A  →  BA' )  = { int,  float,  char}

SELECT( S  →  A )  =  { int,  float,  char}



