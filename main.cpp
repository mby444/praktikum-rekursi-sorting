#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct Player
{
    string name;
    float points = 0;
};

/* Begin Merge Sort algorithm */
void merge(Player arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Player *L = new Player[n1];
    Player *R = new Player[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].points >= R[j].points)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSortDesc(Player arr[], int left, int right)
{
    if (right <= left)
        return;

    int mid = left + (right - left) / 2;

    mergeSortDesc(arr, left, mid);
    mergeSortDesc(arr, mid + 1, right);

    merge(arr, left, mid, right);
}
/* End Merge Sort algorithm */

void showHeader()
{
    cout << endl;
    cout << "========================================" << endl;
    cout << "             TURNAMEN CATUR             " << endl;
    cout << "========================================" << endl;
    cout << "   Selamat datang di ajang bergengsi!   " << endl;
    cout << "   Siapakah yang akan menjadi juara?    " << endl;
    cout << "----------------------------------------" << endl
         << endl;
}

string removePadding(string str)
{

    while (!str.empty() && str.front() == ' ')
        str.erase(str.begin());

    while (!str.empty() && str.back() == ' ')
        str.pop_back();

    return str;
}

bool isStringEmpty(string str)
{
    str = removePadding(str);
    return (str.length() == 0);
}

bool checkNumeric(string str)
{
    if (isStringEmpty(str))
        return false;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return false;
        }
    }

    return true;
}

Player createPlayer(string name)
{
    Player player = {name, 0};
    return player;
}

string inputString(string label)
{
    string input;

    while (true)
    {
        cout << label;
        getline(cin, input);

        if (isStringEmpty(input))
        {
            cout << "Input tidak boleh kosong!" << endl;
            continue;
        }

        break;
    }

    return input;
}

int inputInteger(string label)
{
    string inputStr;
    int input;

    while (true)
    {
        cout << label;
        getline(cin, inputStr);

        if (isStringEmpty(inputStr))
        {
            cout << "Input tidak boleh kosong!" << endl;
            continue;
        }

        if (!checkNumeric(inputStr))
        {
            cout << "Input harus berupa bilangan positif!" << endl;
            continue;
        }

        break;
    }

    return stoi(inputStr);
}

void inputTotals(int *totalPlayers, int *totalRounds)
{
    while (true)
    {
        *totalPlayers = inputInteger("Masukkan jumlah pemain: ");

        if (*totalPlayers <= 0 || *totalPlayers % 2 != 0)
        {
            cout << "Jumlah pemain harus lebih dari nol dan harus berjumlah genap!" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        *totalRounds = inputInteger("Masukkan jumlah ronde: ");

        if (*totalRounds <= 0)
        {
            cout << "Jumlah ronde harus lebih dari nol!" << endl;
            continue;
        }
        break;
    }

    cout << endl;
}

void inputPlayers(Player players[], int n)
{
    string name;
    cout << "Masukkan nama-nama pemain:" << endl;

    for (int i = 0; i < n; i++)
    {
        name = inputString("Nama pemain " + to_string(i + 1) + ": ");
        players[i] = createPlayer(name);
    }

    cout << endl;
}

void sortPlayers(Player players[], int n)
{
    int low = 0, high = n - 1;
    mergeSortDesc(players, low, high);
}

void playGame(Player *whitePlayerPtr, Player *blackPlayerPtr)
{
    int result = rand() % 3;

    switch (result)
    {
    case 0:
        whitePlayerPtr->points += 1;
        cout << whitePlayerPtr->name << " menang vs " << blackPlayerPtr->name << endl;
        break;
    case 1:
        blackPlayerPtr->points += 1;
        cout << whitePlayerPtr->name << " kalah vs " << blackPlayerPtr->name << endl;
        break;
    case 2:
        whitePlayerPtr->points += 0.5;
        blackPlayerPtr->points += 0.5;
        cout << whitePlayerPtr->name << " seri vs " << blackPlayerPtr->name << endl;
        break;
    default:
        cout << "Hasil pertandingan " << whitePlayerPtr->name << " vs " << blackPlayerPtr->name << " tidak sah" << endl;
        break;
    }
}

void simulateMatches(Player players[], int n)
{
    for (int i = 0; i < n; i += 2)
    {
        Player *whitePlayerPtr = &players[i];
        Player *blackPlayerPtr = &players[i + 1];
        playGame(whitePlayerPtr, blackPlayerPtr);
    }
}

void runRound(Player players[], int n, int currentRound, int totalRounds)
{
    if (currentRound > totalRounds)
        return;
    cout << "=== Ronde " << currentRound << " ===" << endl;
    simulateMatches(players, n);
    sortPlayers(players, n);
    cout << endl;
    runRound(players, n, currentRound + 1, totalRounds);
}

void showFinalResults(Player players[], int n)
{
    cout << "=== Hasil Akhir ===" << endl;
    cout << "======================================" << endl;
    cout << "| Peringkat | Nama            | Poin |" << endl;
    cout << "--------------------------------------" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "| "
             << setw(9) << left << i + 1 << " | "
             << setw(15) << left << players[i].name << " | "
             << setw(4) << right << players[i].points << " |" << endl;
    }

    cout << "======================================" << endl;
}

int main()
{
    srand(time(0));
    showHeader();

    int totalPlayers, totalRounds, currentRound = 1;

    inputTotals(&totalPlayers, &totalRounds);

    Player players[totalPlayers];

    inputPlayers(players, totalPlayers);
    runRound(players, totalPlayers, currentRound, totalRounds);
    showFinalResults(players, totalPlayers);

    return 0;
}