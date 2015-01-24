#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <limits>
using namespace std;

// This is a struct that defines a 3D vector for use in calculation.
typedef struct vector {
    int x;
    int y;
    int z;
} Vector;

// This is the token type, and contains all possible tokens in our language.
typedef enum {
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_CROSS,
    T_OPENPAREN,
    T_CLOSEPAREN,
    T_EQUALS,
    T_M,
    T_PRINT,
    T_NUMBER,
    T_COMMA,
    T_EOF
} token;

// This function will convert a token to a string, for display.
std::string tokenToString(token toConvert) {
    switch (toConvert) {
        case T_PLUS:
            return std::string("+");
        case T_MINUS:
            return std::string("-");
        case T_MULTIPLY:
            return std::string("*");
        case T_CROSS:
            return std::string("x");
        case T_OPENPAREN:
            return std::string("(");
        case T_CLOSEPAREN:
            return std::string(")");
        case T_EQUALS:
            return std::string("=");
        case T_M:
            return std::string("m");
        case T_PRINT:
            return std::string("print");
        case T_NUMBER:
            return std::string("number");
        case T_COMMA:
            return std::string(",");
        case T_EOF:
            return std::string("EOF");
        default:
            return std::string("Unknown token");
    }
}

// Throw this error when the parser expects a given token from the scanner
// and the next token the scanner finds does not match.
void mismatchError(int line, token expected, token found) {
    std::cerr << "Parse error: expected " << tokenToString(expected) << " found " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the parser encounters a token that is not valid
// at the beginning of a specific grammar rule.
void parseError(int line, token found) {
    std::cerr << "Parse error: found invalid token " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when an invalid character is found in the input, or
// if a bad character is found as part of a print token.
void scanError(int line, char badCharacter) {
    std::cerr << "Scan error: found invalid character " << badCharacter << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when a number is out of bounds, which means greater than signed INT_MAX.
void outOfBoundsError(int line, long number) {
    std::cerr << "Semantic error: number " << number << " out of bounds at line " << line << std::endl;
    exit(1);
}

class Scanner {
    // You are allowed to private fields to the scanner, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.

    private:
        int lineNum;
        int lastNum;

    public:
        std::string s;

        token nextToken();
        void eatToken(token);
        int lineNumber();
        int getNumberValue();
        
        // You may need to write a constructor for the scanner. This is not
        // required by the project description, but you may need it to complete
        // your implementation.
        // WRITEME
        Scanner();

};

Scanner::Scanner(){
    lineNum = 1;
    lastNum = 0;
}

token Scanner::nextToken() {
    // This is a placeholder token, you will need to replace this code
    // with code to return the correct next token.
    

    // WRITEME
    char c;

    c = std::cin.peek();

    switch(c){
        case '+':
            return T_PLUS;
        case '-':
            return T_MINUS;
        case '*':
            return T_MULTIPLY;
        case 'x':
            return T_CROSS;
        case 'X':
            return T_CROSS;
        case '=':
            return T_EQUALS;
        case '(':
            return T_OPENPAREN;
        case ')':
            return T_CLOSEPAREN;
        case '\n':{
            lineNum++;
            std::cin.get(c);
            return nextToken();
            break;}
        case 'p':
            return T_PRINT;
        case ',':
            return T_COMMA;
        case ' ':{
            std::cin.get(c);
            return nextToken();
            break;}
        case 'm':
        case 'M':
            return T_M;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return T_NUMBER;
        case EOF:
            return T_EOF;
        default:
            //std::cout << "error1\n";
            scanError(lineNumber(),c);
            break;
    }
    return T_EOF;
}

void Scanner::eatToken(token toConsume) {
    // This function consumes the next token.
    // WRITEME

    char c;

 switch(toConsume){
        case T_PLUS:
        case T_MINUS:
        case T_MULTIPLY:
        case T_CROSS:
        case T_OPENPAREN:
        case T_CLOSEPAREN:
        case T_EQUALS:
        case T_M:
        case T_COMMA:
            std::cin.get(c);
            break;
        case T_PRINT:
                std::cin.get(c);
                    if(c == 'p'){
                        std::cin.get(c);
                        if(c == 'r'){
                            std::cin.get(c);
                            if(c == 'i'){
                                std::cin.get(c);
                                if(c == 'n'){
                                    std::cin.get(c);
                                    if(c == 't'){
                                    }
                                    else{
                                        //std::cout << "error2\n";
                                        scanError(lineNumber(),c);
                                        break;
                                    }
                                }
                                else{
                                    //std::cout << "error3\n";
                                    scanError(lineNumber(),c);
                                    break;
                                }
                            }
                            else{
                                //std::cout << "error4\n";
                                scanError(lineNumber(),c);
                                break;
                            }
                        }
                        else{
                            //std::cout << "error5\n";
                            scanError(lineNumber(),c);
                            break;
                        }
                    }
                    else{
                        //std::cout << "error6\n";
                        scanError(lineNumber(),c);
                        break;
                    }
            break;
        case T_NUMBER:
            s = "";
            std::cin.get(c);
            s.push_back(c);
            while(std::cin.peek() >= '0' && std::cin.peek() <= '9'){
                std::cin.get(c);
                s.push_back(c);
            }
            lastNum = stoi(s);
            break;
        case T_EOF:
            break;
    }
}

int Scanner::lineNumber() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the current line number (to be used for errors).
    
    // WRITEME
    return lineNum;
}

int Scanner::getNumberValue() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the last number value that was scanned. This
    // will be used when evaluating expressions.
    
    // WRITEME    
    return lastNum;
}

Vector v;
Vector m;

class Parser {
    // You are allowed to private fields to the parser, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
    private:
        Scanner scanner;
        
        // This flag indicates whether we should perform evaluation and throw
        // out-of-bounds and divide-by-zero errors. ONLY evaluate and throw these
        // errors if this flag is set to TRUE.
        bool evaluate;
        
        // You will need to add more methods for handling nonterminal symbols here.
        void Start();
        void A();
        void B();
        void B1();
        void E();
        void E1(Vector v_c);
        void T();
        void T1(Vector v_c);
        void K();
        void K1(Vector v_c);
        void P();
        void P1();

        
    public:
        void parse();

        int checkBounds(long i);

        Parser(bool evaluate) : evaluate(evaluate) {
            // You may need to complete a Parser constructor here
        }
};

int Parser::checkBounds(long i){
    if (i <= INT_MAX){
        return 1;
    }
    else{
        cout << "Semantic error: number " << i << " out of bounds at line " << scanner.Scanner::lineNumber() << endl;
        exit(1);
    }
}

void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
    m = {.x = 0, .y = 0, .z = 0};
    Start();
}

