# Quack compiler  
Author: Alexander Owen (no partner)  
Course: CIS 461, Winter 2017  
## Execution  
Executable Quack compiler is named `quack`  
Run with `./quack path/to/file`  
Emits an executable named `pgm` which you can execute with  
`./pgm`    
## Compiler functionality  
- Discovers the variable type by using type inference  
- Variable types are flow-insensitive, using least common ancestor to determine 
type in the case of conflicting type inferences  
- Allows user to create their own classes, featuring operator overloading and
inheritance  
- Features dynamic dispatch on method calls when static type does not match
dynamic type  
- Features a stack frame that allows for recursive method calls  
- Features short circuit evaluation for boolean opeartors 'and' and 'or'  
- Type checks for the following  
  - Variable usage is preceded by delcaration on ALL execution paths  
  - Operator method calls are allowed for the variable's type  
  - Method returns the type or a subtype of the type specified in the signature
  - Method calls have the correct number of arguments
  - Method calls arguments are either the same type or subtypes of types specified
in the method delcaration  
  - If/While conditions are of type Boolean  
  - Method overriding uses the correct number of arguments
  - Method overriding uses arguments that are the same type or supertype of the overrriden
method  
  - Method overriding returns a type that is the same type or a subtype of the 
overriden method  
  - Instance variables used within classes are defined

## Known Bugs/Missing Functionality/TODOs  
- "Incompatible pointer" warnings emitted on compilation (requires casting)  
- Constructor calls not checked for proper arguments (requires implementing)  
- Cannot handle class definitions that are out of order, as allowed in Quack  
 - For example, defining `class A extends B` followed by `class B`  
- Resolve memory leaks both in written code and as a result of yylex
