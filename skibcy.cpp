#include "skibcy.h"
#include <iomanip>

string indent_sp(int size)
{ 
    string result = "";
    for(int i = 0; i < size; i++)
      result += " ";
    return result;
}


string beautify_lisp_string(string in_string)
{
    int indent_size = 3;
    int curr_indent = 0;
    string out_string = string(1,in_string[0]);
    string indent = "";
    for (int i = 1; i < in_string.size(); i++)
        if (in_string[i] == '(' and  in_string[i+1] != ' '){
           curr_indent += indent_size;
           out_string += '\n' + indent_sp(curr_indent) + '(';
        }
        else if (in_string[i] == ')'){
          out_string += ')';
          if (curr_indent >= indent_size)
            curr_indent -= indent_size;
        }
        else
          out_string += in_string[i];     
    return out_string;
}


void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}


void printTree(Node* root, Trunk *prev, bool isRight)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "———";
    }
    else if (isRight)
    {
        trunk->str = "r———";
        prev_str = "   |";
    }
    else {
        trunk->str = "l———";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->data << endl;
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}



int main(int argc, const char *args[])
{
    string include_str;

    bool trace;
    if (argc == 3 && string(args[2]) == "-t")
        trace = true;
    else
        trace = false;

    ifstream ifs;
    Node* n;
    ifs.open(args[1]);
    ANTLRInputStream input0(ifs);
    combinatorLexer lexer0(&input0);    
    CommonTokenStream tokens0(&lexer0);
    /*
    cout << "Tokens:" << endl;
    tokens0.fill();
    for (Token *token : tokens0.getTokens())
        cout << token->toString() << endl;/**/
    combinatorParser parser0(&tokens0);
    tree::ParseTree *tree = parser0.toplevel();
    /*
    cout << endl << "Parse tree (Lisp format):" << endl;
    string lisp_tree_str = tree->toStringTree(&parser);
    cout << beautify_lisp_string(lisp_tree_str) << '\n' << endl; /**/  
    Convert *convert = new Convert(false);
    //cout << tokens0.getText() << endl;
    convert->include_flag = true;
    include_str = any_cast<string>(convert->visit(tree));
    //cout << "\n" << include_str << endl;

    ANTLRInputStream input1;
    input1.load(include_str);
    combinatorLexer lexer1(&input1);    
    CommonTokenStream tokens1(&lexer1);
    combinatorParser parser1(&tokens1);
    tree::ParseTree *tree1 = parser1.toplevel();
    
    if (trace)
        cout << "trace:";
    convert = new Convert(trace);
    convert->include_flag = false;
    convert->visit(tree1);

    if (!trace){
        cout << "result (binary tree):\n";
            for (int i = 0; i < convert->comm.size(); i++){
                if (convert->comm[i].second != nullptr){
                    cout << "\n" << convert->comm[i].first << endl;
                    printTree(convert->comm[i].second, nullptr, false); 
                }                
            }  
    }    
    return 0;
}
