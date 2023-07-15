//
// F# program to input a string and print out information
// about the # of vowels and digraphs in that string.
//
// Name: Aqsa Arif
//
// Original author:
//   Prof. Joe Hummel
//   U. of Illinois, Chicago
//   CS 341, Spring 2022
//
//
// explode:
//
// Given a string s, explodes the string into a list of characters.
// Example: explode "apple" => ['a';'p';'p';'l';'e']
//
let explode (S:string) = List.ofArray (S.ToCharArray())

//
// implode
//
// The opposite of explode --- given a list of characters, returns
// the list as a string. Example: implode ['t';'h';'e'] => "the"
//
let implode (L:char list) = new string(List.toArray L)


let rec length L = 
  match L with
  | [] -> 0
  | head::tail -> 1 + length tail

let rec count v L =
  match L with
  | [] -> 0
  | hd::tl when hd = v -> 1 + count v tl
  | _::tl -> 0 + count v tl

// list holder for vowels
let vowels = ['a';'e';'i';'o';'u']

// recursive function for total number of vowels
let rec numVowels L = 
  List.map (fun v -> count v L) vowels |>
  List.sum

// list holder for digraphs
let digraphs = 
  [['a';'i']; ['c';'h']; ['e';'a']; ['i';'e']; 
   ['o';'u']; ['p';'h']; ['s';'h']; ['t';'h']; 
   ['w';'h']; ]

// recursive function that takes 2 char input and compares
// with char list L to math number of digraphs
let rec countDigraph c1 c2 L =
  match L with 
  | [] -> 0
  | a::b::tl when (a = c1) && (b = c2) -> 1 + countDigraph c1 c2 tl
  | _::tl -> 0 + countDigraph c1 c2 tl

// This function returns individual count of digraphs
let diSum digraph L =
    let c1 = List.head digraph
    let tailholder = List.tail digraph
    let c2 = List.head tailholder
    countDigraph c1 c2 L

// This funtion creates a list of the number of digraphs compared
// to the list of digraphs by mapping and returns its sum
// this gives us total number of digraphs
let numDigraph L = 
  List.map (fun digraph -> diSum digraph L) digraphs |>
  List.sum

[<EntryPoint>]
let main argv =
  printfn "Starting"
  printfn ""

  //
  // input string, output length and # of vowels:
  //
  printf("input> ")
  let input = System.Console.ReadLine()

  let L = explode input
  printfn "exploded: %A" L

  let len = length L
  printfn "length: %A" len

  let num = numVowels L
  printfn "vowels: %A" num

  // This function prints vowel char and the number of times it 
  // appears in input
  let printCountVowels v L =
    printfn "%A: %A" v (count v L)

  // this command iterates through the list of vowels and uses
  // print function to print in desired format
  List.iter (fun c -> printCountVowels c L) vowels

  // this function prints total number of digraphs
  let sum = numDigraph L
  printfn "digraphs: %A" sum

  // This function formats print of digraphs and helps in 
  // indexing our list list of digraph
  let printCountDigraph digraph L =
    let c1 = List.head digraph
    let tailholder = List.tail digraph
    let c2 = List.head tailholder
    printfn "%A,%A: %A" c1 c2 (countDigraph c1 c2 L)

  // this command iterates through our list list digraph and
  // runs it against our desired print formating function
  List.iter (fun digraph -> printCountDigraph digraph L) digraphs


  //
  // done: implode list, print, and return
  //
  let S = implode L
  printfn "imploded: %A" S

  printfn ""
  printfn "Done"
  0  // return 0 => success, much like C++