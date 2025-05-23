//UNN
//Litvyakov D. D.
//

#include "tree.h"
#include "skiplist.h"
#include <iostream>
using namespace std;





int main() {
    AVLTree<int> A(10,10);
    SkipList<int> B(0.5);
//    for (size_t a = 0; a < 15; a++) {
//        A.add(a, a);
//        B.add(a, a);
//}
    for (int a = 15; a >=0; --a) {
        A.add(a, a);
        B.add(a, a);
    }
    //A.inorder();
    //cout << endl;
    //
    
    B.print();
    cout << endl;
    for (size_t i = 6; i < 8; ++i) B.remove(i);
    B.print();
    




    return 0;
}



