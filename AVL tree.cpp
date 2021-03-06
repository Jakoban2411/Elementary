#include<iostream>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
struct node
{
    int height,data;
    node* left;
    node* right;
    node(int value,int high):data(value),height(high){}
};
node* CreateNode(int value)
{
    node* newNode=new node(value,1);
    newNode->left=nullptr;
    newNode->right=nullptr;
    return newNode;
}
node* findNode(node* root,int value)
{
    node* ParentNode;
    while(root!=nullptr)
    {
        if(root->data>value)
        {
            ParentNode=root;
            root=root->left;
        }
        else
        {
            ParentNode=root;
            root=root->right;
        }
    }
    return root;
}
int getHeight(node* Node)
{
    if(Node==nullptr)
        return 0;
    return Node->height;
}
node* RRotate(node* root)
{
    node* Temp=root->left;
    root->left=Temp->right;
    Temp->right=root;
    root->height=1+max(getHeight(root->left),getHeight(root->right));
    Temp->height=1+max(getHeight(Temp->left),getHeight(Temp->right));
    return Temp;
}
node* LRotate(node* root)
{
    node* Temp=root->right;
    root->right=Temp->left;
    Temp->left=root;
    root->height=1+max(getHeight(root->left),getHeight(root->right));
    Temp->height=1+max(getHeight(Temp->left),getHeight(Temp->right));
    return Temp;
}
node* insertNode(node* root,int data)
{
    if(root==nullptr)
        return CreateNode(data);
    if(data<root->data)
        root->left=insertNode(root->left,data);
    else
        root->right=insertNode(root->right,data);
    int LHeight=getHeight(root->left);
    int RHeight=getHeight(root->right);
    root->height=1+max(LHeight,RHeight);
    int Hdiff=LHeight-RHeight;
    if(Hdiff>1)
    {
        if(root->left->data>data)
        {
            root=RRotate(root);
        }
        else
        {
            root->left=LRotate(root->left);
            root=RRotate(root);
        }
    }
    if(Hdiff<-1)
    {
        if(root->right->data<data)
        {
            root=LRotate(root);
        }
        else
        {
            root->right=RRotate(root->right);
            root=LRotate(root);
        }
    }
    return root;
}
node* NextGreatest(node* root)
{
    root=root->right;
    while(root->left)
        root=root->left;
    return root;
}
void preOrder(node *root)  
{  
    if(root != nullptr)  
    {  
        cout << root->data << " ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
} 
node* deleteNode(node* root,int value)
{
    if(root->data>value)
        root->left=deleteNode(root->left,value);
    if(root->data<value)
        root->right=deleteNode(root->right,value);
    if(root->data==value)
    {
        if(root->left==nullptr || root->right==nullptr)
        {
            node* temp=root->left?root->left:root->right;
            if(temp==nullptr)
            {
                delete(root);
                return nullptr;
            }
            *root=*temp;
            delete temp;            
        }
        else
        {
            node* temp=NextGreatest(root);
            root->data=temp->data;
            root->right=deleteNode(root->right,temp->data);
        }
    }
    int LHeight=getHeight(root->left);
    int RHeight=getHeight(root->right);
    root->height=1+max(LHeight,RHeight);
    int Hdiff=LHeight-RHeight;
    if(Hdiff>1)
    {
        if(getHeight(root->left->left)>getHeight(root->left->right))
           root=RRotate(root);
        else
        {
            root->left=LRotate(root->left);
            root=RRotate(root);  
        }
    }
    if(Hdiff<-1)
    {
        if(getHeight(root->right->left)<getHeight(root->left->right))
            root=LRotate(root);
        else
        {
            root->right=RRotate(root->right);
            root=LRotate(root);
        }
    }
    return root; 
}

int main()
{
    node* root=nullptr;
    root = insertNode(root,10);
    root = insertNode(root,20);
    root = insertNode(root,30);
    root = insertNode(root,40);
    root = insertNode(root,50);
    root = insertNode(root,25);
    root = insertNode(root,15);
    preOrder(root); 
    root = deleteNode(root, 40);
    cout << "\nPreorder traversal after"
         << " deletion of 40 \n";  
    preOrder(root);  
}
