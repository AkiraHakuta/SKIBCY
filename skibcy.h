#ifndef SKIBCY_H
#define SKIBCY_H


#include "antlr4-runtime.h"
#include "combinatorLexer.h"
#include "combinatorParser.h"
#include "combinatorVisitor.h"
#include <array>

using namespace antlr4;
using namespace tree;
using namespace std;

string indent_sp(int size);


class Node
{
    public:
        string data;
        Node *left, *right;
        bool is_sb;

        Node(string data){
            this->data = data;
            this->left = this->right = nullptr;
            this->is_sb = false;
        }

        Node(){
            this->data = "";
            this->left = this->right = nullptr;
            this->is_sb = false;
        }

        Node(Node* n){        
            this->data = n->data;
            this->is_sb = n->is_sb;
            if (n->left == nullptr)
                this->left = nullptr;
            else
                this->left = new Node(n->left);
            if (n->right == nullptr)
                this->right = nullptr;
            else
                this->right = new Node(n->right);
        }
};


class Trunk
{
    public:
        Trunk *prev;
        string str;

        Trunk(Trunk *prev, string str)
        {
            this->prev = prev;
            this->str = str;
        }
};


void showTrunks(Trunk *p);

void printTree(Node* root, Trunk *prev, bool isLeft);

class Convert : public combinatorVisitor{    
    public:
        bool trace;
        Convert(bool trace0):trace(trace0){};
        vector<pair<string,Node*>> comm;
        map<string, Node*> sq_node_map;
        bool include_flag; 
        
        any visitToplevel(combinatorParser::ToplevelContext *context);

        any visitCom_include(combinatorParser::Com_includeContext *context);

        any visitInclude(combinatorParser::IncludeContext *context);

        any visitC_term(combinatorParser::C_termContext *context);
        
        any visitC_sq_eq_term(combinatorParser::C_sq_eq_termContext *context); 

        any visitC_sq_ceq_term(combinatorParser::C_sq_ceq_termContext *context);  

        any visitC_sq_veq_term(combinatorParser::C_sq_veq_termContext *context); 

        any visitC_sq_vceq_term(combinatorParser::C_sq_vceq_termContext *context); 

        any visitC_dq_string(combinatorParser::C_dq_stringContext *context);

        any visitC_newline(combinatorParser::C_newlineContext *context);  

        any visitT_app_a(combinatorParser::T_app_aContext *context);

        any visitT_a(combinatorParser::T_aContext *context);  

        any visitA_v(combinatorParser::A_vContext *context);

        any visitA_sq(combinatorParser::A_sqContext *context);

        any visitA_paren(combinatorParser::A_parenContext *context);

        any visitV(combinatorParser::VContext *context);    

        any visitVar(combinatorParser::VarContext *context);

        any visitSq(combinatorParser::SqContext *context);

        any visitDqString(combinatorParser::DqStringContext *context);

        void walkBinaryTree(Node* node, bool* changed_ptr);

        Node* eval(Node* n);
};

#endif  // SKIBCY_H