#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

int bestNum = 0;

class Field
{
    int size;
    vector<vector<int>> field;
    int count;

public:
    Field(int size): size(size), field(size, vector<int>(size, 0)), count(0) {
        if(size != 0) {
            constSquares();
        }
    }
    Field(Field const &other): size(other.size), field(other.size, vector<int>(other.size, 0)), count(other.count) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                field[i][j] = other.field[i][j];
    }
    Field& operator=(Field const &other){
        if(&other != this){
            Field tmp(other);
            count = tmp.count;
            size = tmp.size;
            field.swap(tmp.field);
        }
        return *this;
    }
    ~Field(){}

    void constSquares(){
        int temp = size/2;
        insertSquare(0, 0, temp+1);
        insertSquare(0, temp+1, temp);
        insertSquare(temp+1, 0, temp);
    }

    int getnumber(){
        return count;
    }
    int getsize(){
        return size;
    }

    bool isPossible(int i, int j, int n){
        if((i + n) > size || (j + n) > size){
            return false;
        }
        for(int y = i; y < i + n; y++)
            for (int x = j; x < j + n; x++)
                if(field[y][x] != 0){
                    return false;
                }
        return true;
    }
    void insertSquare(int i, int j, int n){
        for(int y = i; y < i + n; y++){
            for (int x = j; x < j + n; x++){
                field[y][x] = n;
            }
        }
        ++count;
    }
    bool checkSpace(int i){
        for(int y = i; y < size; y++)
            for (int x = 0; x < size; x++)
                if(field[y][x] == 0)
                    return true;
        return false;
    }
    int findi(int i){
        for (int y = i; y < size; y++)
            for (int x = 0; x < size; x++)
                if (field[y][x] == 0){
                    return y;
                }
    }
    int findj(int i){
        for (int y = i; y < size; y++)
            for (int x = 0; x < size; x++)
                if (field[y][x] == 0){
                    return x;
                }
    }
    void deleteSquare(int i, int j){
        int val = field[i][j];
        for (int y = i; y < i + val; y++)
            for (int x = j; x < j + val; x++)
                field[y][x] = 0;
    }
    void result(){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(field[i][j] != 0){
                    cout << i + 1 << " " << j + 1 << " " << field[i][j] << endl;
                    deleteSquare(i, j);
                }
            }
        }
    }

};

Field best(0);

Field backTracking(Field field, int i, int j){
    for(int n = field.getsize()/2; n > 0; n--){
        if(field.getnumber() > bestNum){
            return field;
        }
        
        Field shape = field;
        if(shape.isPossible(i, j, n)){
            shape.insertSquare(i,j,n);
            if(shape.checkSpace(i)){
                shape = backTracking(shape, shape.findi(i), shape.findj(i));
            }
            else if(bestNum >= shape.getnumber()){
                best = shape;
                bestNum = shape.getnumber();
            }
        }
    }
    return field;
}

int main(){
    int size = 0;
    cin >> size;

    if (size%2 == 0){
        int temp = size/2;
        cout << "4" << endl;
        cout << "1 1 " << temp << endl;
        cout << temp+1 << " 1 " << temp << endl;
        cout << "1 " << temp+1 << " " << temp << endl;
        cout << temp+1 << " " << temp+1 << " "<< temp << endl;
        return 0;
    }
    if (size%3 == 0){
        int temp = size/3;
        cout << "6" << endl;
        cout << "1" << " 1 " << temp*2 <<  endl;
        cout << "1 " << 1+temp*2 << " " << temp <<  endl;
        cout << 1+temp << " " << 1+temp*2 << " " << temp <<  endl;
        cout << 1+temp*2 << " 1 "  << temp <<  endl;
        cout << 1+temp*2 << " " << 1+temp << " "  << temp <<  endl;
        cout << 1+temp*2 << " " << 1+temp*2 << " " << temp << endl;
        return 0;
    }

    bestNum = size*size;
    Field A(size);
    A = backTracking(A, A.findi(0), A.findj(0));
    cout << bestNum << endl;
    best.result();
}
