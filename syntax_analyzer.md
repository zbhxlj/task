S  = 程序

A = 外部定义序列

B = 外部定义

C = 外部变量定义

E = 变量序列

G = 函数

H = 标识符

I = 形式参数序列

J = 复合语句

K = 形式参数

L = 局部变量定义序列

M = 语句序列

N = 局部变量定义

O = 语句

P = 表达式

Q = 实参序列

ε = 空



S  →  A

A  →  BA'

A'  →  A  |  ε 

B  →  RhB'

B'  →  E' |  G  

C  →  RE ;

E  →  HE'

E'  →  ,  E  |  ε

G  →   ( I )  G'

G'  →  J  |  ; 

H  →  Identifier H'

H'  →  ε  |  [ Integer  ]

I  →  K,  I  | ε

I'  →  , I  |   ε 

K  →  RH

J  →  {  L  M  }

L  →  N  L  |  ε

N  →  RE ;

M  →  OM  |  ε

O  →  P;  |  return P;  |  if ( P ) O O' |  while( P )  O | break; | continue; | for (P ; P ; P) O 

O'  →  else O |  ε

P  →  IntegerP''' | Identifier P'' P''' 

P'''  →  P'P'''  |  ε

P'  →  && P  |  ||  P  |  + P  |  -  P  |  *  P  |  / P  | == P |  != P  |  >  P  |  < P | >=  P | <= P 

P''  →  ε  | ( Q )  |  = P 

Q  →  PQ  |  ε

R  →  int   |  float  |  char
