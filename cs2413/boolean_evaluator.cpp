#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cstring>
using namespace std;

typedef struct AST *pNode;

struct AST {
    string info;
    pNode children[2];
};

typedef struct {
    bool success;
    vector<string> syms;
} tokRslt;

typedef struct {
    bool success;
    AST ast;
} parseRslt;

typedef struct {
    bool val;
    string msg;
} TPERslt;

regex tokens("(<=>)|(T)|(F)|(~)|(=>)|(\\^)|(v)|(\\()|(\\))+\\/g");

tokRslt tokenize(string s);
bool eval(AST tree);
TPERslt TPE(string s);
string TPEOut(string s);
parseRslt parse(vector<string> L);
pNode cons(string s, pNode c1, pNode c2);
parseRslt Const(vector<string> L, int i, int j);
parseRslt U(vector<string> L, int i, int j);
parseRslt N(vector<string> L, int i, int j);
parseRslt C(vector<string> L, int i, int j);
parseRslt D(vector<string> L, int i, int j);
parseRslt I(vector<string> L, int i, int j);
parseRslt B(vector<string> L, int i, int j);

void prin(vector<string> A) {
    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << ", ";    
    }
    cout << endl;
}

// Uses regular expression capture groups to split the string into its appropriate tokens, for example
// with the input string "T=>(F) will turn into ["T", "=>", "(", "F", ")"], if it isn't successful then result.success
// will be false
tokRslt tokenize(string s) {
    tokRslt result;
    if (regex_search(s, tokens)) {
        sregex_iterator begin(s.begin(), s.end(), tokens);
        sregex_iterator end;
        for (sregex_iterator i = begin; i != end; ++i)
            result.syms.push_back(i->str());
        result.success = true;
    } else result.success = false;
    return result;
}

// If the vector of strings is a boolean expression then return the parseRslt with the ast of the vector of strings, and
// a success flag
parseRslt parse(vector<string> L) {
    return B(L, 0, L.size());
}

// Takes in a string s that is a potential boolean expression, if it is made of just valid tokens (token.success),
// then parse the vector of tokens from the input into an abstract syntax tree,
// If the parse is successfull then evaluate the AST and return a TPERslt with the eval of the ast and a success or
// error message
TPERslt TPE(string s) {
    TPERslt result;
    tokRslt token = tokenize(s);
    if (token.success) {
        result.msg = "success";
        parseRslt p = parse(token.syms);
        if (!p.success) result.msg = "grammar error";
        else result.val = eval(p.ast);
    } else result.msg = "symbol error";
    return result;
}

// If string s is a valid boolean expression, then return the value of the expression
// If it isn't (result.msg != "success") then return the error message (grammar or symbol error)
string TPEOut(string s) {
    TPERslt result = TPE(s);
    if (result.msg == "success") {
        if (result.val) return "true";
        else return "false";
    }
    else return result.msg;
}

// Const ::= 'T' | 'F'
// If the vector of symbols L from index i to index j (non-inclusive) is a Const
// then return the parseRslt with ast with "T" or "F" with no children.
parseRslt Const(vector<string> L, int i, int j) {
    parseRslt result;
    if (j - i == 1) {
        if (L[i] == "T" || L[i] == "F") {
            result.success = true;
            result.ast = *cons(L[i], NULL, NULL);
        }
    } else result.success = false;
    return result;
}

// U ::= Const | '(' B ')'
// If the vector of symbols l from index i to index j (non-inclusive) is an Unbreakable expression
// then return the parseRslt with ast of a const or '(' B ')''
parseRslt U(vector<string> L, int i, int j) {
    parseRslt *result = new parseRslt;
    parseRslt result1 = Const(L, i , j);
    if (result1.success) {
        result->success = true;
        result->ast = result1.ast;
        return *result;
    }
    if (L[i] == "(" && L[j-1] == ")") {
        parseRslt result2 = B(L, i+1, j-1);
        if (result2.success) {
            result->success = true;
            result->ast = result2.ast;
            return *result;
        }
    }
    result->success = false;
    return *result;
}

