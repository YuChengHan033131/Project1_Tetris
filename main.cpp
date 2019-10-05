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
Field *field;//declared in global, so that ever function can access without passing
class Block{
    private:
        int rows;
        int cols;
        int *head;
    public:
        Block(){}
        Block(int rows,int cols,int *head):rows(rows),cols(cols),head(head){}
        friend Block rotate90(Block &before);
        void type(int num){
            num--;
            num%=4;
            for(int i=0;i<num;i++){
                *this=rotate90(*this);
            }
        }
        //test function
        void see(){
            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    cout << head[i*cols+j] ;
                }
                cout << endl;
            }
        }
};
Block rotate90(Block &before){
    int *tmp=new int[before.rows*before.cols];
    Block after(before.cols,before.rows,tmp);
    for(int i=0;i<after.rows;i++){
        for(int j=0;j<after.cols;j++){
            after.head[i*after.cols+j]=before.head[(after.cols-1-j)*after.rows+i];
        }
    }
    return after;
}
int main(){
    //custom input
    int H=40,W=15;

    //building field
    int a[(H+5)*(W+2)];
    field=new Field(H+5,W+2,a);

    //block information
    int t[6]={1,1,1,
              0,1,0};
    Block T(2,3,t);
    int i[4]={1,
              1,
              1,
              1};
    Block I(4,1,i);
    int l[6]={1,0,
              1,0,
              1,1};
    Block L(3,2,l);
    int j[6]={0,1,
              0,1,
              1,1};
    Block J(3,2,j);
    int s[6]={0,1,1,
              1,1,0};
    Block S(2,3,s);
    int z[6]={1,1,0,
              0,1,1};
    Block Z(2,3,z);
    int o[4]={1,1,
              1,1};
    Block O(2,2,o);
    
    Block test=I;

    test.see();
    test.type(2);
    cout << endl;
    test.see();


    //field->see();

    return 0;
}