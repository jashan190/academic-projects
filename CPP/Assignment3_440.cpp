#include <iostream>

using namespace std; 

int main(){
    int A[4] = {1,2,3,4};
    char B[3] = {'a','b','c'};

    pair<int,char> R[3] = {make_pair(A[0], B[0]), make_pair(A[1], B[2]), make_pair(A[2], B[1])};

    for (int i=0; i < 4; ++i){

        cout << A[i] << "| ";
        
        for (int j=0; j < 3; ++j){
            bool relationExists = false;

            for (const auto& rel : R){
                if (rel.first == A[i] && rel.second == B[j]){
                    relationExists = true;
                    break;
                }
            }

            cout << (relationExists ? "1 " : "0 "); 
        }
        cout << endl; 

    }

return 0;
}