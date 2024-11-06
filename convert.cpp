#include "skibcy.h"


void Convert::walkBinaryTree(Node* node, bool* changed_ptr) {
    Node* nodeseq[5];
    /*
    Sfgx

     ￬ conversion to binary tree

        r———x
    ———
       |    r———g
        l———
           |    r———f
            l———
                l———S

     ￬ reduction

            r———x
        r———
       |    l———g
    ———
       |    r———x
        l———
            l———f

    */
    if (node == nullptr) 
        return; 
    
    if (node->is_sb)
        if (sq_node_map.find(node->data) != sq_node_map.end()){
            *changed_ptr = true;    
            *node =  *(new Node(sq_node_map[node->data])); 
            return;
        }
        else{
            cout << node->data << " is not found" << endl;
            exit(1);
        }
    if (node->left == nullptr || node->right == nullptr) 
        return;
    walkBinaryTree(node->left, changed_ptr);
    walkBinaryTree(node->right, changed_ptr);
    // I          x
    // node->left node->right
    // nodeseq[0]       nodeseq[1] 
    nodeseq[0] = node->left;
    nodeseq[1] = node->right;
    if (nodeseq[0]->data == "I"){
        *changed_ptr = true;
        *node = *(nodeseq[1]);
        return;
    }
    if (nodeseq[0]->data == "Y"){
        *changed_ptr = true;
        Node* node_right = new Node();
        node_right->left = new Node(nodeseq[0]);
        node_right->right = nodeseq[1];
        node->left = nodeseq[1];
        node->right = node_right;
        return; 
    }
    if (node->left->left == nullptr || node->left->right == nullptr)
        return;
    // K                f                 x
    // node->left->left node->left->right node->right
    // nodeseq[0]       nodeseq[1]        nodeseq[2]
    nodeseq[0] = node->left->left;
    nodeseq[1] = node->left->right;
    nodeseq[2] = node->right;
    if (nodeseq[0]->data == "K"){                
        *changed_ptr = true;
        *node = *(nodeseq[1]);
        return;
    }
    if (node->left->left->left == nullptr || node->left->left->right == nullptr)
        return;
    // S or B or C            f                        g                 x
    // node->left->left->left node->left->-left->right node->left->right node->right
    // nodeseq[0]             nodeseq[1]               nodeseq[2]        nodeseq[3]
    nodeseq[0] = node->left->left->left;
    nodeseq[1] = node->left->left->right;
    nodeseq[2] = node->left->right;
    nodeseq[3] = node->right;    
    if (nodeseq[0]->data == "S"){                
        *changed_ptr = true;

        Node* node_left = new Node();
        node_left->left = nodeseq[1];
        node_left->right = nodeseq[3];
        node->left = node_left;

        Node* node_right = new Node();
        node_right->left = nodeseq[2];
        node_right->right = nodeseq[3];
        node->right = node_right;        
        return;
    }
    else if (nodeseq[0]->data == "B"){                
        *changed_ptr = true;
        node->left = nodeseq[1];
        Node* node_right = new Node();
        node_right->left = nodeseq[2];
        node_right->right = nodeseq[3];
        node->right = node_right;
        return;
    }
    else if (nodeseq[0]->data == "C"){                
        *changed_ptr = true;
        Node* node_left = new Node();
        node_left->left = nodeseq[1];
        node_left->right = nodeseq[3];
        node->left = node_left;
        node->right = nodeseq[2];
        return;
    }
    if (node->left->left->left->left == nullptr || node->left->left->left->right == nullptr)
        return;
    // S' or B' or C'               u                              f                       g                 x
    // node->left->left->left->left node->left->-left->left->right node->left->left->right node->left->right node->right
    // nodeseq[0]                   nodeseq[1]                     nodeseq[2]              nodeseq[3]        nodeseq[4]
    nodeseq[0] = node->left->left->left->left;
    nodeseq[1] = node->left->left->left->right;
    nodeseq[2] = node->left->left->right;
    nodeseq[3] = node->left->right;  
    nodeseq[4] = node->right;
    if (nodeseq[0]->data == "S'"){                
        *changed_ptr = true;

        Node* node_left = new Node();
        Node* node_left_right = new Node();
        node_left_right->left = nodeseq[2];
        node_left_right->right = nodeseq[4];
        node_left->left = nodeseq[1];
        node_left->right = node_left_right;
        node->left = node_left;

        Node* node_right = new Node();
        node_right->left = nodeseq[3];
        node_right->right = nodeseq[4];
        node->right = node_right;        
        return;
    }
    else if (nodeseq[0]->data == "B'"){                
        *changed_ptr = true;

        Node* node_left = new Node();
        node_left->left = nodeseq[1];
        node_left->right = nodeseq[2];
        node->left = node_left;

        Node* node_right = new Node();
        node_right->left = nodeseq[3];
        node_right->right = nodeseq[4];
        node->right = node_right;     
        return;
    }   
    else if (nodeseq[0]->data == "C'"){                
        *changed_ptr = true;

        Node* node_left_right = new Node();
        node_left_right->left = nodeseq[2];
        node_left_right->right = nodeseq[4];

        Node* node_left = new Node();
        node_left->left = nodeseq[1];
        node_left->right = node_left_right;

        node->left = node_left;
        node->right = nodeseq[3];                
        return;
    }             
    return;
}


int counter;

Node* Convert::eval(Node* n){
    if (trace){
        if (counter == 0)
            cout << "\n  ￬ conversion to binary tree\n" << endl;
        else
            cout << "\n  ￬ reduction\n" << endl;
        printTree(n, nullptr, false);
        counter++;        
    }
    bool changed = false;
    walkBinaryTree(n, &changed);

    if (changed)
        return eval(n);        
    else
        return n;
}


