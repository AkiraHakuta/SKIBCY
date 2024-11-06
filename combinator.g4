grammar combinator;

toplevel
    : (com_include)+ 
    ;

com_include
    : include
    | command ';'
    ;

include
    : '#include' dqString
    ;

command
    : term                       # c_term
    | sq '=' term                # c_sq_eq_term
    | sq ':=' term               # c_sq_ceq_term
    | sq '|=' term               # c_sq_veq_term
    | sq '|:=' term              # c_sq_vceq_term
    | 'putStr' '(' dqString ')'  # c_dq_string
    | 'NL'                       # c_newline
    ;

term
    : aterm                # t_a
    | term aterm           # t_app_a
    ;

aterm      
    : v                    # a_v
    | sq                   # a_sq
    |  '(' term ')'        # a_paren
    ;

v : var
  | '(' var ')'
  ;


var : LCID;
sq : SqStr;
dqString : StringLiteral;


LCID : [a-zA-Z] '\''*;
SqStr : '[' [a-zA-Z0-9_']+ ']';
StringLiteral : '"' (~["])* '"';
WS : [ \t\n\r]+                               -> skip;
COMMENT : '/*' .*? '*/'                       -> skip;
SL_COMMENT :  '//' .*? '\n'                   -> skip;
