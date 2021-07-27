// matrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<iomanip>
#include<Windows.h>

using namespace std;
class Matrix
{
private:
    int row;
    int column;
    int** pointer;
public:

    int GetRow() const
    {
        return row;
    } 
    int GetCol()  const
    {
        return column;
    }
    int** GetPointer() const
    {
        return pointer;
    }
   
    //cap phat vung nho
    void Allocate()// cap phat vung nho moi
    {
        pointer = new int* [row];// pointer quan ly hang`
        for (int i = 0; i < row; i++)// tao so luong phan tu cho cac hang
        {
            pointer[i] = new int[column];//pointer[] quan ly cot
        }
    }// 
    Matrix()
    {
        row = 1;
        column = 1;
        Allocate();
        pointer[0][0] = 0;
    }
    Matrix(const int& inRow, const int& inCol)
    {
        row = inRow;
        column = inCol;
        Allocate();
    }
    Matrix(const Matrix& source)
    {
        row = source.row;
        column = source.column;
        Allocate();
        //copy
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                pointer[i][j] = source.pointer[i][j];
            }
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < row; i++) 
        {
            delete[] pointer[i];// giai phong phan tu cua tung hang
            pointer[i] = NULL;
        }
        delete[] pointer;//giai phong cac hang
        pointer = NULL;
    }

    //method
    void EnterMatrix()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cout << "[" << i << "]" << "[" << j << "]: ";
                cin >> pointer[i][j];
            }
        }
    }
    void DisplayMatrix()
    {
        cout << "----------------------"<<endl;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cout << pointer[i][j]<<" ";
            }
            cout << endl;
        }
        cout << "----------------------" << endl;

    }
    void Set0()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                pointer[i][j] = 0;
            }
        }
    }

    //overload operator
    Matrix& operator=(const Matrix& obj)
    {
        if (this == &obj)
        {
            return *this;
        }

        if ((row != obj.row) || (column != obj.column))// #size
        {
            //delete old size
            for (int i = 0; i < row; i++)
            {
                delete[] pointer[i];
                pointer[i] = NULL;
            }
            delete[] pointer;
            //pointer = NULL;// cho nay NULL thi 140 warning def NULL

            //new size
            row = obj.row;
            column = obj.column;
            Allocate();
        }
        //copy phan tu
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                pointer[i][j] = obj.pointer[i][j];
            }
        }
        return *this;
        
    }
    // friend moi cho truyen vao 2 tham so?? 
    friend Matrix operator+(const Matrix& obj1, const Matrix& obj2)
    {
        Matrix temp(obj1);
        temp.Set0();

        for (int i = 0; i < temp.row; i++)
        {
            for (int j = 0; j < temp.column;j++)
            {
                temp.pointer[i][j] = obj1.pointer[i][j] + obj2.pointer[i][j];
            }
        }

        return temp;
    }
    friend Matrix operator-(const Matrix& obj1, const Matrix& obj2)
    {
        Matrix temp(obj1);
        temp.Set0();

        for (int i = 0; i < temp.row; i++)
        {
            for (int j = 0; j < temp.column; j++)
            {
                temp.pointer[i][j] = obj1.pointer[i][j] - obj2.pointer[i][j];
            }
        }
        return temp;
    }
    //combo *
    friend Matrix operator*(const Matrix& obj1, const Matrix& obj2)
    {
        Matrix temp(obj1.GetRow(),obj2.GetCol());
        temp.Set0();
        int i, j, k;

        for (i = 0; i < obj1.row; i++)// nhay hang a
        {
            for (j = 0; j < obj2.column; j++)//nhay cot b
            {
                for (k = 0; k < obj1.column; k++)//Coo=Aoo+Boo + Ao1+B1o + ....
                {
                    temp.pointer[i][j] += obj1.pointer[i][k] * obj2.pointer[k][j];
                }
            }
        }
            
        return temp;
    }
    friend Matrix operator*(const Matrix& obj, const int& number)
    {
        Matrix temp(obj.GetRow(), obj.GetCol());
        temp.Set0();

        for (int i = 0; i < temp.row; i++)
        {
            for (int j = 0; j < temp.column; j++)
            {
                temp.pointer[i][j] = obj.pointer[i][j] * number;
            }
        }
        return temp;
    }
    //combo /
    // A/B=A.B^-1  => tim ma tran chuyen nghich roi nhan 
    friend Matrix GetCofactor(const Matrix& obj, const int& p, const int& q)
    {
        Matrix temp(obj.GetRow(),obj.GetCol());
        int i = 0, j = 0;

        for (int row = 0; row < obj.row; row++)
        {
            for (int col = 0; col < obj.column; col++)
            {
                if (row != p && col != q)
                {
                    temp.GetPointer()[i][j++] = obj.GetPointer()[row][col];

                    if (j == obj.column - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return temp;
    }
    friend float determinant(const Matrix& obj,const int& n)
    {
        float D = 0; 

        if (obj.column == 1)
        {
            return (float) obj.pointer[0][0];
        }

        Matrix temp(obj.GetRow(),obj.GetCol()); 

        int sign = 1;  

         
        for (int i = 0; i <obj.GetCol(); i++)
        {
            
            GetCofactor(obj,0, i);
            D += sign * obj.pointer[0][i] * determinant(temp,obj.GetCol()-1);//k co const n thi k dc??

            
            sign = -sign;
        }

        return D;
    }
    friend Matrix adjoint(const Matrix& obj)// ngang nay 
    {
        Matrix adj(obj.GetRow(), obj.GetCol());
        if (obj.GetCol() == 1)
        {
            adj.pointer[0][0] = obj.pointer[0][0];
            return adj;
        }
      
        int sign = 1;
        Matrix temp(obj.GetRow(), obj.GetCol());

        for (int i = 0; i < obj.GetRow(); i++)
        {
            for (int j = 0; j < obj.GetCol(); j++)
            {
                temp = GetCofactor(obj, i, j);

                sign = ((i + j) % 2 == 0) ? 1 : -1;

                adj.GetPointer()[j][i] = (sign) * (determinant(temp, obj.GetCol() - 1));
            }
        }
        return adj;
    }
    friend Matrix inverse(const Matrix& obj)
    {
        // check dieu kien o day??
        Matrix inver(obj.GetCol(), obj.GetCol());
        Matrix adj = adjoint(obj);
        float det = determinant(obj, obj.GetCol());

        if (det == 0)
        {
            cout << "Singular matrix, can't find its inverse";
            return inver;
        }

        // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
        for (int i = 0; i < obj.GetRow(); i++)
        {
            for (int j = 0; j < obj.GetCol(); j++)
            {
                inver.pointer[i][j] = adj.pointer[i][j] / float(det);
            }
                
        }
        return inver;
    }

    friend Matrix operator/(const Matrix& obj1,const Matrix& obj2)
    {
        
        Matrix inverMatrix2 = inverse(obj2);
        
        
        Matrix temp(obj1.GetRow(), obj2.GetCol());
        temp.Set0();
        temp = obj1 * obj2;
        return temp;
    }
    friend Matrix operator/(const Matrix& obj, const int& number)
    {
        Matrix temp(obj.GetRow(), obj.GetCol());
        temp.Set0();
        
        for (int i = 0; i < temp.row; i++)
        {
            for (int j = 0; j < temp.column; j++)
            {
                temp.pointer[i][j] = obj.pointer[i][j] / number;
            }
        }
        return temp;

    }
};

//Menu
void Menu()
{
    cout << setw(80) << "********************** MATRIX SELECTION ***********************" << endl;
    cout << setw(80) << "*                1. Sum of two matrices                       *" << endl;
    cout << setw(80) << "*                2. Subtraction of two Matrices               *" << endl;
    cout << setw(80) << "*                3. Multiplication of two Matrices            *" << endl;
    cout << setw(80) << "*                4. Multiplication of matrix and number       *" << endl;
    cout << setw(80) << "*                5. Division of two Matrices                  *" << endl;
    cout << setw(80) << "*                6. Division of matrix and number             *" << endl;
    cout << setw(80) << "*                7. Exit                                      *" << endl;
    cout << setw(80) << "***************************************************************" << endl;
}



int main()
{
    
    int row1, col1;
    int row2, col2;
 
    Matrix sumMatrix;
    Matrix subMatrix;
    Matrix mulMatrix;
    Matrix divMatrix;
    int number;

    int select = 0;
enterAgain:
    cout << "Enter two matrix:";
    cout << "Enter row 1: ";
    cin >> row1;
    cout << "Enter col1: ";
    cin >> col1;
    Matrix matrix1(row1, col1);
    matrix1.EnterMatrix();
    matrix1.DisplayMatrix();
    cout << "Enter row 2: ";
    cin >> row2;
    cout << "Enter col2: ";
    cin >> col2;
    Matrix matrix2(row2, col2);
    matrix2.EnterMatrix();
    matrix2.DisplayMatrix();
    
    while(true)
    {
        Menu();

    selectAgain:

        cout << "Enter your selection: ";
        cin >> select;
        
        switch (select)
        {
            case 1:
            {
                 system("cls");
                 cout << "Calculatimg sum of two matrices: "<<endl;
                 if (matrix1.GetRow() != matrix2.GetRow() || matrix1.GetCol() != matrix2.GetCol())
                 {
                     cout << "Not equal size! => Enter rwo matrices again";
                     goto enterAgain;
                 }
                 sumMatrix = matrix1 + matrix2;
                 cout << "Result: ";
                 sumMatrix.DisplayMatrix();

                 Sleep(5000);
                 system("cls");
                 break;
            }
            case 2:
            {
                system("cls");
                cout << "Calculating sub of two matrices: " << endl;
                if (matrix1.GetRow() != matrix2.GetRow() || matrix1.GetCol() != matrix2.GetCol())
                {
                    cout << "Not equal size! => Enter two matrices again";
                    goto enterAgain;
                }
                subMatrix = matrix1 - matrix2;
                cout << "Result: ";
                subMatrix.DisplayMatrix();

                Sleep(5000);
                system("cls");
                break;
            }
            case 3:
            {
                system("cls");
                cout << "Calculating mul of two matrices: " << endl;
                if (matrix1.GetRow() != matrix2.GetCol())
                {
                    cout << "matrix1's row not equal to matrix2's col => Enter two matrices again";
                    goto enterAgain;
                }
                mulMatrix = matrix1 * matrix2;
                cout << "Result: ";
                mulMatrix.DisplayMatrix();

                Sleep(5000);
                system("cls");
                break;
            }
            case 4:
            {
                system("cls");
                cout << "Calculating mul of matrix and number: " << endl;
                cout << "Enter number:";
                cin >> number;
                int choseMatrix;
                cout << "Which matrix:";
                cin >> choseMatrix;
                if (choseMatrix == 1)
                {
                    mulMatrix = matrix1 * number;
                }
                else if (choseMatrix == 2)
                {
                    mulMatrix = matrix2 * number;
                }
                else
                {
                    mulMatrix = matrix1 * matrix2 * number;
                }

                cout << "Result: ";
                mulMatrix.DisplayMatrix();

                Sleep(5000);
                system("cls");
                break;
            }
            case 5:
            {
                system("cls");
                cout << "Calculating div of two matrices: " << endl;
                if (matrix1.GetRow() != matrix2.GetCol())
                {
                    cout << "matrix1's row not equal to matrix2's col => Enter two matrices again";
                    goto enterAgain;
                }
                mulMatrix = matrix1 / matrix2;
                cout << "Result: ";
                mulMatrix.DisplayMatrix();

                Sleep(5000);
                system("cls");
                break;
            }
            case 6:
            {
                system("cls");
                cout << "Calculating div of matrix and number: " << endl;
                cout << "Enter number:";
                cin >> number;
                int choseMatrix;
                cout << "Which matrix:";
                cin >> choseMatrix;
                if (choseMatrix == 1)
                {
                    divMatrix = matrix1 / number;
                }
                else if(choseMatrix == 2)
                {
                    divMatrix = matrix2 / number;
                }
                else
                {
                    divMatrix = matrix1 / number;
                }
           

                cout << "Result: ";
                mulMatrix.DisplayMatrix();

                Sleep(5000);
                system("cls");
                break;
            }
            case 7:
            {
                cout << "Shuting down app!!!!!";

                cout << "Leaving...............";
                Sleep(2000);
                system("cls");

            }
            default:
            {
                cout << "No slection=>Retry";
                goto selectAgain;
            }
            
        }
       
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