any Convert::visitToplevel(combinatorParser::ToplevelContext *ctx) {
    string result_str;        
    for (int i = 0; i < ctx->com_include().size(); i++){  
        counter = 0;
        if (include_flag)
            result_str += any_cast<string>(visit(ctx->com_include(i)));
        else
            comm.push_back(any_cast<pair<string, Node*>>(visit(ctx->com_include(i))));
    }          
    return result_str;
}


any Convert::visitCom_include(combinatorParser::Com_includeContext *ctx){
    any result;
    if (ctx->include())
        result =  visit(ctx->include());
    else if (ctx->command())
        result =  visit(ctx->command());   
    return result;    
}

any Convert::visitInclude(combinatorParser::IncludeContext *ctx){
    string result_str;
    string fname = ctx->dqString()->getText();
    (fname.erase(0, 1)).pop_back();
    ifstream ifs(fname);
    int buf_size = 128;
    char str[buf_size];
    if (ifs.fail()) {
        cerr << fname <<" is not open" << endl;
        exit(1);
    }
    while (ifs.getline(str, buf_size)) {
        result_str = result_str + str + "\n";
    }
    return result_str;   
}


any Convert::visitC_term(combinatorParser::C_termContext *ctx){
    if(include_flag == true)
        return ctx->getText() + ";\n";
    pair<string, Node*> p;
    if (trace)
        cout << "\n\n" << ctx->term()->getText() << endl;
    Node* n = any_cast<Node*>(visit(ctx->term()));
    p.first = "";
    p.second = eval(n);       
    return p;
}


any Convert::visitC_sq_eq_term(combinatorParser::C_sq_eq_termContext *ctx){
    pair<string, Node*> p;
    if(include_flag == true)
        return ctx->getText() + ";\n";
    if (trace)
        cout << "\n\n" << ctx->sq()->getText() + " = " + ctx->term()->getText() << endl;
    Node* n = any_cast<Node*>(visit(ctx->term()));
    p.first = ctx->sq()->getText() + " =";
    p.second = eval(n); 
    sq_node_map[ctx->sq()->getText()] = p.second;         
    return p;
}


any Convert::visitC_sq_ceq_term(combinatorParser::C_sq_ceq_termContext *ctx){
    if(include_flag == true)
        return ctx->getText() + ";\n";
    pair<string, Node*> p;
    Node* n = any_cast<Node*>(visit(ctx->term()));
    p.first = ctx->sq()->getText() + " :=";
    p.second = n;//eval(n); 
    if (trace){
        cout << "\n\n" << ctx->sq()->getText() + " := " + ctx->term()->getText() << endl;
        cout << "\n  ￬ conversion to binary tree\n" << endl;
        printTree(n, nullptr, false); 
    }
    sq_node_map[ctx->sq()->getText()] = n;         
    return p;
}


any Convert::visitC_sq_veq_term(combinatorParser::C_sq_veq_termContext *ctx){
    if(include_flag == true)
        return ctx->getText() + ";\n";
    pair<string, Node*> p;
    Node* n = any_cast<Node*>(visit(ctx->term()));
    p.first = "";
    p.second = nullptr;//eval(n); 
    sq_node_map[ctx->sq()->getText()] = eval(n);         
    return p;
}


any Convert::visitC_sq_vceq_term(combinatorParser::C_sq_vceq_termContext *ctx){
    if(include_flag == true)
        return ctx->getText() + ";\n";
    pair<string, Node*> p;
    Node* n = any_cast<Node*>(visit(ctx->term()));
    p.first = "";
    p.second = nullptr;
    sq_node_map[ctx->sq()->getText()] = n;         
    return p;
}


any Convert::visitC_dq_string(combinatorParser::C_dq_stringContext *ctx){
    if(include_flag == true)
        return ctx->getText() + ";\n";
    pair<string, Node*> p;
    p.first = any_cast<string>(visit(ctx->dqString()));
    p.second = nullptr;
    return p;   
}


any Convert::visitC_newline(combinatorParser::C_newlineContext *ctx){
    if(include_flag == true)
        return ctx->getText() + ";\n";
    pair<string, Node*> p;
    p.first = "";
    p.second = nullptr;
    return p;
}


any Convert::visitT_app_a(combinatorParser::T_app_aContext *ctx){ 
    Node* node = new Node();
    node->left = any_cast<Node*>(visit(ctx->term()));
    node->right =  any_cast<Node*>(visit(ctx->aterm()));
    return node;
}


any Convert::visitT_a(combinatorParser::T_aContext *ctx){ 
    return visit(ctx->aterm());
}


any Convert::visitA_v(combinatorParser::A_vContext *ctx){ 
    return visit(ctx->v());
}


any Convert::visitA_sq(combinatorParser::A_sqContext *ctx) {
    return visit(ctx->sq());
}


any Convert::visitA_paren(combinatorParser::A_parenContext *ctx){ 
    return visit(ctx->term());
}


any Convert::visitV(combinatorParser::VContext *ctx) {
    return new Node(ctx->var()->getText());
}


any Convert::visitVar(combinatorParser::VarContext *ctx) {
    return new Node(ctx->getText());
}


any Convert::visitSq(combinatorParser::SqContext *ctx) {
    Node* node = new Node(ctx->getText());
    node->is_sb = true;
    return node;
}


any Convert::visitDqString(combinatorParser::DqStringContext *ctx) {
    string result_str = ctx->getText();
    (result_str.erase(0, 1)).pop_back();
    return result_str;
}
