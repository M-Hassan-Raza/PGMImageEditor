#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include<stdlib.h>

using namespace std;

#define MaxRows 500
#define MaxCols 500

struct grayImage
{
    grayImage()
    {
        Rows = Cols = 0;
        Loaded = false;
        for(int r = 0; r< MaxRows; r++)
        {
            for(int c = 0; c< MaxCols; c++)
            {
                Image[r][c] = 0;
            }
        }

    }

    unsigned short setPixel(unsigned short value, int r, int c)
    {
        if (r >= Rows || c >= Cols || r < 0 || c < 0)
        {
            return -1;
        }
        Image[r][c] = value;
        return value;
    }

    int getPixel(int r, int c)
    {
        if (r >= Rows || c >= Cols || r < 0 || c < 0)
        {
            return -1;
        }
        return Image[r][c];
    }

    int setRows(int rows)
    {
        if (rows < 1 || rows > MaxRows)
        {
           return -1;
        }
        Rows = rows;
        return Rows;
    }

    int getRows()
    {
        return Rows;
    }

    int setCols(int cols)
    {
        if (cols < 1 || cols > MaxCols)
        {
            return -1;
        }
        Cols = cols;
        return Cols;
    }

    int getCols()
    {
        return Cols;
    }

    int Save(string File_Name)
    {
        ofstream fout(File_Name.c_str());
         fout << "P2"<<endl << "# Comment by Runtime Terror"<<endl << Cols << " " << Rows << endl << Maximum <<endl;

        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                fout << (int)Image[i][j] << " ";
            }
            fout << endl;
        }
        fout.close();

        return 0;
    }

    void Flip(grayImage& Result, int Orientation = 1)
    {
        if (Orientation == 1)
        {
            FlipHorizontal(Result);
        }
        else
        {
            FlipVertical(Result);
        }
    }

    int load(string File_Name)
    {

        ifstream Input(File_Name.c_str());
        if(!Input)
        {
            return 1;
        }

        string MagicNumber, comment;
        int columns, rows, MaxValue, currentValue;
        getline(Input, MagicNumber);
        getline(Input, comment);
        Input >> columns >> rows >> MaxValue;
        setRows(rows);
        setCols(columns);
        Maximum = MaxValue;

        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {

                Input >> currentValue;
                Image[i][j] = currentValue;
            }
        }
        Input.close();
        Loaded = true;
        return 0;

    }


    void combineSideBySide(grayImage& Two, int fillValue = 0)
    {
        int maxRows, maxColumn;

        maxRows=Rows;
        if(Two.Rows>maxRows)
        int maxRows, maxColumn;

        maxRows=Rows;
        if(Two.Rows>maxRows)
        {
            maxRows=Two.Rows;
        }

        maxColumn = Cols+Two.Cols;
        setRows(maxRows);
        setCols(maxColumn);
        if(Rows> Two.Rows )
        {
            fillvalue(Two.Rows,Rows,Cols,maxRows, fillValue);
        }
        else if (Rows < Two.Rows)
        {
            fillvalue(Rows,Two.Rows,0,Cols, fillValue);
        }

        for(int i=0;i<maxRows;i++)
        {
            for(int j=Cols-Two.Cols, k=0;j<Cols; k++, j++)
            {
                Image[i][j]= Two.Image[i][k];
            }
        }
    }

    void combineTopToBottom(grayImage& Two, int fillValue = 0)
    {

        for(int i = 0; i< Two.Rows; i++)
        {
            for(int j = 0; j< Two.Cols; j++)
            {
                if((Rows + i) < MaxRows)
                {
                    Image[Rows+(i-1)][j] = Two.Image[i][j];
                }
            }
        }
        if(Cols < Two.Cols)
        {
            Cols = Two.Cols;
        }
        Rows += Two.Rows;

        if (Rows > MaxRows)
        {
            Rows = MaxRows;
        }

        if(Cols>Two.Cols)
        {
            fillvalue(Rows,Two.Rows,Two.Cols,Cols, fillValue);
        }
        else if (Cols < Two.Cols)
        {
            fillvalue(0,Rows,Cols, Two.Cols, fillValue);
        }
    }

    int publicLoaded()
    {
        return Loaded;
    }

    void FadeIn(grayImage& Two,int Frames, int seconds, string BaseFileName)
    {

        grayImage Result;
        double Stepsize = 1.0/(Frames*seconds);
        int Row, Column, counter = 0;
        char numbered[10];
        Row = Rows;
        if(Row < Two.Rows)
        {
            Row = Two.Rows;
        }
        Column = Cols;
        if(Column < Two.Cols)
        {
           Column = Two.Cols;
        }


        Result.Rows = Row;
        Result.Cols = Column;
        Result.Loaded = true;
        Result.Maximum = Maximum;

        if(Maximum < Two.Maximum)
        {
            Result.Maximum = Two.Maximum;
        }

        for(double omega=1; omega>=0; omega-=Stepsize)
        {
            for(int i=0; i<Row; i++)
            {
                for(int j=0; j<Column;j++)
                {
                    Result.Image[i][j]= (Image[i][j]*omega) + ((1-omega)*Two.Image[i][j]);
                }
            }
            itoa(counter, numbered, 10);
            Result.Save(BaseFileName + numbered + ".pgm");
            counter+=1;
        }
    }


    void Negative(grayImage& Result)
    {
        int maximumNegative = -1, actualValue;
        for(int row = 0; row < Rows; row++)
        {
            for(int column = 0; column < Cols; column++)
            {
                 actualValue = Maximum - Image[row][column];
                 Result.Image[row][column] = actualValue;
                 if(actualValue > maximumNegative)
                 {
                     maximumNegative = actualValue;
                 }

            }
        }
        Result.Rows = Rows;
        Result.Cols = Cols;
        Result.Maximum = maximumNegative;
    }

    void changeBrightness(grayImage& Result,int amount)
    {
        for(int row = 0; row < Rows; row++)
        {
            for(int column = 0; column < Cols; column++)
            {
                if((getPixel(row, column)+amount) > 255)
                {
                    Result.Image[row][column] = 255;
                }
                else if ((getPixel(row, column) + amount) < 0)
                {
                    Result.Image[row][column] = 0;
                }
                else
                {
                    Result.Image[row][column] += amount;
                }

            }
        }
        Result.Rows = Rows;
        Result.Cols = Cols;
        Result.Maximum = Maximum;
    }

    void Quantize(grayImage& Result, int Levels)
    {
        Result.Rows = Rows, Result.Cols = Cols;
        int stepSize = 255/Levels;
        int leftValue = 0, rightValue = stepSize;
        for (int counter = 0; counter < Levels; counter++)
        {
            for (int i = 0; i< Rows; i++)
            {
                for(int j = 0; j< Cols; j++)
                {
                    if((Image[i][j] >= leftValue) && (Image[i][j] <= rightValue))
                    {
                        Result.Image[i][j] = (leftValue+rightValue)/2;
                    }
                }
            }
            leftValue = rightValue;
            rightValue += stepSize;
        }
        Result.Maximum = Maximum;
    }


    void ascendingSelectionSort(int arrA[], int n)
    {
        int minimum, temp;
        for (int i = 0; i<n-1; i++)
        {
            minimum = i;
            for(int j = i+1; j< n; j++ )
            {
                if (arrA[j] < arrA[j-1])
                {
                    minimum = j;
                }
            }
            temp = arrA[minimum];
            arrA[minimum] = arrA[i];
            arrA[i] = temp;
        }
    }
    void Rotate(grayImage& Result, double angle = 90, int aboutx = 0, int abouty = 0 )
    {
        int in , jn ;
        double Angle = ( 3.141592 * angle) / 180.0;
        for(int i = 0 ; i < Rows ; i++)
        {
            for(int j = 0 ; j < Cols ; j++)
            {

                in = ((i-aboutx)*cos(Angle) + (j-abouty)*sin(Angle)) + aboutx;
                jn = ((j-abouty)*cos(Angle) - (i-aboutx)*sin(Angle)) + abouty;

                if( in >= 0 && in < Rows && jn >=0 && jn < Cols)
                {
                    Result.Image[i][j] = (Image[in][jn] +Image[in+1][jn] +Image[in][jn+1] +Image[in+1][jn+1]) / 4;
                }

            }
        }

	    Result.Rows = MaxRows;
	    Result.Cols = MaxCols;
	    Result.Maximum = Maximum;
	    Result.Loaded = true;
    }

    void Resize(grayImage& Result, int NewRows, int NewColumns)
    {
        if(NewColumns>MaxCols)
        {
            NewColumns=MaxCols;
        }
        if(NewRows>MaxRows)
        {
            NewRows=MaxRows;
        }

        double rows = NewRows;
        rows /= Cols;
        double columns = NewColumns;
        columns /= Cols;
        for(int row = 0; row < NewRows; row++)
        {
            for (int column = 0; column < NewColumns; column++)
            {
                int firstRows = row/rows;
                int firstColumns = column/columns;
                Result.Image[row][column] = Image[firstRows][firstColumns];
            }
        }
        Result.Rows = NewRows;
        Result.Cols = NewColumns;
        Result.Maximum = Maximum;
    }

    void Resize(grayImage& Result, double Ratio)
    {
        Resize(Result, Rows*Ratio, Cols*Ratio);
    }

    void Transform(grayImage& Result, double Matrix[3][3])
    {
        double vectorI, vectorJ, vectorK;

        for(int i = 0; i< Rows; i++)
        {
            for(int j = 0; j< Cols; j++)
            {
                vectorI = ((i*Matrix[0][0]) + (j*Matrix[0][1]) + Matrix[0][2]);
                vectorJ = ((i*Matrix[1][0]) + (j*Matrix[1][1]) + Matrix[1][2]);
                vectorK = ((i*Matrix[2][0]) + (j*Matrix[2][1]) + Matrix[2][2]);
                if (vectorK != 0)
                {
                    int trueI = vectorI/vectorK;
                    int trueJ = vectorJ/vectorK;
                    if(trueI>=0 && trueI < MaxRows && trueJ >= 0 && trueJ < MaxCols)
                    {
                        Result.Image[trueI][trueJ] = Image[i][j];
                    }
                }


            }
        }
        Result.Rows = Rows;
        Result.Cols = Cols;
        Result.Maximum = Maximum;
    }

    void Crop(grayImage& Result, int Top, int Bottom, int Left, int Right, int resizeFlag = 0)
    {
        int numberOfRows;
        numberOfRows = (Bottom - Top);
        int numberOfColumns;
        numberOfColumns = (Right - Left);
        int rowCounter = 0, columnCounter = 0;

        for(int rowCounter = 0; rowCounter< numberOfRows; rowCounter++)
        {
            for(int columnCounter = 0; columnCounter <numberOfColumns; columnCounter++)
            {
                Result.Image[rowCounter][columnCounter] = Image[Top+rowCounter][columnCounter];
            }

        }
        if(resizeFlag == 1)
        {
            Resize(Result ,Rows, Cols);
            Result.Rows = Rows;
            Result.Cols = Cols;
            Result.Maximum = Maximum;
            return;
        }
        Result.Rows = numberOfRows;
        Result.Cols = numberOfColumns;
        Result.Maximum = Maximum;

        return;
    }


    void medianFilter(grayImage& Result, int filterSize = 3)
    {
        int sizeOfArray = filterSize*filterSize;
        int pixelStore[sizeOfArray], median = 0, pixelDistance = filterSize/2;
        Result.Rows = Rows;
        Result.Cols = Cols;
        Result.Maximum = Maximum;
        for(int row = 0; row < Rows; row++)
        {
            for(int column = 0; column < Cols; column++)
            {

                int counter = 0;
                for(int pixelRow = row-pixelDistance; pixelRow <= row+pixelDistance; pixelRow++)
                {
                    for(int pixelColumn = column-pixelDistance; pixelColumn <= column+pixelDistance; pixelColumn++)
                    {
                        if (pixelRow >=0 && pixelRow <Rows && pixelColumn >=0 && pixelColumn <Cols)
                        {
                           pixelStore[counter]= Image[pixelRow][pixelColumn];
                           counter++;
                        }
                    }
                }
                ascendingSelectionSort(pixelStore, counter+1);
                if(sizeOfArray % 2 != 0)
                {
                    median = pixelStore[(sizeOfArray/2)+1];
                }
                else
                {
                    int first = 0, second = 0, firstIndex, secondIndex;
                    firstIndex = (sizeOfArray-1)/2;
                    secondIndex = sizeOfArray/2;
                    first = pixelStore[firstIndex];
                    second = pixelStore[secondIndex];
                    median = (first+second)/2;
                }

                Result.Image[row][column]= median;
            }
        }
    }

    void meanFilter(grayImage& Result, int filterSize = 3)
    {
        int mean = 0, pixelDistance = filterSize/2;
        Result.Rows = Rows;
        Result.Cols = Cols;
        int sizeOfSample = filterSize*filterSize;

        for(int row = 0; row < Rows; row++)
        {
            for(int column = 0; column < Cols; column++)
            {

                for(int pixelRow = row-pixelDistance; pixelRow < row+pixelDistance; pixelRow++)
                {
                    for(int pixelColumn = column-pixelDistance; pixelColumn < column+pixelDistance; pixelColumn++)
                    {
                        if (pixelRow >=0 && pixelRow <Rows && pixelColumn >=0 && pixelColumn <Cols)
                        {
                            mean+= Image[pixelRow][pixelColumn];
                        }
                    }
                }
                mean /= (sizeOfSample-2);
                Result.Image[row][column]= mean;
            }
        }
    }
    void Filter(grayImage& Result, double Mask[3][3])
    {
        double pixelArray[9];
        int rowsFirst,columnsFirst,counter = 0, filterValue;
        for(int i=0; i<Rows; i++)
        {
            for(int j=0; j<Cols; j++)
            {
                rowsFirst = i-1;
                columnsFirst = j-1;
                for(; counter < 9; counter++)
                {
                    pixelArray[counter]=Image[rowsFirst][columnsFirst];
                    if(counter % 3 != 0)
                    {
                        columnsFirst++;

                    }
                    else
                    {
                        rowsFirst++;
                        columnsFirst = j-1;
                    }

                }
                filterValue = mask_Calculator(pixelArray,Mask);
                Result.Image[i][j]=filterValue;
                counter = 0;
            }

        }
        Result.Rows =Rows;
        Result.Cols= Cols;
        Result.Maximum= Maximum;
    }

    void DerivativeImage (grayImage & Result, double firstMask[3][3], double secondMask[3][3])
    {
        int firstMaskValue = 0, secondMaskValue = 0, resultantMaskValue = 0;
        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                for (int imageRow = i, maskRow = 0; imageRow < (i + 3); imageRow++, maskRow++)
                {
                    for (int imageCol = j, maskCol = 0; imageCol < (j + 3); imageCol++, maskCol++)
                    {
                        firstMaskValue += Image[imageRow][imageCol] * firstMask[maskRow][maskCol];
                        secondMaskValue += Image[imageRow][imageCol] * secondMask[maskRow][maskCol];
                    }
                }
                resultantMaskValue = sqrt((firstMaskValue * firstMaskValue) + (secondMaskValue * secondMaskValue));
                Result.Image[i][j] = resultantMaskValue;
                firstMaskValue = 0, secondMaskValue = 0;
            }
        }
        Result.Rows = Rows;
        Result.Cols = Cols;
        Result.Maximum = Maximum;
    }

