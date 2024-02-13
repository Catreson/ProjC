#include <iostream>
#include <iomanip>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <string>


//User definitions
#define rank_plus 1
#define rank_minus 1
#define rank_multiply 2
#define rank_divide 2
#define rank_power 3
#define rank_high 4


//User defined global variables
long double value_of_x;

//User defined structures
struct Tree{
    Tree *father;
    Tree *left_son;
    Tree *right_son;
    char type;
    long double number;
    char symbol;
    long double *x;
    Tree();
};
Tree::Tree()
    {
        father=nullptr;
        left_son=nullptr;
        right_son=nullptr;
    }

//User defined funcion declarations
int syntax_check(std::string& text);
void space_erase(std::string& text);
void bracket_erase(std::string& text);
int root_finder(std::string& text, bool& is_single);
int vertex_finder(std::string& text,Tree* tree,bool &is_single);
void tree_creator(std::string& text, Tree* tree, int pos, bool& is_single);
void draw_tree(Tree* root);
long double calculate_tree(Tree *root);
void kill_tree(Tree *root); 


//Main
int main()
{
    //Static variables declarations and init
    int itmp;
    bool single=false;
    std::string text_line;  
    Tree tree_root;
    bool syntax_correct=false;
    bool input_correct=false;

    while(!input_correct)   //Input check loop
    {
        syntax_correct=false;
    
        while(!syntax_correct) //Syntax check loop
        {
            std::cout<<"Give input:\n";
            std::getline(std::cin,text_line);   //Input
            space_erase(text_line);             //Erasing any spaces from input
            bracket_erase(text_line);           //Erasing outer brackets if necesary
            if(!syntax_check(text_line))        //Syntex check loop condition
                syntax_correct=true;
        }

        //Input to compare
        std::cout<<text_line<<std::endl;
        
        itmp=root_finder(text_line);            //Trying to find valid root for tree
        if(itmp!=0)                             //Input check loop condition
            input_correct=true;                 
        else{
            std::cout<<"No sense, nothing to calculate\n";            
        }
    }

    //When valid root found tree_root is inicialized
    tree_root.type='o';
    tree_root.symbol=text_line[itmp];

    //Tree building recursive function called
    tree_creator(text_line,&tree_root, itmp, single);

    //Input presented in Łukasiewicz notation
    draw_tree(&tree_root);
    
    //Asking for x value, no mater if it's present
    std::cout<<'\n'<<"Input x value:\t";
    std::cin>>value_of_x;

    //Presenting value of function in point x0
    std::cout<<'\n'<<"Result is:\t";
    std::cout<<calculate_tree(&tree_root)<<'\n';
    kill_tree(&tree_root);
    tree_root.left_son=nullptr;
    tree_root.right_son=nullptr;
   return 0; 
}
//User defined function definitions


void tree_creator(std::string& text, Tree* tree, int pos, bool& is_single){  //Tree building recursive function, builds tree
    int itmp=0;
    bool single=false;
    std::string text_l;
    std::string text_r; 
    text_l=text.substr(0,pos);
    text_r=text.substr(pos+1,text.length()-pos);
    Tree *left_branch = new Tree;
    tree->left_son=left_branch;
    left_branch->father=tree;
    bracket_erase(text_l);
    itmp=vertex_finder(text_l,left_branch,single);
    if(itmp)
        tree_creator(text_l,left_branch,itmp);
    
    if(!is_single)
    {
    Tree *right_branch = new Tree;
    right_branch->father=tree;
    tree->right_son=right_branch;
    bracket_erase(text_r);
    itmp=vertex_finder(text_r,right_branch);
    if(itmp)
        tree_creator(text_r,right_branch,itmp);
    }
    


}

long double calculate_tree(Tree *root){                     //Tree calculation recursive function, calculates the value of branch
Tree *tree=root;
switch(tree->type)
{
    case 'x':
        return value_of_x;
    break;
    case 'n':
        return tree->number;
    break;
    case 'o':
        switch(tree->symbol)
        {
            case '+':
                return calculate_tree(tree->left_son)+calculate_tree(tree->right_son);
            break;
            case '-':
                return calculate_tree(tree->left_son)-calculate_tree(tree->right_son);
            break;
            case '*':
                return calculate_tree(tree->left_son)*calculate_tree(tree->right_son);
            break;
            case '/':
                if(calculate_tree(tree->right_son)!=0)
                    return calculate_tree(tree->left_son)/calculate_tree(tree->right_son);
                else
                    std::cout<<"Cannot divide by 0";
                    return -1;
            break;
            case '^':
                return pow(calculate_tree(tree->left_son),calculate_tree(tree->right_son));
            break;
    }
    break;
}
return -1;

}

void kill_tree(Tree *root)                       //Tree killing function, does what expected
{
    Tree *tree=root;
    if(tree->left_son!=nullptr)
        kill_tree(tree->left_son);
    if(tree->right_son!=nullptr)
        kill_tree(tree->right_son);
    if(tree->father!=nullptr)
            delete tree;
}

void draw_tree(Tree* root){                     //Function that reads the tree in VLR order and outputs as console output
Tree *tree=root;
switch(tree->type)
{
    case 'o':
        std::cout<<tree->symbol;
    break;
    case 'x':
        std::cout<<'x';
    break;
    case 'n':
        std::cout<<tree->number;
    break;
}
if(tree->left_son!=nullptr)
    draw_tree(tree->left_son);
if(tree->right_son!=nullptr)
    draw_tree(tree->right_son);
}

