#include <bits/stdc++.h>
using namespace std;

class userInfo;
class treap;
class userInfo
{
public:
    string name;
    string userName;
    string email;


    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        userInfo::name = name;
    }

    const string &getUserName() const {
        return userName;
    }

    void setUserName(const string &userName) {
        userInfo::userName = userName;
    }

    const string &getEmail() const {
        return email;
    }

    void setEmail(const string &email) {
        userInfo::email = email;
    }
    friend ostream& operator << (ostream& out, userInfo& ls)
    {

        out
                << "user Name : "<< ls.getUserName() <<endl
                << "Name: " << ls . getName() << endl
                << "email : " << ls.getEmail()<< endl;
        return out ;
    }


};
struct node
{
    node(string userName,userInfo *ref)
    {
        key=userName;
        this->ref=ref;
        left=right=NULL;
    }
    string key;
    userInfo *ref;
    node *left, *right;
};
class treap
{
public:


    node *root;
    node* search(node* root, string key)
    {


        if (root == NULL || root->key == key)
            return root;


        if (root->key < key)
            return search(root->right, key);

        // Key is smaller than root's key
        return search(root->left, key);
    }
    void searchNode(string key)
    {
        node *x = search(root, key);
        if (x->key==key)
        {
            cout<<x->key<<" ";
            cout<<"found ya 3am ";
        }

    }


    node* insert(node* root, string key,userInfo *ref)
    {

        if (!root)
            return new node(key,ref);


        if (key <= root->key)
        {
            // Insert in left subtree
            root->left = insert(root->left, key,ref);

            // Fix Heap property if it is violated
            if (root->left->key > root->key)
                root = rightRotate(root);
        }
        else  // If key is greater
        {
            // Insert in right subtree
            root->right = insert(root->right, key,ref);

            // Fix Heap property if it is violated
            if (root->right->key > root->key)
                root = leftRotate(root);
        }
        return root;
    }
    void insertNode(string key, userInfo *ref)
    {

        root = insert(root, key, ref);
    }
    node *leftRotate(node *x)
    {
        node *y = x->right, *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Return new root
        return y;
    }
    node *rightRotate(node *y)
    {
        node *x = y->left, *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Return new root
        return x;
    }
    void inorder(node* rot)
    {
        if (rot)
        {
            inorder(rot->left);
            cout<<*(rot->ref)<<" ";
            inorder(rot->right);
        }
    }

};

class Node {
public:
    userInfo data;
    treap friends;
    Node* next;
};

class LinkedList{
public:
    Node* head;
public:
    LinkedList() { // constructor
        head = NULL;
    }
    void addNode(userInfo val) {
        Node* newnode = new Node();
        newnode->data = val;
        newnode->next = NULL;
        if (head == NULL) {
            head = newnode;
        }
        else {
            Node* temp = head; // head is not NULL
            while (temp->next != NULL) {
                temp = temp->next; // go to end of list
            }
            temp->next = newnode; // linking to newnode
        }
    }
    void display() {
        if (head == NULL) {
            cout << "List is empty!" << endl;
        }
        else {
            Node* temp = head;
            while (temp != NULL) {
                cout << temp->data.userName<<", "<< temp->data.name<<" ,"<<temp->data.email<< ", "<<endl;
                temp = temp->next;
            }
            cout << endl;
        }
    }
    Node* isHere(string userName)
    {
        Node *temp=new Node();
        temp= head;
        while (temp!=NULL)
        {
            if (temp->data.userName==userName)
                return temp;
            temp=temp->next;
        }
        return NULL;

    }

};
LinkedList ls;

LinkedList fileToLL()
{
    LinkedList list_for_users;
    fstream file ;
    file.open("C:\\Users\\mahmoud\\Desktop\\CS214-project\\CS214-project\\all-users.in", ios :: in);


    int i = 0 ;
    if (file.is_open())
    {
        string line ;
        string name;
        string userName ;
        string email ;

        while (getline(file,line))
        {
            userName = line.substr(0,line.find_first_of(','));
            line.erase(0,line.find_first_of(',')+2);

            name = line . substr(0,line.find_first_of(','));
            line.erase(0,line.find_first_of(','));

            email = line . substr( 2, line.size());
            userInfo user;
            user.userName=userName;
            user.name=name;
            user.email=email;
            list_for_users.addNode(user);
        }
        file.close();
        return list_for_users;
    }


}


void printTree(node * root){
    if(root==NULL){   /// base case
        return;
    }
    cout<<endl;
    cout<<root->key<<": ";
    printTree(root->left);
    printTree(root->right);
}





void fileToTree()
{
    fstream file ;
    file.open("C:\\Users\\mahmoud\\Desktop\\CS214-project\\CS214-project\\all-users-relations.in", ios :: in);


    int i = 0 ;
    if (file.is_open())
    {
        string line  ;
        while (getline(file,line))
        {
            string first=line.substr(0,line.find(','));
            string sec=line.substr(line.find(',')+2);
            userInfo temp1;
            temp1.userName=first;
            userInfo temp2;
            temp2.userName= sec;
            Node *fnode=new Node();
            fnode=ls.isHere(first);
            fnode->friends.insertNode(sec,&temp2);
            Node *snode=new Node();
            snode=ls.isHere(sec);
            snode->friends.insertNode(first,&temp1);




        }
        file.close();
    }

}
int main() {


    ls=fileToLL();
    fileToTree();
    Node *op=new Node();
    op=ls.isHere("emy2000");
    printTree(op->friends.root);

    return 0;
}