private:

    double mask_Calculator(double pixelArray[],double mask[3][3])
    {
        int counter = 0;
        double sum=0,avg;
        for (int j = 0; j< 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                pixelArray[counter] *= mask[j][k];
                sum += pixelArray[counter];
                counter++;
            }
        }
        avg =sum/9.0;
        return avg;
    }

    void FlipVertical(grayImage& Result)
    {
        for (int i = 0; i< Rows; i++)
        {
            for (int j = 0; j< Cols; j++)
            {
                Result.Image[i][j] = Image[i][Cols-(j+1)];
            }
        }
        Result.Cols = Cols;
        Result.Rows = Rows;
        Result.Maximum = Maximum;
        return;
    }

    void FlipHorizontal(grayImage& Result)
    {
        for (int i = 0; i< Cols; i++)
        {
            for (int j = 0; j< Rows; j++)
            {
                Result.Image[j][i] = Image[Rows-(j+1)][i];
            }
        }
        Result.Cols = Cols;
        Result.Rows = Rows;
        Result.Maximum = Maximum;
        return;
    }

    void fillvalue(int top, int bottom, int left , int right, int fillVal = 255)
    {
        for(int row=top; row<= bottom; row++)
        {
            for(int column = left; column <= right; column++)
            {
                Image[row][column] = fillVal;
            }
        }
    }

    unsigned short Image[MaxRows][MaxCols];
    int Rows, Cols, Maximum;
    bool Loaded;
};

