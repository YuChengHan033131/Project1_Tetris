#include <iostream>
#include <fstream>
using namespace std;
class Field
{
private:
    int rows;
    int cols;
    int *head;

public:
    Field(int rows, int cols, int *head) : rows(rows), cols(cols), head(head)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (j == 0 || j == cols - 1 || i == rows - 1)
                {
                    head[i * cols + j] = 1;
                }
                else
                {
                    head[i * cols + j] = 0;
                }
            }
        }
    }
    int getRows()
    {
        return rows;
    }
    int getCols()
    {
        return cols;
    }
    int *getHead()
    {
        return head;
    }
    void see()
    {   
        ofstream outf("Tetris.final");
            if(!outf){
                cout << "error" << endl ;
            }
            for (int i = 4; i < rows-1; i++){
                for (int j = 1; j < cols-1; j++){
                    outf << head[i * cols + j];
                }
                outf << endl;
            }
        outf.close();
        
    }
    void test(){
        for (int i = 4; i < rows-1; i++){
                for (int j = 1; j < cols-1; j++){
                    cout << head[i * cols + j];
                }
                cout << endl;
        }
        cout << endl;
    }
};
Field *field; //declared in global, so that ever function can access without passing
class Block
{
private:
    int rows;
    int cols;
    int *head;

public:
    Block() {}
    Block(int rows, int cols, int *head) : rows(rows), cols(cols), head(head) {}
    void type(int num)
    {
        num--;
        num %= 4;
        for (int i = 0; i < num; i++)
        {
            *this = rotate90(*this);
        }
    }
    int getRows() { return rows; }
    int getCols() { return cols; }
    int *getHead() { return head; }
    friend Block rotate90(Block &before);
    friend bool blockFit(Block block, int posX, int posY);
    //test function
    void see()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << head[i * cols + j];
            }
            cout << endl;
        }
    }
};
Block rotate90(Block &before)
{
    int *tmp = new int[before.rows * before.cols];
    Block after(before.cols, before.rows, tmp);
    for (int i = 0; i < after.rows; i++)
    {
        for (int j = 0; j < after.cols; j++)
        {
            after.head[i * after.cols + j] = before.head[(after.cols - 1 - j) * after.rows + i];
        }
    }
    return after;
}
bool blockFit(Block block, int posRow, int posCol)
{
    for (int i = 0; i < block.rows; i++)
    {
        for (int j = 0; j < block.cols; j++)
        {
            if (block.head[i * block.cols + j])
            {
                if (field->getHead()[field->getCols() * (posRow + i - block.getRows() + 1) + posCol + j])
                {
                    return false;
                }
            }
        }
    }

    return true;
}
int main()
{
    int H = 10, W = 15;
    //input
    ifstream inf("D:\\c++\\Project1_Tetris\\test_case\\1073007S\\Tetris.data");
    if (!inf)
    {
        cout << "input error" << endl ;
    }
    inf >> H >> W;
    //building field
    int a[(H + 5) * (W + 2)];
    field = new Field(H + 5, W + 2, a);

    //block information
    int t[6] = {1, 1, 1,
                0, 1, 0};
    Block T(2, 3, t);
    int i[4] = {1,
                1,
                1,
                1};
    Block I(4, 1, i);
    int l[6] = {1, 0,
                1, 0,
                1, 1};
    Block L(3, 2, l);
    int j[6] = {0, 1,
                0, 1,
                1, 1};
    Block J(3, 2, j);
    int s[6] = {0, 1, 1,
                1, 1, 0};
    Block S(2, 3, s);
    int z[6] = {1, 1, 0,
                0, 1, 1};
    Block Z(2, 3, z);
    int o[4] = {1, 1,
                1, 1};
    Block O(2, 2, o);
    bool winGame=true;
    while (1)
    {
        char blockChar = 'I';
        int type = 2, posCol = 10;
        //file input
        inf >> blockChar ;
        if(blockChar=='E'){
            break;
        }
        if(blockChar!='O'){
            inf >> type;
        }
        inf >> posCol;
        Block block;
        switch (blockChar)
        {
        case 'T':
            block = T;
            break;
        case 'L':
            block = L;
            break;
        case 'J':
            block = J;
            break;
        case 'S':
            block = S;
            break;
        case 'Z':
            block = Z;
            break;
        case 'O':
            block = O;
            break;
        case 'I':
            block = I;
            break;
        default:
            cout << "block type error!";
            break;
        }
        if(blockChar!='O'){
            block.type(type);
        }
        int posRow = 3;
        if (blockFit(block, posRow, posCol)){ //block enter field check
            //block falling collison check
            while (blockFit(block, posRow, posCol))
            {
                posRow++;
            }
            posRow--;
            //block output to field
            for (int i = 0; i < block.getRows(); i++){
                for (int j = 0; j < block.getCols(); j++){ 
                    if(block.getHead()[i*block.getCols()+j]){
                        field->getHead()[field->getCols() * (posRow + i - block.getRows() + 1) + posCol + j] = block.getHead()[i * block.getCols() + j];
                    }  
                }
            }
            //line clear detect
            for(int i=0;i<4;){
                int j=1;
                if(posRow-i==3){
                	break;
                }
                for(j=1;j<field->getCols()-1;j++){
                    if(!field->getHead()[field->getCols()*(posRow-i)+j]){
                        // don't clear
                        i++;
                        break;
                    }
                }
                if(j==field->getCols()-1){
                    //clear
                    for(j=posRow-i;j>0;j--){
                        for(int k=1;k<field->getCols()-1;k++){
                            field->getHead()[(j)*field->getCols()+k]=field->getHead()[(j-1)*field->getCols()+k];
                        }
                    }
                    //check the line again after line falling
                        //so don't i++
                    
                }
            }
            //detect entering area empty or not (top 4 rows of field)
            for(int i=0;i<4;i++){
                for(int j=1;j<field->getCols()-1;j++){
                    if(field->getHead()[(i)*field->getCols()+j]){//something in entering area
                        //end game
                        winGame=false;
                        break;
                    }
                }
                if(!winGame){
                    break;
                }
            }
            if(!winGame){
                break;
            }
            //field->test();
        }
        else{
            winGame=false;
            break;
        }
    }
    inf.close();
    //win(no needed ?)
    /*if(winGame==true){
        cout << "win!!" << endl ;
    }else{
        cout << "loser!" << endl;
    }*/

    //game result file output
    //field->test();
    field->see();
    return 0;
}