void Parser::Start() {
    // This is an example of a recursive-descent function for a
    // non-terminal symbol. In this case, it is just a placeholder
    // which accepts infinite numbers of T_PLUS. You will need to
    // replace this with correct code for the real grammar start symbol.
    
    A();
}

void Parser::A(){
    B();
    B1();
}

void Parser::B1(){
    //std::cout << "B1" << std::endl; 
    switch(scanner.nextToken()){
        case T_PRINT:
            B();
            B1();
            break;
        case T_M:
            B();
            B1();
            break;
        case T_EOF:
            break;
        default:
            //std::cout << tokenToString(scanner.nextToken()) << std::endl;
            parseError(scanner.Scanner::lineNumber(), scanner.nextToken());
            break;
    }    
}

void Parser::B(){

    //std::cout << "B" << std::endl; 
    switch(scanner.nextToken()){
        case T_M:
            ///std::cout << "hehehe " << std::endl;
            scanner.eatToken(scanner.nextToken());
            if(scanner.nextToken() == T_EQUALS){
                scanner.eatToken(scanner.nextToken());
                E();
                m.x = v.x;
                m.y = v.y;
                m.z = v.z;
                break;
            }
            else
                mismatchError(scanner.Scanner::lineNumber(),T_EQUALS ,scanner.nextToken());
        case T_PRINT:
            scanner.eatToken(scanner.nextToken());
            E();
            if (evaluate == true)
                std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
            break;
        default:

            parseError(scanner.Scanner::lineNumber(), scanner.nextToken());
    }



    // if(scanner.nextToken() == T_M){
    //     scanner.eatToken(scanner.nextToken());
    //     if(scanner.nextToken() == T_EQUALS){
    //         scanner.eatToken(scanner.nextToken());
    //         E();
    //     }
    //     else
    // }
    // else if(scanner.nextToken() == T_PRINT){
    //     scanner.eatToken(scanner.nextToken());
    //     E();
    // }
    // else{
    //     std::cout << tokenToString(scanner.nextToken()) << std::endl;
    //     parseError(scanner.Scanner::lineNumber(), scanner.nextToken());
    // }
}

void Parser::E(){
    //std::cout << "E" << std::endl; 
    T();
    E1(v);
}

void Parser::E1(Vector v_c){
    //std::cout << "E1" << std::endl; 
    long newX = 0;
    long newY = 0;
    long newZ = 0;
    //std::cout << tokenToString(scanner.nextToken()) << std::endl;
    switch(scanner.nextToken()){
        case T_PLUS:
            scanner.eatToken(scanner.nextToken());
            T();
            newX = (long) v.x + v_c.x;
            checkBounds(newX);
            v.x = newX;
            newY = (long) v.y + v_c.y;
            checkBounds(newY);
            v.y = newY;
            newZ = (long) v.z + v_c.z;
            checkBounds(newZ);
            v.z = newZ;
            E1(v);
            break;
        case T_MINUS:
            scanner.eatToken(scanner.nextToken());
            T();
            newX = (long) v.x - v_c.x;
            checkBounds(newX);
            v.x = newX;
            newY = (long) v.y - v_c.y;
            checkBounds(newY);
            v.y = newY;
            newZ = (long) v.z - v_c.z;
            checkBounds(newZ);
            v.z = newZ;
            E1(v);            
            break;
        case T_EOF:
            break;
        case T_M:
            break;
        case T_PRINT:
            break; ////POSSIBLE ERROR!!
        case T_CLOSEPAREN:
            break; ////POSSIBLE ERROR!!
        default:
            //std::cout << tokenToString(scanner.nextToken()) << std::endl;
            parseError(scanner.Scanner::lineNumber(),scanner.nextToken());
    }
}