// N ::= U | '~' N
// If the vector of symbols L from index i to index j (non-inclusive) is a negation
// then return the parseRslt with ast of a U or '~' N
parseRslt N(vector<string> L, int i, int j) {
    parseRslt *result = new parseRslt;
    parseRslt result1 = U(L, i, j);
    if (result1.success) {
        result->success = true;
        result->ast = result1.ast;
        return *result;
    } else {
	    if (L[i] == "~") {
	    	parseRslt result2 = N(L, i+1, j);
	    	if (result2.success) {
	    		result->success = true;
	    		result->ast = *cons("~", &result2.ast, NULL);
	    		return *result;
	    	}
	    }
	}
    result->success = false;
    return *result;
}

// C ::= N | C '^' N
// If the vector of symbols L from index i to index j (non-inclusive) is a Conjuction
// then return the parseRslt with ast of of N or C '^' N
parseRslt C(vector<string> L, int i, int j) {
    parseRslt *result = new parseRslt;
    parseRslt result1 = N(L, i, j);
    if (result1.success) {
        result->success = true;
        result->ast = result1.ast;
        return *result;
    } else {
        for (unsigned int c = i + 1; c < j; c++) {
            if (L[c] == "^") {
                parseRslt result2 = C(L, i, c);
                if (result2.success) {
                    parseRslt result3 = N(L, c+1, j);
                    if (result3.success) {
                        result->success = true;
                        result->ast = *cons("^", &result2.ast, &result3.ast);
                        return *result;
                    }
                }
            }
        }
    }
    result->success = false;
    return *result;
}

// D ::= C | D 'v' C
// If the vector of symbols L from index i to index j (non-inclusive) is a Disjunction
// then return the parseRslt with ast of C or D 'v' C
parseRslt D(vector<string> L, int i, int j) {
    parseRslt *result = new parseRslt;
    parseRslt result1 = C(L, i, j);
    if (result1.success) {
        result->success = true;
        result->ast = result1.ast;
        return *result;
    } else {
        for (unsigned int c = i + 1; c < j; c++) {
            if (L[c] == "v") {
                parseRslt result2 = D(L, i, c);
                if (result2.success) {
                    parseRslt result3 = C(L, c+1, j);
                    if (result3.success) {
                        result->success = true;
                        result->ast = *cons("v", &result2.ast, &result3.ast);
                        return *result;
                    }
                }
            }
        }
    }
    result->success = false;
    return *result;
}

// I ::= D | D '=>' I

parseRslt I(vector<string> L, int i, int j) {
    parseRslt *result = new parseRslt;
    parseRslt result1 = D(L, i , j);
    if (result1.success) {
        result->success = true;
        result->ast = result1.ast;
        return *result;
    } else {
        for (unsigned int c = i + 1; c < j; c++) {
            if (L[c] == "=>") {
                parseRslt result2 = D(L, i, c);
                if (result2.success) {
                    parseRslt result3 = I(L, c+1, j);
                    if (result3.success) {
                        result->success = true;
                        result->ast = *cons("=>", &result2.ast, &result3.ast);
                        return *result;
                    }
                }
            }
        }
    }
    result->success = false;
    return *result;
}

// B ::= I | I '<=>' B
parseRslt B(vector<string> L, int i, int j) {
    parseRslt *result = new parseRslt;
    parseRslt result1 = I(L, i, j);
    if (result1.success) {
        result->success = true;
        result->ast = result1.ast;
        return *result;
    } else {
        for (int c = i + 1; c < j; c++) {
            if (L[c] == "<=>") {
                parseRslt result2 = I(L, i, c);
                if (result2.success) {
                    parseRslt result3 = B(L, c+1, j);
                    if (result3.success) {
                        result->success = true;
                        result->ast = *cons("<=>", &result2.ast, &result3.ast);
                        return *result;
                    }
                }
            }
        }
    }
    result->success = false;
    return *result;
}

pNode cons(string s, pNode c1, pNode c2) {
    pNode ret = new AST;
    ret->info = s;
    ret->children[0] = c1;
    ret->children[1] = c2;
    return ret;
}

bool eval(AST tree) {
    if (tree.info == "=>")
        return (eval(*(tree.children[0])) && !eval(*(tree.children[1])));
    else if (tree.info == "<=>")
        return (eval(*(tree.children[0])) == eval(*(tree.children[1])));
    else if (tree.info == "~")
        return (!(eval(*(tree.children[0]))));
    else if (tree.info == "^")
        return (eval(*(tree.children[0])) && eval(*(tree.children[1])));
    else if (tree.info == "v")
        return (eval(*(tree.children[0])) != eval(*(tree.children[1])));
    else if (tree.info == "T")
        return true;
    return false;
}
