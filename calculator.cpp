#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <limits>


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

};

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
                                    if(c == 't'){}
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
            std::cin.get(c);
            s.push_back(c);
            while(std::cin.peek() >= '0' && std::cin.peek() <= '9'){
                std::cin.get(c);
                s.push_back(c);
            }
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
    int num;

    num = stoi(s);
    return num;
}


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
        
    public:
        void parse();
        
        Parser(bool evaluate) : evaluate(evaluate) {
            // You may need to complete a Parser constructor here
        }
};

void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
    Start();
}

void Parser::Start() {
    // This is an example of a recursive-descent function for a
    // non-terminal symbol. In this case, it is just a placeholder
    // which accepts infinite numbers of T_PLUS. You will need to
    // replace this with correct code for the real grammar start symbol.
    
    switch (scanner.nextToken()) {
        case T_PLUS:
            scanner.eatToken(T_PLUS);
            Start();
            break;
        case T_EOF:
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
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
