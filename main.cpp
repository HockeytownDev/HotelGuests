#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>

using namespace std;

void swapReserveItems(int reservations[][5], int indexA, int indexB);
void readTable(std::istream& in, int row[], int numCols);
void sortReservations(int reservations[][5], int numItems);
void writeTable(std::ostream& out, int row[], int numCols);
void writeGuest(std::ostream& out, std::string guest[], int numCols);
void readGuest(std::istream& in, std::string guest[], int numCols);
void loadGuests(std::istream& in, std::string guests[][5], int numGuests);
void swapGuestItems(std::string guest[][5], int indexA, int indexB);
std::string getGuestPhone();
void sortGuests(std::string guests[][5], int numItems);
void saveGuests(std::string guests[][5], int numGuests);
void saveTables(int table[][9], int numRows);
bool guestExists(std::string guests[][5], int numGuests, std::string Gname);
void addGuest(std::string guests[][5], int numGuests, std::string row[], int numCols);
void readReservation(std::istream& in, int reservation[], int numCols);
std::string genNewGuestID(std::string guests[][5], int numGuests);
std::string GuestNameByGID(std::string guests[][5],int numGuests,int GID);
int getGuestIndex(std::string guests[][5], int numGuests, std::string Gname);
void writeReservation(std::ostream& out, int reservation[], int numCols);
void printAvailibility(std::ostream& out, int table[][9], int numRows, int party);
bool insertReservedTable(int table[][9], int numRows, int time, int party, int RID);
bool releaseTable(int table[][9], int numRows, int RID);
void loadTables(std::istream& in, int table[][9], int numRows);
int genNewResID(int reservation[][5],int numRIDs);
void loadReservations(std::istream& in, int reservations[][5], int numRIDs);
void saveReservations(int reservations[][5], int numRIDs);
void deleteRes(int reservation[][5],int numRIDs, int index);
void addReservation(int reservations[][5], int numRIDs, int row[], int numCols);

std::string getGuestExpiry();
std::string getGuestCC();
void printAllRID(std::ostream& out, int reservations[][5], int numRIDs, std::string guests[][5], int numGuests);
void cancelReservation(int reservations[][5], int numRIDs, std::string guests[][5], int numGuests, int tables[][9], int numRows);
int getTime(int numRows);
int getNumParty();
int menu();
void NewReservation(int reservation[][5], int numRIDs, std::string guests[][5], int numGuests, int tables[][9], int numRows);
bool reservationCycle();


int main()
{
    bool loop = true;
    while(loop)
    {
        loop = reservationCycle();
    }

    return 0;
}


void swapReserveItems(int reservations[][5], int indexA, int indexB)
{
    ///swaps 2 items in reservation by row index
    for(int j = 0; j<5; j++)
    {
        int temp = reservations[indexA][j];
        reservations[indexA][j]=reservations[indexB][j];
        reservations[indexB][j]=temp;
    }
}

void readTable(std::istream& in, int row[], int numCols)
{
    ///reads a single table row from a line in a stream
    for (int i = 0; i < numCols; ++i)
    {
        int value;
        in >> value;
        row[i] = value;
    }
}

void sortReservations(int reservations[][5], int numItems)
{
    ///sorts the reservations by reservation number(the first element in each row of the array)
    std::qsort(reservations, numItems, sizeof(*reservations),
    [](const void *arg1, const void *arg2)->int
    {
       int const *a = static_cast<int const*>(arg1);
       int const *b = static_cast<int const*>(arg2);
       return a[0] < b[0];
    });
}

void writeTable(std::ostream& out, int row[], int numCols)
{
    /// writes a single table to a stream
    for(int i = 0; i< numCols; i++)
    {
        out<<row[i]<<" ";
    }
    out<<std::endl;

}

void writeGuest(std::ostream& out, std::string guest[], int numCols)
{
    /// writes a single guest to a stream
    for (int i = 0; i < numCols; ++i)
    {
        out << guest[i];
        if (i < numCols - 1)
        {
            out << " ";
        }
    }
    out << endl;
}

void readGuest(std::istream& in, std::string guest[], int numCols)
{
    ///reads a single guest from a line in a stream
    for(int i=0; i<numCols; i++)
    {
        in>>guest[i];
    }
}

