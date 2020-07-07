#include "bks.h"

// TODO: Implement all empty methods (marked with "...")

template <class T>
BKS<T>::BKS(const BKS<T> &copy)
{
    // ...
}

template <class T>
BKS<T> &BKS<T>::operator=(const BKS<T> &copy)
{
    if (&copy != this)
    { // check for self-assignment
        // ...
    }
    return *this;
}

template <class T>
BKS<T>::BKS(const vector<pair<int, int>> &weight_benefit_list)
{
    // ...
}

template <class T>
bool BKS<T>::set(const vector<Item>& items)
{
    // ...

    return validateItems();
}

template <class T> bool BKS<T>::validateItems() const
{
    // ...
    return false;
}

template <class T>
vector<int> BKS<T>::selectedItems(int capacity)
{
    compute_for_capacity(capacity);
    return current_selection_;
}

template <class T>
void BKS<T>::selectedItems(int capacity, vector<int> &result)
{
    compute_for_capacity(capacity);
    result.clear();
    for (auto i : current_selection_)
    {
        result.push_back(i);
    }
}

template <class T>
int BKS<T>::getMaximalBenefit(int capacity)
{
    compute_for_capacity(capacity);
    return maximal_benefit_;
}

template <class T>
void BKS<T>::compute_for_capacity(int capacity)
{
    // ...
}

template <class T>
int BKS<T>::compute_knapsack(int k, int w)
{
    assert(k >= 0);
    assert(k <= (int)itemlist_.size());
    assert(w >= 0);
    assert(w <= current_capacity_);

    if(k == 0)
    {
        return 0;
    }
    if(w == 0)
    {
        return 0;
    }

    // ...
}

template <class T>
void BKS<T>::select_items(int k, int w)
{
    assert(k >= 0);
    assert(k <= (int)itemlist_.size());
    assert(w >= 0);
    assert(w <= current_capacity_);

    if(k < 1)
    {
        return;
    }

    // ...
}

template <class T>
void print_bks(BKS<T> &bks, int capacity)
{
    cout << "item list: ";
    for (auto x : bks.get())
    {
        cout << x.identifier << ":" << x.weight << "," << x.benefit << "; ";
    }
    cout << endl;
    if (bks.validateItems())
    {
        cout << "validation of items successful" << endl;
    }
    else
    {
        cout << "validation of items NOT successful" << endl;
    }

    cout << "max. benefit " << bks.getMaximalBenefit(capacity) << " for capacity of " << capacity << endl;
    cout << "selected items: ";
    for (auto i : bks.selectedItems(capacity))
    {
        cout << bks.get()[i].identifier << " ";
    }
    cout << endl << endl;
}

int main(int argc, char **argv)
{
    vector<pair<int, int>> testdata{{2, 3}, {3, 4}, {4, 5}, {5, 6}};
    BKS<int> example1{testdata};
    print_bks(example1, 5);
    // max. benefit 7 for capacity of 5
    // selected items: 1 2

    BKS<int> example2;
    example2.set({{1, 23, 92}, {2, 31, 57}, {3, 29, 49}, {4, 44, 68}, {5, 53, 60}, {6, 38, 43}, {7, 63, 67}, {8, 85, 84}, {9, 89, 87}, {10, 82, 72}});
    print_bks(example2, 165);
    // max. benefit 309 for capacity of 165
    // selected items: 1 2 3 4 6

    BKS<string> example3{{{"a", 23, 92}, {"b", 31, 57}, {"c", 29, 49}, {"d", 44, 68}, {"e", 53, 60}, {"f", 38, 43}, {"g", 63, 67}, {"h", 85, 84}, {"i", 89, 87}, {"j", 82, 72}}};
    print_bks(example3, 165);
    // max. benefit 309 for capacity of 165
    // selected items: a b c d f

    return 0;
}
