#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <random>
#include <vector>


struct RX
{
    std::string FRString;
    int RXID;
};

class generator
{
    public:
    std::vector<std::string> FRStringVector;
    std::vector<int> RXIDVector;

    std::string generateFRString()
    {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,2);
        std::string FRString;

        int x = dist6(rng);

        std::uniform_int_distribution<std::mt19937::result_type> dist7(1,5);
        int y = dist7(rng);

        std::uniform_int_distribution<std::mt19937::result_type> dist8(1,5);
        int z = dist8(rng);

        FRString = "FR" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
        makesureFRStringisUnique(FRString);
        return  FRString;
    }

    int generateRXID()
    {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,48);
        int a = dist6(rng);

        makesureRXIDisUnique(a);
        return a;
    }

    void makesureFRStringisUnique(std::string &FRString)
    {
        bool isUnique = false;
        if(FRStringVector.empty())
        {
            FRStringVector.push_back(FRString);
            isUnique = true;
        }

        while (!isUnique)
        {
            for (auto element : FRStringVector)
            {
                if (element == FRString)
                {
                    FRString = generateFRString();
                }
            }
            isUnique = true;
        }
    }

    void makesureRXIDisUnique(int RXID)
    {
        bool isUnique = false;
        if(RXIDVector.empty())
        {
            RXIDVector.push_back(RXID);
        }

        while (!isUnique)
        {
            for (auto element : RXIDVector)
            {
                if (element == RXID)
                {
                    RXID = generateRXID();
                }
            }
            isUnique = true;
        }
    }
};

bool operator== (RX lhs, RX rhs)
{
    return (lhs.FRString == rhs.FRString) && (lhs.RXID == rhs.RXID);
}

class Cell
{
    public:
        RX *ArrayOfRX; // = new RX[size]
        int RXCount;
        generator RXGenerator;
        Cell()
        {
            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist1(1,4);
            RXCount = dist1(rng);
            ArrayOfRX = new RX[RXCount];
            std::cout << "The Amount of RX in cell: " << RXCount << std::endl;
            FillCellWithRandomUniqueRX();
            displayAllRXinCell();
        }

        void FillCellWithRandomUniqueRX()
        {
            for (int x = 0 ; x < RXCount ; x++)
            {
                (ArrayOfRX + x)->FRString= RXGenerator.generateFRString();
                (ArrayOfRX + x)->RXID = RXGenerator.generateRXID();
            }
        }

        void displayAllRXinCell()
        {
            std::cout << "The RXs in cell are: " << std::endl;
            for (int x = 0 ; x < RXCount ; x++)
            {
                std::cout << (ArrayOfRX + x)->FRString << " ";
                std::cout << (ArrayOfRX + x)->RXID << std::endl;
            }
        }

        ~Cell()
        {
            delete [] ArrayOfRX;
        }
};

void compareAndSwapRX( RX& higher, RX& lower, bool& swaphappened)
{
    //std::string R1Temp = std::to_string(Cell1.RX1.RXID) + Cell1.RX1.FRString;
    char* R1 = new char[higher.FRString.size()+1];
    strcpy (R1, higher.FRString.c_str());

    char* R2 = new char[lower.FRString.size()+1];
    strcpy (R2, lower.FRString.c_str());

    for(int i = 0; R1[i] != '\0'; i++)
    {
        //std::cout << "Currently Comparing: " << R1[i] << " with " << R2[i] << std::endl;
        if ( R1[i] == R2[i] )
        {
            //do nothing
        }
        else if(R1[i] > R2[i])
        {
            RX temp = higher;
            higher = lower;
            lower = temp;
            swaphappened = true;
            return;
        }
        else if(R1[i] < R2[i])
        {
            return;
        }
        else
        {
            //do nothing
        }
    }
    // if FRSTRING is still the same

    if(higher.RXID > lower.RXID)
    {
        RX temp = higher;
        higher = lower;
        lower = temp;
        swaphappened = true;
        return;
    }

}

void sortRXPriority(std::vector<RX>& AllRXinCell, int& index)
{
    bool swaphappened = true;
    while (swaphappened)
    {
        swaphappened = false;
            if(index != AllRXinCell.size())
                compareAndSwapRX(AllRXinCell[index], AllRXinCell[index+1], swaphappened);
                index++;
                if(index+1 != AllRXinCell.size())
                    sortRXPriority(AllRXinCell, index);
            if(swaphappened == true)
                index =0;
    }
}


int main()
{

    //this activity assumes that we have a way to know how many RX are in the cell
    Cell Cell1;
    std::vector<RX> AllRXinCell;
    std::cout << std::endl;
    if (Cell1.RXCount == 1)
    {
        std::cout << "There is only 1 RX no need to sort" << std::endl;
        return 0;
    }

    for( int x = 0; x < Cell1.RXCount ; x++)
    {
        AllRXinCell.push_back(*(Cell1.ArrayOfRX + x));
    }
    int index =0;
    sortRXPriority(AllRXinCell, index);
    // for(std::vector<int>::size_type x = 0; x != AllRXinCell.size(); x++)
    // {
    //     if(x == 0)
    //     {
    //         compareAndSwapRX(AllRXinCell[x], AllRXinCell[x+1]);
    //     }
    //     if(Cell1.RXCount > 2 && x == 1)
    //     {
    //         compareAndSwapRX(AllRXinCell[x], AllRXinCell[x+1]);
    //         compareAndSwapRX(AllRXinCell[x-1], AllRXinCell[x]);
    //     }
    //     if(Cell1.RXCount > 2 && x == 2)
    //     {
    //         compareAndSwapRX(AllRXinCell[x-1], AllRXinCell[x]);
    //         compareAndSwapRX(AllRXinCell[x-2], AllRXinCell[x-1]);
    //         //compareAndSwapRX(AllRXinCell[x-2], AllRXinCell[x-1]);
    //     }
    //     // if(Cell1.RXCount > 2 && x == 3)
    //     // {
    //     //     compareAndSwapRX(AllRXinCell[x-1], AllRXinCell[x]);
    //     //     compareAndSwapRX(AllRXinCell[x-2], AllRXinCell[x-1]);
    //     //     compareAndSwapRX(AllRXinCell[x-3], AllRXinCell[x-2]);
    //     // }
    // }

    for(std::vector<int>::size_type x = 0; x != AllRXinCell.size(); x++)
    {
        std::cout << AllRXinCell[x].FRString << " ";
        std::cout << AllRXinCell[x].RXID << std::endl;
    }
    return 0;
}