void loadGuests(std::istream& in, std::string guests[][5], int numGuests)
{
    /// loads guests from a stream
    for(int i=0; i<numGuests; i++)
    {
        readGuest(in, guests[i], 5);
    }
}

void swapGuestItems(std::string guest[][5], int indexA, int indexB)
{
    ///swaps 2 items in guest by row index
    std::string aux[5];
    for (int i = 0; i < 5; ++i)
    {
        aux[i] =guest[indexA][i];
        guest[indexA][i] = guest[indexB][i];
        guest[indexB][i] = aux[i];
    }
}

std::string getGuestPhone()
{
    ///prompts the user for a guests phone number
    while(true)
    {
        std::string phone="";
        std::cout<<"Enter phone(no punctuation): ";
        std::cin>>phone;
        if(!std::cin || phone.length()!=10 || !(phone.find_first_not_of( "0123456789" ) == string::npos))  /// checks phone number is a series of digits of the right length
        {
            std::cout<<"\r:::Invalid Entry!!!:::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');

            return phone;
        }

    }
    return "";
}




void sortGuests(std::string guests[][5], int numItems)
{
    ///sorts the guests by guest number
    for(int i=1; i<numItems; i++)
    {
        for(int j=0; j<numItems-i; j++)
        {
            if(atoi(guests[j][0].c_str())>atoi(guests[j+1][0].c_str()))
            {
                swapGuestItems(guests,j,j+1);
            }
        }
    }

}


void saveGuests(std::string guests[][5], int numGuests)
{
    /// saves guest array to a file
    std::fstream outFile;
    outFile.open("guests.txt", std::ios::out);
    outFile<<numGuests<<std::endl;
    for(int i=0; i<numGuests; i++)
    {
        writeGuest(outFile, guests[i], 5);
    }
    outFile.close();
}

void saveTables(int table[][9], int numRows)
{
    ///saves tables in table array to a file
    std::fstream outFile;
    outFile.open("tables.txt", std::ios::out);
    outFile<<numRows<<std::endl;
    for(int i=0; i<numRows; i++)
    {
        writeTable(outFile, table[i],9);
    }
    outFile.close();
}




bool guestExists(std::string guests[][5], int numGuests, std::string Gname)
{
    ///checks to see if a guest exists by their last name
    for( int i=0; i<numGuests; i++)
    {
        if (guests[i][1]==Gname)
        {
            return true;
        }
    }
    return false;

}

void addGuest(std::string guests[][5], int numGuests, std::string row[], int numCols)
{
    ///adds a guest held in row[] to a temp array and saves the new array to file
    std::string temp[numGuests+1][5];
    for(int i = 0; i<numGuests; i++)
    {
        for(int j = 0; j<numCols; j++)
        {
            temp[i][j]=guests[i][j];
        }
    }
    for(int i = 0; i<numCols; i++)
    {
        temp[numGuests][i]=row[i];
    }
    saveGuests(temp, numGuests+1);

}

void readReservation(std::istream& in, int reservation[], int numCols)
{
    ///reads a single reservation from a stream and loads it into the row reservation[]
    for(int i=0; i<numCols; i++)
    {
        in>>reservation[i];
    }
}

std::string genNewGuestID(std::string guests[][5], int numGuests)
{
    ///finds either an empty ID to return or returns a new one
    bool found = false;
    int largest=0;
    int ID=0;
    sortGuests(guests,numGuests);
    ///looks for a gap in the sorted IDs
    for(int i=0; i<numGuests-1; i++)
    {
        if(atoi(guests[i][0].c_str()) < atoi(guests[i+1][0].c_str())-1)
        {
            ID = atoi(guests[i][0].c_str())+1;
            found = true;
            break;
        }
        if(atoi(guests[i][0].c_str())>largest)
        {
            largest = atoi(guests[i][0].c_str());
        }
    }
    ///if a gap was not found, set ID to largest + 1
    if(!found)
    {
        std::stringstream ss;
        ss<<largest+2;
        return ss.str();
    }
    std::stringstream ss;
    ss<<ID;
    return ss.str();
}

std::string GuestNameByGID(std::string guests[][5],int numGuests,int GID)
{
    /// returns a guests name given the GID
    for(int i=0; i<numGuests; i++)
    {
        if(atoi(guests[i][0].c_str())==GID)
        {
            return guests[i][1];
        }
    }
    return "Unknown";
}