int main()
{
    grayImage GM, GM2, GM3;

    string inputFileName, outputFileName;
    int choice, loadedStatusFirst = -1;
    while(loadedStatusFirst != 0)
    {
        cout << "\n\n\t\t\t\tLet's load an image to get things going!\n";
        cout << "Please enter the name of the file you want to load.\n";
        cin >> inputFileName;
        int stringLength = inputFileName.size();
        if ((inputFileName.substr(stringLength-4, 4) != ".pgm"))
        {
            inputFileName += ".pgm";
            loadedStatusFirst = GM.load(inputFileName);
            if(loadedStatusFirst == 1)
            {
                cout << "The file could not be loaded. Please check the name and verify the location of the image.\n";
            }
        }
        else if ((inputFileName.substr(stringLength-4, 4) == ".pgm"))
        {
            loadedStatusFirst = GM.load(inputFileName);
            if(loadedStatusFirst == 1)
            {
                cout << "The file could not be loaded. Please check the name and verify the location of the image.\n";
            }
        }
    }

    cout << "\t\t\t\tPlease what operation you would like to perform\n\n";
    cout << "\n\n1.  Load Another Image\t\t\t\t2.  Save Image\t\t\t\t3.  Combine Image Side by Side\n4.  Combine Image Top to Bottom\t\t\t5.  Flip Image\t\t\t\t6.  Create Negative" <<
    "\n7.  Alter Brightness\t\t\t\t8.  Apply Mean Filter\t\t\t9.  Apply Median Filter\n10. Quantize\t\t\t\t\t11. Calculate Derivative\t\t12. Crop\n" <<
    "13. Filter\t\t\t\t\t14. Transform\t\t\t\t15. Resize\n16. Rotate\t\t\t\t\t17.Fade-In\t\t\t\t0. Quit\n";
    cin >> choice;
    do
    {
        switch(choice)
        {
            case 1:
                {
                    int loadSlot, loadStatusLoad;
                    string loadImageName;
                    cout << "1. Load Image in the 1st Slot\t\t\t2. Load Image in the 2nd Slot\n";
                    cin >> loadSlot;
                    cout << "Please enter the name of the file you want to load.\n";
                    cin >> loadImageName;
                    int stringLength = loadImageName.size();
                    if ((loadImageName.substr(stringLength-4, 4) != ".pgm"))
                    {
                        loadImageName += ".pgm";
                    }
                    if (loadSlot == 1)
                    {
                        loadStatusLoad = GM.load(loadImageName);
                        if(loadStatusLoad == 1)
                        {
                            cout << "The file could not be loaded. Please check the name and verify the location of the image.\n";
                        }
                        else
                        {
                            cout << "Image Loaded Successfully!\n";
                        }
                    }
                    else if (loadSlot == 2)
                    {
                        loadStatusLoad = GM2.load(loadImageName);
                        if(loadStatusLoad == 1)
                        {
                            cout << "The file could not be loaded. Please check the name and verify the location of the image.\n";
                        }
                        else
                        {
                            cout << "Image Loaded Successfully!\n";
                        }
                    }
                    else
                    {
                        cout << "Invalid Load Slot chosen :(\n";
                    }

                    break;
                }

            case 2:
                {
                    int stringLen, SaveChoice;
                    string saveFileName;

                    if( (GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        cout << "Please enter the name of the file you want to save.\n";
                        cin >> saveFileName;
                        stringLen = saveFileName.size();
                        if ((saveFileName.substr(stringLen-4, 4) != ".pgm"))
                        {
                            saveFileName += ".pgm";
                            GM.Save(saveFileName);
                            cout << "Image was saved Successfully!\n";
                        }
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Save first Image\t\t\t2. Save second Image";
                        cin >> SaveChoice;
                        if (SaveChoice == 1)
                        {
                            cout << "Please enter the name of the file you want to save.\n";
                            cin >> saveFileName;
                            stringLen = saveFileName.size();
                            if ((saveFileName.substr(stringLen-4, 4) != ".pgm"))
                            {
                                saveFileName += ".pgm";
                                GM.Save(saveFileName);
                                cout << "Image was saved Successfully!\n";
                            }
                        }
                        else if (SaveChoice == 2)
                        {
                            cout << "Please enter the name of the file you want to save.\n";
                            cin >> saveFileName;
                            stringLen = saveFileName.size();
                            if ((saveFileName.substr(stringLen-4, 4) != ".pgm"))
                            {
                                saveFileName += ".pgm";
                                GM2.Save(saveFileName);
                                cout << "Image was saved Successfully!\n";
                            }
                        }
                        else
                        {
                            cout << "Wrong Option Chosen. No file was saved.\n";
                        }
                    }
                    break;
                }
            case 3:
                {
                    int fillVal, loadedCombineSecond, secondStrLength;
                    string secondCombineName;
                    cout << "Please enter the color you want to place in the empty space.\n";
                    cin >> fillVal;
                    if(fillVal <0)
                    {
                        cout << "Fill value was below the minimum number allowed, so It has been set to 0\n";
                        fillVal = 0;
                    }
                    else if (fillVal > 255)
                    {
                        cout << "Fill value was above the maximum number allowed, so It has been set to 255\n";
                        fillVal = 255;
                    }
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        cout << "Enter the name of the second file.\n";
                        cin >> secondCombineName;
                        secondStrLength = secondCombineName.size();
                        if ((secondCombineName.substr(secondStrLength-4, 4) != ".pgm"))
                        {
                            secondCombineName += ".pgm";
                            loadedCombineSecond = GM2.load(secondCombineName);
                            if(loadedCombineSecond == 1)
                            {
                                cout << "The file could not be loaded. Please check the name and verify the location of the image.\n";
                            }
                            else
                            {
                                GM.combineSideBySide(GM2, fillVal);
                                GM.Save("Combine Side By Side.pgm");
                                cout << "Image saved successfully!\n";
                            }
                        }
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        GM.combineSideBySide(GM2, fillVal);
                        GM.Save("Combine Side By Side.pgm");
                        cout << "Image saved successfully!\n";
                    }
                    break;
                }
            case 4:
                {
                    int fillVal, loadedCombineSecond, secondStrLength;
                    string secondCombineName;
                    cout << "Please enter the color you want to place in the empty space.\n";
                    cin >> fillVal;
                    if(fillVal <0)
                    {
                        cout << "Fill value was below the minimum number allowed, so It has been set to 0\n";
                        fillVal = 0;
                    }
                    else if (fillVal > 255)
                    {
                        cout << "Fill value was above the maximum number allowed, so It has been set to 255\n";
                        fillVal = 255;
                    }
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        cout << "Enter the name of the second file.\n";
                        cin >> secondCombineName;
                        secondStrLength = secondCombineName.size();
                        if ((secondCombineName.substr(secondStrLength-4, 4) != ".pgm"))
                        {
                            secondCombineName += ".pgm";
                            loadedCombineSecond = GM2.load(secondCombineName);
                            if(loadedCombineSecond == 1)
                            {
                                cout << "The file could not be loaded. Please check the name and verify the location of the image.\n";
                            }
                            else
                            {
                                GM.combineTopToBottom(GM2, fillVal);
                                GM.Save("Combine Top to Bottom.pgm");
                                cout << "Image saved successfully!\n";
                            }
                        }
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        GM.combineTopToBottom(GM2, fillVal);
                        GM.Save("Combine  Top to Bottom.pgm");
                        cout << "Image saved successfully!\n";
                    }
                    break;
                }
            case 5:
                {
                    int stringLength, flipChoice, flipFileChoice;
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        cout << "1. Horizontal Flip\t\t\t2. Vertical Flip\n";
                        cin >> flipChoice;
                        if (flipChoice == 1)
                        {
                            GM.Flip(GM3, flipChoice);
                            GM3.Save("First Horizontally Flipped Image.pgm");
                            cout << "Image was saved successfully!\n";
                        }
                        else if (flipChoice == 2)
                        {
                            GM.Flip(GM3, flipChoice);
                            GM3.Save("First Vertically Flipped Image.pgm");
                            cout << "Image was saved successfully!\n";
                        }
                        else
                        {
                            cout << "Wrong Flip choice\n";
                        }

                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Flip First Image\t\t\t2. Flip Second Image\n";
                        cin >> flipFileChoice;
                        if (flipFileChoice == 1)
                        {
                            cout << "1. Horizontal Flip\t\t\t2. Vertical Flip\n";
                            cin >> flipChoice;
                            if (flipChoice == 1)
                            {
                                GM.Flip(GM3, flipChoice);
                                GM3.Save("First Horizontally Flipped Image.pgm");
                                cout << "Image was saved successfully!\n";
                            }
                            else if (flipChoice == 2)
                            {
                                GM.Flip(GM3, flipChoice);
                                GM3.Save("First Vertically Flipped Image.pgm");
                                cout << "Image was saved successfully!\n";
                            }
                            else
                            {
                                cout << "Wrong Flip choice\n";
                            }

                        }
                        else if (flipFileChoice == 2)
                        {
                            cout << "1. Horizontal Flip\t\t\t2. Vertical Flip\n";
                            cin >> flipChoice;
                            if (flipChoice == 1)
                            {
                                GM2.Flip(GM3, flipChoice);
                                GM3.Save("Second Horizontally Flipped Image.pgm");
                                cout << "Image was saved successfully!\n";
                            }
                            else if (flipChoice == 2)
                            {
                                GM2.Flip(GM3, flipChoice);
                                GM3.Save("Second Vertically Flipped Image.pgm");
                                cout << "Image was saved successfully!\n";
                            }
                            else
                            {
                                cout << "Wrong Flip choice\n";
                            }
                        }
                        else
                        {
                            cout << "Wrong file choice.\n";
                        }

                    }
                    break;
                }
            case 6:
                {
                    int negChoice;
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.Negative(GM3);
                        GM3.Save("First Negative Image.pgm");
                        cout << "Negative Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Negative of Image 1\t\t\t2. Negative of Image 2\n";
                        cin >> negChoice;
                        if (negChoice == 1)
                        {
                            GM.Negative(GM3);
                            GM3.Save("First Negative Image.pgm");
                        }
                        else if (negChoice == 2)
                        {
                            GM2.Negative(GM3);
                            GM3.Save("Second Negative Image.pgm");
                        }
                    }
                    break;
                }
            case 7:
                {
                    int brightChoice, brightnessValue;
                    cout << "Input the Brightness value. Enter a Negative number to decrease brightness.\n";
                    cin >> brightnessValue;
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.changeBrightness(GM3, brightnessValue);
                        GM3.Save("First Brightness.pgm");
                        cout << "Image with changed brightness created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Negative of Image 1\t\t\t2. Negative of Image 2\n";
                        cin >> brightChoice;
                        if (brightChoice == 1)
                        {
                            GM.changeBrightness(GM3, brightnessValue);
                            GM3.Save("First Negative Image.pgm");
                            cout << "Image with changed brightness created successfully!";
                        }
                        else if (brightChoice == 2)
                        {
                            GM2.changeBrightness(GM3, brightnessValue);
                            GM3.Save("Second Negative Image.pgm");
                            cout << "Image with changed brightness created successfully!";
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 8:
                {
                    int meanChoice, filterSize;
                    do
                    {
                        cout << "Enter the Filter Size, e.g 3, 5, 7";
                        cin >> filterSize;
                    }
                    while(filterSize <3 || filterSize%2 == 0);

                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.meanFilter(GM3, filterSize);
                        GM3.Save("First Mean Image.pgm");
                        cout << "Mean Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Mean of Image 1\t\t\t2. Mean of Image 2\n";
                        cin >> meanChoice;
                        if (meanChoice == 1)
                        {
                            GM.meanFilter(GM3, filterSize);
                            GM3.Save("First Mean Image.pgm");
                            cout << "Mean Image created successfully!";
                        }
                        else if (meanChoice == 2)
                        {
                            GM2.meanFilter(GM3, filterSize);
                            GM3.Save("Second Mean Image.pgm");
                            cout << "Mean Image created successfully!";
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 9:
                {
                    int medianChoice;
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.medianFilter(GM3);
                        GM3.Save("First Median Image.pgm");
                        cout << "Median Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Median of Image 1\t\t\t2. Median of Image 2\n";
                        cin >> medianChoice;
                        if (medianChoice == 1)
                        {
                            GM.medianFilter(GM3);
                            GM3.Save("First Mean Image.pgm");
                        }
                        else if (medianChoice == 2)
                        {
                            GM2.medianFilter(GM3);
                            GM3.Save("Second Mean Image.pgm");
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 10:
                {
                    int quantizeChoice, levels;
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        do
                        {
                            cout << "Input the levels of Quantization\n";
                            cin >> levels;
                        }
                        while(levels <= 0 || levels > 255);
                        GM.Quantize(GM3, levels);
                        GM3.Save("First Quantizated Image.pgm");
                        cout << "Mean Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Quantization of Image 1\t\t\t2. Quantization of Image 2\n";
                        cin >> quantizeChoice;
                        if (quantizeChoice == 1)
                        {
                            do
                            {
                                cout << "Input the levels of Quantization\n";
                                cin >> levels;
                            }
                            while(levels <= 0 || levels > 255);

                            GM.Quantize(GM3, levels);
                            GM3.Save("First Quantizated Image.pgm");
                        }
                        else if (quantizeChoice == 2)
                        {
                            do
                            {
                                cout << "Input the levels of Quantization\n";
                                cin >> levels;
                            }
                            while(levels <= 0 || levels > 255);
                            GM.Quantize(GM3, levels);
                            GM3.Save("Second Quantizated Image.pgm");
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 11:
                {
                    double Mask1[3][3]={ {-1,0,1}, {-1,0,1} ,{-1,0,1} };
                    double Mask2[3][3]={ {-1,0,-1}, {0,0,0} , {1,1,1} };
                    int derivativeChoice;
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.DerivativeImage(GM3, Mask1, Mask2);
                        GM3.Save("First Derivative Image.pgm");
                        cout << "Derivative Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Derivative of Image 1\t\t\t2. Derivative of Image 2\n";
                        cin >> derivativeChoice;
                        if (derivativeChoice == 1)
                        {
                            GM.DerivativeImage(GM3, Mask1, Mask2);
                            GM3.Save("First Derivative Image.pgm");
                            cout << "Derivative Image created successfully!";
                        }
                        else if (derivativeChoice == 2)
                        {
                            GM2.DerivativeImage(GM3, Mask1, Mask2);
                            GM3.Save("Second Derivative Image.pgm");
                            cout << "Derivative Image created successfully!";
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 12:
                {
                    int cropChoice, Top, Bottom, Left, Right, ResizeFlag;
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        do
                        {
                            cout << "Enter the value of Top Row\n";
                            cin >> Top;
                        }
                        while(Top < 0 || Top > GM.getRows());

                        do
                        {
                            cout << "Enter the value of Bottom Row\n";
                            cin >> Bottom;
                        }
                        while(Bottom < 0 || Bottom >= GM.getRows() || Bottom <= Top);

                        do
                        {
                            cout << "Enter the value of Left Column\n";
                            cin >> Left;
                        }
                        while(Left < 0 || Left > GM.getCols());

                        do
                        {
                            cout << "Enter the value of Right Column\n";
                            cin >> Right;
                        }
                        while(Right < 0 || Right >= GM.getCols() || Right <= Left);
                        do
                        {
                            cout << "1. Resize Image to the original\t\t\t2. Don't Resize\n";
                            cin >> ResizeFlag;
                        }
                        while(ResizeFlag != 1 && ResizeFlag != 2);


                        GM.Crop(GM3, Top, Bottom, Left, Right, ResizeFlag);
                        GM3.Save("First Cropped Image.pgm");
                        cout << "Cropped Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Crop Image 1\t\t\t2. Crop Image 2\n";
                        cin >> cropChoice;
                        if (cropChoice == 1)
                        {
                            do
                            {
                                cout << "Enter the value of Top Row\n";
                                cin >> Top;
                            }
                            while(Top < 0 || Top > GM.getRows());

                            do
                            {
                                cout << "Enter the value of Bottom Row\n";
                                cin >> Bottom;
                            }
                            while(Bottom < 0 || Bottom >= GM.getRows() || Bottom <= Top);

                            do
                            {
                                cout << "Enter the value of Left Column\n";
                                cin >> Left;
                            }
                            while(Left < 0 || Left > GM.getCols());

                            do
                            {
                                cout << "Enter the value of Right Column\n";
                                cin >> Right;
                            }
                            while(Right < 0 || Right >= GM.getCols() || Right <= Left);

                            GM.Crop(GM3, Top, Bottom, Left, Right, ResizeFlag);
                            GM3.Save("First Cropped Image.pgm");
                            cout << "Cropped Image created successfully!";
                        }
                        else if (cropChoice == 2)
                        {
                            do
                            {
                                cout << "Enter the value of Top Row\n";
                                cin >> Top;
                            }
                            while(Top < 0 || Top > GM2.getRows());

                            do
                            {
                                cout << "Enter the value of Bottom Row\n";
                                cin >> Bottom;
                            }
                            while(Bottom < 0 || Bottom >= GM2.getRows() || Bottom <= Top);

                            do
                            {
                                cout << "Enter the value of Left Column\n";
                                cin >> Left;
                            }
                            while(Left < 0 || Left > GM2.getCols());

                            do
                            {
                                cout << "Enter the value of Right Column\n";
                                cin >> Right;
                            }
                            while(Right < 0 || Right >= GM2.getCols() || Right <= Left);

                            GM2.Crop(GM3, Top, Bottom, Left, Right, ResizeFlag);
                            GM3.Save("Second Cropped Image.pgm");
                            cout << "Cropped Image created successfully!";
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 13:
                {
                    int filterChoice;
                    double Mask[3][3]={0};
                    cout << "Please enter the Mask [3]x[3]";
                    for(int i = 0; i< 3; i++)
                    {
                        for(int j = 0; j< 3; j++)
                        {
                            cin >> Mask[i][j];
                        }
                    }
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.Filter(GM3, Mask);
                        GM3.Save("First Filtered Image.pgm");
                        cout << "Filtered Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Filter of Image 1\t\t\t2. Filter of Image 2\n";
                        cin >> filterChoice;
                        if (filterChoice == 1)
                        {
                            GM.Filter(GM3, Mask);
                            GM3.Save("First Filtered Image.pgm");
                            cout << "Filtered Image created successfully!";
                        }
                        else if (filterChoice == 2)
                        {
                            GM2.Filter(GM3, Mask);
                            GM3.Save("Second Filtered Image.pgm");
                            cout << "Filtered Image created successfully!";
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 14:
                {
                    int transformChoice;

                    double Mask[3][3]={0};
                    cout << "Please enter the Mask [3]x[3]";
                    for(int i = 0; i< 3; i++)
                    {
                        for(int j = 0; j< 3; j++)
                        {
                            cin >> Mask[i][j];
                        }
                    }
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.Transform(GM3, Mask);
                        GM3.Save("First Transformed Image.pgm");
                        cout << "Transformed Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Transform Image 1\t\t\t2. Transform of Image 2\n";
                        cin >> transformChoice;
                        if (transformChoice == 1)
                        {
                            GM.Filter(GM3, Mask);
                            GM3.Save("First Transformed Image.pgm");
                            cout << "Transformed Image created successfully!";
                        }
                        else if (transformChoice == 2)
                        {
                            GM2.Transform(GM3, Mask);
                            GM3.Save("Second Transformed Image.pgm");
                            cout << "Transformed Image created successfully!";
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 15:
                {
                    int resizeChoice;
                    double ratioOfImage;
                    do
                    {
                        cout << "Please input the ratio of the image you want to create, e.g \"Ratio = 2 --> Double the size\"\n";
                        cin >> ratioOfImage;
                    }
                    while(ratioOfImage <0);

                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.Resize(GM3, ratioOfImage);
                        GM3.Save("First Resized Image.pgm");
                        cout << "Resized Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Resize Image 1\t\t\t2. Resize Image 2\n";
                        cin >> resizeChoice;
                        if (resizeChoice == 1)
                        {
                            GM.Resize(GM3, ratioOfImage);
                            GM3.Save("First Resized Image.pgm");
                            cout << "Resized Image created successfully!";
                        }
                        else if (resizeChoice == 2)
                        {
                            GM2.Resize(GM3, ratioOfImage);
                            GM3.Save("Second Resized Image.pgm");
                            cout << "Resized Image created successfully!";
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 16:
                {
                    int rotateChoice, xAxis, yAxis;
                    double angle;
                    cout << "Please input the angle of rotation. Enter negative value for Anti-Clockwise rotation\n";
                    cin >> angle;
                    cout << "Please enter the X-Axis of Rotation rotation.\n";
                    cin >> xAxis;
                    cout << "Please enter the Y-Axis of Rotation rotation.\n";
                    cin >> yAxis;
                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        GM.Rotate(GM3, angle, xAxis, yAxis);
                        GM3.Save("First Rotated Image.pgm");
                        cout << "Rotated Image created successfully!";
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        cout << "1. Rotate Image 1\t\t\t2. Rotate Image 2\n";
                        cin >> rotateChoice;
                        if (rotateChoice == 1)
                        {
                            GM.Rotate(GM3, angle, xAxis, yAxis);
                            GM3.Save("First Rotated Image.pgm");
                            cout << "Rotated Image created successfully!";
                        }
                        else if (rotateChoice == 2)
                        {
                            GM2.Rotate(GM3, angle, xAxis, yAxis);
                            GM3.Save("Second Rotated Image.pgm");
                            cout << "Rotated Image created successfully!";
                        }
                        else
                        {
                            cout << "Wrong image chosen\n";
                        }
                    }

                    break;
                }
            case 17:
                {
                    int seconds, frameRate, loadStatusFade;
                    string fadeInName;
                    do
                    {
                        cout << "Enter number of seconds\n";
                        cin >> seconds;
                        cout << "Enter Frame Rate\n";
                        cin >> frameRate;
                    }
                    while(seconds <= 0 || frameRate <=0);


                    if((GM.publicLoaded() == true) && (GM2.publicLoaded() == false))
                    {
                        cout << "Please enter the name of the second file.\n";
                        cin >> fadeInName;
                        int stringLengthFade = fadeInName.size();
                        if ((fadeInName.substr(stringLengthFade-4, 4) != ".pgm"))
                        {
                            fadeInName += ".pgm";
                            loadStatusFade = GM.load(fadeInName);
                            if(loadStatusFade == 1)
                            {
                                cout << "The file could not be loaded. Please check the name and verify the location of the image.\n";
                            }
                            else
                            {
                                GM.FadeIn(GM2, frameRate, seconds, "Fade-In");
                                cout<<"Files saved successfully\n";
                            }
                        }
                        if ((fadeInName.substr(stringLengthFade-4, 4) == ".pgm"))
                        {
                            loadStatusFade = GM2.load(fadeInName);
                            if(loadStatusFade == 1)
                            {
                                cout << "The file could not be loaded. Please check the name and verify the location of the image.\n";
                            }
                            else
                            {
                                GM.FadeIn(GM2, frameRate, seconds, "Fade-In");
                                cout<<"Files saved successfully\n";
                            }
                        }
                    }
                    else if ((GM.publicLoaded() == true) && (GM2.publicLoaded() == true))
                    {
                        GM.FadeIn(GM2, frameRate, seconds, "Fade-In");
                        cout<<"Files saved successfully\n";
                    }

                    break;
                }
        }
        cout << "\n\n1.  Load Another Image\t\t\t\t2.  Save Image\t\t\t\t3.  Combine Image Side by Side\n4.  Combine Image Top to Bottom\t\t\t5.  Flip Image\t\t\t\t6.  Create Negative" <<
        "\n7.  Alter Brightness\t\t\t\t8.  Apply Mean Filter\t\t\t9.  Apply Median Filter\n10. Quantize\t\t\t\t\t11. Calculate Derivative\t\t12. Crop\n" <<
        "13. Filter\t\t\t\t\t14. Transform\t\t\t\t15. Resize\n16. Rotate\t\t\t\t\t17.Fade-In\t\t\t\t0. Quit\n";
        cin >> choice;
    }
    while(choice != 0);
    return 0;
}