void Parser::T(){
    //std::cout << "T" << std::endl; 
    K();
    T1(v);
}

void Parser::T1(Vector v_c){
    //std::cout << "T1" << std::endl; 
    Vector tmp;
    switch(scanner.nextToken()){
        case T_CROSS:
            scanner.eatToken(scanner.nextToken());
            K();
            tmp.x = v.x;
            tmp.y = v.y; 
            tmp.z = v.z;
            v.x = (v_c.y * tmp.z) - (v_c.z * tmp.y);
            v.y = (v_c.z * tmp.x) - (v_c.x * tmp.z);
            v.z = (v_c.x * tmp.y) - (v_c.y * tmp.x);
            T1(v);
            // v.x = v.y * v_c.z - v.z * v_c.y;
            break;
        case T_EOF:
            break;
        case T_PLUS:
            break;
        case T_M:
            break;
        case T_MINUS:
            break;
        case T_CLOSEPAREN: ////POSSIBLE ERROR!!
            break;
        case T_PRINT: ////POSSIBLE ERROR!!
            break;
        default:

            parseError(scanner.Scanner::lineNumber(),scanner.nextToken());
    }
}

void Parser::K(){
    //std::cout << "K" << std::endl; 
    P();
    K1(v);
}

void Parser::K1(Vector v_c){
    //std::cout << "K1" << std::endl; 
    switch(scanner.nextToken()){
        case T_MULTIPLY:
            scanner.eatToken(scanner.nextToken());
            P();
            v.x *= v_c.x;
            v.y *= v_c.y;
            v.z *= v_c.z;
            K1(v);
            break;
        case T_EOF:
            break;
        case T_CROSS:
            break;
        case T_PRINT:
            break;
        case T_PLUS:
           break;
        case T_MINUS:
           break;
        case T_CLOSEPAREN: ////POSSIBLE ERROR!!
           break;
        case T_M:
            break;
        default:
            parseError(scanner.Scanner::lineNumber(),scanner.nextToken());
            break;
    }
}

void Parser::P(){
    //std::cout << "P" << std::endl; 
    switch(scanner.nextToken()){
        case T_M:
            //std::cout << "P M" << std::endl; 
            v.x = m.x;
            v.y = m.y;
            v.z = m.z;
            scanner.eatToken(scanner.nextToken());
            break;
        case T_OPENPAREN:
            scanner.eatToken(scanner.nextToken());
            P1();
            break;
        default:
            parseError(scanner.Scanner::lineNumber(),scanner.nextToken());
    }
}

void Parser::P1(){
    //std::cout << "P1" << std::endl; 
    switch(scanner.nextToken()){
        case T_NUMBER:
            scanner.eatToken(scanner.nextToken());
            v.x = scanner.getNumberValue();
            if(scanner.nextToken() == T_COMMA){
                scanner.eatToken(scanner.nextToken());
                if(scanner.nextToken() == T_NUMBER){
                    scanner.eatToken(scanner.nextToken());
                    v.y = scanner.getNumberValue();
                    if(scanner.nextToken() == T_COMMA){
                        scanner.eatToken(scanner.nextToken());
                        if(scanner.nextToken() == T_NUMBER){
                            scanner.eatToken(scanner.nextToken()); 
                            v.z = scanner.getNumberValue();   
                            if(scanner.nextToken() == T_CLOSEPAREN){
                                scanner.eatToken(scanner.nextToken());
                                break;
                            }
                            else{
                                mismatchError(scanner.Scanner::lineNumber(),T_CLOSEPAREN,scanner.nextToken());
                            }
                        }
                        else
                            mismatchError(scanner.Scanner::lineNumber(),T_NUMBER , scanner.nextToken());
                    }
                    else
                        mismatchError(scanner.Scanner::lineNumber(),T_COMMA,scanner.nextToken());
                }
                else
                    mismatchError(scanner.Scanner::lineNumber(),T_NUMBER , scanner.nextToken());
            }
            else
                mismatchError(scanner.Scanner::lineNumber(),T_COMMA,scanner.nextToken());
            break;
        default:
            E();
            if(scanner.nextToken() == T_CLOSEPAREN){
                scanner.eatToken(scanner.nextToken());
                break;
            }
            else{
                mismatchError(scanner.Scanner::lineNumber(), T_CLOSEPAREN, scanner.nextToken());
            }
            break;
    }
}



int main(int argc, char* argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
            std::cout << tokenToString(scanner.nextToken()) << " ";
            scanner.eatToken(scanner.nextToken());
        }
        std::cout<<std::endl;
    } else if (argc == 2 && (strcmp(argv[1], "-e") == 0)) {
        Parser parser(true);
        parser.parse();
    } else {
        Parser parser(false);
        parser.parse();
    }
    return 0;
}