int getGuestIndex(std::string guests[][5], int numGuests, std::string Gname)
{
    /// returns the index of a guest given guests name
    for(int i=0; i<numGuests; i++)
    {
        if(guests[i][1]==Gname)
        {
            return i;
        }
    }

    return 0;
}

void writeReservation(std::ostream& out, int reservation[], int numCols)
{
    /// writes a single reservation to a stream
    for(int i = 0; i< numCols; i++)
    {
        out<<reservation[i]<<" ";
    }
    out<<std::endl;
}

void printAvailibility(std::ostream& out, int table[][9], int numRows, int party)
{
    /// prints the availability of tables based on party size
    for(int i=0; i<numRows; i++)
    {
        out<<"\t"<<i<<"\t"<<table[i][0];
        if(party>2&&party<=4)
        {
            if(table[i][4]==0)
            {
                out<<"\t"<<4<<std::endl;
                continue;
            }
            else
            {
                out<<"\tNA"<<std::endl;
            }
        }
        else if(party > 4 && party <= 8)
        {
            if(table[i][8]==0)
            {
                out<<"\t"<<8<<std::endl;
                continue;
            }
            else
            {
                out<<"\tNA"<<std::endl;
            }
        }
        else
        {
            int counter = 0;
            for(int j=1; j<9; j++)
            {
                if(j==4 || j==8)
                {
                    continue;
                }
                else if(table[i][j]==0)
                {
                    out<<"\t"<<j;
                    counter ++;
                }
            }
            if(counter == 0)
            {
                out<<"\tNA";
            }
            out<<std::endl;
        }
    }

}


bool insertReservedTable(int table[][9], int numRows, int time, int party, int RID)
{
    /// adds a reservation to the table array
    for(int i=0; i<numRows; i++)
    {
        if(table[i][0]==time)
        {
            if(party>2 && party <= 4)
            {
                if(table[i][4]==0)
                {
                    table[i][4]=RID;
                    std::cout<<"\n::::Reservation Completed::::"<<std::endl;
                    saveTables(table,numRows);
                    return true;
                }

            }
            if(party>4 && party <=8)
            {
                if(table[i][8]==0)
                {
                    table[i][8]=RID;
                    std::cout<<"\n::::Reservation Completed::::"<<std::endl;
                    saveTables(table,numRows);
                    return true;
                }
            }
            else
            {
                for(int j = 1; j<9; j++)
                {
                    if(j == 4 || j == 8)
                    {
                        continue;
                    }
                    else if(table[i][j]==0)
                    {
                        table[i][j]=RID;
                        std::cout<<"\n::::Reservation Completed::::"<<std::endl;
                        saveTables(table,numRows);
                        return true;
                    }
                }
            }
        }
    }

    std::cout<<"\n:::Table already Taken!!!:::"<<std::endl;
    return false;


}


bool releaseTable(int table[][9], int numRows, int RID)
{
    ///releases a table from the table array
    for(int i=0; i< numRows; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(table[i][j]==RID)
            {
                table[i][j]=0;
                std::cout<<"\n::::Reservation Removed::::"<<std::endl;
                saveTables(table,numRows);
                return true;
            }
        }
    }
    std::cout<<"\n::::Reservation Not Found::::"<<std::endl;
    return false;

}


void loadTables(std::istream& in, int table[][9], int numRows)
{
    ///loads tables from a stream
    for(int i=0; i<numRows; i++)
    {
        readTable(in, table[i], 9);
    }
}



int genNewResID(int reservation[][5],int numRIDs)
{
    ///finds either an empty ID to return or returns a new one
    bool found = false;
    int largest=0;
    int ID=0;
    sortReservations(reservation,numRIDs);
    ///looks for a gap in the sorted IDs
    for(int i=0; i<numRIDs-1; i++)
    {
        if(reservation[i][0] < reservation[i+1][0]-1)
        {
            ID = reservation[i][0]+1;
            found = true;
            break;
        }
        if(reservation[i][0]>largest)
        {
            largest = reservation[i][0];
        }
    }
    ///if a gap was not found, set ID to largest + 2 (plus one would set it equal to the last item in the list. The last item is never evaluated for largest because of the nature of the for loop used)
    if(!found)
    {
        return largest+2;
    }
    return ID;
}



void loadReservations(std::istream& in, int reservations[][5], int numRIDs)
{
    /// loads reservations to an array from a stream
    for(int i=0; i<numRIDs; i++)
    {
        readReservation(in, reservations[i], 5);
    }

}


