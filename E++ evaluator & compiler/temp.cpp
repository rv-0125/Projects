// evaluator.cpp
#include "evaluator.h"

Evaluator::Evaluator() {
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    // Clean up dynamically allocated memory and resources
    for (ExprTreeNode* node : expr_trees) {
        delete node;
    }
    expr_trees.clear();
    delete symtable;
}

void Evaluator::parse(vector<string> code) {
    // Initialize any necessary variables or data structures
    expr_trees.clear(); // Clear existing expression trees
    
    // Initialize a vector for expressions
    vector<ExprTreeNode*> expressionVector;

    for (const string& token : code) {
        ExprTreeNode* node = new ExprTreeNode();
        
        // Handle different token types
        if (token == ":=") {
            // Assignment statement - pop operands and construct a tree
            if (!expressionVector.empty()) {
                node->type = ":=";
                node->right = expressionVector.back();
                expressionVector.pop_back();
                node->left = expressionVector.back();
                expressionVector.pop_back();
            }
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Binary operator
            node->type = token;
            if (!expressionVector.empty()) {
                node->right = expressionVector.back();
                expressionVector.pop_back();
                node->left = expressionVector.back();
                expressionVector.pop_back();
            }
        } else {
            // Operand (variable or value)
            node->type = "VAL"; // Assume it's a value by default
            if (isalpha(token[0])) {
                node->type = "VAR"; // If it starts with a letter, it's a variable
                node->id = token;
            } else {
                // Convert the token to an UnlimitedRational and set it as the value
                UnlimitedRational* value = new UnlimitedRational(UnlimitedInt(token));
                node->val = value;
            }
        }

        // Push the constructed node into the vector
        expressionVector.push_back(node);
    }

    // The root of the expression tree should be at the end of the vector
    if (!expressionVector.empty()) {
        expr_trees.push_back(expressionVector.back());
    }
}

void Evaluator::eval() {
    if (expr_trees.empty()) {
        return; // Nothing to evaluate
    }

    // Evaluate the last element of the expr_trees vector
    ExprTreeNode* root = expr_trees.back();
    if (root->type == ":=") {
        // Assignment statement
        string variableName = root->left->id;
        UnlimitedRational* result = evaluateExpression(root->right);
        // Insert the result into the symbol table
        symtable->insert(variableName, result);
    }
    // Populate the symbol table during evaluation
    populateSymbolTable(root);
}

UnlimitedRational* Evaluator::evaluateExpression(ExprTreeNode* node) {
    if (node->type == "VAR") {
        // Variable - look up its value in the symbol table
        return symtable->search(node->id);
    } else if (node->type == "VAL") {
        // Value - return the associated UnlimitedRational
        return node->val;
    } else {
        // Operator - evaluate the left and right subtrees
        UnlimitedRational* leftOperand = evaluateExpression(node->left);
        UnlimitedRational* rightOperand = evaluateExpression(node->right);
        return performOperation(node->type, leftOperand, rightOperand);
    }
}

UnlimitedRational* Evaluator::performOperation(const string& op, UnlimitedRational* left, UnlimitedRational* right) {
    // Implement the logic for arithmetic operations here
    // You'll need to handle addition, subtraction, multiplication, and division
    // Be sure to consider edge cases (e.g., division by zero)
    // Return the result as a new UnlimitedRational
    // Example code for addition:
    if (op == "+") {
        return *left + *right;
    } else if (op == "-") {
        return *left - *right;
    } else if (op == "*") {
        return *left * *right;
    } else if (op == "/") {
        // Handle division by zero here and return a special value if needed
        if (*right == UnlimitedRational::ZERO) {
            // Division by zero, return a special value (e.g., NaN)
            return new UnlimitedRational(); // Implement the special value accordingly
        } else {
            return *left / *right;
        }
    }
    return new UnlimitedRational(); // Handle unsupported operations
}

void Evaluator::populateSymbolTable(ExprTreeNode* node) {
    if (node == nullptr) {
        return;
    }

    if (node->type == "VAR") {
        symtable->insert(node->id, new UnlimitedRational());
    }

    populateSymbolTable(node->left);
    populateSymbolTable(node->right);
}




Evaluator::Evaluator(){
    SymbolTable* symtable= new SymbolTable();
}

Evaluator::~Evaluator() {
    for (int i=0; i<expr_trees.size();i++) {
        delete expr_trees[i];
    }
    expr_trees.clear();

    delete symtable;
}

bool isOperator(const std::string& token) {
    if (token == "+" || token == "-" || token == "*" || token == "/"){
        return true;
    }
    return false;
}

ExprTreeNode* CreateExprTree(std::vector<std::string>& code) {
    if (code.empty()) {
        return nullptr;
    }

    std::string token = code.back();
    code.pop_back();

    ExprTreeNode* node = new ExprTreeNode(token);

    if (isOperator(token)) {
        node->right = CreateExprTree(code);
        node->left = CreateExprTree(code);
    }

    return node;
}


void Evaluator::parse(vector<string> code){
    if (code.empty()) {
        return;
    }

    ExprTreeNode* root = CreateExprTree(code);

    expr_trees.push_back(root);
}

int evaluateExpression(ExprTreeNode* node){
    if (!node->left && !node->right) {
        try {
            return std::stoi(node->val); 
        }
    }
}
void Evaluator::eval(){
     if (!expr_trees.empty()) {
            ExprTreeNode* root = expr_trees.back();
            int result = evaluateExpression(root);
            
            symtable->insert("result", result);
    }
    
}

