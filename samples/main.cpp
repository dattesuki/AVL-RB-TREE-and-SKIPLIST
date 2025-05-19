//UNN
//Litvyakov D. D.
//

#include "tree.h"
#include "skiplist.h"
#include <iostream>
using namespace std;





int main() {
    AVLTree<int> A(10,10);
    
    for (size_t a = 0; a < 10; a++) {
        A.add(a, a);
}
    A.inorder();
    cout << endl;
    
    return 0;
}