void saveReservations(int reservations[][5], int numRIDs)
{
    /// saves the array reservations to a file
    std::fstream outFile;
    outFile.open("reserved.txt");
    outFile<<numRIDs<<std::endl;
    for(int i=0; i<numRIDs; i++)
    {
        writeReservation(outFile, reservations[i], 5);
    }
    outFile.close();
}


void deleteRes(int reservation[][5],int numRIDs, int index)
{
    /// swaps a reservation with the end of the reservation array, then saves the array numRIDs-1 to file
    swapReserveItems(reservation,index,numRIDs-1);
    saveReservations(reservation,numRIDs-1);

}


void addReservation(int reservations[][5], int numRIDs, int row[], int numCols)
{
    /// adds a reservation to the file
    int temp[numRIDs + 1][5];
    for(int i=0; i<numRIDs; i++)
    {
        for( int j=0; j<numCols; j++)
        {
            temp[i][j]=reservations[i][j];
        }
    }
    for(int i=0; i<numCols; i++)
    {
        temp[numRIDs][i]=row[i];
    }
    saveReservations(temp,numRIDs+1);
}

///**********************************************************************************
///**************ALL BELOW THIS LINE STAYS IN MAIN***********************************
///**********************************************************************************


std::string getGuestExpiry()
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    while(true)
    {
        int MM=0;
        int YYYY=0;
        std::cout<<"Enter phone(MM YYYY): ";
        std::cin>>MM;
        std::cin>>YYYY;

        ///validates the expiration data against the current date
        if(!std::cin || ((MM<1||MM>12)||(YYYY < (timePtr->tm_year+1900) || YYYY > 9999 ))||(YYYY==(timePtr->tm_year + 1900) && MM < (timePtr->tm_mon + 1)))
        {
            std::cout<<"\r:::Invalid Date!!!:::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            ///converts the year to 2 digits
            YYYY= YYYY%100;
            std::stringstream ss;
            ss<<MM<<'/'<<YYYY;
            return ss.str();
        }

    }

    return "";
}

std::string getGuestCC()
{
    ///prompts the user for a guests credit card number
    while(true)
    {
        std::string CC="";
        std::cout<<"Enter CC#(no punctuation): ";
        std::cin>>CC;
        if(!std::cin || CC.length()!=16 || !(CC.find_first_not_of( "0123456789" ) == string::npos))
        {
            std::cout<<"\r:::Invalid Entry!!!:::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');

            return CC;
        }

    }

    return "";
}


void printAllRID(std::ostream& out, int reservations[][5], int numRIDs, std::string guests[][5], int numGuests)
{
    /// Prints all of the reservations to a stream
    out<<"\n\n:::::::::::::::::::::Reservations::::::::::::::::::::::::::\n"<<std::endl;
    out<<"\n\tIndex\tTime\t"<<std::left<<std::setw(20)<<"Name"<<"Party"<<std::endl;
    for(int i=0; i<numRIDs; i++)
    {
        std::cout<<"\t"<<i+1<<"\t"<<reservations[i][3]<<"\t"<<std::left<<std::setw(20)<<GuestNameByGID(guests,numGuests,reservations[i][1])<<"\t"<<reservations[i][2]<<std::endl;
    }

}

void cancelReservation(int reservations[][5], int numRIDs, std::string guests[][5], int numGuests, int tables[][9], int numRows)
{
    /// removes reservation from the different arrays
    printAllRID(std::cout, reservations, numRIDs, guests,numGuests);
    int selection =0;
    while(true)
    {
        std::cout<<"Select reservation to cancel(0-"<<numRIDs-1<<"): ";
        std::cin>>selection;
        if(!cin || (selection > (numRIDs) || selection< 1))
        {
            std::cout<<":::::Invalid Selection:::::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            break;
        }
    }
    int RID = reservations[selection-1][0];
    deleteRes(reservations, numRIDs, selection-1);
    releaseTable(tables, numRows, RID);

}

int getTime(int numRows)
{
    /// prompts user for time of a reservation
    int time=0;
    while(true)
    {
        std::cout<<"Select a time (0-"<<numRows-1<<")";
        std::cin>>time;
        if(!std::cin || (time<0 || time> (numRows-1)))
        {
            std::cout<<"\r:::::Invalid Selection:::::";
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            time = (time * 100)+1700;
            return time;
        }
    }
    return time;
}

