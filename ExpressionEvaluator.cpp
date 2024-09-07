#include<iostream>
#include<vector>
#include<string>
using namespace std;
int check(char c){
    if(c=='+'||c=='-'||c=='/'||c=='*') return 1;
    else return 0;
}
int prec(char c){
    if(c=='/'||c=='*') return 2;
    if(c=='+'||c=='-') return 1;
    else 0;
}
string infix(string exp){
    vector <char> opr;
    string res;
    for(int i=0;exp[i]!='\0';i++){
        char c = exp[i];
        if(!check(c)){
            if(c=='('){
                opr.push_back(c);
            }
            else if(c==')'){
                while(opr.back()!='('){
                    res+= opr.back(); opr.pop_back();
                }
                opr.pop_back();
            }
            else{
                res+=c;
            }
        }
        else{
            while(!opr.empty() && prec(c)<=prec(opr.back())){
                res+=opr.back(); opr.pop_back();
            }
            opr.push_back(c);
        }
    }
    while(!opr.empty()){
        res+=opr.back(); opr.pop_back();
    }
    return res;
}
string prefix(string exp){
    vector<string> op;
    int l= exp.length();
    for(int i=l-1; i>-1;i--){
        string c; c.push_back(exp[i]);
        if(!check(c[0])){
            op.push_back(c);
        }
        else{
            string y = op.back(); op.pop_back();
            string x = op.back(); op.pop_back();
            string z = y + x+c;
            op.push_back(z);
        }
    }
    string res = op.back(); op.pop_back();
    return res;
}
typedef struct Node{
    char data;
    struct Node* left;
    struct Node* right;
    Node(char data): data(data), left(nullptr), right(nullptr){}
}Node;
class Exptree{
    Node* root;
    public:
    Exptree() : root(nullptr) {}
    void build(string exp);
    int evaluate();
    int result(Node* node);
};
void Exptree::build(string exp){
    vector<Node*> tree;
    for(auto& c: exp){
        if(!check(c)){
            tree.push_back(new Node(c));
        }
        else{
            Node* newNode = new Node(c);
            newNode->right = tree.back(); tree.pop_back();
            newNode->left = tree.back(); tree.pop_back();
            tree.push_back(newNode);
        }
    }
    root = tree.back(); tree.pop_back();
}
int Exptree::evaluate(){
    return result(root);
}
int Exptree::result(Node* node){
    if(node==nullptr) return 0;
    if(!check(node->data)) return node->data-'0';
    int left = result(node->left);
    int right = result(node->right);
        switch(node->data){
            case '+':
            return left + right ;
            case '-':
            return left - right ;
            case '*':
            return left * right ;
            case '/':
            return left / right ;
            default: return 0;
        }
}
int main(){
    Exptree tree;
    string exp;
    cout<<"Enter any single digit expression (Prefix/Infix/Postfix): ";
    cin>>exp;
    int l=exp.length();
    string exp2;
    if(check(exp[0])){
        exp2=prefix(exp);
        tree.build(exp2);
    }
    else if(check(exp[l-1])){
        tree.build(exp);
    }
    else{
        exp2=infix(exp);
        tree.build(exp2);
    }
    cout<<exp<<" = "<<tree.evaluate()<<endl;
    return 0;
}