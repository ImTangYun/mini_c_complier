// this is some comment
// this is also some comment

/* a nother type of comment*/

struct node
{
    node* left_;
    node* right_;
    int value;
};

void foo()
{
    for (int i = 0; i < 100; ++i) {
        if (i > 50) {
            return 50;
        }
        if (i > 40) i *= 20;
        i /= 10;
    }
    return;
}
int main()
{
    foo();
    node* root_;
    root->left_ = NULL;
    return 0;
}