int getNumParty()
{
    /// prompts the user for the number in a guests party
    while(true)
    {
        int party=0;
        std::cout<<"Enter size of party: ";
        std::cin>>party;
        if(!std::cin || party > 8 || party < 1)
        {
            std::cout<<"\r:::Invalid Entry!!!:::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            return party;
        }

    }
    return 0;
}

int menu()
{
    ///displays the menu and returns a users selection
    int selection=0;
    while(true)
    {
        std::cout<<"\n\n:::::::::::::::::::Main Menu::::::::::::::::::::\n"<<std::endl;
        std::cout<<"\t1:\tNew Reservation\n\t2:\tShow Reservations\n\t3:\tCancel Reservation\n\t4:\tExit"<<std::endl;
        std::cout<<"\nEnter Selection: ";
        std::cin>>selection;
        if(!std::cin || (selection < 1 || selection > 4))
        {
            std::cout<<"\r:::::Invalid Selection:::::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            continue;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            return selection;
        }
    }
}

void NewReservation(int reservation[][5], int numRIDs, std::string guests[][5], int numGuests, int tables[][9], int numRows)
{
    ///allows a user to enter a new reservation
    std::string Gname="";
    int GID=0;
    std::cout<<"Enter the guests last name: ";
    std::cin>>Gname;
    std::cin.clear();
    std::cin.ignore(256,'\n');
    if(!guestExists(guests,numGuests,Gname))
    {
        std::string Grow[5];
        Grow[0]=genNewGuestID(guests,numGuests);
        Grow[1]=Gname;
        Grow[2]=getGuestPhone();
        Grow[3]=getGuestCC();
        Grow[4]=getGuestExpiry();
        addGuest(guests,numGuests,Grow, 5);
        GID=atoi(Grow[0].c_str());

    }
    else
    {
        std::cout<<":::Guest already Exists :):::"<<std::endl;
        GID = atoi(guests[getGuestIndex(guests,numGuests,Gname)][0].c_str());
    }
    int Rrow[5];
    Rrow[0]=genNewResID(reservation, numRIDs);
    Rrow[1]=GID;
    Rrow[2]=getNumParty();

    int time =0;
    while(true)
    {
        printAvailibility(std::cout,tables, numRows, Rrow[2]);
        time = getTime(numRows);
        if(!insertReservedTable(tables,numRows,time,Rrow[2],Rrow[0]))
        {
            std::cout<<":::Time not available:::";
        }
        else
        {
            break;
        }
    }
    Rrow[3]=time;
    Rrow[4]=0;
    addReservation(reservation,numRIDs, Rrow, 5);

}


bool reservationCycle()
{
    ///handles the menu and general function calls
    int numGuests=0;
    int numRIDs=0;
    int numRows=0;
    std::fstream inFile;
    inFile.open("reserved.txt",std::ios::in);
    inFile>>numRIDs;
    if(!inFile)
    {
        std::cout<<":::File \"reserved.txt\" missing or corrupted:::"<<std::endl;
        return false;
    }
    int reservations[numRIDs][5];
    loadReservations(inFile, reservations,numRIDs);
    inFile.close();
    inFile.open("guests.txt",std::ios::in);
    inFile>>numGuests;
    if(!inFile)
    {
        std::cout<<":::File \"guests.txt\" missing or corrupted:::"<<std::endl;
        return false;
    }
    std::string guests[numGuests][5];
    loadGuests(inFile,guests,numGuests);
    inFile.close();
    inFile.open("tables.txt", std::ios::in);
    inFile>>numRows;
    if(!inFile)
    {
        std::cout<<"\n"<<numRows<<std::endl;
        std::cout<<":::File \"tables.txt\" missing or corrupted:::"<<std::endl;
        return false;
    }
    int tables[numRows][9];
    loadTables(inFile, tables, numRows);
    inFile.close();
    int selection = menu();
    switch(selection)
    {
        case 1:
            NewReservation(reservations,numRIDs,guests,numGuests, tables, numRows);
            return true;
        case 2:
            printAllRID(std::cout, reservations,numRIDs, guests, numGuests);
            return true;
        case 3:
            cancelReservation(reservations,numRIDs, guests, numGuests, tables, numRows);
            return true;
        case 4:
            return false;
    }
    return false;
}