int root_finder(std::string& text){                     //Funtcion that finds the best root for input statement
    int root=0;
    int bracket=0;
    char val=0;
    int rank=rank_high;
    for(int i=text.length()-1;i>=0;--i)
    {
        if(text[i]=='(')
            bracket++;
        if(text[i]==')')
            bracket--;
        if(bracket==0)
        {
            switch (text[i])
            {
            case '+':
                if(rank>rank_plus&&i>0)
                {
                    root=i;
                    val='+';
                    rank=rank_plus;
                }
                break;
            case '-':
                if(rank>rank_minus&&i>0)
                {
                    root=i;
                    val='-';
                    rank=rank_minus;
                }
                break;
            case '*':
                if(rank>rank_multiply&&i>0)
                {
                    root=i;
                    val='*';
                    rank=rank_multiply;
                }
                break;
            case '/':
                if(rank>rank_divide&&i>0)
                {
                    root=i;
                    val='/';
                    rank=rank_divide;
                }
                break;
            case '^':
                if(rank>rank_power&&i>0)
                {
                    root=i;
                    val='^';
                    rank=rank_power;
                }
                break;
            default:
                break;
            }
        }
        
    }

    return root;
}

int vertex_finder(std::string& text, Tree* tree,bool& is_single){               //Function that finds what should be vertex for this tree layer
    int bracket=0;
    int vertex=0;
    char val=0;
    int rank=rank_high;
    long double num=0;
    for(int i=text.length()-1;i>=0;--i)
    {
        if(text[i]=='(')
            bracket++;
        if(text[i]==')')
            bracket--;
        if(bracket==0)
        {
            switch (text[i])
            {
            case '+':
                if(rank>rank_plus&&i>0)
                {
                    vertex=i;
                    val=text[i];
                    rank=rank_plus;
                }
                break;
            case '-':
                if(rank>rank_minus&&i>0)
                {
                    vertex=i;
                    val=text[i];
                    rank=rank_minus;
                }
                break;
            case '*':
                if(rank>rank_multiply&&i>0)
                {
                    vertex=i;
                    val=text[i];
                    rank=rank_multiply;
                }
                break;
            case '/':
                if(rank>rank_divide&&i>0)
                {
                    vertex=i;
                    val=text[i];
                    rank=rank_divide;
                }
                break;
            case '^':
                if(rank>rank_power&&i>0)
                {
                    vertex=i;
                    val=text[i];
                    rank=rank_power;
                }
                break;
            default:
                break;
            }
        }
    }

        if(vertex==0)
        {
            if(text[0]=='x')
                {
                    tree->type='x';
                    tree->number=value_of_x;
                }
            else{
                tree->type='n';
                tree->number=std::stold(text);
            }
        }
        else{
            tree->type='o';
            tree->symbol=val;
        }
        
    

    return vertex;
}

void bracket_erase(std::string& text){                          //Bracket erasing function
    std::string stmp;
    int is_open_cnt=0;
    if(text[0]=='('&&text[text.length()-1]==')')
        {
            stmp=text.substr(1,text.length()-2);
            for(int i=0;i<stmp.length();++i)
                {
                    if(stmp[i]==')')
                    {
                        if(is_open_cnt==0)
                            return;
                        else
                            is_open_cnt--;
                    }
                    if(stmp[i]=='(')
                        is_open_cnt++;
                }
            text.erase(0,1);
            text.erase(text.length()-1,1);
        }

}

void space_erase(std::string& text){                        //Space and coma erasing function
    for(int i=0;i<text.length();++i)
        {
            if(text[i]==' ')
                {
                    text.erase(i,1);
                }
            if(text[i]==',')
                text[i]='.';

        }
}
int syntax_check(std::string& text){                        //Checking for not allowed symbols and if brackets are ok
    int cnt=0;
    std::size_t seeker=text.find("sin");
    while(seeker!=std::string::npos)
        {
                text.replace(seeker,3,"s");
                seeker=text.find("sin");
        }

    seeker=text.find("cos");
    while(seeker!=std::string::npos)
        {
                text.replace(seeker,3,"c");
                seeker=text.find("cos");
        }
    
    seeker=text.find("tan");
    while(seeker!=std::string::npos)
        {
                text.replace(seeker,3,"t");
                seeker=text.find("tan");
        }
    
    seeker=text.find("cot");
    while(seeker!=std::string::npos)
        {
                text.replace(seeker,3,"q");
                seeker=text.find("cot");
        }
    
    seeker=text.find("pi");
    while(seeker!=std::string::npos)
        {
                text.replace(seeker,2,"p");
                seeker=text.find("pi");
        }

    for(int i=0;i<text.length();++i)
        {
            switch (text[i]){

                case '(':
                    cnt++;
                break;
                case ')':
                    cnt--;
                break;
                case '.':
                break;
                case 'x':
                break;
                case '^':
                break;
                case '/':
                break;
                case '+':
                break;
                case '-':
                break;
                case '*':
                break;
                case '0':
                break;
                case '1':
                break;
                case '2':
                break;
                case '3':
                break;
                case '4':
                break;
                case '5':
                break;
                case '6':
                break;
                case '7':
                break;
                case '8':
                break;
                case '9':
                break;
                case 's':
                break;
                case 'c':
                break;
                case 'q':
                break;
                case 't':
                break;
                case 'p':
                break;
                case 'e':
                break;
                default:
                    std::cout<<"Syntax error\n";
                    return 1;
                break;
            }
        
        }
    if(cnt!=0)
    {
        std::cout<<"Missing bracket\n";
        return 1;
    }
    
        return 0;
}


//Thats whole alpha version