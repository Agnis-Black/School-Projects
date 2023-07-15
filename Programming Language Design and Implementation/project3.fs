//
// Parser for simple C programs.  This component checks 
// the input program to see if it meets the syntax rules
// of simple C.  The parser returns a string denoting
// success or failure. 
//
// Returns: the string "success" if the input program is
// legal, otherwise the string "syntax_error: ..." is
// returned denoting an invalid simple C program.
//
// Aqsa Arif
//
// Original author:
//   Prof. Joe Hummel
//   U. of Illinois, Chicago
//   CS 341, Spring 2022
//

namespace compiler

module parser =
  //
  // NOTE: all functions in the module must be indented.
  //

  //
  // matchToken
  //
  let private matchToken expected_token tokens =
    //
    // if the next token matches the expected token,  
    // keep parsing by returning the rest of the tokens.
    // Otherwise throw an exception because there's a 
    // syntax error, effectively stopping compilation
    // at the first error.
    //
    let next_token = List.head tokens
  
    if expected_token = next_token then  
      List.tail tokens
    else
      failwith ("expecting " + expected_token + ", but found " + next_token)

  //
  // simpleC
  //

// recursive decent parsing based on BNF
  let rec private stmts tokens = 
    match tokens with
    | hd::tl when hd = ";" -> morestmts tl
    | a::tl when (a = "int") -> morestmts tl
    | a::tl when (a = "else") -> else_part tl 
    // part of the if-then-else recursion calls
    | a::b::tl when (a = "cin") && (b = ">>")-> morestmts tl
    | a::b::tl when (a = "cout") && (b = "<<") -> output tl 
    // call output function if cout command detected
    | a::b::tl when a.StartsWith("identifier") && (b = "=") -> expr tl
    // when identifier keyword in string jump to <expr> function call
    | a::tl when a.StartsWith("identifier") -> morestmts tl
    | a::tl when (a = "if") -> ifstmt tl
    // start of the if-then-else recursive chain
    | hd::tl when hd = "}" -> tokens
  and private morestmts tokens =
  // same basic function as stmts but prevents looping by recursion call
  // ensures main code isn't empty
    match tokens with
    | hd::tl when hd = ";" -> stmts tl
    | a::tl when (a = "int") -> stmts tl
    | a::tl when (a = "else") -> else_part tl
    | a::b::tl when (a = "cin") && (b = ">>") -> stmts tl
    | a::b::tl when (a = "cout") && (b = "<<") -> output tl
    | a::b::tl when a.StartsWith("identifier") && (b = "=") -> expr tl
    | a::tl when a.StartsWith("identifier") -> stmts tl
    | a::tl when (a = "if") -> ifstmt tl
    | hd::tl when hd = "}" -> tokens
    // signifies ending of main code return to simpleC
  and private ifstmt tokens =
    match tokens with 
    | a::tl when a = "(" -> condition tl
    // after if string identifies go to condition expression
    | a::tl when a = ")" -> then_part tl
    // after expression is complete got to then part of if-then-else
  and private then_part tokens =
    stmts tokens
  and private else_part tokens =
    stmts tokens
  and private condition tokens =  
    expr tokens
  and private output tokens =
    match tokens with
    | hd::tl when hd = "endl" -> stmts tl
    // if output ends in endl return to stmts with tail end of list
    | _ -> exprvalue tokens
    // otherwise go to <exprvalue> function
  and private exprvalue tokens = 
    match tokens with 
    | hd::tl when hd.StartsWith("identifier") -> exprop tl
    | hd::tl when hd.StartsWith("int_literal") -> exprop tl
    | hd::tl when hd.StartsWith("str_literal") -> exprop tl
    | hd::tl when hd = "true" -> exprop tl
    | hd::tl when hd = "false" -> exprop tl
    | hd::tl when hd = ")" -> ifstmt tokens
    | hd::tl when hd = ";" -> stmts tokens
  and private expr tokens = 
    exprvalue tokens
  and private exprop tokens = 
    match tokens with
    // tokens with operations
    |hd::tl when hd = "+" -> exprvalue tl
    |hd::tl when hd = "-" -> exprvalue tl
    |hd::tl when hd = "*" -> exprvalue tl
    |hd::tl when hd = "/" -> exprvalue tl
    |hd::tl when hd = "^" -> exprvalue tl
    |hd::tl when hd = "<" -> exprvalue tl
    |hd::tl when hd = ">" -> exprvalue tl
    |hd::tl when hd = ">=" -> exprvalue tl
    |hd::tl when hd = "==" -> exprvalue tl
    |hd::tl when hd = "<=" -> exprvalue tl
    |hd::tl when hd = "!=" -> exprvalue tl
    | _ -> exprvalue tokens
  
  let private simpleC tokens = 
    let T2 = matchToken "void" tokens
    let T3 = matchToken "main" T2
    let T4 = matchToken "(" T3
    let T5 = matchToken ")" T4
    let T6 = matchToken "{" T5
    let T7 = stmts T6
    let T8 = matchToken "}" T7
    let T9 = matchToken "$" T8 //$ => EOF, there should be no more tokens
    T9
  
    
  //
  // parse tokens
  //
  // Given a list of tokens, parses the list and determines
  // if the list represents a valid simple C program.  Returns
  // the string "success" if valid, otherwise returns a 
  // string of the form "syntax_error:...".
  //
  let parse tokens = 
    try
      let result = simpleC tokens
      "success"
    with 
      | ex -> "syntax_error: " + ex.Message
