#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

template <class T>
class BKS final
{
public:
    struct Item
    {
        T identifier;
        int weight;
        int benefit;
    };

    BKS() {}
    BKS(const BKS<T> &copy);
    BKS(const vector<Item> &items) : itemlist_{items} {}
    BKS(const vector<pair<int, int>> &weight_benefit_list);
    BKS<T> &operator=(const BKS<T> &copy);

    int size() const { return itemlist_.size(); }
    Item operator[](int i) const { return itemlist_[i]; }

    bool set(const vector<Item> &items);
    const vector<Item> &get() { return itemlist_; }
    bool validateItems() const;

    vector<int> selectedItems(int capacity);
    void selectedItems(int capacity, vector<int> &result);
    int getMaximalBenefit(int capacity);

private:
    vector<Item> itemlist_;
    vector<int> current_selection_;
    int current_capacity_ {0};
    int maximal_benefit_ {0};

    int compute_knapsack(int k, int w);
    void select_items(int k, int w);
    void compute_for_capacity(int capacity);
};
