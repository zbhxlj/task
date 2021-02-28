A =  Identifier

B = '#' A D

C = " Identifier "  |  Expression  Expression  



SELECT( C  →  # A B ) = {  #  }

SELECT( D  →  " Identifier ") = {  "  }

SELECT(D  →  Expression Expression )  = {  any other character }