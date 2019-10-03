#include <iostream>
using namespace std;
class Field{
    private:
        int rows;
        int cols;
        int *head;
    public:
        Field(int rows,int cols,int *head):rows(rows),cols(cols),head(head){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    if(j==0||j==cols-1||i==rows-1){
                        head[i*cols+j]=1;
                    }
                    else{
                        head[i*cols+j]=0;
                    }
                }
            }
        }
        //testing function
        void see(){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    cout << head[i*cols+j] ;
                }
                cout << endl ;
            }
        }
};
Field *field;
int main(){
    int H=40,W=15;
    int a[(H+5)*(W+2)];
    field=new Field(H+5,W+2,a);
    field->see();
    
    return 0;
}